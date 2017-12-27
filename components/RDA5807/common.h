/* BSD 3-Clause License
 * 
 * RDA5807M driver for ESP8266
 * Copyright (c) 2017, ccbruce0812 (ccbruce@gmail.com)
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif


#if defined(__xtensa__)
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define I2C_MASTER_NUM I2C_NUM_0   /*!< I2C port number for master dev */
#define I2C_MASTER_TX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_MASTER_RFREQ_HZ    100000     /*!< I2C master clock frequency (400000 max*/
#define ACK_CHECK_EN   0x1     /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS  0x0     /*!< I2C master will not check ack from slave */
#define ACK_VAL    0x0
#define NACK_VAL   0x1
extern xSemaphoreHandle semI2C;
#else
#include <i2c/i2c.h>
#include <FreeRTOS.h>
#include <task.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

//#define SWAP(a, b) { a^=b^=a^=b; }
#define SWAP(x,y) x ^= y; y ^= x; x ^= y
#define MSEC2TICKS(n) (n/portTICK_PERIOD_MS)

#ifndef RDA5807M_NDEBUG
static inline int RDA5807M___dbg__(const char *loc, const char *fmt, ...) {
	va_list args;
	char _fmt[256]="";
	int res;
	
	va_start(args, fmt);
	sprintf(_fmt, "[%s] %s", loc, fmt);
	res=vprintf(_fmt, args);
	va_end(args);
	
	return res;
}

#define DBG(...) RDA5807M___dbg__(__func__, __VA_ARGS__)
#else
#define DBG(...)
#endif

int RDA5807M_readReg(unsigned char regAddr, unsigned short *pData);
int RDA5807M_readRegOnly( unsigned short *pData,int len) ;
int RDA5807M_writeReg(unsigned char regAddr, unsigned short data);
#define readReg(a, b) RDA5807M_readReg(a, b)
#define writeReg(a, b) RDA5807M_writeReg(a, b)

/*
static int readRegs(unsigned short *pData, unsigned int count);
static int writeRegs(unsigned short *pData, unsigned int count);
*/

#ifdef __cplusplus
}
#endif

#endif
