/*
 * app_main.h
 *
 *  Created on: 13.03.2017
 *      Author: michaelboeckling
 *  Modified on 15.09.2017 for KaraDio32
 *		jp Cocatrix
 */
#include "driver/timer.h"

#ifndef MAIN_INCLUDE_APP_MAIN_H_
#define MAIN_INCLUDE_APP_MAIN_H_
#include "audio_renderer.h"

//TIMER_BASE_CLK = APB_CLK_FREQ
//#define  APB_CLK_FREQ                                ( 80*1000000 )       //unit: Hz
#define TIMER_DIVIDER 16 
#define TIMER_DIVIDER1MS 8000 //10000Hz 
#define TIMER_SCALE    (TIMER_BASE_CLK / TIMER_DIVIDER)  /*!< used to calculate counter value */
#define TIMER_FINE_ADJ   (1.4*(TIMER_BASE_CLK / TIMER_DIVIDER)/1000000) /*!< used to compensate alarm value */
#define TIMER_INTERVAL0_SEC   (3.4179)   /*!< test interval for timer 0 */
#define TIMER_INTERVAL1_SEC   (5.78)   /*!< test interval for timer 1 */
#define TIMERGROUP TIMER_GROUP_0 
#define TIMERGROUP1MS TIMER_GROUP_1
#define TIMERVALUE(x) (x*5000000 -7)
#define TIMERVALUE1MS(x) (x*10) //x in ms
#define msTimer	TIMER_0
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

#endif /* MAIN_INCLUDE_APP_MAIN_H_ */
