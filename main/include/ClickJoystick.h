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
// Modified for  IDF
// (c) 2019 KaRadio
// ----------------------------------------------------------------------------

#ifndef __have__ClickJoystick_h__
#define __have__ClickJoystick_h__

#include "driver/gpio.h"
#include "esp_adc_cal.h"

// ---Button defaults-------------------------------------------------------------
#define ENC_BUTTONINTERVAL    10  // check enc->button every x milliseconds, also debouce time
#define BTN_DOUBLECLICKTIME  600  // second click within 400ms
#define BTN_HOLDTIME        1000  // report held button after 1s

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
typedef gpio_mode_t pinMode_t;
#undef INPUT
#define INPUT	GPIO_MODE_INPUT
#undef INPUT_PULLUP
#define INPUT_PULLUP GPIO_MODE_INPUT
#undef LOW
#define LOW 0
#undef HIGH
#define HIGH 1
#undef MIDDLE
#define MIDDLE 2
#define digitalRead(x) gpio_get_level((gpio_num_t)x)
#define NBBUTTONS	2

#ifndef __have__ClickEncoder_h__
  typedef enum Buttons_e {
    Open = 0,
    Closed,    
    Pressed,
    Held,
    Released,   
    Clicked,
    DoubleClicked   
  } Button;
#endif

  typedef struct {
//  int8_t pinBTN;
  adc1_channel_t  channel ;
  
  bool pinsActive;
  
  volatile Button button[NBBUTTONS];
  bool doubleClickEnabled;
  bool buttonHeldEnabled;
  uint16_t keyDownTicks[NBBUTTONS] ;
  uint16_t doubleClickTicks[NBBUTTONS] ; 
//  unsigned long lastButtonCheck[NBBUTTONS];
  } Joystick_t;	  
  
  
  Joystick_t* ClickJoystickInit(int8_t A );
  void serviceJoystick(Joystick_t *enc); 
  Button getJoystick(Joystick_t *enc,uint8_t index);
  


// ----------------------------------------------------------------------------

#endif // __have__ClickJoystick_h__
