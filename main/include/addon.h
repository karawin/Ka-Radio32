
#ifndef __have__addon_h__
#define __have__addon_h__


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <u8g2.h>

// lcd_type
// m>in 128x64
#define LCD_COLOR		0x80	//128
#define LCD_SPI			0x40
#define LCD_I2C			0
#define LCD_NONE 0xFF
#define LCD_I2C_SH1106	0
#define LCD_I2C_SSD1306	1
#define LCD_I2C_SSD1309	2
#define LCD_I2C_SSD1325 3

#define LCD_SPI_SSD1306 		0x40  //64
#define LCD_SPI_SSD1309 		0x41
#define LCD_SPI_ST7565_ZOLEN	0x42
#define LCD_SPI_SSD1322_NHD		0x43
#define LCD_SPI_IL3820_V2		0x44
#define LCD_SPI_SSD1607			0x45
#define LCD_SPI_LS013B7DH03		0x46


typedef struct {
    int channel;             /*!< event type */
    uint16_t addr;                /*!< nec addr */
    uint16_t cmd;                 /*!< nec cmdr */
	bool repeat_flag;
} event_ir_t;


extern xQueueHandle event_ir;
extern u8g2_t u8g2;
void task_addon(void *pvParams);
void lcd_init(uint8_t Type);
void (*serviceAddon)();
void dVolume(uint16_t vol);
void addonParse(const char *fmt, ...);


#endif