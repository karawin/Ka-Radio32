/******************************************************************************
 * 
 * Copyright 2018 karawin (http://www.karawin.fr)
 *
*******************************************************************************/
#ifndef __custom_h__
#define __custom_h__

void LedBacklightInit();
bool LedBacklightOn(int) ;
bool  LedBacklightOff();
void backlight_percentage_set(int value);
#endif