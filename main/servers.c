/* (c)jp cocatrix May 2017
 *
 * Copyright 2017 karawin (http://www.karawin.fr)

	Main task for the web websocket and telnet servers.
*/
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h> 
#include "lwip/sockets.h"
#include "telnet.h"
#include "websocket.h"
#include "webserver.h"
#include "interface.h"
#include "app_main.h"
#include "eeprom.h"
//4400
#define stack  	5500 
#define TAG	"servers"

#define  strsTELNET  "Servers Telnet Socket fails %s errno: %d"
#define  strsWSOCK  "WebServer Socket fails %s errno: %d"


static fd_set readfds;
xSemaphoreHandle semclient = NULL ;


const char strsocket[] = {"Socket"};
const char strbind[] = {"Bind"};
const char strlisten[] = {"Listen"};

void serversTask(void* pvParams) {
	//telnet, client and websocket
	struct sockaddr_in tenetserver_addr, tenetclient_addr;
	int telnetServer_sock, telnetClient_sock;
	socklen_t telnetSin_size;
	//web
	struct sockaddr_in server_addr, client_addr;
	int server_sock;
	int  client_sock;
	socklen_t sin_size;
	
	semclient = xSemaphoreCreateCounting(4,4); 
	semfile = xSemaphoreCreateCounting(1,1); 
	
	portBASE_TYPE uxHighWaterMark;
	
	
	int max_sd;
	int activity;
	int	ret, sd;	

	int i;
//	telnetinit();
//	websocketinit();
	uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
	ESP_LOGD(TAG,"watermark: 0x%x  %d",uxHighWaterMark,uxHighWaterMark);
	while(1)
	{
/////////////////////		
// telnet socket init
/////////////////////
		bzero(&tenetserver_addr, sizeof(struct sockaddr_in));
        tenetserver_addr.sin_family = AF_INET;
        tenetserver_addr.sin_addr.s_addr = INADDR_ANY;
        tenetserver_addr.sin_port = htons(23);
		
        if (-1 == (telnetServer_sock = socket(AF_INET, SOCK_STREAM, 0))) {
			ESP_LOGE(TAG,strsTELNET,strsocket, errno);
			vTaskDelay(5);	
            break;
        }
		ESP_LOGD(TAG,"telnetServer_sock socket: %d, errno: %d", telnetServer_sock, errno);
        if (-1 == bind(telnetServer_sock, (struct sockaddr *)(&tenetserver_addr), sizeof(struct sockaddr))) {
			ESP_LOGE(TAG,strsTELNET,strbind, errno);
			close(telnetServer_sock);
			vTaskDelay(10);	
            break;
        }
        if (-1 == listen(telnetServer_sock, 5)) {
			ESP_LOGE(TAG,strsTELNET,strlisten,errno);
			close(telnetServer_sock);
			vTaskDelay(10);	
            break;
        }
        telnetSin_size = sizeof(tenetclient_addr);	
////////////////////////		
// telnet socket init end
////////////////////////


////////////////////////
// webserver socket init
////////////////////////
		bzero(&server_addr, sizeof(struct sockaddr_in));
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = INADDR_ANY;
		server_addr.sin_port = htons(80);

		if (-1 == (server_sock = socket(AF_INET, SOCK_STREAM, 0))) {
			ESP_LOGE(TAG,strsWSOCK, strsocket, errno);
			vTaskDelay(5);	
			break;
		}
		ESP_LOGD(TAG,"Webserver socket: %d, errno: %d", server_sock, errno);
		if (-1 == bind(server_sock, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr))) {
			ESP_LOGE(TAG,strsWSOCK, strbind,errno);
			close(server_sock);
			vTaskDelay(10);	
            break;
		}
		if (-1 == listen(server_sock, 5)) {
			ESP_LOGE(TAG,strsWSOCK,strlisten,errno);
			close(server_sock);
			vTaskDelay(10);	
			break;
		}
		sin_size = sizeof(client_addr);
/////////////////////////////		
// webserver socket init end
////////////////////////////
		
		while (1)  //main loop
		{
			
			//clear the socket set
			FD_ZERO(&readfds);;
			
			//add server_sock to set (webserver)
			FD_SET(server_sock, &readfds);
			max_sd = server_sock ; 
//printf("server_sock SD_set %d\n",server_sock);			
				
			//add telnetServer_sock to set (telnet)
			if (g_device->current_ap != APMODE) //inhibe telnet in AP mode
			{				
				FD_SET(telnetServer_sock, &readfds);
				max_sd = telnetServer_sock > max_sd ? telnetServer_sock : max_sd;  
			}
//printf("telnetServer_sock SD_set %d\n",telnetServer_sock);		
			//add child sockets to set (wssocket)
			for (i = 0;i<NBCLIENT;i++) 
			{
				sd = webserverclients[i].socket;
				//if valid socket descriptor then add to read list
				if(sd != -1)
				{	
					FD_SET( sd , &readfds);   
//printf("wssocket SD_set %d\n",sd);
					//highest file descriptor number, need it for the select function
					max_sd = sd > max_sd ? sd : max_sd;
				}				
			}
			
			//add child sockets to set (telnet)
			for (i = 0;i<NBCLIENTT;i++) 
			{
				sd = telnetclients[i];
				//if valid socket descriptor then add to read list
				if(sd != -1)
				{	
					FD_SET( sd , &readfds);   
//printf("SD_set %d, max_sd: %d\n",sd,max_sd);
					//highest file descriptor number, need it for the select function
					max_sd = sd > max_sd ? sd : max_sd;
				}				
			}	


		
//printf("lwip_socket_offset: %d\n",lwip_socket_offset);	
//printf("ws call select. Max sd: %d\n",max_sd);

			//wait for an activity on one of the sockets , 
			activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
//			if (activity != 0) ESP_LOGV(TAG,"Activity %d, max_fd: %d",activity,max_sd);
   
			if ((activity < 0) && (errno!=EINTR) && (errno!=0)) 
			{
				ESP_LOGE(TAG,strsTELNET,"select",errno);
				vTaskDelay(100);
				continue;
			}	
//			if (activity == 0)	{vTaskDelay(10);continue;}	
	
//If something happened on the master webserver socket , then its an incoming connection
			if (FD_ISSET(server_sock, &readfds)) 
			{	
				FD_CLR(server_sock , &readfds); 
//				ESP_LOGV(TAG,"Server web accept, socket: %d.",server_sock);				
				if ((client_sock = accept(server_sock, (struct sockaddr *) &client_addr, &sin_size)) < 0) {
						ESP_LOGE(TAG,strsWSOCK,"accept",errno);
						vTaskDelay(10);					
				} else
				{
					while (1) 
					{
//						printf ("Heap size server: %d\n",xPortGetFreeHeapSize( ));
//						printf ("Accept socket %d\n",client_sock);
						if (xSemaphoreTake(semclient,portMAX_DELAY))
						{						
							while (xTaskCreatePinnedToCore( serverclientTask,
								"serverclientTask",
								stack,
								(void *) client_sock,
								PRIO_SUBSERV, 
								NULL, CPU_SUBSERV ) != pdPASS) 
							{								
								vTaskDelay(200);
								ESP_LOGE(TAG,"Server low mem. Retrying...");
							}	
							vTaskDelay(1);							
							break; // while 1
						}
						else  // xSemaphoreTake fails
						{
							vTaskDelay(300); 
							ESP_LOGE(TAG,"Server busy. Retrying...");
						}
					}
				}					
			}
			
			
//If something happened on the master telnet socket , then its an incoming connection
			if (FD_ISSET(telnetServer_sock, &readfds)) 
			{
				FD_CLR(telnetServer_sock , &readfds); 
				ESP_LOGD(TAG,"telnetServer_sock accept. Socket: %d",telnetServer_sock);	 				
				if ((telnetClient_sock = accept(telnetServer_sock, (struct sockaddr *) &tenetclient_addr, &telnetSin_size)) < 0) 
				{
					ESP_LOGE(TAG,strsTELNET,"accept",errno);
					close(telnetClient_sock);
					vTaskDelay(50);					
				} else
				{
					if (!telnetAccept(telnetClient_sock))
					{
						ESP_LOGE(TAG,strsTELNET,"Accept1n",errno);
						close(telnetClient_sock);
						vTaskDelay(50);	
					}
				}
			} 			
						
// telnet sockets				
			for (i = 0; i < NBCLIENTT; i++) 
			{
				sd = telnetclients[i];
             
				if ((sd!=-1) &&(FD_ISSET( sd , &readfds))) 
				{
					FD_CLR(sd , &readfds);  
//					ESP_LOGV(TAG,"telnetclients .");	
					ret =telnetRead(sd);
//printf("Call telnetRead i: %d, socket: %d, ret: %d\n" ,i, sd,ret);  
					if (ret == 0) 
					{
						telnetremoveclient(sd);						
//						ESP_LOGV(TAG,strsTELNET,"Clear",errno); 
					}
				}
			} 
			
			
// websocket sockets				
			for (i = 0; i < NBCLIENT; i++) 
			{
				sd = webserverclients[i].socket;
             
				if ((sd!=-1) &&(FD_ISSET( sd , &readfds))) 
				{
					FD_CLR(sd , &readfds);  
//					ESP_LOGV(TAG,"webserverclients.");
					ret =websocketRead(sd);
//					ESP_LOGV(TAG,"Call websocketRead i: %d, socket: %d, ret: %d" ,i, sd,ret);  
					if (ret <= 0) 
					{
						websocketremoveclient(sd);						
						ESP_LOGV(TAG,"Clear i: %d, socket: %d, errno: %d\n" ,i, sd,errno); 
					}
				}
			}    				
						
		}			
					
	} 
	vTaskDelete( NULL );	// never called
}
