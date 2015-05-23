/*
 * Timing.h
 *
 *  Created on: Dec 20, 2014
 *      Author: arjan
 */

#ifndef MODULES_TIMING_H_
#define MODULES_TIMING_H_

#define INVALID_TIMERID 255

typedef void (*timer_handler_func)(unsigned int, unsigned int);

void timer_init();
void timing_process(void);
unsigned char timer_register(timer_handler_func,unsigned int ,unsigned int );
unsigned char timer_start(unsigned char timer_id);
unsigned char timer_stop(unsigned char timer_id);
unsigned char timer_update(timer_handler_func, unsigned int, unsigned int, unsigned char );
void timerClrNrOfExecs(unsigned char timer_id);
#endif /* MODULES_TIMING_H_ */
