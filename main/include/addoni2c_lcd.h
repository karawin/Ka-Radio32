
/******************************************************************************
 * 
 * Copyright 2018 karawin (http://www.karawin.fr)
 *
*******************************************************************************/

#include <stdint.h>

#ifndef ADDONUI2C_LCD_H_
#define ADDONUI2C_LCD_H_
void playingI2c_lcd();
void namesetI2c_lcd(char* ici);
void statusI2c_lcd(const char* label);
void icy0I2c_lcd(char* ici);
void metaI2c_lcd(char* ici);
char* getNameNumI2c_lcd();
void scrollI2c_lcd();
void drawTTitleI2c_lcd(char* ttitle);
void drawStationI2c_lcd(uint8_t mTscreen,char* snum,char* ddot);
void drawVolumeI2c_lcd(uint8_t mTscreen);
void drawTimeI2c_lcd(uint8_t mTscreen,unsigned timein);
void initI2c_lcd(uint8_t* lcd_type);
void setVolumeI2c_lcd(uint16_t vol);
void clearAllI2c_lcd();

#endif /* ADDONUI2C_LCD_H_ */