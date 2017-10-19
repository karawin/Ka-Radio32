/*
 * Copyright 2016 karawin (http://www.karawin.fr)
*/

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "interface.h"
#include "webserver.h"
#include "serv-fs.h"
#include "servers.h"
#include "driver/timer.h"
#include "driver/uart.h"
#include "audio_renderer.h"
#include "app_main.h"
#include "ota.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "webclient.h"
#include "vs1053.h"

#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "eeprom.h"
#include "interface.h"


#define TAG "webserver"

xSemaphoreHandle semfile = NULL ;

const char strsROK[]  =  {"HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\nConnection: keep-alive\r\n\r\n%s"};
const char tryagain[] = {"try again"};

const char lowmemory[]  = { "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\nContent-Length: 11\r\n\r\nlow memory\n"};
const char strsMALLOC[]  = {"WebServer inmalloc fails for %d\n"};
const char strsMALLOC1[]  = {"WebServer %s malloc fails\n"};
const char strsSOCKET[]  = {"WebServer Socket fails %s errno: %d\n"};
const char strsID[]  = {"getstation, no id or Wrong id %d\n"};
const char strsRAUTO[]  = {"HTTP/1.1 200 OK\r\nContent-Type:application/json\r\nContent-Length:13\r\n\r\n{\"rauto\":\"%c\"}"};
const char strsICY[]  = {"HTTP/1.1 200 OK\r\nContent-Type:application/json\r\nContent-Length:%d\r\n\r\n{\"curst\":\"%s\",\"descr\":\"%s\",\"name\":\"%s\",\"bitr\":\"%s\",\"url1\":\"%s\",\"not1\":\"%s\",\"not2\":\"%s\",\"genre\":\"%s\",\"meta\":\"%s\",\"vol\":\"%s\",\"treb\":\"%s\",\"bass\":\"%s\",\"tfreq\":\"%s\",\"bfreq\":\"%s\",\"spac\":\"%s\",\"auto\":\"%c\"}"};
const char strsWIFI[]  = {"HTTP/1.1 200 OK\r\nContent-Type:application/json\r\nContent-Length:%d\r\n\r\n{\"ssid\":\"%s\",\"pasw\":\"%s\",\"ssid2\":\"%s\",\"pasw2\":\"%s\",\"ip\":\"%s\",\"msk\":\"%s\",\"gw\":\"%s\",\"ua\":\"%s\",\"dhcp\":\"%s\",\"mac\":\"%s\"}"};
const char strsGSTAT[]  = {"HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n{\"Name\":\"%s\",\"URL\":\"%s\",\"File\":\"%s\",\"Port\":\"%d\",\"ovol\":\"%d\"}"};

static int8_t clientOvol = 0;


void *inmalloc(size_t n)
{
	void* ret;	
	ESP_LOGV(TAG, "server Malloc of %d %d,  Heap size: %d",n,((n / 32) + 1) * 32,xPortGetFreeHeapSize( ));
	ret = malloc(n);
/*	if (ret == NULL)//
	{
		//printf(strsMALLOC,n);
		char* test = malloc(10);
		if (test != NULL) free(test);
		ret = malloc(n);
	}	
*/		
	ESP_LOGV(TAG,"server Malloc of %x : %d bytes Heap size: %d",(int)ret,n,xPortGetFreeHeapSize( ));
//	if (n <4) printf("Server: incmalloc size:%d\n",n);	
	return ret;
}	
void infree(void *p)
{
	ESP_LOGV(TAG,"server free of   %x,            Heap size: %d",(int)p,xPortGetFreeHeapSize( ));
	if (p != NULL)free(p);
}	



static struct servFile* findFile(char* name)
{
	struct servFile* f = (struct servFile*)&indexFile;
	while(1)
	{
		if(strcmp(f->name, name) == 0) return f;
		else f = f->next;
		if(f == NULL) return NULL;
	}
}


static void respOk(int conn,char* message)
{
	char rempty[] = {""};
	if (message == NULL) message = rempty;
	char* fresp = inmalloc(strlen(strsROK)+strlen(message)+15);
	if (fresp!=NULL)
	{
		sprintf(fresp,strsROK,"text/plain",strlen(message),message);
	ESP_LOGV(TAG,"respOk %s",fresp);
		write(conn, fresp, strlen(fresp));
		infree(fresp);
	}		
	ESP_LOGV(TAG,"respOk exit");
}

static void respKo(int conn)
{
//printf("ko\n");
	write(conn, lowmemory, strlen(lowmemory));
}

