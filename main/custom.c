/******************************************************************************
 * 
 * Copyright 2018 karawin (http://www.karawin.fr)
 *
 *
 * This file contain empty functions definition on the standard delivery
*******************************************************************************/
#include "driver/gpio.h"
#include "gpio.h"
#include "custom.h"

//#define gpioLedBacklight 5
gpio_num_t lcdb;
// LedBacklight control a gpio to switch on or off the lcd backlight 
// in addition of the sys.lcdout("x")  configuration for system with battries.
// added by Vadim Polyakovsky 
// Schematic on the KaRadio facebook group:
// https://www.facebook.com/photo.php?fbid=1971836752872801&set=p.1971836752872801&type=3&ifg=1
void LedBacklightInit()
{
	gpio_get_lcd_backlightl(&lcdb);
	if (lcdb != GPIO_NONE)
	{
		gpio_output_conf(lcdb);
		gpio_set_level(lcdb,1);
	}
}	 
 
void LedBacklightOn() 
{
	if (lcdb != GPIO_NONE)
		gpio_set_level(lcdb,1);
}	 
 
void  LedBacklightOff() 
{
	if (lcdb != GPIO_NONE)
		gpio_set_level(lcdb,0);
}	 
