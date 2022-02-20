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
#include "ClickButtons.h"
#include "app_main.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <driver/i2c.h>
#include "gpio.h"
// ----------------------------------------------------------------------------

#define TAG "ClickButton"
bool getPinStates(Button_t *enc,uint8_t index);
uint8_t i2c_keypad_read();  
// ----------------------------------------------------------------------------
uint8_t rexp; // expansion ports for esplay
	
//bool getpinsActives(Button_t *enc) {return enc->pinsActive;}

Button_t* ClickButtonsInit(int8_t A, int8_t B, int8_t C, bool Active)
{
	Button_t* enc = kmalloc(sizeof(Button_t));
	enc->pinBTN[0] = A; 
	enc->pinBTN[1] = B;
	enc->pinBTN[2] = C;
	enc->expGpio = false;
	enc->pinsActive = Active; 
	for (int i=0;i<3;i++)
	{
		enc->button[i] = Open;
		enc->keyDownTicks[i] = 0;
		enc->doubleClickTicks[i] = 0;
//		enc->lastButtonCheck[i] = 0;
	}
	enc->doubleClickEnabled = true; enc->buttonHeldEnabled = true;

	gpio_config_t gpio_conf;
	gpio_conf.mode = GPIO_MODE_INPUT;
	gpio_conf.pull_up_en =  (enc->pinsActive == LOW) ?GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE;
	gpio_conf.pull_down_en = (enc->pinsActive == LOW) ?GPIO_PULLDOWN_DISABLE : GPIO_PULLDOWN_ENABLE;
	gpio_conf.intr_type = GPIO_INTR_DISABLE;	

  if (enc->pinBTN[0] != (int8_t) GPIO_NONE)
  {
	gpio_conf.pin_bit_mask = ((uint64_t)(((uint64_t)1)<<enc->pinBTN[0]));
	ESP_ERROR_CHECK(gpio_config(&gpio_conf));
  }
  if (enc->pinBTN[1] != (int8_t) GPIO_NONE)
  {
	gpio_conf.pin_bit_mask = ((uint64_t)(((uint64_t)1)<<enc->pinBTN[1]));
	ESP_ERROR_CHECK(gpio_config(&gpio_conf));
  }
  if (enc->pinBTN[2] != (int8_t) GPIO_NONE)
  {
	gpio_conf.pin_bit_mask = ((uint64_t)(((uint64_t)1)<<enc->pinBTN[2]));
	ESP_ERROR_CHECK(gpio_config(&gpio_conf));
  }
  
  return enc;
}

//Buttons on a gpio expander
Button_t* ClickexpButtonsInit(int8_t A, int8_t B, int8_t C, bool Active)
{
	Button_t* enc = kmalloc(sizeof(Button_t));
	enc->pinBTN[0] = A; 
	enc->pinBTN[1] = B;
	enc->pinBTN[2] = C;
	enc->expGpio = true;
	enc->pinsActive = Active; 
	for (int i=0;i<3;i++)
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
IRAM_ATTR void serviceBtn(Button_t *enc)
{
  // handle enc->button
  //
//  unsigned long currentMillis = xTaskGetTickCount()* portTICK_PERIOD_MS;

//  if (enc->expGpio) rexp = i2c_keypad_read(); // read the expansion
  
  for(uint8_t i = 0; i < 3; i++) 
  {
//	if (currentMillis < enc->lastButtonCheck[i]) enc->lastButtonCheck[i] = 0;        // Handle case when millis() wraps back around to zero
	if (enc->pinBTN[i] != (int8_t) GPIO_NONE )        // check enc->button only, if a pin has been provided
//		&& ((currentMillis - enc->lastButtonCheck[i]) >= ENC_BUTTONINTERVAL))            // checking enc->button is sufficient every 10-30ms
	{ 
//		enc->lastButtonCheck[i] = currentMillis;

		bool pinRead = getPinStates(enc,i);
    
		if (pinRead == enc->pinsActive) { // key is down
			enc->keyDownTicks[i]++;
			if ((enc->keyDownTicks[i] > (BTN_HOLDTIME / ENC_BUTTONINTERVAL)) && (enc->buttonHeldEnabled)) 
			{
				enc->button[i] = Held;
			}
		}

		if (pinRead == !enc->pinsActive) { // key is now up
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
Button getButtons(Button_t *enc,uint8_t index)
{
  noInterrupts();
  Button ret = enc->button[index];
  if (enc->button[index] != Held && ret != Open) {
    enc->button [index]= Open; // reset
  }
  interrupts();
  return ret;
}

//----------------------------
 // Read the esplay keypad
 //---------------------------
#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define WRITE_BIT I2C_MASTER_WRITE  /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ    /*!< I2C master read */
#define ACK_CHECK_EN 0x1            /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0           /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                 /*!< I2C ack value */
#define NACK_VAL 0x1                /*!< I2C nack value */
#define I2C_ADDR 0x40				// esplay i2c address

IRAM_ATTR  uint8_t i2c_keypad_read()
{
uint8_t val;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, I2C_ADDR  | READ_BIT, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, &val, NACK_VAL);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return val;
}


bool getPinStates(Button_t *enc,uint8_t index) {
/*  bool pinState;
  {
    if (!enc->expGpio) 
		pinState = digitalRead(enc->pinBTN[index]);
	else 
		pinState = (rexp >>enc->pinBTN[index]) & 1;
  }
  return pinState;
*/  
  if (enc->pinBTN[index] == (int8_t) GPIO_NONE) return false;
  return (enc->expGpio?((rexp >> (enc->pinBTN[index]-1) & 1)):digitalRead(enc->pinBTN[index]));
}

  

