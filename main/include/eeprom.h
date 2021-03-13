/******************************************************************************
 * 
 * Copyright 2017 karawin (http://www.karawin.fr)
 *
*******************************************************************************/

#pragma once

#include "esp_system.h"
#include "audio_renderer.h"

//define for bit array options
#define T_THEME 	1
#define NT_THEME	0xFE
#define T_PATCH 	2
#define NT_PATCH	0xFD
#define T_LED		4
#define NT_LED		0xFB
#define T_LEDPOL	8
#define NT_LEDPOL	0xF7
#define T_LOGTEL	0x10
#define NT_LOGTEL	0xEF
#define T_WOLFSSL	0x60
#define NT_WOLFSSL	0x9F
#define S_WOLFSSL	0x5 //Shift right 
//define for bit array options32
#define T_DDMM		1
#define NT_DDMM		0xFE
#define T_ROTAT		2
#define NT_ROTAT	0xFD
#define T_ENC0		4
#define T_ENC1		8
#define NT_ENC0	0xFB
#define NT_ENC1	0xF7
#define T_WIFIAUTO	0x10
#define NT_WIFIAUTO 0xEF
#define T_TOGGLETIME  0x20
#define NT_TOGGLETIME 0xDF

#define APMODE		0
#define STA1		1
#define STA2		2
#define SSIDLEN		32
#define PASSLEN		64
#define HOSTLEN		24
#define USERAGLEN	38

struct device_settings {
	uint16_t cleared; 		// 0xAABB if initialized
	uint8_t dhcpEn1;
	uint8_t ipAddr1[4];
	uint8_t mask1[4];
	uint8_t gate1[4];
	uint8_t dhcpEn2;		
	uint8_t ipAddr2[4];		
	uint8_t mask2[4];		
	uint8_t gate2[4];			
	char ssid1[SSIDLEN]; 
	char ssid2[SSIDLEN]; 
	char pass1[PASSLEN];	
	char pass2[PASSLEN];	
	uint8_t current_ap; // 0 = AP mode, else STA mode: 1 = ssid1, 2 = ssid2
	uint8_t vol;
	int8_t treble;
	uint8_t bass;
	int8_t freqtreble;
	uint8_t freqbass;
	uint8_t spacial;
	uint16_t currentstation;  // 
	uint8_t autostart; // 0: stopped, 1: playing
	uint8_t i2sspeed; // 0 = 48kHz, 1 = 96kHz, 2 = 128kHz
	uint32_t uartspeed; // serial baud
	uint8_t options;  // bit0:0 theme ligth blue, 1 Dark brown, bit1: 0 patch load  1 no patch, bit2: O blink led  1 led on On play, bit3:led polarity 0 normal 1 reverse, bit 4: log syst on telnet, 
	// bit 3&4: log wolfssl  OFF(0)  ERROR&INFO(1) ENTER&LEAVE(2)  OTHER_LOG(3)
	char ua[USERAGLEN]; // user agent
	int8_t tzoffsetm; //timezone offset (minutes)
	int8_t tzoffseth; //timezone offset	(hour)
	uint32_t sleepValue; 	
	uint32_t wakeValue;	
// esp32
	output_mode_t audio_output_mode; // 
	uint8_t trace_level;
	uint8_t lcd_type; // the lcd in use
	uint8_t led_gpio; // the gpio of the led
	uint32_t filler;	// timeout in seconds to switch off the lcd. 0 = no timeout
	uint8_t options32;	// bit0:0 = MMDD, 1 = DDMM  in the time display, bit1: 0= lcd without rotation  1 = lcd rotated 180
						// bit 2: Half step of encoder0, bit3: Half step of encoder1, bit4: wifi auto reconnect
						// bit5: TOGGLE time or main sreen
	char hostname[HOSTLEN];
	uint32_t tp_calx;
	uint32_t tp_caly;

} Device_Settings;

struct shoutcast_info {
	char domain[73]; //url
	char file[116];  //path
	char name[64];
	int8_t ovol; // offset volume
	uint16_t port;	//port
};

extern struct device_settings* g_device;

void partitions_init(void);
void copyDeviceSettings();
void restoreDeviceSettings();
bool eeSetData(int address, void* buffer, int size);
bool eeSetData1(int address, void* buffer, int size);
void eeErasesettings(void);
void eeEraseAll();
void saveStation(struct shoutcast_info *station, uint16_t position);
void saveMultiStation(struct shoutcast_info *station, uint16_t position, uint8_t number);
void eeEraseStations(void);
struct shoutcast_info* getStation(uint8_t position);
void saveDeviceSettings(struct device_settings *settings);
void saveDeviceSettingsVolume(struct device_settings *settings);
struct device_settings* getDeviceSettings();
struct device_settings* getDeviceSettingsSilent();


// Protect: html page is password protected.
void setProtect(bool);
bool getProtect();