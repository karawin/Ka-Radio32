/*
 * app_main.h
 *
 *  Created on: 13.03.2017
 *      Author: michaelboeckling
 *  Modified on 15.09.2017 for KaraDio32
 *		jp Cocatrix
 */

#ifndef MAIN_INCLUDE_APP_MAIN_H_
#define MAIN_INCLUDE_APP_MAIN_H_
#include "audio_renderer.h"
// isr event for timers
#define TIMER_SLEEP   0   
#define TIMER_WAKE    1 

typedef struct {
    int type;                  /*!< event type */
    int group;                 /*!< timer group */
    int idx;                   /*!< timer number */
} timer_event_t;

output_mode_t get_audio_output_mode() ;

uint8_t getIvol();
void setIvol( uint8_t vol);

#endif /* MAIN_INCLUDE_APP_MAIN_H_ */
