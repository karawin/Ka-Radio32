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

#ifndef __have__ClickButton_h__
#define __have__ClickButton_h__

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
  int8_t pinBTN[3];
  bool expGpio;
  bool pinsActive;
  
  volatile Button button[3];
  bool doubleClickEnabled;
  bool buttonHeldEnabled;
  uint16_t keyDownTicks[3] ;
  uint16_t doubleClickTicks[3] ; 
//  unsigned long lastButtonCheck[3];
  } Button_t;	  
  
  
  Button_t* ClickButtonsInit(int8_t A, int8_t B, int8_t C , bool Active);
  Button_t* ClickexpButtonsInit(int8_t A, int8_t B, int8_t C , bool Active);
  void serviceBtn(Button_t *enc); 
  Button getButtons(Button_t *enc,uint8_t index);
  uint8_t i2c_keypad_read();
// ----------------------------------------------------------------------------
extern uint8_t rexp; // expansion ports for esplay
#endif // __have__ClickButton_h__
