
#ifndef INTERFACE_H
#define INTERFACE_H

#include "telnet.h"

//#define PROGMEM   ICACHE_RODATA_ATTR
#define PSTR(s) (s)
#define MAXDATAT	 256


#define RELEASE "0.1"
#define REVISION "0"

uint32_t checkUart(uint32_t speed);
extern unsigned short adcdiv;	
void switchCommand(void );
void checkCommand(int size, char* s);
void wifiConnectMem();
char* webInfo();
char* webList(int id);


#define kprintf(fmt, ...) do {    \
        printf(fmt, ##__VA_ARGS__);   \
		telnetWrite(2*MAXDATAT,fmt, ##__VA_ARGS__); \
	} while (0)
		
#define kprintfl(fmt, ...) do {    \
        printf(fmt, ##__VA_ARGS__);   \
		telnetWrite(1024,fmt, ##__VA_ARGS__); \
	} while (0)
		
#endif
		