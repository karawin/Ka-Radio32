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
void vTelnetWrite(uint32_t lenb,const char *fmt, va_list ap);

int telnetRead(int tsocket);
// the telnet server task
void telnetTask(void* pvParams) ;

extern void* kmalloc(size_t memorySize);
extern void* kcalloc(size_t elementCount, size_t elementSize);
#endif