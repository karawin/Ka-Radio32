// ----------------------------------------------------------------------------
// Rotary Encoder Driver with Acceleration
// Supports Click, DoubleClick, Long Click
//
// (c) 2010 karl@pitrich.com
// (c) 2014 karl@pitrich.com
// 
// Timer-based rotary encoder logic by Peter Dannegger
// http://www.mikrocontroller.net/articles/Drehgeber
// ----------------------------------------------------------------------------

#include "ClickEncoder.h"
#include "app_main.h"
#include "gpio.h"
#include "webclient.h"
#include "webserver.h"

// ----------------------------------------------------------------------------
// Button configuration (values for 1ms timer service calls)
//
#define ENC_BUTTONINTERVAL    10  // check button every x milliseconds, also debouce time

// ----------------------------------------------------------------------------
// Acceleration configuration (for 1000Hz calls to ::service())
//
#define ENC_ACCEL_TOP      3072   // max. acceleration: *12 (val >> 8)
#define ENC_ACCEL_INC        25
#define ENC_ACCEL_DEC         2

// ----------------------------------------------------------------------------

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





void noInterrupts()
{noInterrupt1Ms();}

void interrupts()
{interrupt1Ms();}


#if ENC_DECODER != ENC_NORMAL
#  if ENC_HALFSTEP
     // decoding table for hardware with flaky notch (half resolution)
     const int8_t ClickEncoder::table[16] __attribute__((__progmem__)) = { 
       0, 0, -1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, -1, 0, 0 
     };    
#  else
     // decoding table for normal hardware
     const int8_t ClickEncoder::table[16] __attribute__((__progmem__)) = { 
       0, 1, -1, 0, -1, 0, 0, 1, 1, 0, 0, -1, 0, -1, 1, 0 
     };    
#  endif
#endif

// ----------------------------------------------------------------------------

void ClickEncoderInit(int8_t A, int8_t B, int8_t BTN)
{
	pinA = A; pinB = B; pinBTN = BTN;
	pinsActive = LOW; delta = 0; last = 0; steps = 4; accelerationEnabled = true; button = Open;
	doubleClickEnabled = true; buttonHeldEnabled = true;
	
	gpio_config_t gpio_conf;
	gpio_conf.mode = GPIO_MODE_INPUT;
	gpio_conf.pull_up_en =  (pinsActive == LOW) ?GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE;
	gpio_conf.pull_down_en =  GPIO_PULLDOWN_DISABLE;
	gpio_conf.intr_type = GPIO_INTR_DISABLE;
	
  if (pinA >= 0) 
  {
	gpio_conf.pin_bit_mask = BIT(pinA);
	ESP_ERROR_CHECK(gpio_config(&gpio_conf));
  }
  if (pinB >= 0) 
  {
	gpio_conf.pin_bit_mask = BIT(pinB);
	ESP_ERROR_CHECK(gpio_config(&gpio_conf));
  }
  if (pinBTN >= 0) 
  {
	gpio_conf.pin_bit_mask = BIT(pinBTN);
	ESP_ERROR_CHECK(gpio_config(&gpio_conf));
  }

  
  if (digitalRead(pinA) == pinsActive) {
    last = 3;
  }

  if (digitalRead(pinB) == pinsActive) {
    last ^=1;
  }
}

