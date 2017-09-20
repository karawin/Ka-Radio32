/*
 * Copyright 2016 karawin (http://www.karawin.fr)
*/
#pragma once

#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

#include "esp_system.h"
#include "webclient.h"
#include "vs1053.h"

#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "flash.h"
#include "eeprom.h"
#include "interface.h"
#include "websocket.h"
#include "driver/timer.h"


#define TIMER_DIVIDER 16 
#define TIMERGROUP TIMER_GROUP_0 
#define TIMERVALUE(x) (x*5000000 -7)
#define sleepTimer  TIMER_0
#define wakeTimer TIMER_1

//extern os_timer_t sleepTimer;
extern uint32_t sleepDelay;
//extern os_timer_t wakeTimer;
extern uint32_t wakeDelay;
extern xSemaphoreHandle semclient;
extern xSemaphoreHandle semfile;

//void serverTask(void *pvParams);
extern int8_t clientOvol ;
extern uint8_t clientIvol ;
void sleepCallback(void *pArg);
void wakeCallback(void *pArg);
void startSleep(uint32_t delay);
void stopSleep();
void stopWake();
void serverclientTask(void *pvParams);
void playStationInt(int sid);
void websockethandle(int socket, wsopcode_t opcode, uint8_t * payload, size_t length);

#endif