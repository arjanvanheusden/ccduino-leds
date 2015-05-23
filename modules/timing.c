/*
 * Timing.c
 *
 *  Created on: Dec 20, 2014
 *      Author: arjan
 */

#include <avr/io.h>
#include "../peripherals/TIMERS.h"
#include "../modules/timing.h"


#define MAXTIMERREGISTERED 10



typedef struct{
	void (*func)(unsigned int, unsigned int);/*function to exec when timer elapsed*/
	unsigned int nrOfExecs;
	unsigned int nrOfExecsCount;
	unsigned int interval; /*interval in ms*/
	unsigned int count; /*counted ms*/
	unsigned char running;
} s_timerReg;

s_timerReg timerReg[MAXTIMERREGISTERED];
static unsigned char timerRegReservedCnt = 0;


void timer_init()
{
	/*initialize all timer registers*/
	unsigned int i;

	for(i=0; i < sizeof(timerReg); i++){
		*((unsigned char *)(timerReg + i)) = 0;
	}
}
/***
 *  update timer props
 */
unsigned char timer_update(timer_handler_func func,
					unsigned int nrOfExecs,
					unsigned int interval,
					unsigned char timer_id)
{
	/* check timer_id */
	if(timer_id < timerRegReservedCnt){
		timerReg[timer_id].func = func;
		timerReg[timer_id].nrOfExecs = nrOfExecs;
		timerReg[timer_id].nrOfExecsCount = 0;
		timerReg[timer_id].interval = interval;
		timerReg[timer_id].count = 0;
		//timerReg[timer_id].running = 0;
		return timer_id;
	}
	else return INVALID_TIMERID;
}


/***
 *  reserve and register a timer
 */
unsigned char timer_register(timer_handler_func func,
					unsigned int nrOfExecs,
					unsigned int interval)
{
	unsigned char timer_id;
	if(timerRegReservedCnt < MAXTIMERREGISTERED){

		timer_id = timerRegReservedCnt++; /*reserve id*/
		timer_id = timer_update(func,nrOfExecs,interval,timer_id); /*fill in*/
		return timer_id;
	}
	else return INVALID_TIMERID;
}
unsigned char timer_start(unsigned char timer_id)
{
	unsigned char was_running = (unsigned char)-1;
	if(timer_id <timerRegReservedCnt){
		was_running = timerReg[timer_id].running;
		timerReg[timer_id].running = 1;
	}
	return was_running;
}

void timerClrNrOfExecs(unsigned char timer_id)
{

	if(timer_id <timerRegReservedCnt){
		timerReg[timer_id].nrOfExecsCount = 0;
	}
}
unsigned int timerGetNrOdExecs(unsigned char timer_id){return timerReg[timer_id].nrOfExecsCount;}

unsigned char timer_stop(unsigned char timer_id)
{
	unsigned char was_running = (unsigned char)-1;
	if(timer_id <timerRegReservedCnt){
		was_running = timerReg[timer_id].running;
		timerReg[timer_id].running = 0;
	}
	return was_running;
}

/***
 *
 */
void timing_process(void)
{
	unsigned int ms_count;
	unsigned char i;
	if(getTimerUpdated(&ms_count,0))
	{
		for(i=0;i<MAXTIMERREGISTERED;i++){
			if(timerReg[i].running)
			{
				if((timerReg[i].count) < timerReg[i].interval){
					/* increment counter*/
					timerReg[i].count++;
				} else {
					/** Timer elapsed **/
					/*reset counter*/
					timerReg[i].count = 0;;
					/*execute if it should be executed*/
					if( (timerReg[i].nrOfExecsCount < timerReg[i].nrOfExecs)
							||
							timerReg[i].nrOfExecs == 0){
						/* Execute function, pass exec counter */
						if(timerReg[i].func != 0)
							timerReg[i].func(timerReg[i].nrOfExecsCount, timerReg[timerRegReservedCnt].nrOfExecs);
						/* increment exec counter*/
						timerReg[i].nrOfExecsCount++;

					}
					/*reset counter*/
					if(timerReg[i].nrOfExecs != 0)
						timerReg[i].nrOfExecsCount %= timerReg[i].nrOfExecs;

				}
			}
		}
	}
}





