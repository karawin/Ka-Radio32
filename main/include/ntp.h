//////////////////////////////////////////////////
// Simple NTP client for ESP8266.
// Copyright 2016 jp cocatrix (KaraWin)
// jp@karawin.fr
// See license.txt for license terms.
//////////////////////////////////////////////////

#ifndef __NTP_H__
#define __NTP_H__
#include <time.h>

typedef struct {
	uint8_t options;
	uint8_t stratum;
	uint8_t poll;
	uint8_t precision;
	uint32_t root_delay;
	uint32_t root_disp;
	uint32_t ref_id;
	uint8_t ref_time[8];
	uint8_t orig_time[8];
	uint8_t recv_time[8];
	uint8_t trans_time[8];
} ntp_t;

//void ntpTask(void *pvParams);

// print locale date time in ISO-8601 local time
bool ntp_get_time(struct tm **dt);
void ntp_print_time();
int8_t  applyTZ(struct tm *time);
extern void* kmalloc(size_t memorySize);
extern void* kcalloc(size_t elementCount, size_t elementSize);
#endif