/* (c)jp cocatrix May 2017
 *
 * Copyright 2017 karawin (http://www.karawin.fr)

	Main task for the web websocket and telnet servers.
*/

#include "telnet.h"
#include "websocket.h"
#include "webserver.h"
#include "interface.h"
#include <stdio.h>
#include <stdarg.h>
#include <strings.h>
#include "driver/timer.h"

#define stack  2500//320


const char strsTELNET[]  = {"Servers Telnet Socket fails %s errno: %d\n"};
const char strsWEB[]  = {"Servers Web Socket fails %s errno: %d\n"};
const char strsWSOCK[]  = {"WebServer Socket fails %s errno: %d\n"};

fd_set readfds;
xSemaphoreHandle semclient = NULL ;

const char strsocket[] = {"Socket"};
const char strbind[] = {"Bind"};
const char strlisten[] = {"Listen"};

void serversTask(void* pvParams) {
	//telnet
	struct sockaddr_in tenetserver_addr, tenetclient_addr;
	int telnetServer_sock, telnetClient_sock;
	int server_sock;
	socklen_t telnetSin_size;
	//web
	struct sockaddr_in server_addr, client_addr;
	int  client_sock;
	socklen_t sin_size;
	timer_config_t config;
	config.alarm_en = 1;
    config.auto_reload = 0;
    config.counter_dir = TIMER_COUNT_UP;
    config.divider = TIMER_DIVIDER;
    config.intr_type = TIMER_INTR_LEVEL;
    config.counter_en = TIMER_PAUSE;
	
    /*Configure timer*/
    timer_init(TIMERGROUP, sleepTimer, &config);
    /*Stop timer counter*/
	timer_pause(TIMERGROUP, sleepTimer);
	timer_enable_intr(TIMERGROUP, sleepTimer);
	timer_isr_register(TIMERGROUP, sleepTimer, sleepCallback, (void*) sleepTimer, ESP_INTR_FLAG_IRAM, NULL);
	
    /*Configure timer*/
    timer_init(TIMERGROUP, wakeTimer, &config);
    /*Stop timer counter*/
	timer_pause(TIMERGROUP, wakeTimer);
	timer_enable_intr(TIMERGROUP, wakeTimer);
	timer_isr_register(TIMERGROUP, wakeTimer, wakeCallback, (void*) wakeTimer, ESP_INTR_FLAG_IRAM, NULL);	
	
	semclient = xSemaphoreCreateCounting(5,5); 
	semfile = xSemaphoreCreateCounting(5,5); 
	
//	portBASE_TYPE uxHighWaterMark;
	
	
	int max_sd;
	int activity;
	int	ret, sd;	
	
/*	
	uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
	printf(PSTR("watermark serverstask %d\n"),uxHighWaterMark);
*/	


	int i;
	telnetinit();
	websocketinit();
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
			printf (strsTELNET,strsocket, errno);
			vTaskDelay(5);	
            break;
        }
        if (-1 == bind(telnetServer_sock, (struct sockaddr *)(&tenetserver_addr), sizeof(struct sockaddr))) {
			printf (strsTELNET,strbind, errno);
			close(telnetServer_sock);
			vTaskDelay(10);	
            break;
        }
        if (-1 == listen(telnetServer_sock, 5)) {
			printf (strsTELNET,strlisten,errno);
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
			printf (strsWSOCK, strsocket, errno);
			vTaskDelay(5);	
			break;
		}
		if (-1 == bind(server_sock, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr))) {
			printf (strsWSOCK, strbind,errno);
			close(server_sock);
			vTaskDelay(10);	
            break;
		}
		if (-1 == listen(server_sock, 5)) {
			printf (strsWSOCK,strlisten,errno);
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
				

			//add telnetServer_sock to set (telnet)
			FD_SET(telnetServer_sock, &readfds);
			max_sd = telnetServer_sock > max_sd ? telnetServer_sock : max_sd;  


			//add child sockets to set (wssocket)
			for (i = 0;i<NBCLIENT;i++) 
			{
				sd = webserverclients[i].socket;
				//if valid socket descriptor then add to read list
				if(sd != -1)
				{	
					FD_SET( sd , &readfds);   
//					printf("wssocket SD_set %d\n",sd);
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
//					printf("SD_set %d, max_sd: %d\n",sd,max_sd);
					//highest file descriptor number, need it for the select function
					max_sd = sd > max_sd ? sd : max_sd;
				}				
			}	
			
//			printf("ws call select. Max sd: %d\n",max_sd);

			//wait for an activity on one of the sockets , 
			activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
//			if (activity != 0) printf ("Activity %d, max_fd: %d\n",activity,max_sd);
   
			if ((activity < 0) && (errno!=EINTR) && (errno!=0)) 
			{
				printf(strsTELNET,"select",errno);
				vTaskDelay(100);
				continue;
			}	
			if (activity == 0)	{vTaskDelay(10);continue;}	
	
//If something happened on the master webserver socket , then its an incoming connection
			if (FD_ISSET(server_sock, &readfds)) 
			{	
				FD_CLR(server_sock , &readfds); 
//printf(PSTR("Server web accept.%c"),0x0d);				
				if ((client_sock = accept(server_sock, (struct sockaddr *) &client_addr, &sin_size)) < 0) {
						printf (strsWSOCK,"accept",errno);
						vTaskDelay(10);					
				} else
				{
					while (1) 
					{
//						printf ("Heap size server: %d\n",xPortGetFreeHeapSize( ));
//						printf ("Accept socket %d\n",client_sock);
						if (xSemaphoreTake(semclient,portMAX_DELAY))
						{
//printf ("Take client_sock: %d\n",client_sock);							
							while (xTaskCreate( serverclientTask,
								"t10",
								stack,
								(void *) client_sock,
								4, 
								NULL ) != pdPASS) 
							{								
								vTaskDelay(200);
//printf(PSTR("Server low mem. Retrying...%c"),0x0d);
							}	
							vTaskDelay(4);							
//							xSemaphoreGive(semclient);	
							break; // while 1
						}
						else  // xSemaphoreTake fails
						{
							vTaskDelay(200); 
							printf(PSTR("Server busy. Retrying...%c"),0x0d);
						}
					}
				}					
			}
			
			
//If something happened on the master telnet socket , then its an incoming connection
			if (FD_ISSET(telnetServer_sock, &readfds)) 
			{
				FD_CLR(telnetServer_sock , &readfds);  				
				if ((telnetClient_sock = accept(telnetServer_sock, (struct sockaddr *) &tenetclient_addr, &telnetSin_size)) < 0) 
				{
					printf (strsTELNET,"accept",errno);
					close(telnetClient_sock);
					vTaskDelay(50);					
				} else
				{
					if (!telnetAccept(telnetClient_sock))
					{
						printf (strsTELNET,"Accept1n",errno);
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
					ret =telnetRead(sd);
					//printf("Call telnetRead i: %d, socket: %d, ret: %d\n" ,i, sd,ret);  
					if (ret == 0) 
					{
						telnetremoveclient(sd);						
//						printf(strsTELNET,"Clear",errno); 
					}
//					if (--activity ==0) break;
				}
//				vTaskDelay(1);
			} 
			
			
// websocket sockets				
			for (i = 0; i < NBCLIENT; i++) 
			{
				sd = webserverclients[i].socket;
             
				if ((sd!=-1) &&(FD_ISSET( sd , &readfds))) 
				{
					FD_CLR(sd , &readfds);  
					ret =websocketRead(sd);
//					printf("Call websocketRead i: %d, socket: %d, ret: %d\n" ,i, sd,ret);  
					if (ret <= 0) 
					{
						websocketremoveclient(sd);						
						//printf("Clear i: %d, socket: %d, errno: %d\n" ,i, sd,errno); 
					}
//					if (--activity ==0) break;
				}
			}    				
			
/*			uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
			printf(PSTR("watermark middle ssTask: %d\n"),uxHighWaterMark);
*/			
		}			
					
	} 
//	printf("telnet task abnormal exit\n");
	vTaskDelete( NULL );	// never called
}