static void serveFile(char* name, int conn)
{
#define PART 1024
#define LIMIT 128

	int length;
	int progress,part,gpart;
	char buf[150];
	char *content;
	if (strcmp(name,"/style.css") == 0)
	{
		struct device_settings *device;
		device = getDeviceSettings();
		if (device != NULL)	 {
			if (device->options & T_THEME) strcpy(name , "/style1.css");
//			printf("name: %s, theme:%d\n",name,device->options&T_THEME);
			infree(device);
		}
	}
	struct servFile* f = findFile(name);
	ESP_LOGV(TAG,"find %s at %x",name,(int)f);
	ESP_LOGV(TAG,"Heap size: %d",xPortGetFreeHeapSize( ));
	gpart = PART;
	if(f != NULL)
	{
		length = f->size;
		content = (char*)f->content;
		progress = 0;
	}
	else length = 0;
	if(length > 0)
	{
		if (xSemaphoreTake(semfile,portMAX_DELAY ))
		{				
		
			ESP_LOGV(TAG,"serveFile socket:%d,  %s. Length: %d  sliced in %d",conn,name,length,gpart);		
			sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Encoding: gzip\r\nContent-Length: %d\r\nConnection: keep-alive\r\n\r\n", (f!=NULL ? f->type : "text/plain"), length);
			ESP_LOGV(TAG,"serveFile send %d bytes\n%s",strlen(buf),buf);	
			vTaskDelay(1); // why i need it? Don't know. 
			if (write(conn, buf, strlen(buf)) == -1) 
					 {respKo(conn); ESP_LOGE(TAG,"semfile fails 0 errno:%d",errno);xSemaphoreGive(semfile);	return;}
			progress = length;
			part = gpart;
			if (progress <= part) part = progress;
			while (progress > 0) 
			{
				if (write(conn, content, part) == -1) 
					  {respKo(conn); ESP_LOGE(TAG,"semfile fails 1 errno:%d",errno);xSemaphoreGive(semfile);	return;}

				ESP_LOGV(TAG,"serveFile socket:%d,  read at %x len: %d",conn,(int)content,(int)part);					
				content += part;
				progress -= part;
				if (progress <= part) part = progress;
				//vTaskDelay(1);
			} 
			xSemaphoreGive(semfile);	
		} else  {respKo(conn); ESP_LOGE(TAG,"semfile fails 2 errno:%d",errno);xSemaphoreGive(semfile);	return;}
	}
	else
	{
		respKo(conn);
	}
	ESP_LOGV(TAG,"serveFile socket:%d, end",conn);
}




static char* getParameter(char* sep,char* param, char* data, uint16_t data_length) {
	if ((data == NULL) || (param == NULL))return NULL;
	char* p = strstr(data, param);
	if(p != NULL) {
		p += strlen(param);
		char* p_end = strstr(p, sep);
		if(p_end ==NULL) p_end = data_length + data;
		if(p_end != NULL ) {
			if (p_end==p) return NULL;
			char* t = inmalloc(p_end-p + 1);
			if (t == NULL) { printf(PSTR("getParameterF fails%c"),0x0d); return NULL;}
			ESP_LOGV(TAG,"getParameter malloc of %d  for %s",p_end-p + 1,param);
			int i;
			for(i=0; i<(p_end-p + 1); i++) t[i] = 0;
			strncpy(t, p, p_end-p);
			ESP_LOGV(TAG,"getParam: in: \"%s\"   \"%s\"",data,t);
			return t;
		} else return NULL;
	} else return NULL;
}
static char* getParameterFromResponse(char* param, char* data, uint16_t data_length) {
	return getParameter("&",param,data, data_length) ;
}
static char* getParameterFromComment(char* param, char* data, uint16_t data_length) {
	return getParameter("\"",param,data, data_length) ;
}

// volume offset
static void clientSetOvol(int8_t ovol)
{
	clientOvol = ovol;
	kprintf(PSTR("##CLI.OVOLSET#: %d\n"),ovol);
	vTaskDelay(10);
}

// set the volume with vol,  add offset
void setVolumei(int16_t vol) {
	vol += clientOvol;
	if (vol > 254) vol = 254;
	if (vol <0) vol = 1;
	if (get_audio_output_mode() == VS1053) VS1053_SetVolume(vol);
	if (vol <3) vol--;
	renderer_volume(vol+2); // max 256
}
void setVolume(char* vol) {
	setIvol(atoi(vol));
	int16_t uvol = atoi(vol);
	uvol += clientOvol;
	if (uvol > 254) uvol = 254;
	if (uvol <0) uvol = 1;
	if(vol) {
		if (get_audio_output_mode() == VS1053) VS1053_SetVolume(uvol);
		if (uvol <3) uvol--;
		renderer_volume(uvol+2); // max 256
		kprintf(PSTR("##CLI.VOL#: %d\n"),getIvol());		
	}
}
// set the current volume with its offset
static void setOffsetVolume(void) {
	int16_t uvol = getIvol();
	uvol += clientOvol;
	if (uvol > 254) uvol = 254;
	if (uvol <=0) uvol = 1;
	ESP_LOGV(TAG,"setOffsetVol: %d",clientOvol);
	setVolumei(uvol);
}



uint16_t getVolume() {
	return (getIvol());
}

// Set the volume with increment vol
void setRelVolume(int8_t vol) {
	char Vol[5];
	int16_t rvol;
	rvol = getIvol()+vol;
	if (rvol <0) rvol = 0;
	if (rvol > 254) rvol = 254;
	sprintf(Vol,"%d",rvol);	
	setVolume(Vol);
	wsVol(Vol);
}

// flip flop the theme indicator
static void theme() {
		struct device_settings *device;
		device = getDeviceSettings();
		if (device != NULL)	 {
			if ((device->options&T_THEME)!=0) device->options&=NT_THEME; else device->options |= T_THEME;
			saveDeviceSettings(device);
			ESP_LOGV(TAG,"theme:%d",device->options&T_THEME);
			infree(device);	
		}
}

