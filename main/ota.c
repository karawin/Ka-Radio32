/*
 * ESPRSSIF MIT License
 *
 * Copyright (c) 2015 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
/*
 * Copyright 2017 jp Cocatrix (http://www.karawin.fr)
*/
#define TAG "OTA"
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include <string.h>
#include <sys/socket.h>
#include "esp_system.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "interface.h"
#include "webclient.h"
#include "app_main.h"
#include "websocket.h"

#define BUFFSIZE 1024

const char strupd[]  = {\
"GET /%s.bin HTTP/1.1\r\nHost: karadio.karawin.fr:80\r\n\r\n"};

/*an ota data write buffer ready to write to the flash*/
static char ota_write_data[BUFFSIZE + 1] = { 0 };
/*an packet receive buffer*/
static char text[BUFFSIZE + 1] = { 0 };
/* an image total length*/
static int binary_file_length = 0;
static bool taskState = false;

static unsigned int  reclen = 0;
	

/******************************************************************************
 * FunctionName : wsUpgrade
 * Description  : send the OTA feedback to websockets
 * Parameters   : number to send as string
 * Returns      : none
*******************************************************************************/
void wsUpgrade(const char* str,int count,int total)
{
	char answer[50];
	if (strlen(str)!= 0)
		sprintf(answer,"{\"upgrade\":\"%s\"}",str);
	else		
	{
		int value = count*100/total;
		memset(answer,0,50);
		if (value >= 100)
			sprintf(answer,"{\"upgrade\":\"Done. Refresh the page.\"}");
		else
		if (value == 0)
			sprintf(answer,"{\"upgrade\":\"Starting.\"}");
		else
			sprintf(answer,"{\"upgrade\":\"%d / %d\"}",value,100);
	}
	websocketbroadcast(answer, strlen(answer));
}
	
	
	
/*read buffer by byte still delim ,return read bytes counts*/
static int read_until(char *buffer, char delim, int len)
{
//  /*TODO: delim check,buffer check,further: do an buffer length limited*/
    int i = 0;
    while (buffer[i] != delim && i < len) {
        ++i;
    }
    return i + 1;
}

/* resolve a packet from http socket
 * return true if packet including \r\n\r\n that means http packet header finished,start to receive packet body
 * otherwise return false
 * */
static bool read_past_http_header(char text[], int total_len, esp_ota_handle_t update_handle)
{
    /* i means current position */
    int i = 0, i_read_len = 0;
    while (text[i] != 0 && i < total_len) {
        i_read_len = read_until(&text[i], '\n', total_len);
        // if we resolve \r\n line,we think packet header is finished
        if (i_read_len == 2) {
            int i_write_len = total_len - (i + 2);
            memset(ota_write_data, 0, BUFFSIZE);
            /*copy first http packet body to write buffer*/
            memcpy(ota_write_data, &(text[i + 2]), i_write_len);

            esp_err_t err = esp_ota_write( update_handle, (const void *)ota_write_data, i_write_len);
            if (err != ESP_OK) {
                ESP_LOGE(TAG, "Error: esp_ota_write failed! err=0x%x", err);
                return false;
            } else {
                ESP_LOGI(TAG, "esp_ota_write header OK");
                binary_file_length += i_write_len;
            }
            return true;
        }
        i += i_read_len;
    }
    return false;
}


