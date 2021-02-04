/* (c)jp cocatrix May 2016 
 *
 * Copyright 2016 karawin (http://www.karawin.fr)

	quick and dirty telnet inplementation for wifi webradio
	minimal implementaion for log and command
*/
#define TAG "TELNET"
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "lwip/opt.h"
#include "esp_system.h"
#include "lwip/sockets.h"
#include "cencode_inc.h"
#include "telnet.h"
#include "interface.h"



//const char strtMALLOC1[] = {"Telnet %s malloc fails\n"};
#define strtSOCKET	"Telnet Socket fails %s errno: %d"
const char strtWELCOME[]  ={"Karadio telnet\n> "};


int telnetclients[NBCLIENTT];
//set of socket descriptors
// reception buffer
static char brec[256];
static char iac[3];
static bool inIac = false; // if in negociation
static char *obrec;  //precedent received command
static uint16_t irec;
static uint8_t iiac;
xSemaphoreHandle sTELNET = NULL;

static uint8_t telnet_take_semaphore() {
	if(sTELNET) if(xSemaphoreTake(sTELNET, portMAX_DELAY)) return 1;
	return 0;
}

static void telnet_give_semaphore() {
	if(sTELNET) xSemaphoreGive(sTELNET);
}

///////////////////////
// init some data
void telnetinit(void)
{
	int i;
	vSemaphoreCreateBinary(sTELNET);
	
	for (i = 0;i<NBCLIENTT;i++) 
	{
		telnetclients[i] = -1;
	}
	memset(brec,0,sizeof(brec));
	irec = 0;
	iiac = 0;
	obrec = malloc(2);
}

/////////////////////////////////////////////////////////////////////
// a socket with a websocket request. Note it and answer to the client
bool telnetnewclient(int socket)
{
	int i ;
//	printf("ws newclient:%d\n",socket);
	for (i = 0;i<NBCLIENTT;i++) if (telnetclients[i] == socket) return true;
	else
	for (i = 0;i<NBCLIENTT;i++) if (telnetclients[i] == -1) 
	{
		telnetclients[i] = socket;
		return true;
	}	
	return false; // no more room
}
/////////////////////////////////////////////////////////////////////
// remove the client in the list of clients
void telnetremoveclient(int socket)
{
	int i ;
//	printf("ws removeclient:%d\n",socket);
	for (i = 0;i<NBCLIENTT;i++) 
		if (telnetclients[i] == socket) 
		{
			telnetclients[i] = -1;
//			printf("ws removeclient:%d removed\n",socket);
			close(socket);
			return;
		}
}
////////////////////////
// is socket a telnet one?
bool istelnet( int socket)
{
	int i ;
	for (i = 0;i<NBCLIENTT;i++) 
		if ((telnetclients[i]!= -1)&&(telnetclients[i] == socket)) return true;
	return false;
}


bool telnetAccept(int tsocket)
{
	if ((!istelnet(tsocket ))&&(telnetnewclient(tsocket))) 
	{
//			printf("telnet write accept\n");
			write(tsocket, strtWELCOME, strlen(strtWELCOME));  // reply to accept	
			return true;
	} else close(tsocket);
	return false;
}
void vTelnetWrite(uint32_t lenb,const char *fmt, va_list ap)
{
	char *buf = NULL;
	int i;
	
	buf = (char *)malloc(lenb+1);
	if (buf == NULL) return;
	buf[0] = 0;
	vsprintf(buf,fmt, ap);	
	// write to all clients
	telnet_take_semaphore();
	for (i = 0;i<NBCLIENTT;i++)	
		if (istelnet( telnetclients[i]))
		{
			write( telnetclients[i],  buf, strlen(buf));
		}	
	telnet_give_semaphore();		
	free (buf);
}

