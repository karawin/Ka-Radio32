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
#include "ClickEncoder.h"
#include "app_main.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



// ----------------------------------------------------------------------------
// enc->button configuration (values for 1ms timer service calls)
//
#define ENC_BUTTONINTERVAL    10  // check enc->button every x milliseconds, also debouce time

// ----------------------------------------------------------------------------
// enc->acceleration configuration (for 1000Hz calls to ::service())
//
#define ENC_ACCEL_TOP      3072   // max. enc->acceleration: *12 (val >> 8)
#define ENC_ACCEL_INC        25
#define ENC_ACCEL_DEC         2

// ----------------------------------------------------------------------------
/*
  int8_t enc->pinA;
  int8_t enc->pinB;
  int8_t enc->pinBTN;
  bool enc->pinsActive;
  volatile int16_t enc->delta;
  volatile int16_t enc->last;
  volatile uint8_t enc->steps;
  volatile uint16_t enc->acceleration;
  bool enc->accelerationEnabled;
  volatile enc->button enc->button;
  bool enc->doubleClickEnabled;
  bool buttonHeldEnabled;
  bool enc->buttonOnPinZeroEnabled = false;
  uint16_t enc->keyDownTicks = 0;
  uint16_t enc->doubleClickTicks = 0;
  uint16_t buttonHoldTime = BTN_HOLDTIME;
  uint16_t buttonDoubleClickTime = BTN_DOUBLECLICKTIME;
  unsigned long enc->lastButtonCheck = 0;
*/


#define TAG "ClickEncoder"



void noInterrupts()
{noInterrupt1Ms();}

void interrupts()
{interrupt1Ms();}


// ----------------------------------------------------------------------------

bool getpinsActive(Encoder_t *enc) {return enc->pinsActive;}

Encoder_t* ClickEncoderInit(int8_t A, int8_t B, int8_t BTN)
{
	
	Encoder_t* enc = malloc(sizeof(Encoder_t));
	enc->pinA = A; enc->pinB = B; enc->pinBTN = BTN;
	enc->pinsActive = LOW; enc->delta = 0; enc->last = 0; enc->steps = 4; 
	enc->accelerationEnabled = true; enc->button = Open;
	enc->doubleClickEnabled = true; enc->buttonHeldEnabled = true;

	enc->buttonOnPinZeroEnabled = false;
	enc->keyDownTicks = 0;
	enc->doubleClickTicks = 0;
	enc->buttonHoldTime = BTN_HOLDTIME;
	enc->buttonDoubleClickTime = BTN_DOUBLECLICKTIME;
	enc->lastButtonCheck = 0;
	
	gpio_config_t gpio_conf;
	gpio_conf.mode = GPIO_MODE_INPUT;
	gpio_conf.pull_up_en =  (enc->pinsActive == LOW) ?GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE;
	gpio_conf.pull_down_en = (enc->pinsActive == LOW) ?GPIO_PULLDOWN_DISABLE : GPIO_PULLDOWN_ENABLE;
	gpio_conf.intr_type = GPIO_INTR_DISABLE;
	
  if (enc->pinA >= 0) 
  {
	gpio_conf.pin_bit_mask = BIT(enc->pinA);
	ESP_ERROR_CHECK(gpio_config(&gpio_conf));
  }
  if (enc->pinB >= 0) 
  {
	gpio_conf.pin_bit_mask = BIT(enc->pinB);
	ESP_ERROR_CHECK(gpio_config(&gpio_conf));
  }
  if (enc->pinBTN >= 0) 
  {
	gpio_conf.pin_bit_mask = BIT(enc->pinBTN);
	ESP_ERROR_CHECK(gpio_config(&gpio_conf));
  }

  
  if (digitalRead(enc->pinA) == enc->pinsActive) {
    enc->last = 3;
  }

  if (digitalRead(enc->pinB) == enc->pinsActive) {
    enc->last ^=1;
  }
  return enc;
}