/******************************************************************************
 * FunctionName : ota task
 * Description  : 
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
static void ota_task(void *pvParameter)
{
	// the get request
	char http_request[80] = {0};
	struct hostent *serv ;
	int sockfd;
	struct sockaddr_in dest;	
	char* name = (char*)pvParameter; // name of the bin file to load
    unsigned int cnt =0;
	clientDisconnect("OTA");

	//esp32: found a partition to flash
    esp_err_t err;
    /* update handle : set by esp_ota_begin(), must be freed via esp_ota_end() */
    esp_ota_handle_t update_handle = 0 ;
    const esp_partition_t *update_partition = NULL;

    ESP_LOGI(TAG, "Starting update ...");
	kprintf("Starting update ...\n");
	wsUpgrade( "",0,100);
    const esp_partition_t *configured = esp_ota_get_boot_partition();
    const esp_partition_t *running = esp_ota_get_running_partition();

    if (configured != running) {
        ESP_LOGW(TAG, "Configured OTA boot partition at offset 0x%08x, but running from offset 0x%08x",
                 configured->address, running->address);
        ESP_LOGW(TAG, "(This can happen if either the OTA boot data or preferred boot image become corrupted somehow.)");
    }
    ESP_LOGI(TAG, "Running partition type %d subtype %d (offset 0x%08x)",
             running->type, running->subtype, running->address);
	
		
	// prepare connection to the server
	serv =(struct hostent*)gethostbyname("karadio.karawin.fr");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd >= 0) {ESP_LOGI(TAG,"WebClient Socket created"); }
	else {ESP_LOGE(TAG,"socket create errno: %d",errno);wsUpgrade("Failed: socket errno", 0,100); goto exit;}
	bzero(&dest, sizeof(dest));	
    dest.sin_family = AF_INET;
    dest.sin_port   = htons(80);
    dest.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)(serv-> h_addr_list[0]))); // remote server ip
	ESP_LOGI(TAG,"distant ip: %x   ADDR:%s\n", dest.sin_addr.s_addr, inet_ntoa(*(struct in_addr*)(serv-> h_addr_list[0])));

	
	/*---Connect to server---*/
	if (connect(sockfd, (struct sockaddr*)&dest, sizeof(dest)) >= 0)
		{ESP_LOGI(TAG,"Connected to server");}
	else
	{
		ESP_LOGE(TAG, "Connect to server failed! errno=%d", errno);
		close(sockfd);
		wsUpgrade("Connect to server failed!" , 0,100);
		goto exit;
	}
	
	
	 int res = -1;
    /*send GET request to http server*/
	sprintf(http_request,strupd,name);
	ESP_LOGV(TAG,"request sent: %s",http_request);
    res = send(sockfd, http_request, strlen(http_request), 0);
    if (res == -1) {
        ESP_LOGE(TAG, "Send GET request to server failed");
		wsUpgrade("Send GET request to server failed" , 0,100);
        goto exit;
    } else {
        ESP_LOGI(TAG, "Send GET request to server succeeded");
    }

	update_partition = esp_ota_get_next_update_partition(NULL);
    ESP_LOGI(TAG, "Writing to partition subtype %d at offset 0x%x",
             update_partition->subtype, update_partition->address);
    assert(update_partition != NULL);
    err = esp_ota_begin(update_partition, OTA_SIZE_UNKNOWN, &update_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_ota_begin failed, error=%d", err);
		wsUpgrade("esp_ota_begin failed" , 0,100);
        goto exit;
    }
    ESP_LOGI(TAG, "esp_ota_begin succeeded");

    bool resp_body_start = false, flag = true;
    /*deal with all receive packet*/
    while (flag) {
		vTaskDelay(1);
        memset(text, 0, BUFFSIZE);
        memset(ota_write_data, 0, BUFFSIZE);
        int buff_len = recv(sockfd, text, BUFFSIZE, 0);
        if (buff_len < 0) { /*receive error*/
            ESP_LOGE(TAG, "Error: receive data error! errno=%d", errno);
			kprintf("Error: receive data error! errno=%d\n", errno);
			wsUpgrade("Error: receive data error!" , 0,100);
            goto exit;
        } else if (buff_len > 0 && !resp_body_start) 
		{ /*deal with response header*/
			/*the header*/
			char header[BUFFSIZE + 1] = { 0 };
			strncat(header,text,buff_len);
            resp_body_start = read_past_http_header(text, buff_len, update_handle);
			if (resp_body_start)
			{
				char* str = NULL;
				str=strstr(header,"Content-Length:");
				if (str!=NULL) reclen = atoi(str+15);				
				ESP_LOGI(TAG, "must receive:%d bytes",reclen);
				kprintf("must receive:%d bytes\n",reclen);
			}
			
			
        } else if (buff_len > 0 && resp_body_start) { /*deal with response body*/
            memcpy(ota_write_data, text, buff_len);
            err = esp_ota_write( update_handle, (const void *)ota_write_data, buff_len);
            if (err != ESP_OK) {
                ESP_LOGE(TAG, "Error: esp_ota_write failed! err=0x%x", err);
				kprintf("Error: esp_ota_write failed! err=0x%x\n", err);
				wsUpgrade("Error: esp_ota_write failed!" , 0,100);
                goto exit;
            }
			vTaskDelay(1);			
            binary_file_length += buff_len;
//            ESP_LOGI(TAG, "Have written image length %d  of  %d", binary_file_length,reclen);
			cnt = (cnt+1) & 0x1F;
			if (cnt ==0){
				kprintf("Written  %d  of  %d\n", binary_file_length,reclen);
				wsUpgrade( "",binary_file_length,reclen);
			}
			if (binary_file_length >= reclen)
			{
				flag = false; // all received, exit
				kprintf("Have written image length %d  of  %d\n", binary_file_length,reclen);
				wsUpgrade("", binary_file_length,reclen);				
				ESP_LOGI(TAG, "Connection closed, all packets received");
				kprintf("\nConnection closed, all packets received\n");
				close(sockfd);
			}
        } else if (buff_len == 0) {  /*packet over*/
            flag = false;
            ESP_LOGI(TAG, "Connection closed, all packets not received");
			kprintf("\nConnection closed, all packets not received\n");
            close(sockfd);
        } else {
            ESP_LOGE(TAG, "Unexpected recv result");
        }

		TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
		TIMERG0.wdt_feed=1;
		TIMERG0.wdt_wprotect=0;
	}
	kprintf("\n");
    ESP_LOGI(TAG, "Total Write binary data length : %d", binary_file_length);
	kprintf("Total Write binary data length : %d\n", binary_file_length);

    if (esp_ota_end(update_handle) != ESP_OK) {
        ESP_LOGE(TAG, "esp_ota_end failed!");
		kprintf("esp_ota_end failed!\n");
		wsUpgrade("esp_ota_end failed!" , 0,100);
        goto exit;
    }
    err = esp_ota_set_boot_partition(update_partition);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_ota_set_boot_partition failed! err=0x%x", err);
		kprintf("esp_ota_set_boot_partition failed!\n");
		wsUpgrade("esp_ota_set_boot_partition failed!" , 0,100);
        goto exit;
    }
    ESP_LOGI(TAG, "Prepare to restart system!");
	kprintf("Update firmware succeded. Restarting\n");
	vTaskDelay(10);
    esp_restart();	
	
	exit:
	taskState = false;
	close(sockfd);
	(void)vTaskDelete( NULL ); 	
}

/******************************************************************************
 * FunctionName : update_firmware
 * Description  : config remote server param and init bin info
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void update_firmware(char* fname)
{
	if (!taskState)
	{
		taskState = true;
		xTaskHandle pxCreatedTask;
		xTaskCreatePinnedToCore(ota_task, "ota_task", 8192, fname, PRIO_OTA, &pxCreatedTask,CPU_OTA);
		ESP_LOGI(TAG, "ota_task: %x",(unsigned int)pxCreatedTask);
	} else
	{
		ESP_LOGI(TAG, "ota_task: already running. Ignore");
		wsUpgrade("Update already running. Ignored." , 0,100);
	}

}
