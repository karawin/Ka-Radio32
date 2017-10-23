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

#define BTN_DOUBLECLICKTIME  400  // second click within 400ms
#define BTN_HOLDTIME        1000  // report held button after 1s


// ----------------------------------------------------------------------------




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

  void ClickEncoderInit(int8_t A, int8_t B, int8_t BTN );
  void (*serviceEncoder)();
  void service(void); 
  int16_t getValue(void);
  Button getButton(void);
  bool getPinState();
  bool getpinsActive();
  


// ----------------------------------------------------------------------------

#endif // __have__ClickEncoder_h__
