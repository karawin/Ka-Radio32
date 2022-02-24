/******************************************************************************
 * 
 * Copyright 2018 karawin (http://www.karawin.fr)
 *
*******************************************************************************/
#ifndef INTERFACE_H
#define INTERFACE_H
#include "esp_log.h"
#include "telnet.h"
#include "addon.h"

// need this for ported soft to esp32
#define ESP32_IDF

#define PSTR(s) (s)
#define MAXDATAT	 256


#define RELEASE "2.3"
#define REVISION "0"

uint32_t checkUart(uint32_t speed);
extern unsigned short adcdiv;	
void switchCommand(void );
void checkCommand(int size, char* s);
esp_log_level_t getLogLevel();
void setLogLevel(esp_log_level_t level);
void wifiConnectMem();
char* webInfo();
char* webList(int id);
uint16_t getCurrentStation();
void setCurrentStation( uint16_t vol);
void clientVol(char *s);
uint8_t getLedGpio();
void setLedGpio(uint8_t val);
uint32_t getLcdOut();
uint32_t getLcdStop();
bool getAutoWifi(void);
void setAutoWifi();
int8_t get_rssi(void);
void fmSeekUp();
void fmSeekDown();
void fmVol(char* tmp);
void fmMute();
void fmUnmute();
void setDdmm(uint8_t dm);
uint8_t getDdmm();
void setRotat(uint8_t dm);
uint8_t getRotat();
void setHostname(char* s);

#define kprintf(fmt, ...) do {    \
		telnetWrite(printf(fmt, ##__VA_ARGS__),fmt, ##__VA_ARGS__); \
		addonParse(fmt, ##__VA_ARGS__);\
	} while (0)



void lkprintf(const char *format, va_list ap);
	
#endif
		