// treat the received message of the websocket
void websockethandle(int socket, wsopcode_t opcode, uint8_t * payload, size_t length)
{
//	struct device_settings *device;
	//wsvol
	ESP_LOGV(TAG,"websocketHandle: %s",payload);
	if (strstr((char*)payload,"wsvol=")!= NULL)
	{
		char answer[17];
		if (strstr((char*)payload,"&") != NULL)
			*strstr((char*)payload,"&")=0;
		else return;
//		setVolume(payload+6);
		sprintf(answer,"{\"wsvol\":\"%s\"}",payload+6);
		websocketlimitedbroadcast(socket,answer, strlen(answer));
	}
	else if (strstr((char*)payload,"startSleep=")!= NULL)
	{
		if (strstr((char*)payload,"&") != NULL)
			*strstr((char*)payload,"&")=0;
		else return;
		startSleep(atoi((char*)payload+11));
	}
	else if (strstr((char*)payload,"stopSleep")!= NULL){stopSleep();}
	else if (strstr((char*)payload,"startWake=")!= NULL)
	{
		if (strstr((char*)payload,"&") != NULL)
			*strstr((char*)payload,"&")=0;
		else return;
		startWake(atoi((char*)payload+10));
	}
	else if (strstr((char*)payload,"stopWake")!= NULL){stopWake();}
	//monitor
	else if (strstr((char*)payload,"monitor")!= NULL){wsMonitor();}
	else if (strstr((char*)payload,"upgrade")!= NULL){update_firmware("KaRadio32");	}
	else if (strstr((char*)payload,"theme")!= NULL){theme();}
}


void playStationInt(int sid) {
	struct shoutcast_info* si;
	char answer[24];
	struct device_settings *device;
	si = getStation(sid);

	if(si != NULL &&si->domain && si->file) {
			int i;
			vTaskDelay(4);
			clientSilentDisconnect();
//			clientDisconnect("playStationInt");
			ESP_LOGV(TAG,"playstationInt: %d, new station: %s",sid,si->name);
			for (i = 0;i<100;i++)
			{
				if(!clientIsConnected())break;
				vTaskDelay(5);
			}
			clientSetName(si->name,sid);
			clientSetURL(si->domain);
			clientSetPath(si->file);
			clientSetPort(si->port);
			clientSetOvol(si->ovol);
			clientConnect();
			setOffsetVolume();
			for (i = 0;i<100;i++)
			{
				if (clientIsConnected()) break;
				vTaskDelay(5);
			}
	}
	infree(si);
	sprintf(answer,"{\"wsstation\":\"%d\"}",sid);
	websocketbroadcast(answer, strlen(answer));
	device = getDeviceSettings();
	if (device != NULL)
	{
		ESP_LOGV(TAG,"playstationInt: %d, device: %d",sid,device->currentstation);
		if (device->currentstation != sid)
		{
			device->currentstation = sid;
			saveDeviceSettings(device);
		}
		infree(device);
	}
}
	
void playStation(char* id) {
	

	int uid;
	uid = atoi(id) ;
	ESP_LOGV(TAG,"playstation: %d",uid);
	if (uid < 255)
		setCurrentStation (atoi(id)) ;
	playStationInt(getCurrentStation());	
}

// replace special  json char
static void pathParse(char* str)
{
	int i ;
	char *pend;
	char  num[3]= {0,0,0};
	uint8_t cc;
	if (str == NULL) return;
	for (i=0; i< strlen(str);i++)
	{
		if (str[i] == '%')
		{
			num[0] = str[i+1]; num[1] = str[i+2];
			cc = strtol(num, &pend,16);
			str[i] = cc;			
			str[i+1]=0;
			if (str[i+3] !=0)strcat(str, str+i+3);
		}
	}
}