//broadcast a txt data to all clients
void telnetWrite(uint32_t lenb,const char *fmt, ...)
{
	int i ;
	char *buf = NULL;
	int rlen;
	buf = (char *)malloc(lenb+1);
	if (buf == NULL) return;
	buf[0] = 0;
	strcpy(buf,"ok\n");
	
	va_list ap;
	va_start(ap, fmt);	
	rlen = 0;
	rlen = vsprintf(buf,fmt, ap);		
	va_end(ap);
	buf = realloc(buf,rlen+1);
	if (buf == NULL) return;
	// write to all clients
	telnet_take_semaphore();
	for (i = 0;i<NBCLIENTT;i++)	
		if (istelnet( telnetclients[i]))
		{
			write( telnetclients[i],  buf, strlen(buf));
		}	
	telnet_give_semaphore();		
	free (buf);

}

void telnetNego(int tsocket)
{
	const uint8_t NONEG[2] = {0xFF,0xFC}; // WON't

	if (iiac == 2)
	{
	// refuse all
		if (iac[0] == 251) { write(tsocket,NONEG,2);write(tsocket,iac+1,1);}
	}
	else
	{
		if (iac[0] == 246) write(tsocket,"\n>",2);  // are you there
	}
}
	
void telnetCommand(int tsocket)
{
	if (irec == 0) return;
	ESP_LOGV(TAG,"%sHEAPd0: %d #\n","##SYS.",xPortGetFreeHeapSize( ));	
	brec[irec] = 0x0;
	write(tsocket,"\n> ",1);
	ESP_LOGV(TAG,"brec: %s\n",brec);
	obrec = realloc(obrec,strlen(brec)+1);
	strcpy(obrec,brec); // save old command
	checkCommand(irec, brec);
	write(tsocket,"> ",2);
	irec = 0;
}

int telnetRead(int tsocket)
{
	char *buf ;
	int32_t recbytes ;
	int i;	
	buf = (char *)malloc(MAXDATAT);	
	recbytes = 0;
    if (buf == NULL)
	{
		vTaskDelay(100); // wait a while and retry
		buf = (char *)malloc(MAXDATAT);	
	}	
	if (buf != NULL)
	{
		recbytes = read(tsocket , buf, MAXDATAT);

		if (recbytes <= 0) {
			if ((errno != EAGAIN )&& (errno != ENOTCONN) &&(errno != 0 ))
			{
				if (errno != ECONNRESET )
				{
					ESP_LOGE(TAG,strtSOCKET,"read", errno);	
				} 
			} 
			free(buf);
			return 0; // free the socket
		}	

		buf = realloc(buf,recbytes+2);
//		printf("%sHEAPdi1: %d #\nrecbytes: %d\n","##SYS.",xPortGetFreeHeapSize(),recbytes);	
		if (buf != NULL)
		{
			for (i = 0;i< recbytes;i++)
			{
//				printf("%x ",buf[i]);
				if (!inIac)
				switch(buf[i]){
				case '\r':
				case '\n':
					telnetCommand(tsocket);
					break;
				case 0x08:	//backspace
				case 0x7F:	//delete
					if (irec >0) --irec;
					break;
				case 0x1B:
					if (i+2 <= recbytes)
					{
						if ((buf[i+1]=='[') && (buf[i+2]=='A')) // arrow up
						{
							strcpy(brec,obrec); 
							write(tsocket,"\r",1);
							write(tsocket,brec,strlen(brec));
							irec = strlen(brec);
							buf = realloc(buf,2);
							vTaskDelay(2);	
							telnetCommand(tsocket);
						}						
						i =recbytes; // exit for
					}
					break;
				case 0xff: // iac
					inIac = true;
				break;
				default:
					brec[irec++] = buf[i];
					if (irec == sizeof(brec)) irec = 0;	
				}
				else // in iac
				{
					iac[iiac++] = buf[i];
					if (iiac == 2)
					{	
						telnetNego(tsocket);
						inIac = false;
						iiac = 0;
					}
				}
			}	
			free(buf);	
		}		
	}
	return recbytes;
}



