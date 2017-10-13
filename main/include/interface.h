
#ifndef INTERFACE_H
#define INTERFACE_H
#include "esp_log.h"
#include "telnet.h"
#include "ota.h"

// need this for ported soft to esp32
#define ESP32_IDF

#define PSTR(s) (s)
#define MAXDATAT	 256


#define RELEASE "0.3"
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


#define kprintf(fmt, ...) do {    \
        printf(fmt, ##__VA_ARGS__);   \
		telnetWrite(2*MAXDATAT,fmt, ##__VA_ARGS__); \
	} while (0)
		
#define kprintfl(fmt, ...) do {    \
        printf(fmt, ##__VA_ARGS__);   \
		telnetWrite(1024,fmt, ##__VA_ARGS__); \
	} while (0)
		
#endif
		