static void handlePOST(char* name, char* data, int data_size, int conn) {
	ESP_LOGD(TAG,"HandlePost %s\n",name);
	int i;
	bool changed = false;
	struct device_settings *device;
	if(strcmp(name, "/instant_play") == 0) {
		if(data_size > 0) {
			char* url = getParameterFromResponse("url=", data, data_size);
			char* path = getParameterFromResponse("path=", data, data_size);
			pathParse(path);
			char* port = getParameterFromResponse("port=", data, data_size);
			if(url != NULL && path != NULL && port != NULL) {
				clientDisconnect(PSTR("Post instant_play"));
				for (i = 0;i<100;i++)
				{
					if(!clientIsConnected())break;
					vTaskDelay(4);
				}
				
				clientSetURL(url);
				clientSetPath(path);
				clientSetPort(atoi(port));
				clientSetOvol(0);
				clientConnectOnce();
				setOffsetVolume();
				for (i = 0;i<100;i++)
				{
					if (clientIsConnected()) break;
					vTaskDelay(5);
				}
			} 
			infree(url);
			infree(path);
			infree(port);
		}
	} else if(strcmp(name, "/soundvol") == 0) {
		if(data_size > 0) {
			char * vol = data+4;
			data[data_size-1] = 0;
			ESP_LOGD(TAG,"/sounvol vol: %s num:%d",vol, atoi(vol));
			setVolume(vol); 
		}
	} else if(strcmp(name, "/sound") == 0) {
		if(data_size > 0) {
			char* bass = getParameterFromResponse("bass=", data, data_size);
			char* treble = getParameterFromResponse("treble=", data, data_size);
			char* bassfreq = getParameterFromResponse("bassfreq=", data, data_size);
			char* treblefreq = getParameterFromResponse("treblefreq=", data, data_size);
			char* spacial = getParameterFromResponse("spacial=", data, data_size);
			device = getDeviceSettings();
			if (device != NULL)
			{
				changed = false;
				if(bass) {
					
					if (device->bass != atoi(bass))
					{ 
						if (get_audio_output_mode() == VS1053)
						{
							VS1053_SetBass(atoi(bass));
							changed = true;
							device->bass = atoi(bass); 
						}
					}
					infree(bass);
				}
				if(treble) {				
					if (device->treble != atoi(treble))
					{ 
						if (get_audio_output_mode() == VS1053)
						{
							VS1053_SetTreble(atoi(treble));
							changed = true;
							device->treble = atoi(treble); 
						}
					}
					infree(treble);
				}
				if(bassfreq) {					
					if (device->freqbass != atoi(bassfreq))
					{ 
						if (get_audio_output_mode() == VS1053) 
						{
							VS1053_SetBassFreq(atoi(bassfreq));
							changed = true;
							device->freqbass = atoi(bassfreq); 
						}
					}
					infree(bassfreq);
				}
				if(treblefreq) {					
					if (device->freqtreble != atoi(treblefreq))
					{
						if (get_audio_output_mode() == VS1053)
						{
							VS1053_SetTrebleFreq(atoi(treblefreq)); 
							changed = true;
							device->freqtreble = atoi(treblefreq); 
						}
					}
					infree(treblefreq);
				}
				if(spacial) {					
					if (device->spacial != atoi(spacial))
					{
							if (get_audio_output_mode() == VS1053) 
							{	
								VS1053_SetSpatial(atoi(spacial)); 
								changed = true;
								device->spacial = atoi(spacial); 
							}
					}
					infree(spacial);
				}
				if (changed) 
					saveDeviceSettings(device);
				infree(device);
			}
		}
	} else if(strcmp(name, "/getStation") == 0) {
		if(data_size > 0) {
			char* id = getParameterFromResponse("idgp=", data, data_size);
			if (id ) 
			{
				if ((atoi(id) >=0) && (atoi(id) < 255)) 
				{
					char ibuf [6];	
					char *buf;
					for(i = 0; i<sizeof(ibuf); i++) ibuf[i] = 0;
					struct shoutcast_info* si;
					si = getStation(atoi(id));
					if (strlen(si->domain) > sizeof(si->domain)) si->domain[sizeof(si->domain)-1] = 0; //truncate if any (rom crash)
					if (strlen(si->file) > sizeof(si->file)) si->file[sizeof(si->file)-1] = 0; //truncate if any (rom crash)
					if (strlen(si->name) > sizeof(si->name)) si->name[sizeof(si->name)-1] = 0; //truncate if any (rom crash)
					sprintf(ibuf, "%d%d", si->ovol,si->port);
					int json_length = strlen(si->domain) + strlen(si->file) + strlen(si->name) + strlen(ibuf) + 50;
					buf = inmalloc(json_length + 75);
					
					if (buf == NULL)
					{	
						ESP_LOGE(TAG," %s malloc fails","getStation");
						respKo(conn);
					}
					else {				
						
						for(i = 0; i<sizeof(buf); i++) buf[i] = 0;
						sprintf(buf, strsGSTAT,					
						json_length, si->name, si->domain, si->file,si->port,si->ovol);
						ESP_LOGV(TAG,"getStation Buf len:%d : %s",strlen(buf),buf);						
						write(conn, buf, strlen(buf));
						infree(buf);
					}
					infree(si);
					infree(id);
					return;
				} else printf(strsID,atoi(id));
				infree (id);
			} 			
		}
	} else if(strcmp(name, "/setStation") == 0) 
	{
		if(data_size > 0) {
//printf("data:%s\n",data);
			char* nb = getParameterFromResponse("nb=", data, data_size);
			uint16_t unb,uid = 0;
			ESP_LOGV(TAG,"Setstation: nb init:%s",nb);
			bool pState = getState();  // remember if we are playing
			if (nb) {unb = atoi(nb); infree(nb);}
			else unb = 1;
			ESP_LOGV(TAG,"unb init:%d",unb);
			char* id; char* url; char* file; char* name; char* port; char* ovol;
			struct shoutcast_info *si =  inmalloc(sizeof(struct shoutcast_info)*unb);
			struct shoutcast_info *nsi ;
			
			if (si == NULL) {
				ESP_LOGE(TAG," %s malloc fails","setStation");
				respKo(conn);
				return;
			}
			char* bsi = (char*)si;
			int j;
			for (j=0;j< sizeof(struct shoutcast_info)*unb;j++) bsi[j]=0; //clean 

			for (i=0;i<unb;i++)
			{
				nsi = si + i;
				id = getParameterFromResponse("id=", data, data_size);
				url = getParameterFromResponse("url=", data, data_size);
				file = getParameterFromResponse("file=", data, data_size);
				pathParse(file);
				name = getParameterFromResponse("name=", data, data_size);
				port = getParameterFromResponse("port=", data, data_size);
				ovol = getParameterFromResponse("ovol=", data, data_size);
				ESP_LOGV(TAG,"nb:%d,si:%x,nsi:%x,id:%s,url:%s,file:%s",i,(int)si,(int)nsi,id,url,file);
				if(id ) {
					if (i == 0) uid = atoi(id);
					if ((atoi(id) >=0) && (atoi(id) < 255))
					{	
						if(url && file && name && port) {
							if (strlen(url) > sizeof(nsi->domain)) url[sizeof(nsi->domain)-1] = 0; //truncate if any
							strcpy(nsi->domain, url);
							if (strlen(file) > sizeof(nsi->file)) url[sizeof(nsi->file)-1] = 0; //truncate if any
							strcpy(nsi->file, file);
							if (strlen(name) > sizeof(nsi->name)) url[sizeof(nsi->name)-1] = 0; //truncate if any
							strcpy(nsi->name, name);
							nsi->ovol = (ovol==NULL)?0:atoi(ovol);
							nsi->port = atoi(port);
						}
					} 					
				} 
				infree(ovol);
				infree(port);
				infree(name);
				infree(file);
				infree(url);
				infree(id);
				
				data = strstr(data,"&&")+2;
				ESP_LOGV(TAG,"si:%x, nsi:%x, addr:%x",(int)si,(int)nsi,(int)data);
			}
			ESP_LOGV(TAG,"save station: %d, unb:%d, addr:%x",uid,unb,(int)si);
			saveMultiStation(si, uid,unb);
			ESP_LOGV(TAG,"save station return: %d, unb:%d, addr:%x",uid,unb,(int)si);
			infree (si);	
			if (pState != getState()) 
				if (pState) {clientConnect();vTaskDelay(200);}	 //we was playing so start again the play		
		}
	} else if(strcmp(name, "/play") == 0) {
		if(data_size > 4) {
			char * id = data+3;
			data[data_size-1] = 0;
				playStation(id);
		}
	} else if(strcmp(name, "/auto") == 0) {
		if(data_size > 4) {
			char * id = data+3;
			data[data_size-1] = 0;
			device = getDeviceSettings();
			if (device != NULL)
			{
				if ((strcmp(id,"true"))&&(device->autostart==1))
				{
					device->autostart = 0;
					ESP_LOGV(TAG,"autostart: %s, num:%d",id,device->autostart);
					saveDeviceSettings(device);
				}
				else
				if ((strcmp(id,"false"))&&(device->autostart==0))
				{
					device->autostart = 1;
					ESP_LOGV(TAG,"autostart: %s, num:%d",id,device->autostart);
					saveDeviceSettings(device);
				}
				infree(device);	
			}			
		}
	} else if(strcmp(name, "/rauto") == 0) {
		char *buf = inmalloc( strlen(strsRAUTO)+16);
		if (buf == NULL)
		{	
			ESP_LOGE(TAG," %s malloc fails","post rauto");
			respOk(conn,"nok");
		}
		else {			
			device = getDeviceSettings();
			if (device != NULL)
			{
				sprintf(buf, strsRAUTO,(device->autostart)?'1':'0' );
				write(conn, buf, strlen(buf));
				infree(buf);
				infree(device);	
			}
		}
		
		return;		
	} else if(strcmp(name, "/stop") == 0) {
		if (clientIsConnected())
		{	
			clientDisconnect(PSTR("Post Stop"));
			for (i = 0;i<100;i++)
			{
				if (!clientIsConnected()) break;
				vTaskDelay(4);
			}
		}
	} else if(strcmp(name, "/icy") == 0)	
	{	
		ESP_LOGV(TAG,"icy vol");
		char currentSt[5]; sprintf(currentSt,"%d",getCurrentStation());
		char vol[5]; sprintf(vol,"%d",(getVolume() ));
		char treble[5]; sprintf(treble,"%d",(get_audio_output_mode() == VS1053)?VS1053_GetTreble():0);
		char bass[5]; sprintf(bass,"%d",(get_audio_output_mode() == VS1053)?VS1053_GetBass():0);
		char tfreq[5]; sprintf(tfreq,"%d",(get_audio_output_mode() == VS1053)?VS1053_GetTrebleFreq():0);
		char bfreq[5]; sprintf(bfreq,"%d",(get_audio_output_mode() == VS1053)?VS1053_GetBassFreq():0);
		char spac[5]; sprintf(spac,"%d",(get_audio_output_mode() == VS1053)?VS1053_GetSpatial():0);
				
		struct icyHeader *header = clientGetHeader();
		ESP_LOGV(TAG,"icy start header %x",(int)header);
		char* not2;
		not2 = header->members.single.notice2;
		if (not2 ==NULL) not2=header->members.single.audioinfo;
		if ((header->members.single.notice2 != NULL)&&(strlen(header->members.single.notice2)==0)) not2=header->members.single.audioinfo;
		int json_length ;
		json_length =166+ //144 155
		((header->members.single.description ==NULL)?0:strlen(header->members.single.description)) +
		((header->members.single.name ==NULL)?0:strlen(header->members.single.name)) +
		((header->members.single.bitrate ==NULL)?0:strlen(header->members.single.bitrate)) +
		((header->members.single.url ==NULL)?0:strlen(header->members.single.url))+ 
		((header->members.single.notice1 ==NULL)?0:strlen(header->members.single.notice1))+
		((not2 ==NULL)?0:strlen(not2))+
		((header->members.single.genre ==NULL)?0:strlen(header->members.single.genre))+
		((header->members.single.metadata ==NULL)?0:strlen(header->members.single.metadata))
		+ strlen(currentSt)+	strlen(vol) +strlen(treble)+strlen(bass)+strlen(tfreq)+strlen(bfreq)+strlen(spac)
		;
		ESP_LOGD(TAG,"icy start header %x  len:%d vollen:%d vol:%s",(int)header,json_length,strlen(vol),vol);
		
		char *buf = inmalloc( json_length + 75);
		if (buf == NULL) 
		{	
			ESP_LOGE(TAG," %s malloc fails","post icy");
			infree(buf);
			respKo(conn);
		}
		else 
		{	
			uint8_t vauto = 0;
			device = getDeviceSettings();
			if (device != NULL)
			{
				vauto = (device->autostart)?'1':'0' ;
				infree(device);	
			}
			sprintf(buf, strsICY,
			json_length,
			currentSt,
			(header->members.single.description ==NULL)?"":header->members.single.description,
			(header->members.single.name ==NULL)?"":header->members.single.name,
			(header->members.single.bitrate ==NULL)?"":header->members.single.bitrate,
			(header->members.single.url ==NULL)?"":header->members.single.url,
			(header->members.single.notice1 ==NULL)?"":header->members.single.notice1,
			(not2 ==NULL)?"":not2 ,
			(header->members.single.genre ==NULL)?"":header->members.single.genre,
			(header->members.single.metadata ==NULL)?"":header->members.single.metadata,			
			vol,treble,bass,tfreq,bfreq,spac,
			vauto );
			ESP_LOGV(TAG,"test: len fmt:%d %d\n%s\nfmt: %s",strlen(strsICY),strlen(strsICY),buf,strsICY);
			write(conn, buf, strlen(buf));
			infree(buf);
			wsMonitor();
			
		}		
		return;
	} else if(strcmp(name, "/hardware") == 0)
	{		
		bool val = false;
		uint8_t cout;
		struct device_settings *device;
		changed = false;
		if(data_size > 0) {
			device = getDeviceSettings();
			if (device ==NULL)
			{
				infree(device);
				respKo(conn);
				return;
			}
			char* valid = getParameterFromResponse("valid=", data, data_size);
			if(valid != NULL) if (strcmp(valid,"1")==0) val = true;	
			char* coutput = getParameterFromResponse("coutput=", data, data_size);
			cout = atoi(coutput);
			if (val)
			{
				device->audio_output_mode = cout;
				changed = true;
				saveDeviceSettings(device);	
			}
			int json_length ;
			json_length =15;
				
			char *buf = inmalloc( json_length + 95);
			if (buf == NULL) 
			{	
				ESP_LOGE(TAG," %s malloc fails","post wifi");
				respKo(conn);
			}
			else {	
				sprintf(buf, "HTTP/1.1 200 OK\r\nContent-Type:application/json\r\nContent-Length:%d\r\n\r\n{\"coutput\":\"%d\"}",
				json_length,
				device->audio_output_mode);
				ESP_LOGV(TAG,"hardware Buf len:%d\n%s",strlen(buf),buf);
				write(conn, buf, strlen(buf));
				infree(buf);
			}
			infree(valid); infree(coutput);
			if (val){
				// set current_ap to the first filled ssid
				ESP_LOGD(TAG,"audio_output_mode: %d",device->audio_output_mode);
				vTaskDelay(50);	
				esp_restart();			
			}	
			infree(device);			
		}		
	} else if(strcmp(name, "/wifi") == 0)	
	{
		bool val = false;
		char tmpip[16],tmpmsk[16],tmpgw[16];
		struct device_settings *device;
		changed = false;		
		if(data_size > 0) {
			device = getDeviceSettings();
			if (device ==NULL)
			{
				infree(device);
				respKo(conn);
				return;
			}
			char* valid = getParameterFromResponse("valid=", data, data_size);
			if(valid != NULL) if (strcmp(valid,"1")==0) val = true;
			char* ssid = getParameterFromResponse("ssid=", data, data_size);
			pathParse(ssid);
			char* pasw = getParameterFromResponse("pasw=", data, data_size);
			pathParse(pasw);
			char* ssid2 = getParameterFromResponse("ssid2=", data, data_size);
			pathParse(ssid2);
			char* pasw2 = getParameterFromResponse("pasw2=", data, data_size);
			pathParse(pasw2);
			char* aip = getParameterFromResponse("ip=", data, data_size);
			char* amsk = getParameterFromResponse("msk=", data, data_size);
			char* agw = getParameterFromResponse("gw=", data, data_size);
			char* aua = getParameterFromResponse("ua=", data, data_size);
			pathParse(aua);
			char* adhcp = getParameterFromResponse("dhcp=", data, data_size);
			if (val) {
				ESP_LOGV(TAG,"wifi received  valid:%s,val:%d, ssid:%s, pasw:%s, aip:%s, amsk:%s, agw:%s, adhcp:%s, aua:%s",valid,val,ssid,pasw,aip,amsk,agw,adhcp,aua);
				changed = true;
				ip_addr_t valu;
				ipaddr_aton(aip, &valu);
				memcpy(device->ipAddr1,&valu,sizeof(uint32_t));
				ipaddr_aton(amsk, &valu);
				memcpy(device->mask1,&valu,sizeof(uint32_t));
				ipaddr_aton(agw, &valu);
				memcpy(device->gate1,&valu,sizeof(uint32_t));
				if (adhcp!= NULL)
				{ 
					if (strlen(adhcp)!=0) 
					{
						if (strcmp(adhcp,"true")==0)device->dhcpEn1 = 1; else device->dhcpEn1 = 0;
					}
				}
				strcpy(device->ssid1,(ssid==NULL)?"":ssid);
				strcpy(device->pass1,(pasw==NULL)?"":pasw);
				strcpy(device->ssid2,(ssid2==NULL)?"":ssid2);
				strcpy(device->pass2,(pasw2==NULL)?"":pasw2);				
			}
			if (strlen(device->ua)==0)
			{
				if (aua==NULL) {aua= inmalloc(12); strcpy(aua,"Karadio/1.5");}
			}	
			if (aua!=NULL) 
			{
				if (strcmp(device->ua,aua) != 0)
				{
					strcpy(device->ua,aua);
					changed = true;
				}
			}
			if (changed)
			{
				saveDeviceSettings(device);	
//printf("WServer saveDeviceSettings\n");
			}			
			uint8_t *macaddr = inmalloc(10*sizeof(uint8_t));
			char* macstr = inmalloc(20*sizeof(char));
			//wifi_get_macaddr ( 0, macaddr );	
			esp_wifi_get_mac(WIFI_IF_STA,macaddr);		
			int json_length ;
			json_length =95+ //64 //86 95
			strlen(device->ssid1) +
			strlen(device->pass1) +
			strlen(device->ssid2) +
			strlen(device->pass2) +
			strlen(device->ua)+
			sprintf(tmpip,"%d.%d.%d.%d",device->ipAddr1[0], device->ipAddr1[1],device->ipAddr1[2], device->ipAddr1[3])+
			sprintf(tmpmsk,"%d.%d.%d.%d",device->mask1[0], device->mask1[1],device->mask1[2], device->mask1[3])+
			sprintf(tmpgw,"%d.%d.%d.%d",device->gate1[0], device->gate1[1],device->gate1[2], device->gate1[3])+
			sprintf(adhcp,"%d",device->dhcpEn1)+
			sprintf(macstr,MACSTR,MAC2STR(macaddr));

			char *buf = inmalloc( json_length + 95);
			if (buf == NULL) 
			{	
				ESP_LOGE(TAG," %s malloc fails","post wifi");
				respKo(conn);
			}
			else {			
				sprintf(buf, strsWIFI,
				json_length,
				device->ssid1,device->pass1,device->ssid2,device->pass2,tmpip,tmpmsk,tmpgw,device->ua,adhcp,macstr);
				ESP_LOGV(TAG,"wifi Buf len:%d\n%s",strlen(buf),buf);
				write(conn, buf, strlen(buf));
				infree(buf);
			}
			infree(ssid); infree(pasw);infree(ssid2); infree(pasw2);  
			infree(aip);infree(amsk);infree(agw);infree(aua);
			infree(valid); infree(adhcp); infree(macaddr); 
			infree(macstr);
			if (val){
				// set current_ap to the first filled ssid
				ESP_LOGD(TAG,"currentAP: %d",device->current_ap);
				if (device->current_ap == APMODE)
				{
					if (strlen(device->ssid1)!= 0) device->current_ap = STA1;
					else
					if (strlen(device->ssid2)!= 0) device->current_ap = STA2;
					saveDeviceSettings(device);
				}
				ESP_LOGD(TAG,"currentAP: %d",device->current_ap);				
				vTaskDelay(50);	
				esp_restart();			
			}	
			infree(device);
		}	
		return;
	} else if(strcmp(name, "/clear") == 0)	
	{
		eeEraseStations();	//clear all stations
	}
	respOk(conn,NULL);
}

