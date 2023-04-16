/******************************************************************************
 * 
 *Copyright 2018 karawin (http://www.karawin.fr)
 *
 *******************************************************************************/
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "addon.h"
#include "app_main.h"
#include "gpio.h"
#include <time.h>
#include "esp_log.h"
#include "i2c_lcd.h"
#include "interface.h"
#include "eeprom.h"
#include "addoncommon.h"

#define TAG "addoni2c_lcd"

#define I2C_MASTER_TX_BUF_LEN    0                     // disabled
#define I2C_MASTER_RX_BUF_LEN    0                     // disabled
#define I2C_MASTER_FREQ_HZ       100000

// nams < --> num of line
#define STATIONNAME 1
#define TITLE1 2
#define STATION1 1
#define STATION2 2
#define VOLUME 3
#define TIME 0


////////////////////////////////////////
char *getNameNumI2c_lcd()
{
	return nameNum;
}

void setVolumeI2c_lcd(uint16_t vol)
{
	volume = vol;
}

////////////////////////////////////////
// Clear all buffers and indexes
void clearAllI2c_lcd()
{
	title[0] = 0;
	station[0] = 0;
	for (int i = 1; i < LINES; i++)
	{
		lline[i] = NULL;
		iline[i] = 0;
		tline[i] = 0;;
		mline[i] = 1;
	}
}

////////////////////////////////////////
void cleartitleI2c_lcd(uint8_t froml)
{
    title[0] = 0;
    for (int i = froml;i<LINES;i++)  // clear lines
	{
		lline[i] = NULL;
		iline[i] = 0;
		tline[i] = 0;
		mline[i] = 1;
    }
}


////////////////////////////////////////
// scroll each line
void scrollI2c_lcd()
{
	i2c_lcd_info_t * lcd_info = i2c_lcd_malloc();

    i2c_lcd_scroll_display_left(lcd_info);
    vTaskDelay(200 / portTICK_RATE_MS);
}


void eraseSlashes(char *str)
{
	//Symbols: \" \' \\ \? \/
	char *sym = str, *sym1;
	if (str != NULL)
	{
		while (*sym != 0)
		{
			if (*sym == 0x5c)
			{
				sym1 = sym + 1;
				if (*sym1 == 0x22 || *sym1 == 0x27 || *sym1 == 0x5c || *sym1 == 0x3f || *sym1 == 0x2f)
				{ 		*sym = 0x1f;	//Erase \ to non-printable symbol
					sym++;
				}
			}

			sym++;
		}
	}
}

//////////////////////////
void drawTTitleI2c_lcd(char *ttitle)
{
}

//////////////////////////
void drawStationI2c_lcd(uint8_t mTscreen, char *snum, char *ddot)
{
}

//////////////////////////
void drawVolumeI2c_lcd(uint8_t mTscreen)
{

}

void drawTimeI2c_lcd(uint8_t mTscreen, unsigned timein)
{

}

////////////////////////////////////////
void separatorI2c_lcd(char *from)
{
	char *interp;
	while (from[strlen(from) - 1] == ' ') from[strlen(from) - 1] = 0;	// avoid blank at end
	while ((from[0] == ' '))
	{
		strcpy(from, from + 1);
	}

	interp = strstr(from, " - ");
	if (from == nameset)
	{
		lline[0] = nameset;
		lline[1] = NULL;
		lline[2] = NULL;
		return;
	}

	if ((interp != NULL) && (yy != 32))
	{
		from[interp - from] = 0;
		lline[(from == station) ? 1 : 3] = from;
		lline[(from == station) ? 2 : 4] = interp + 3;
	}
	else
	{
		lline[(from == station) ? 1 : 3] = from;
	}
}

//cli.meta
void metaI2c_lcd(char *ici)
{
	cleartitleI2c_lcd(3);
	strcpy(title, ici + 7);
	separatorI2c_lcd(title);
}

//cli.icy0
void icy0I2c_lcd(char *ici)
{
	clearAllI2c_lcd();
	if (strlen(ici + 7) == 0) strcpy(station, nameset);
	else strcpy(station, ici + 7);
	separatorI2c_lcd(station);
}

//cli.stopped or label
void statusI2c_lcd(const char *label)
{
	cleartitleI2c_lcd(3);
	strcpy(title, label);
	lline[TITLE1] = title;
}

