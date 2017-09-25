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

// isr event for timers
#define TIMER_SLEEP   0   
#define TIMER_WAKE    1 

typedef struct {
    int type;                  /*!< event type */
    int group;                 /*!< timer group */
    int idx;                   /*!< timer number */
} timer_event_t;



#endif /* MAIN_INCLUDE_APP_MAIN_H_ */
