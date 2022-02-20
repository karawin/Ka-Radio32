// ----------------------------------------------------------------------------
// Rotary Encoder Driver with enc->acceleration
// Supports Click, DoubleClick, Long Click
//
// (c) 2010 karl@pitrich.com
// (c) 2014 karl@pitrich.com
// 
// Timer-based rotary encoder logic by Peter Dannegger
// http://www.mikrocontroller.net/articles/Drehgeber
// ----------------------------------------------------------------------------
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include "ClickJoystick.h"
#include "app_main.h"
#include "gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

// ----------------------------------------------------------------------------

#define TAG "ClickJoystick"
 void getJoyStates(Joystick_t *enc, bool *ps); 
// ----------------------------------------------------------------------------

//bool getpinsActives(Joystick_t *enc) {return enc->pinsActive;}

Joystick_t* ClickJoystickInit(int8_t A)
{
	Joystick_t* enc = kmalloc(sizeof(Joystick_t));
	if (enc == NULL) return enc;
	enc->channel = gpioToChannel(A); 
	ESP_LOGD(TAG,"Joystick Channel: %i",enc->channel);
	if (enc->channel != GPIO_NONE)
	{
		adc1_config_width(ADC_WIDTH_BIT_12);
		adc1_config_channel_atten(enc->channel, ADC_ATTEN_DB_11);
	}
	
	enc->pinsActive = HIGH; 
	for (int i=0;i<NBBUTTONS;i++)
	{
		enc->button[i] = Open;
		enc->keyDownTicks[i] = 0;
		enc->doubleClickTicks[i] = 0;
//		enc->lastButtonCheck[i] = 0;
	}
	enc->doubleClickEnabled = true; enc->buttonHeldEnabled = true;

  return enc;
}

// ----------------------------------------------------------------------------
// call this every 1 millisecond via timer ISR
//
//void (*serviceEncoder)() = NULL;
IRAM_ATTR void serviceJoystick(Joystick_t *enc)
{
  // handle enc->button
  //
//  unsigned long currentMillis = xTaskGetTickCount()* portTICK_PERIOD_MS;
  bool pinRead[NBBUTTONS];
  getJoyStates(enc, pinRead);
  for(uint8_t i = 0; i < NBBUTTONS; i++) 
  {
//	if (currentMillis < enc->lastButtonCheck[i]) enc->lastButtonCheck[i] = 0;        // Handle case when millis() wraps back around to zero
//	if (((currentMillis - enc->lastButtonCheck[i]) >= ENC_BUTTONINTERVAL))            // checking enc->button is sufficient every 10-30ms
	{ 
//		enc->lastButtonCheck[i] = currentMillis;
   
		if (pinRead[i] == true) { // key is down
			enc->keyDownTicks[i]++;
			if ((enc->keyDownTicks[i] > (BTN_HOLDTIME / ENC_BUTTONINTERVAL)) && (enc->buttonHeldEnabled)) 
			{
				enc->button[i] = Held;
			}
		}

		if (pinRead[i] == false) { // key is now up
			if (enc->keyDownTicks[i] > 1) {               //Make sure key was down through 1 complete tick to prevent random transients from registering as click
			if (enc->button[i] == Held) {
				enc->button[i] = Released;
				enc->doubleClickTicks[i] = 0;
			}
			else {
				#define ENC_SINGLECLICKONLY 1
				if (enc->doubleClickTicks[i] > ENC_SINGLECLICKONLY) {   // prevent trigger in single click mode
					if (enc->doubleClickTicks[i] < (BTN_DOUBLECLICKTIME / ENC_BUTTONINTERVAL)) {
					enc->button[i] = DoubleClicked;
					enc->doubleClickTicks[i] = 0;
					}
				}
				else {
					enc->doubleClickTicks[i] = (enc->doubleClickEnabled) ? (BTN_DOUBLECLICKTIME / ENC_BUTTONINTERVAL) : ENC_SINGLECLICKONLY;
				}
				}
			}
			enc->keyDownTicks[i] = 0;
		}
  
		if (enc->doubleClickTicks[i] > 0) {
			enc->doubleClickTicks[i]--;
			if (enc->doubleClickTicks[i] == 0) {
				enc->button[i] = Clicked;
			}
		}
	}
  }
}

// ----------------------------------------------------------------------------
Button getJoystick(Joystick_t *enc,uint8_t index)
{
  noInterrupts();
  Button ret = enc->button[index];
  if (ret != Open) ESP_LOGD(TAG,"getJoystick %d = %d",index,ret);
  if (enc->button[index] != Held && ret != Open) {
    enc->button [index]= Open; // reset
  }
  interrupts();
  return ret;
}



void getJoyStates(Joystick_t *enc, bool *ps) {
  {
	uint32_t voltage;
	adc1_channel_t  chan = enc->channel;
 //   pinState = digitalRead(enc->pinBTN[index]);
	voltage = (adc1_get_raw(chan)+adc1_get_raw(chan))/2;
//	voltage = (voltage)*110/(409);
	if (voltage < 1000) {ps[0] = false; ps[1] = false;} 
	if (voltage >3000) {ps[0] = true; ps[1] = false;} 
	if ((voltage >= 1000)&&(voltage <= 3000)) {ps[0] = false; ps[1] = true;} 	
  }
}

  

