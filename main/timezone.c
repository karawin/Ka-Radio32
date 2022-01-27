//////////////////////////////////////////////////
// Simple timezone example for ESP8266.
// Copyright 2015 Richard A Burton
// richardaburton@gmail.com
// See license.txt for license terms.
//////////////////////////////////////////////////
// Modified for KaraDio

// custom function to apply a timezone to the supplied tm struct
// hard coded rules

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "eeprom.h"

int8_t  applyTZ(struct tm *time) {

	bool dst = false;
	int8_t tzo = g_device->tzoffseth;
	if ((unsigned char)g_device->tzoffsetm == 0xFF) g_device->tzoffsetm = 0; // if not initialized
	int8_t tzom = g_device->tzoffsetm;
 
	// apply base timezone offset
//	time->tm_hour += 1; // e.g. central europe
	time->tm_min += tzom;
	time->tm_hour += tzo;

	// call mktime to fix up (needed if applying offset has rolled the date back/forward a day)
	// also sets yday and fixes wday (if it was wrong from the rtc)
	mktime(time);

	// work out if we should apply dst, modify according to your local rules
    if (time->tm_mon < 2 || time->tm_mon > 9) {
		// these months are completely out of DST
	} else if (time->tm_mon > 2 && time->tm_mon < 9) {
		// these months are completely in DST
		dst = true;
	} else {
		// else we must be in one of the change months
		// work out when the last sunday was (could be today)
		int previousSunday = time->tm_mday - time->tm_wday;
		if (time->tm_mon == 2) { // march
			// was last sunday (which could be today) the last sunday in march
			if (previousSunday >= 25) {
				// are we actually on the last sunday today
				if (time->tm_wday == 0) {
					// if so are we at/past 2am gmt
					int s = (time->tm_hour * 3600) + (time->tm_min * 60) + time->tm_sec;
					if (s >= 7200) dst = true;
				} else {
					dst = true;
				}
			}
		} else if (time->tm_mon == 9) {
			// was last sunday (which could be today) the last sunday in october
			if (previousSunday >= 25) {
				// we have reached/passed it, so is it today?
				if (time->tm_wday == 0) {
					// change day, so are we before 1am gmt (2am localtime)
					int s = (time->tm_hour * 3600) + (time->tm_min * 60) + time->tm_sec;
					if (s < 3600) dst = true;
				}
			} else {
				// not reached the last sunday yet
				dst = true;
			}
		}
	}

	if (dst) {
		// add the dst hour
		time->tm_hour += 1;
		// mktime will fix up the time/date if adding an hour has taken us to the next day
		mktime(time);
		// don't rely on isdst returned by mktime, it doesn't know about timezones and tends to reset this to 0
		time->tm_isdst = 1;
	} else {
		time->tm_isdst = 0;
	}
	return tzo;
}