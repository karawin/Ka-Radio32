/*
 * Copyright 2016 karawin (http://www.karawin.fr)
*/
#pragma once

#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "websocket.h"

extern xSemaphoreHandle semclient;
extern xSemaphoreHandle semfile;

void serverclientTask(void *pvParams);
void playStationInt(int sid);
void websockethandle(int socket, wsopcode_t opcode, uint8_t * payload, size_t length);
uint16_t getVolume(void);
void setVolume(char* vol);
void setVolumei(int16_t vol);
void setRelVolume(int8_t vol);

#endif