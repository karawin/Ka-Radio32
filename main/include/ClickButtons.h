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

#include "driver/gpio.h"
// ---Button defaults-------------------------------------------------------------
#define ENC_BUTTONINTERVAL    10  // check enc->button every x milliseconds, also debouce time
#define BTN_DOUBLECLICKTIME  600  // second click within 400ms
#define BTN_HOLDTIME        1000  // report held button after 1s

// ----------------------------------------------------------------------------




// 

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

  typedef struct {
  int8_t pinBTN[3];
  int8_t pinA;
  int8_t pinB;
  int8_t pinC;
  bool pinsActive;
  
  volatile Button button[3];
  bool doubleClickEnabled;
  bool buttonHeldEnabled;
  uint16_t keyDownTicks[3] ;
  uint16_t doubleClickTicks[3] ; 
  unsigned long lastButtonCheck[3];
  } Button_t;	  
  
  
  Button_t* ClickButtonsInit(int8_t A, int8_t B, int8_t C );
  void service(Button_t *enc); 
  int16_t getValue(Button_t *enc);
  Button getButton(Button_t *enc,uint8_t index);
  bool getPinState(Button_t *enc,uint8_t index);
  bool getpinsActive(Button_t *enc);
  


// ----------------------------------------------------------------------------

#endif // __have__ClickEncoder_h__