// ----------------------------------------------------------------------------
// call this every 1 millisecond via timer ISR
//
//void (*serviceEncoder)() = NULL;
void service(Encoder_t *enc)
{
  bool moved = false;
  int8_t curr = 0;

  if (enc->pinA >= 0 && enc->pinB >= 0) {
  if (enc->accelerationEnabled) { // decelerate every tick
    enc->acceleration -= ENC_ACCEL_DEC;
    if (enc->acceleration & 0x8000) { // handle overflow of MSB is set
      enc->acceleration = 0;
    }
  }

  if (digitalRead(enc->pinA) == enc->pinsActive) {
    curr = 3;
  }

  if (digitalRead(enc->pinB) == enc->pinsActive) {
    curr ^= 1;
  }
  
  int8_t diff = enc->last - curr;
  if (diff & 1) {            // bit 0 = step
    enc->last = curr;
    enc->delta += (diff & 2) - 1; // bit 1 = direction (+/-)
    moved = true;    
  }

  if (enc->accelerationEnabled && moved) {
    // increment accelerator if encoder has been moved
    if (enc->acceleration <= (ENC_ACCEL_TOP - ENC_ACCEL_INC)) {
      enc->acceleration += ENC_ACCEL_INC;
    }
  }
}
  // handle enc->button
  //
  unsigned long currentMillis = xTaskGetTickCount()* portTICK_PERIOD_MS;
  if (currentMillis < enc->lastButtonCheck) enc->lastButtonCheck = 0;        // Handle case when millis() wraps back around to zero
  if ((enc->pinBTN > 0 || (enc->pinBTN == 0 && enc->buttonOnPinZeroEnabled))        // check enc->button only, if a pin has been provided
      && ((currentMillis - enc->lastButtonCheck) >= ENC_BUTTONINTERVAL))            // checking enc->button is sufficient every 10-30ms
  { 
    enc->lastButtonCheck = currentMillis;

    bool pinRead = getPinState(enc);
    
    if (pinRead == enc->pinsActive) { // key is down
      enc->keyDownTicks++;
      if ((enc->keyDownTicks > (enc->buttonHoldTime / ENC_BUTTONINTERVAL)) && (enc->buttonHeldEnabled)) {
        enc->button = Held;
      }
    }

    if (pinRead == !enc->pinsActive) { // key is now up
      if (enc->keyDownTicks > 1) {               //Make sure key was down through 1 complete tick to prevent random transients from registering as click
        if (enc->button == Held) {
          enc->button = Released;
          enc->doubleClickTicks = 0;
        }
        else {
          #define ENC_SINGLECLICKONLY 1
          if (enc->doubleClickTicks > ENC_SINGLECLICKONLY) {   // prevent trigger in single click mode
            if (enc->doubleClickTicks < (enc->buttonDoubleClickTime / ENC_BUTTONINTERVAL)) {
              enc->button = DoubleClicked;
              enc->doubleClickTicks = 0;
            }
          }
          else {
            enc->doubleClickTicks = (enc->doubleClickEnabled) ? (enc->buttonDoubleClickTime / ENC_BUTTONINTERVAL) : ENC_SINGLECLICKONLY;
          }
        }
      }

      enc->keyDownTicks = 0;
    }
  
    if (enc->doubleClickTicks > 0) {
      enc->doubleClickTicks--;
      if (enc->doubleClickTicks == 0) {
        enc->button = Clicked;
      }
    }
  }
}

// ----------------------------------------------------------------------------

int16_t getValue(Encoder_t *enc)
{
  int16_t val;
  
  noInterrupts();
  val = enc->delta;

  if (enc->steps == 2) enc->delta = val & 1;
  else if (enc->steps == 4) enc->delta = val & 3;
  else enc->delta = 0; // default to 1 step per notch

  if (enc->steps == 4) val >>= 2;
  if (enc->steps == 2) val >>= 1;

  int16_t r = 0;
  int16_t accel = ((enc->accelerationEnabled) ? (enc->acceleration >> 8) : 0);

  if (val < 0) {
    r -= 1 + accel;
  }
  else if (val > 0) {
    r += 1 + accel;
  }
  interrupts();

  return r;
}

// ----------------------------------------------------------------------------
Button getButton(Encoder_t *enc)
{
  noInterrupts();
  Button ret = enc->button;
  if (enc->button != Held && ret != Open) {
    enc->button = Open; // reset
  }
  interrupts();

  return ret;
}



bool getPinState(Encoder_t *enc) {
  bool pinState;
  {
    pinState = digitalRead(enc->pinBTN);
  }
  return pinState;
}

  

