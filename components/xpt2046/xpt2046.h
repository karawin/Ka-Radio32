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

bool xpt_read_touch(int *x, int* y, uint8_t raw);
void xpt_init(spi_host_device_t spi_num, gpio_num_t  cspin, gpio_num_t  tirq);

#endif