/*
 * TIMERS.h
 *
 *  Created on: Dec 17, 2014
 *      Author: arjan
 */

#ifndef PERIPHERALS_TIMERS_H_
#define PERIPHERALS_TIMERS_H_

void TIMERS_Init(void);
unsigned char getTimerRaw(void);
unsigned char getMSCounter(void);
unsigned char getTimerUpdated(unsigned int * l_ms_count, unsigned int * l_sec_count);


#endif /* PERIPHERALS_TIMERS_H_ */
