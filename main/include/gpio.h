#pragma once
#ifndef __GPIO_H__
#define __GPIO_H__

//-------------------------------//
// Define GPIO used in KaRadio32 //
//-------------------------------//
// Compatible ESP32 ADB
// https://www.tindie.com/products/microwavemont/esp32-audio-developing-board-esp32-adb/


// status led if any.
//------------------- 
#define GPIO_LED	GPIO_NUM_4

// gpio of the vs1053
//-------------------
#define PIN_NUM_XCS  GPIO_NUM_32
#define PIN_NUM_RST  GPIO_NUM_21
#define PIN_NUM_XDCS GPIO_NUM_33
#define PIN_NUM_DREQ GPIO_NUM_34
// spi
#define PIN_NUM_MISO GPIO_NUM_19
#define PIN_NUM_MOSI GPIO_NUM_23
#define PIN_NUM_CLK  GPIO_NUM_18

// Encoder knob
//-------------
#define PIN_ENC_A   GPIO_NUM_16
#define PIN_ENC_B   GPIO_NUM_17
#define PIN_ENC_BTN GPIO_NUM_5

// I2C Oled
//----------
#define PIN_I2C_SCL GPIO_NUM_14
#define PIN_I2C_SDA GPIO_NUM_13

// I2S DAC or PDM
//----------------
#define PIN_I2S_LRCK GPIO_NUM_25
#define PIN_I2S_BCLK GPIO_NUM_26
#define PIN_I2S_DATA GPIO_NUM_22


// to set a value: 		gpio_set_level(gpio_num_t gpio_num,value);
// to read a value: 	int gpio_get_level(gpio_num_t gpio_num)

void gpio_output_conf(gpio_num_t gpio);

#endif
