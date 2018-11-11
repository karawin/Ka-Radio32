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

#ifndef __have__ClickButtons_h__
#define __have__ClickButtons_h__

#include "driver/gpio.h"
// ---Button defaults-------------------------------------------------------------

#define BTN_DOUBLECLICKTIME  400  // second click within 400ms
#define BTN_HOLDTIME        1000  // report held button after 1s

#undef LOW
#define LOW 0
#undef HIGH
#define HIGH 1
#define digitalRead(x) gpio_get_level((gpio_num_t)x)

  typedef enum Button_e {
    Open = 0,
    Closed,    
    Pressed,
    Held,
    Released,   
    Clicked,
    DoubleClicked   
  } Button;

  void ClickEncoderInit(int8_t A, int8_t B, int8_t BTN );
  void (*serviceEncoder)();
  void service(void); 
  Button getButton(uint8_t index);
  bool getPinState(uint8_t index);
  bool getpinsActive();
  


// ----------------------------------------------------------------------------

#endif // __have__ClickButtons_h__