//cli.nameset
void namesetI2c_lcd(char *ici)
{
	strcpy(nameset, ici + 8);
	ici = strstr(nameset, " ");
	if (ici != NULL)
	{
		clearAllI2c_lcd();
		strncpy(nameNum, nameset, ici - nameset + 1);
		nameNum[ici - nameset + 1] = 0;
		setFuturNum(atoi(nameNum));
	}

	char nameseti[BUFLEN];
	strcpy(nameseti, nameset + strlen(nameNum));
	strcpy(nameset, nameseti);
	lline[STATIONNAME] = nameset;
}

// cli.playing
void playingI2c_lcd()
{
	if (strcmp(title, "STOPPED") == 0)
	{
		cleartitleI2c_lcd(3);
		separatorI2c_lcd(title);
	}
}

// uart_rx_one_char_block() causes a watchdog trigger, so use the non-blocking
// uart_rx_one_char() and delay briefly to reset the watchdog.
static uint8_t _wait_for_user(void)
{
    uint8_t c = 0;

#ifdef USE_STDIN
    while (!c)
    {
       STATUS s = uart_rx_one_char(&c);
       if (s == OK) {
          printf("%c", c);
       }
       vTaskDelay(1);
    }
#else
    vTaskDelay(1000 / portTICK_RATE_MS);
#endif
    return c;
}

void initI2c_lcd(uint8_t *lcd_type)
{

	gpio_num_t scl;
	gpio_num_t sda;

	if (*lcd_type == LCD_NONE) return;

	//This is switch between different types of I2C LCD with different i2c addresses
	switch (*lcd_type)
	{
		case LCD_I2C_1602:
			#define LCD_NUM_ROWS               2
			#define LCD_NUM_COLUMNS            32
			#define LCD_NUM_VISIBLE_COLUMNS    16
			break;
		case LCD_I2C_2004:
			#define LCD_NUM_ROWS               4
			#define LCD_NUM_COLUMNS            40
			#define LCD_NUM_VISIBLE_COLUMNS    20
			break;
		default:
			ESP_LOGE(TAG, "UNKNOWN LCD lcd_type %d. Fall back to type \"LCD_NONE\"", *lcd_type);
			*lcd_type = LCD_NONE;
	}

	if (*lcd_type != LCD_NONE)
	{
		ESP_LOGD(TAG, "lcd init type: %d", *lcd_type);

		// Set up I2C
		int i2c_master_port = I2C_NUM_0;
		i2c_config_t conf;
		conf.mode = I2C_MODE_MASTER;
		conf.sda_io_num = sda;
		conf.sda_pullup_en = GPIO_PULLUP_DISABLE;  // GY-2561 provides 10kΩ pullups
		conf.scl_io_num = scl;
		conf.scl_pullup_en = GPIO_PULLUP_DISABLE;  // GY-2561 provides 10kΩ pullups
		i2c_param_config(i2c_master_port, &conf);
		i2c_driver_install(i2c_master_port, conf.mode,
							I2C_MASTER_RX_BUF_LEN,
							I2C_MASTER_TX_BUF_LEN, 0);
		i2c_port_t i2c_num = I2C_NUM_0;
		uint8_t address = LCD_I2C_ADDRESS;

		//////////////////////////////////
		// Set up the SMBus
		smbus_info_t * smbus_info = smbus_malloc();
		ESP_ERROR_CHECK(smbus_init(smbus_info, i2c_num, address));
		ESP_ERROR_CHECK(smbus_set_timeout(smbus_info, 1000 / portTICK_RATE_MS));

		// Set up the I2C LCD with backlight off
		i2c_lcd_info_t * lcd_info = i2c_lcd_malloc();
		ESP_ERROR_CHECK(i2c_lcd_init(lcd_info, smbus_info, true,
		                                 LCD_NUM_ROWS, LCD_NUM_COLUMNS, LCD_NUM_VISIBLE_COLUMNS));

		ESP_ERROR_CHECK(i2c_lcd_reset(lcd_info));

		// turn off backlight
		ESP_LOGI(TAG, "backlight off");
		_wait_for_user();
		i2c_lcd_set_backlight(lcd_info, false);

		// turn on backlight
		ESP_LOGI(TAG, "backlight on");
		_wait_for_user();
		i2c_lcd_set_backlight(lcd_info, true);

		ESP_LOGI(TAG, "cursor on");
		_wait_for_user();
		i2c_lcd_set_cursor(lcd_info, true);

		vTaskDelay(100);
	}
}
