/* (c)jp cocatrix May 2017 
	quick and dirty telnet inplementation for wifi webradio
Inspirated by:
 * 
 * This file is part of the WebSockets for Arduino.
 *
 * Copyright 2017 karawin (http://www.karawin.fr)
*/

#ifndef __TELNET_H__
#define __TELNET_H__
// max size of the WS Message Header


#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
//#include "esp_common.h"
//#include "esp_softap.h"
#include "esp_wifi.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
//#include "ssl/ssl_crypto.h"
#include "cencode_inc.h"
#include "esp_system.h"

#define NBCLIENTT 5
//#define MAXDATAT	 256

//extern const char strtWELCOME[] ;
extern int telnetclients[NBCLIENTT];

// public:
// init some data
void telnetinit(void);
// a demand received, accept it
bool telnetAccept(int tsocket);
// a socket with a telnet . 
bool telnetnewclient(int socket);
// a socket with a telnet closed
void telnetremoveclient(int socket);
// is socket a telnet?
bool istelnet( int socket);

//write a txt data
void telnetWrite(uint32_t len,const char *fmt, ...);

int telnetRead(int tsocket);
// the telnet server task
void telnetTask(void* pvParams) ;

#endif