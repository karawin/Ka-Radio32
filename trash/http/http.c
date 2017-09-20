#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "errno.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

#include "url_parser.h"
#include "http.h"


#define TAG "http_client"

/* function picks the first URL with .mp3 extension and replces the "original" URL.
   It is not failsave against bad-formatted records or records without mp3-Urls. */
//Aug.16, 2017: m3u support by Frantz
//modified the "http.c" module to detect the "m3u" extension, get the page and extract the URL for the mp3-stream. 
//It works with some of "m3u" links.
url_t *m3urequest(url_t *url, int sock)
{
	 char *request;
	 char *p;
	 char *x;
	 url_t *url1;

	    if(asprintf(&request, "%s%s%s%s%s", "GET ", url->path, " HTTP/1.0\r\nHost: ", url->host, "\r\n\r\n") < 0)
	    {
	        return 0;
	    }

	    ESP_LOGI(TAG, "requesting %s", request);

	    if (write(sock, request, strlen(request)) < 0) {
	        ESP_LOGE(TAG, "... x-socket send failed");
	        close(sock);
	        return 0;
	    }

	    free(request);
	    ESP_LOGI(TAG, "... x-socket send success");

	    /* Read HTTP response */
	    char recv_buf[512];
	    bzero(recv_buf, sizeof(recv_buf));
	    ssize_t recved;

	    /* intercept on_headers_complete() */
	     recved = read(sock, recv_buf, sizeof(recv_buf)-1);
	     ESP_LOGI(TAG, "fs...%d %s",recved,recv_buf);
	     // search for 1st http: text in answer, this is taken as new URL
	     p=strstr(recv_buf,"http:");
	     if (p)
	     {
	    	 x=p;
	    	 while(*x > 20) x++;
	         if(x) *x=0;
	    	 url1 = url_create(p);
	    	 ESP_LOGI(TAG, "new URL...%s %s",url1->host, url1->path);
	    	 free(url);
	    	 return url1;
	     }
	     return 0;
}
/**
 * @brief simple http_get
 * see https://github.com/nodejs/http-parser for callback usage
 */
int http_client_get(char *uri, http_parser_settings *callbacks, void *user_data)
{
	int sock;

    const struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res;
    struct in_addr *addr;
    char port_str[6]; // stack allocated
    int again = 1;

    url_t *url = url_create(uri);

    while(again)  // use while for detecting possible m3u records and reopen with new URL
    {

        snprintf(port_str, 6, "%d", url->port);
        int err = getaddrinfo(url->host, port_str, &hints, &res);
        if(err != ESP_OK || res == NULL)
        {
          ESP_LOGE(TAG, "DNS lookup failed err=%d res=%p", err, res);
          free(url);
          return err;
        }

        // print resolved IP
        addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
        ESP_LOGI(TAG, "DNS lookup succeeded. IP=%s", inet_ntoa(*addr));

        // allocate socket
        sock = socket(res->ai_family, res->ai_socktype, 0);
        if(sock < 0)
        {
           ESP_LOGE(TAG, "... Failed to allocate socket.");
           freeaddrinfo(res);
           return ESP_FAIL;
        }
        ESP_LOGI(TAG, "... allocated socket");


         // connect, retrying a few times
        char retries = 0;
        while(connect(sock, res->ai_addr, res->ai_addrlen) != 0)
        {
          retries++;
          ESP_LOGE(TAG, "... socket connect attempt %d failed, errno=%d", retries, errno);

          if(retries > 5) {
            ESP_LOGE(TAG, "giving up");
            close(sock);
            freeaddrinfo(res);
            return ESP_FAIL;
          }

        }

        ESP_LOGI(TAG, "... connected");
        freeaddrinfo(res);
        // check if m3u list
        if(strstr(url->path,".m3u"))
        {
    	  if ((url=m3urequest(url,sock))==0) // memory of old url should be freed
    	  {
    	    ESP_LOGE(TAG, "... m3u not supported !");
    	    close(sock);
    	    freeaddrinfo(res);
    	    return ESP_FAIL;
    	   }
    	  continue;
        }
    	again=0;

      } ;

    // write http request

    char *request;
    if(asprintf(&request, "%s%s%s%s%s", "GET ", url->path, " HTTP/1.0\r\nHost: ", url->host, "\r\n\r\n") < 0)
    {
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "requesting %s", request);

    if (write(sock, request, strlen(request)) < 0) {
        ESP_LOGE(TAG, "... socket send failed");
        close(sock);
        return ESP_FAIL;
    }

    free(request);
    ESP_LOGI(TAG, "... socket send success");


    /* Read HTTP response */
    char recv_buf[64];  //fsj
    bzero(recv_buf, sizeof(recv_buf));
    ssize_t recved;

    /* intercept on_headers_complete() */

    /* parse response */
    http_parser parser;
    http_parser_init(&parser, HTTP_RESPONSE);
    parser.data = user_data;

    esp_err_t nparsed = 0;
    do {
        recved = read(sock, recv_buf, sizeof(recv_buf)-1);

        // using http parser causes stack overflow somtimes - disable for now
        // ESP_LOGI(TAG, "... received len=%d =%s", recved, recv_buf);//fsj
        nparsed = http_parser_execute(&parser, callbacks, recv_buf, recved);

        // invoke on_body cb directly
        // nparsed = callbacks->on_body(&parser, recv_buf, recved);
    } while(recved > 0 && nparsed >= 0);

    free(url);

    ESP_LOGI(TAG, "... done reading from socket. Last read return=%d errno=%d", recved, errno);
    close(sock);
    ESP_LOGI(TAG, "socket closed");

    return 0;
}