// ----------------------------------------------------------------------------
// call this every 1 millisecond via timer ISR
//
void (*serviceEncoder)() = NULL;
void service(void)
{
  bool moved = false;

  if (pinA >= 0 && pinB >= 0) {
  if (accelerationEnabled) { // decelerate every tick
    acceleration -= ENC_ACCEL_DEC;
    if (acceleration & 0x8000) { // handle overflow of MSB is set
      acceleration = 0;
    }
  }

#if ENC_DECODER == ENC_FLAKY
  last = (last << 2) & 0x0F;

  if (digitalRead(pinA) == pinsActive) {
    last |= 2;
  }

  if (digitalRead(pinB) == pinsActive) {
    last |= 1;
  }

  int8_t tbl = pgm_read_byte(&table[last]); 
  if (tbl) {
    delta += tbl;
    moved = true;
  }
#elif ENC_DECODER == ENC_NORMAL
  int8_t curr = 0;

  if (digitalRead(pinA) == pinsActive) {
    curr = 3;
  }

  if (digitalRead(pinB) == pinsActive) {
    curr ^= 1;
  }
  
  int8_t diff = last - curr;

  if (diff & 1) {            // bit 0 = step
    last = curr;
    delta += (diff & 2) - 1; // bit 1 = direction (+/-)
    moved = true;    
  }
#else
# error "Error: define ENC_DECODER to ENC_NORMAL or ENC_FLAKY"
#endif

  if (accelerationEnabled && moved) {
    // increment accelerator if encoder has been moved
    if (acceleration <= (ENC_ACCEL_TOP - ENC_ACCEL_INC)) {
      acceleration += ENC_ACCEL_INC;
    }
  }
}
  // handle button
  //
  unsigned long currentMillis = xTaskGetTickCount();
  if (currentMillis < lastButtonCheck) lastButtonCheck = 0;        // Handle case when millis() wraps back around to zero
  if ((pinBTN > 0 || (pinBTN == 0 && buttonOnPinZeroEnabled))        // check button only, if a pin has been provided
      && ((currentMillis - lastButtonCheck) >= ENC_BUTTONINTERVAL))            // checking button is sufficient every 10-30ms
  { 
    lastButtonCheck = currentMillis;

    bool pinRead = getPinState();
    
    if (pinRead == pinsActive) { // key is down
      keyDownTicks++;
      if ((keyDownTicks > (buttonHoldTime / ENC_BUTTONINTERVAL)) && (buttonHeldEnabled)) {
        button = Held;
      }
    }

    if (pinRead == !pinsActive) { // key is now up
      if (keyDownTicks > 1) {               //Make sure key was down through 1 complete tick to prevent random transients from registering as click
        if (button == Held) {
          button = Released;
          doubleClickTicks = 0;
        }
        else {
          #define ENC_SINGLECLICKONLY 1
          if (doubleClickTicks > ENC_SINGLECLICKONLY) {   // prevent trigger in single click mode
            if (doubleClickTicks < (buttonDoubleClickTime / ENC_BUTTONINTERVAL)) {
              button = DoubleClicked;
              doubleClickTicks = 0;
            }
          }
          else {
            doubleClickTicks = (doubleClickEnabled) ? (buttonDoubleClickTime / ENC_BUTTONINTERVAL) : ENC_SINGLECLICKONLY;
          }
        }
      }

      keyDownTicks = 0;
    }
  
    if (doubleClickTicks > 0) {
      doubleClickTicks--;
      if (doubleClickTicks == 0) {
        button = Clicked;
      }
    }
  }
}

// ----------------------------------------------------------------------------

int16_t getValue(void)
{
  int16_t val;
  
  noInterrupts();
  val = delta;

  if (steps == 2) delta = val & 1;
  else if (steps == 4) delta = val & 3;
  else delta = 0; // default to 1 step per notch

  if (steps == 4) val >>= 2;
  if (steps == 2) val >>= 1;

  int16_t r = 0;
  int16_t accel = ((accelerationEnabled) ? (acceleration >> 8) : 0);

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
Button getButton(void)
{
  noInterrupts();
  Button ret = button;
  if (button != Held && ret != Open) {
    button = Open; // reset
  }
  interrupts();

  return ret;
}



bool getPinState() {
  bool pinState;
  {
    pinState = digitalRead(pinBTN);
  }
  return pinState;
}

  

void task_encoder(void *pvParams)
{
  enum modeStateEncoder { encVolume, encStation } ;
  static enum modeStateEncoder stateEncoder = encVolume;
  int16_t newValue = 0;
  Button newButton = Open;
  static int16_t oldValue = 0;
	
	ClickEncoderInit(PIN_ENC_A, PIN_ENC_B, PIN_ENC_BTN);
	serviceEncoder = &service;	
	uint16_t volume = getVolume();
	while (1)
	{
		newValue = - getValue();
		newButton = getButton();
		if (newValue != 0) 
		{
		//    Serial.print("Encoder: ");Serial.println(newValue);
			// reset our accelerator
			if ((newValue >0)&&(oldValue<0)) oldValue = 0;
			if ((newValue <0)&&(oldValue>0)) oldValue = 0;
		}
		else
		{
			// lower accelerator 
			if (oldValue <0) oldValue++;
			if (oldValue >0) oldValue--;
		}
    
/*		if (newButton != Open)
		{    
		//    Serial.print("Button: ");Serial.println(newButton);
			if (newButton == Clicked) {stationOk();}
			if (newButton == DoubleClicked) {startStop();}
			if (newButton == Held) {stopStation();}
		}
*/
		if (/*(stateScreen  != sstation)&&*/(newValue != 0))
		{    
		//    Serial.print("Value: ");Serial.println(newValue);
		//    Serial.print("Volume: ");Serial.println(volume+newValue+(oldValue*2));
			char avolume[5];
			sprintf(avolume,"%d",volume+newValue+(oldValue*3));
			clientVol(avolume);
		} 		
		vTaskDelay(100);
		oldValue += newValue;
	}
	vTaskDelete( NULL ); 
}
