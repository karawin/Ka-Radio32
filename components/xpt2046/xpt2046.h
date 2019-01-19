/*
 * xpt2046.h
 *
 *  Created on: jan 12, 2019
 *      Author: karawin
 */

#ifndef _XPT2046_h_
#define _XPT2046_h_

#define KaRadio32 

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/i2c.h"
bool haveTouch();
void  getTaskLcd(xTaskHandle* hdt);
void getTouchSize(int* w, int* h);
void setTouchSize(int w, int h);
bool xpt_read_touch(int *x, int* y, uint8_t raw);
void xpt_init();
void saveCalibration(uint32_t x, uint32_t y);
void xpt_calibrate();

#endif