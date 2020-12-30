/******************************************************************************
 * 
 * Copyright 2018 karawin (http://www.karawin.fr)
 *
 *
 * This file contain empty functions definition on the standard delivery
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "driver/gpio.h"
#include "gpio.h"
#include "custom.h"
#include "driver/ledc.h"
/**********************
 *  STATIC VARIABLES
 **********************/
static const int DUTY_MAX = 0x1fff;
static const int LCD_BACKLIGHT_ON_VALUE = 1;

//#define gpioLedBacklight 5
gpio_num_t lcdb;
// LedBacklight control a gpio to switch on or off the lcd backlight 
// in addition of the sys.lcdout("x")  configuration for system with battries.
// added by Vadim Polyakovsky 
// Schematic on the KaRadio facebook group:
// https://www.facebook.com/photo.php?fbid=1971836752872801&set=p.1971836752872801&type=3&ifg=1
 
	 
static void backlight_init()
{
	//configure timer0
	ledc_timer_config_t ledc_timer;
	memset(&ledc_timer, 0, sizeof(ledc_timer));

	ledc_timer.duty_resolution = LEDC_TIMER_13_BIT; //set timer counter bit number
	ledc_timer.freq_hz = 5000;						//set frequency of pwm
	ledc_timer.speed_mode = LEDC_LOW_SPEED_MODE;	//timer mode,
	ledc_timer.timer_num = LEDC_TIMER_0;			//timer index

	ledc_timer_config(&ledc_timer);

	//set the configuration
	ledc_channel_config_t ledc_channel;
	memset(&ledc_channel, 0, sizeof(ledc_channel));

	//set LEDC channel 0
	ledc_channel.channel = LEDC_CHANNEL_0;
	//set the duty for initialization.(duty range is 0 ~ ((2**duty_resolution)-1)
	ledc_channel.duty = (LCD_BACKLIGHT_ON_VALUE) ? 0 : DUTY_MAX;
	//GPIO number
	ledc_channel.gpio_num = lcdb;
	//GPIO INTR TYPE, as an example, we enable fade_end interrupt here.
	ledc_channel.intr_type = LEDC_INTR_FADE_END;
	//set LEDC mode, from ledc_mode_t
	ledc_channel.speed_mode = LEDC_LOW_SPEED_MODE;
	//set LEDC timer source, if different channel use one timer,
	//the frequency and duty_resolution of these channels should be the same
	ledc_channel.timer_sel = LEDC_TIMER_0;

	ledc_channel_config(&ledc_channel);

	//initialize fade service.
	ledc_fade_func_install(0);

	// duty range is 0 ~ ((2**duty_resolution)-1)
	ledc_set_fade_with_time(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, (LCD_BACKLIGHT_ON_VALUE) ? DUTY_MAX : 0, 500);
	ledc_fade_start(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, LEDC_FADE_NO_WAIT);
	
}

void backlight_percentage_set(int value)
{
	if (lcdb != GPIO_NONE)
	{
		if (value > 100) value = 100;
		int duty = DUTY_MAX * (value * 0.01f);
//		printf("backlight_percentage_set  %d\n",value);
		ledc_set_fade_with_time(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty, 20);
		ledc_fade_start(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, LEDC_FADE_WAIT_DONE);
	}
}


void LedBacklightInit()
{
	gpio_get_lcd_backlightl(&lcdb);
	if (lcdb != GPIO_NONE)
	{
		gpio_output_conf(lcdb);
		gpio_set_level(lcdb,1);
		backlight_init();		
	}
}	 
bool LedBacklightOn(int blv) 
{
	if (lcdb != GPIO_NONE)
	{
	//		gpio_set_level(lcdb,1);
		// duty range is 0 ~ ((2**duty_resolution)-1)
		ledc_set_fade_with_time(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, (LCD_BACKLIGHT_ON_VALUE) ?(DUTY_MAX * (blv * 0.01f)) : 0, 500);
		ledc_fade_start(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, LEDC_FADE_WAIT_DONE);
		return true;
	}
	return false;
}	 
 
bool  LedBacklightOff() 
{
	if (lcdb != GPIO_NONE)
	{
	//		gpio_set_level(lcdb,0);
		// duty range is 0 ~ ((2**duty_resolution)-1)
		ledc_set_fade_with_time(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, (LCD_BACKLIGHT_ON_VALUE) ? 0:DUTY_MAX , 500);
		ledc_fade_start(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, LEDC_FADE_WAIT_DONE);
		return true;
	}
	return false;
}