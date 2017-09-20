/*
 * Copyright 2016 karawin (http://www.karawin.fr)
*/
#ifndef __WEBCLIENT_H__
#define __WEBCLIENT_H__
#include "esp_system.h"
#include "esp_log.h"
//#include "websocket.h"

#define METADATA 9
#define METAINT 8
#define BITRATE 5
#define METANAME 0
#define ICY_HEADERS_COUNT 9
#define ICY_HEADER_COUNT 10
//2000 1440 1460
#define RECEIVE 1440
extern uint16_t currentStation;

typedef enum
{
    KMIME_UNKNOWN = 1, KOCTET_STREAM, KAUDIO_AAC, KAUDIO_MP4, KAUDIO_MPEG
} contentType_t;


struct icyHeader
{
	union
	{
		struct
		{
			char* name;
			char* notice1;
			char* notice2;
			char* url;
			char* genre;
			char* bitrate;
			char* description;
			char* audioinfo;
			int metaint;
			char* metadata;
		} single;
		char* mArr[ICY_HEADER_COUNT];
	} members;
};


enum clientStatus {C_HEADER0, C_HEADER, C_HEADER1,C_METADATA, C_DATA, C_PLAYLIST, C_PLAYLIST1 };

void clientInit();
uint8_t clientIsConnected();
bool clientParsePlaylist(char* s);
void clientSetURL(char* url);
void clientSetName(char* name,uint16_t index);
void clientSetPath(char* path);
void clientSetPort(uint16_t port);
bool clientPrintHeaders();
void clientPrintState();
bool getState();
char* getMeta();

struct icyHeader* clientGetHeader();
void clientConnect();
void clientSilentConnect(); 
void clientConnectOnce();
void clientDisconnect(const char* from);
void clientSilentDisconnect();
void clientTask(void *pvParams);
void vsTask(void *pvParams) ;
void wsVol(char* vol);
void wsMonitor();
void wsStationNext();
void wsStationPrev();
#endif
