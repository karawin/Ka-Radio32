/*
 * app_main.h
 *
 *  Created on: 13.03.2017
 *      Author: michaelboeckling
 *  Modified on 15.09.2017 for KaraDio32
 *		jp Cocatrix
 * Copyright (c) 2017, jp Cocatrix
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

#ifndef MAIN_INCLUDE_APP_MAIN_H_
#define MAIN_INCLUDE_APP_MAIN_H_
#include "audio_renderer.h"
#include "driver/timer.h"

#define TIMER_DIVIDER 16 	//5000000Hz 5MHz
#define TIMER_DIVIDER1MS TIMER_BASE_CLK/10000 //10000Hz 
#define TIMER_DIVIDER1mS 8 //10000000Hz 10MHz

#define TIMERVALUE(x) (x*5000000 )
#define TIMERVALUE1MS(x) (x*10) 
#define TIMERVALUE1mS(x) (x*10000 )
#define TIMERGROUP TIMER_GROUP_0 
#define TIMERGROUP1MS TIMER_GROUP_1
#define TIMERGROUP1mS TIMER_GROUP_1
#define msTimer	TIMER_0
#define microsTimer	TIMER_1
#define sleepTimer  TIMER_0
#define wakeTimer TIMER_1

//extern os_timer_t sleepTimer;
extern uint32_t sleepDelay;
//extern os_timer_t wakeTimer;
extern uint32_t wakeDelay;

// event for timers and encoder
#define TIMER_SLEEP   0   
#define TIMER_WAKE    1 
#define TIMER_1MS	2
#define TIMER_1mS	3

/* // Tasks priority
#define PRIO_MAD 		7
#define PRIO_VS1053 	4
#define PRIO_RMT		7
#define PRIO_UART		2
#define PRIO_CLIENT		4
#define PRIO_SERVER		3
#define PRIO_ADDON		5
#define PRIO_LCD		6
#define PRIO_SUBSERV	3
#define PRIO_TIMER		1
#define PRIO_OTA		10

// CPU for task
#define CPU_MAD			0  // internal decoder and vs1053
#define CPU_RMT			0
#define CPU_UART		1
#define CPU_CLIENT		1
#define CPU_SERVER		0
#define CPU_ADDON		1
#define CPU_LCD			1
#define CPU_SUBSERV		0
#define CPU_TIMER		1
 */


// Tasks priority
#define PRIO_MAD 		5
#define PRIO_VS1053 	4
#define PRIO_RMT		5
#define PRIO_UART		2
#define PRIO_CLIENT		5
#define PRIO_SERVER		6
#define PRIO_ADDON		6
#define PRIO_LCD		4
#define PRIO_SUBSERV	6
#define PRIO_TIMER		11
#define PRIO_OTA		8

// CPU for task
#define CPU_MAD			0  // internal decoder and vs1053
#define CPU_RMT			1
#define CPU_UART		1
#define CPU_CLIENT		1
#define CPU_SERVER		0
#define CPU_ADDON		1
#define CPU_LCD			0
#define CPU_SUBSERV		1
#define CPU_TIMER		0

#define TEMPO_SAVE_VOL	10000

typedef struct {
    int type;               /*!< event type */
    int i1;                 /*!< TIMER_xxx timer group */
    int i2;                 /*!< TIMER_xxx timer number */
} queue_event_t;

output_mode_t get_audio_output_mode() ;

uint8_t getIvol();
void setIvol( uint8_t vol);
bool bigSram();

void sleepCallback(void *pArg);
void wakeCallback(void *pArg);
void startSleep(uint32_t delay);
void stopSleep();
void startWake(uint32_t delay);
void stopWake();
void noInterrupt1Ms();
void interrupt1Ms();
#define noInterrupts noInterrupt1Ms
#define interrupts interrupt1Ms
//void noInterrupts();
//void interrupts();
char* getIp();


#endif /* MAIN_INCLUDE_APP_MAIN_H_ */