static bool httpServerHandleConnection(int conn, char* buf, uint16_t buflen) {
	char* c;
	char* d;
	ESP_LOGD(TAG,"Heap size: %d",xPortGetFreeHeapSize( ));
//printf("httpServerHandleConnection  %20c \n",&buf);
	if( (c = strstr(buf, "GET ")) != NULL)
	{
		ESP_LOGV(TAG,"GET socket:%d len: %d, str:\n%s",conn,buflen,buf);
		if( ((d = strstr(buf,"Connection:")) !=NULL)&& ((d = strstr(d," Upgrade")) != NULL))
		{  // a websocket request
			websocketAccept(conn,buf,buflen);	
			ESP_LOGD(TAG,"websocketAccept socket: %d",conn);
			return false;
		} else
		{
//			char fname[32];
//			uint8_t i;
//			for(i=0; i<32; i++) fname[i] = 0;
			c += 4;
			char* c_end = strstr(c, "HTTP");
			if(c_end == NULL) return true;
			*(c_end-1) = 0;
			c_end = strstr(c,"?");
//			
// web command api,
/////////////////// 		
			if(c_end != NULL) // commands api
			{
				char* param;
//printf("GET commands  socket:%d command:%s\n",conn,c);
// uart command
				param = strstr(c,"uart") ;
				if (param != NULL) {uart_set_baudrate(0, 115200);} //UART_SetBaudrate(0, 115200);}	
// volume command				
				param = getParameterFromResponse("volume=", c, strlen(c)) ;
				if ((param != NULL)&&(atoi(param)>=0)&&(atoi(param)<=254))
				{	
					setVolume(param);
					wsVol(param);
				}	
				infree(param);
// play command				
				param = getParameterFromResponse("play=", c, strlen(c)) ;
				if (param != NULL) {playStation(param);infree(param);}
// start command				
				param = strstr(c,"start") ;
				if (param != NULL) {playStationInt(getCurrentStation());}
// stop command				
				param = strstr(c,"stop") ;
				if (param != NULL) {clientDisconnect(PSTR("Web stop"));}
// instantplay command				
				param = getParameterFromComment("instant=", c, strlen(c)) ;
				if (param != NULL) {
					clientDisconnect(PSTR("Web Instant"));
					pathParse(param);
//					printf("Instant param:%s\n",param);
					clientParsePlaylist(param);clientConnectOnce();
					infree(param);
				}
// version command				
				param = strstr(c,"version") ;
				if (param != NULL) {
					char* vr = malloc(30);
					if (vr != NULL)
					{
						sprintf(vr,"Release: %s, Revision: %s\n",RELEASE,REVISION);
						printf("Version:%s\n",vr);
						respOk(conn,vr); 
						infree(vr);
						return true;
					}
				}
// infos command				
				param = strstr(c,"infos") ;				
				if (param != NULL) {
					char* vr = webInfo();	
					respOk(conn,vr); 
					infree(vr);
					return true;
				}		
// list command	 ?list=1 to list the name of the station 1			
				param = getParameterFromResponse("list=", c, strlen(c)) ;
				if ((param != NULL)&&(atoi(param)>=0)&&(atoi(param)<=254))
				{
					char* vr = webList(atoi(param));
					respOk(conn,vr); 
					infree(vr);
					return true;
				}				
				respOk(conn,NULL); // response OK to the origin
			}
			else 
// file GET		
			{
				if(strlen(c) > 32) {
					respKo(conn); 
					return true;}
				ESP_LOGV(TAG,"GET file  socket:%d file:%s",conn,c);
				serveFile(c, conn);
				ESP_LOGV(TAG,"GET end socket:%d file:%s",conn,c);
			}
		}
	} else if( (c = strstr(buf, "POST ")) != NULL) {
// a post request		
		ESP_LOGV(TAG,"POST socket: %d  buflen: %d",conn,buflen);
		char fname[32];
		uint8_t i;
		for(i=0; i<32; i++) fname[i] = 0;
		c += 5;
		char* c_end = strstr(c, " ");
		if(c_end == NULL) return true;
		uint8_t len = c_end-c;
		if(len > 32) return true;
		strncpy(fname, c, len);
		ESP_LOGV(TAG,"POST Name: %s", fname);
		// DATA
		char* d_start = strstr(buf, "\r\n\r\n");
		ESP_LOGV(TAG,"dstart:%s",d_start);
		if(d_start != NULL) {
			d_start += 4;
			uint16_t len = buflen - (d_start-buf);
			handlePOST(fname, d_start, len, conn);
		}
	}
	return true;
}


