/******************************************************************************
 * 
 * Copyright 2017 karawin (http://www.karawin.fr)
 *
*******************************************************************************/

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include "ClickEncoder.h"
#include "app_main.h"
#include "gpio.h"
#include "webclient.h"
#include "webserver.h"
#include "interface.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "addon.h"
#include "u8g2_esp32_hal.h"


#define TAG "addon"
u8g2_t u8g2; // a structure which will contain all the data for one display
uint8_t lcd_type;
uint8_t lcd_family;

void lcd_init(uint8_t Type)
{
	lcd_type = Type;
	if (lcd_type & LCD_COLOR) // Color one
	{
		lcd_family = LCD_COLOR;
	} else
	if (lcd_type & LCD_SPI) // SPI
	{
		lcd_family = LCD_SPI;
		u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
		u8g2_esp32_hal.clk   = PIN_NUM_CLK;
		u8g2_esp32_hal.mosi  = PIN_NUM_MOSI;
		u8g2_esp32_hal.cs    = PIN_LCD_CS;
		u8g2_esp32_hal.dc    = PIN_LCD_A0;
		u8g2_esp32_hal.reset = PIN_LCD_RST;
		u8g2_esp32_hal_init(u8g2_esp32_hal);		
	} else //BW I2C
	{
		lcd_family = LCD_I2C;
		u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
		u8g2_esp32_hal.sda   = PIN_I2C_SDA;
		u8g2_esp32_hal.scl  = PIN_I2C_SCL;
		u8g2_esp32_hal_init(u8g2_esp32_hal);
	}
	
	switch (lcd_type){
	case LCD_I2C_SH1106:
		u8g2_Setup_sh1106_128x64_noname_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_i2c_cb,
			u8g2_esp32_msg_i2c_and_delay_cb);  // init u8g2 structure
		break;
	case LCD_I2C_SH1306:
		u8g2_Setup_sh1106_128x64_noname_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_i2c_cb,
			u8g2_esp32_msg_i2c_and_delay_cb);  // init u8g2 structure	
		break;		
	case LCD_I2C_SSD1309:	
		u8g2_Setup_ssd1309_128x64_noname2_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_i2c_cb,
			u8g2_esp32_msg_i2c_and_delay_cb);  // init u8g2 structure	
		break;	
	case LCD_I2C_SSD1325:	
		u8g2_Setup_ssd1325_nhd_128x64_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_i2c_cb,
			u8g2_esp32_msg_i2c_and_delay_cb);  // init u8g2 structure	
		break;	


		
	case LCD_SPI_SSD1306:	
		u8g2_Setup_ssd1306_128x32_univision_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;	
	case LCD_SPI_SSD1309:	
		u8g2_Setup_ssd1309_128x64_noname2_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;	
	case LCD_SPI_ST7565_ZOLEN:	
		u8g2_Setup_st7565_zolen_128x64_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;		
	case LCD_SPI_SSD1322_NHD:	
		u8g2_Setup_ssd1322_nhd_256x64_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;	
	case LCD_SPI_IL3820_V2:	//E Paper
		u8g2_Setup_il3820_v2_296x128_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;	
	case LCD_SPI_SSD1607:	//E Paper
		u8g2_Setup_ssd1607_200x200_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;	
	case LCD_SPI_LS013B7DH03:	
		u8g2_Setup_ls013b7dh03_128x128_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;				
	default:
		ESP_LOGE(TAG,"Unknown lcd lcd_type %d. Fall back to type 0",lcd_type);
		lcd_type = 0;
		lcd_family = LCD_I2C;
		u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
		u8g2_esp32_hal.sda   = PIN_I2C_SDA;
		u8g2_esp32_hal.scl  = PIN_I2C_SCL;
		u8g2_esp32_hal_init(u8g2_esp32_hal);
		u8g2_Setup_sh1106_128x64_noname_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_i2c_cb,
			u8g2_esp32_msg_i2c_and_delay_cb);  // init u8g2 structure
	}

	if (lcd_family != LCD_COLOR)
	{
		if (lcd_family == LCD_I2C) u8x8_SetI2CAddress(&u8g2.u8x8,0x78);
		u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,
		u8g2_SetPowerSave(&u8g2, 0); // wake up display
		u8g2_ClearBuffer(&u8g2);
		u8g2_SetFontPosTop(&u8g2);
	} else
	{
		ESP_LOGE(TAG,"Not yet lcd_type %d",lcd_type);
	}

}


void task_addon(void *pvParams)
{
	
// Encoder	init
  enum modeStateEncoder { encVolume, encStation } ;
  //static enum modeStateEncoder stateEncoder = encVolume;
  int16_t newValue = 0;
  Button newButton = Open;
  static int16_t oldValue = 0;
  ClickEncoderInit(PIN_ENC_A, PIN_ENC_B, PIN_ENC_BTN);
  serviceEncoder = &service;	; // connect the 1ms interruption
  //------
  // Init lcd
  // in app_main
  //  lcd_init();
//----------
	

	while (1)
	{
// Encoder loop		
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
    
		if (getPinState() == getpinsActive())
		{    
			if (newValue > 0) wsStationNext();
			else if (newValue < 0) wsStationPrev();

		} else

		if (/*(stateScreen  != sstation)&&*/(newValue != 0))
		{    
			ESP_LOGD(TAG,"Enc value: %d, oldValue: %d,  incr volume: %d",newValue, oldValue,newValue+(oldValue*3));
			setRelVolume(newValue+(oldValue*3));
		} 		
		oldValue += newValue;
// end Encoder loop

		vTaskDelay(10);
	}
	
	
	vTaskDelete( NULL ); 
}
