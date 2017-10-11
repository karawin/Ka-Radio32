// ----------------------------------------------------------------------------
// Rotary Encoder Driver with Acceleration
// Supports Click, DoubleClick, Long Click
//
// (c) 2010 karl@pitrich.com
// (c) 2014 karl@pitrich.com
// 
// Timer-based rotary encoder logic by Peter Dannegger
// http://www.mikrocontroller.net/articles/Drehgeber
//
// Modified for ESP32 IDF
// (c) 2017 KaRadio
// ----------------------------------------------------------------------------

#ifndef __have__ClickEncoder_h__
#define __have__ClickEncoder_h__

// ---Button defaults-------------------------------------------------------------

#define BTN_DOUBLECLICKTIME  400  // second click within 400ms
#define BTN_HOLDTIME        1000  // report held button after 1s


// ----------------------------------------------------------------------------

#include <stdlib.h>
#include <stddef.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/gpio.h"


// ----------------------------------------------------------------------------

#define ENC_NORMAL        (1 << 1)   // use Peter Danneger's decoder
#define ENC_FLAKY         (1 << 2)   // use Table-based decoder

// ----------------------------------------------------------------------------

#ifndef ENC_DECODER
#  define ENC_DECODER     ENC_NORMAL
#endif

#if ENC_DECODER == ENC_FLAKY
#  ifndef ENC_HALFSTEP
#    define ENC_HALFSTEP  1        // use table for half step per default
#  endif
#endif

// ----------------------------------------------------------------------------


typedef gpio_mode_t pinMode_t;
#define INPUT	GPIO_MODE_INPUT
#define INPUT_PULLUP GPIO_MODE_INPUT
#define LOW 0
#define HIGH 1
#define digitalRead(x) gpio_get_level((gpio_num_t)x)

class ClickEncoder
{
public:
  typedef enum Button_e {
    Open = 0,
    Closed,
    
    Pressed,
    Held,
    Released,
    
    Clicked,
    DoubleClicked
    
  } Button;

public:
  ClickEncoder(int8_t A, int8_t B, int8_t BTN = -1, 
               uint8_t stepsPerNotch = 4, bool active = LOW);

  void service(void);  
  int16_t getValue(void);

public:
  Button getButton(void);

protected:
  int8_t pinA;
  int8_t pinB;
  int8_t pinBTN;
  bool pinsActive;
  volatile int16_t delta;
  volatile int16_t last;
  volatile uint8_t steps;
  volatile uint16_t acceleration;
  bool accelerationEnabled;
#if ENC_DECODER != ENC_NORMAL
  static const int8_t table[16];
#endif
  volatile Button button;
  bool doubleClickEnabled;
  bool buttonHeldEnabled;
  bool buttonOnPinZeroEnabled = false;
  uint16_t keyDownTicks = 0;
  uint16_t doubleClickTicks = 0;
  uint16_t buttonHoldTime = BTN_HOLDTIME;
  uint16_t buttonDoubleClickTime = BTN_DOUBLECLICKTIME;
  unsigned long lastButtonCheck = 0;
  bool getPinState();


public:
  void setDoubleClickTime(uint16_t durationMilliseconds)
  {
    buttonDoubleClickTime = durationMilliseconds;
  }
  
public:
  void setHoldTime(uint16_t durationMilliseconds)
  {
    buttonHoldTime = durationMilliseconds;
  }
  
public:
  void setDoubleClickEnabled(const bool &d)
  {
    doubleClickEnabled = d;
  }

  bool getDoubleClickEnabled()
  {
    return doubleClickEnabled;
  }
  
public:
  void setButtonHeldEnabled(const bool &d)
  {
    buttonHeldEnabled = d;
  }

  bool getButtonHeldEnabled()
  {
    return buttonHeldEnabled;
  }
  
public:
  void setButtonOnPinZeroEnabled(const bool &d)
  {
    buttonOnPinZeroEnabled = d;
  }

  bool getButtonOnPinZeroEnabled()
  {
    return buttonOnPinZeroEnabled;
  }


public:
  void setAccelerationEnabled(const bool &a)
  {
    accelerationEnabled = a;
    if (accelerationEnabled == false) {
      acceleration = 0;
    }
  }

  bool getAccelerationEnabled() 
  {
    return accelerationEnabled;
  }

};

class DigitalButton : public ClickEncoder
{ 
  public:
    explicit DigitalButton(int8_t BTN, bool active = false);  // Constructor for using a button only
};


// ----------------------------------------------------------------------------

#endif // __have__ClickEncoder_h__