#define RECLEN	768
#define DRECLEN (RECLEN*2)

// Server child task to handle a request from a browser.
void serverclientTask(void *pvParams) {
	struct timeval timeout; 
	char buf[2*RECLEN]; 
    timeout.tv_sec = 3; 
    timeout.tv_usec = 0;
	int recbytes ,recb;
	portBASE_TYPE uxHighWaterMark;
	int  client_sock =  (int)pvParams;
 //   char *buf = (char *)inmalloc(reclen);
	bool result = true;
	
	if (buf != NULL)
	{
		memset(buf,0,DRECLEN);
		if (setsockopt (client_sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
			printf(strsSOCKET,"setsockopt",errno);

		while (((recbytes = read(client_sock , buf, DRECLEN)) != 0)) 
		{ // For now we assume max. DRECLEN bytes for request 
			if (recbytes < 0) {
				break;
				if (errno != EAGAIN )
				{
					printf(strsSOCKET,"client_sock",errno);
					vTaskDelay(10);	
					break;
				} else {printf(strsSOCKET,tryagain,errno);break;}
			}	
			char* bend = NULL;
			do {
				bend = strstr(buf, "\r\n\r\n");
				if (bend != NULL) 
				{	
					bend += 4;
					if (strstr(buf,"POST") ) //rest of post?
					{
						uint16_t cl = atoi(strstr(buf, "Content-Length: ")+16);
						vTaskDelay(1);
						if ((bend - buf +cl)> recbytes)
						{	
//printf ("Server: try receive more:%d bytes. , must be %d\n", recbytes,bend - buf +cl);
							while(((recb = read(client_sock , buf+recbytes, cl))==0)){vTaskDelay(1);printf(".");}
							buf[recbytes+recb] = 0;
//printf ("Server: received more now: %d bytes, rec:\n%s\nEnd\n", recbytes+recb,buf);
							if (recb < 0) {
								ESP_LOGE(TAG,"read fails 0  errno:%d",errno);
								respKo(client_sock);
								break;
/*								if (errno != EAGAIN )
								{
									printf(strsSOCKET,"read",errno);
									vTaskDelay(10);	
									break;
								} else printf(strsSOCKET,tryagain,errno);
*/								
							}
							recbytes += recb;
						}
					}
				} 
				else { 
					
//					printf ("Server: try receive more for end:%d bytes\n", recbytes);					
					while(((recb= read(client_sock , buf+recbytes, DRECLEN-recbytes))==0)) vTaskDelay(1);
//					printf ("Server: received more for end now: %d bytes\n", recbytes+recb);
					if (recb < 0) {
						ESP_LOGE(TAG,"read fails 1  errno:%d",errno);
						respKo(client_sock);
						break;	
					}
					recbytes += recb;
				} //until "\r\n\r\n"
			} while (bend == NULL);
			if (bend != NULL)
				result = httpServerHandleConnection(client_sock, buf, recbytes);
			//if (buf == NULL) printf("WARNING\n");
			memset(buf,0,DRECLEN);
			if (!result) 
			{
				break; // only a websocket created. exit without closing the socket
			}	
			vTaskDelay(1);
		}
//		infree(buf);
	} else  printf(strsMALLOC1,"buf");
	if (result)
	{
		int err;
		err = shutdown(client_sock,SHUT_RDWR);
		vTaskDelay(20);
		err = close(client_sock);
		if (err != ERR_OK) 
		{
			err=close(client_sock);
//			printf ("closeERR:%d\n",err);
		}
	}
	xSemaphoreGive(semclient);	
	ESP_LOGV(TAG,"Give client_sock: %d",client_sock);		
	uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
	ESP_LOGD(TAG,"watermark serverClientTask: %x  %d",uxHighWaterMark,uxHighWaterMark);	


	ESP_LOGV(TAG,"Client exit socket:%d result %d \n",client_sock,result);
	vTaskDelete( NULL );	
}	


