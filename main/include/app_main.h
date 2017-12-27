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

//TIMER_BASE_CLK = APB_CLK_FREQ
//#define  APB_CLK_FREQ                                ( 80*1000000 )       //unit: Hz
#define TIMER_DIVIDER 16 	//5000000Hz 5MHz
#define TIMER_DIVIDER1MS 8000 //10000Hz 
#define TIMER_DIVIDER1mS 8 //10000000Hz 10MHz
//#define TIMER_SCALE    (TIMER_BASE_CLK / TIMER_DIVIDER)  /*!< used to calculate counter value */
#define TIMER_FINE_ADJ   (1.4*(TIMER_BASE_CLK / TIMER_DIVIDER)/1000000) /*!< used to compensate alarm value (7)*/
#define TIMERMS_FINE_ADJ   (1.4*(TIMER_BASE_CLK / TIMER_DIVIDER1MS)/1000000) /*!< used to compensate alarm value */
#define TIMERmS_FINE_ADJ   (1.4*(TIMER_BASE_CLK / TIMER_DIVIDER1mS)/1000000) /*!< used to compensate alarm value (14) */
#define TIMERVALUE(x) (x*5000000 - TIMER_FINE_ADJ)
#define TIMERVALUE1MS(x) (x*10) - TIMERMS_FINE_ADJ//x in ms
#define TIMERVALUE1mS(x) (x*10000 - TIMERmS_FINE_ADJ) //x in µs
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


typedef struct {
    int type;               /*!< event type */
    int i1;                 /*!< TIMER_xxx timer group */
    int i2;                 /*!< TIMER_xxx timer number */
} queue_event_t;

output_mode_t get_audio_output_mode() ;

uint8_t getIvol();
void setIvol( uint8_t vol);


void sleepCallback(void *pArg);
void wakeCallback(void *pArg);
void startSleep(uint32_t delay);
void stopSleep();
void startWake(uint32_t delay);
void stopWake();
void noInterrupt1Ms();
void interrupt1Ms();
char* getIp();



#endif /* MAIN_INCLUDE_APP_MAIN_H_ */
