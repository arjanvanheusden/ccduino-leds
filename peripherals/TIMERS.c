/*
 * TIMERS.c
 *
 *  Created on: Dec 17, 2014
 *      Author: arjan
 */


#include <avr/io.h>
#include <avr/interrupt.h>

#include "../peripherals/USART.h"


#define CLKRATE 16000000 //Hz
#define TIMERMATCHINTERVAL 1 //ms
#define PRESCALER64REGVAL 3
#define PRESCALER64 64
/***
 * clock = 16Meg, = period = 1/16M, prescaler p --> p/16M --> counts =
 * 1m/(p/16M) = 16k/p
 */

unsigned char cross_isr_flag = 0;
unsigned int isr_ms_count = 0, isr_sec_count = 0;
unsigned int ms_count = 0, sec_count = 0;

void TIMERS_Init(void)
{
	/*Normal counting mode*/
	TCCR0A = 0;
	/*Nothing special | clocksrc = clock/64, p = 64 */
	TCCR0B = (0)|(PRESCALER64REGVAL);
	/*use match register A: 1000 is for ms conversion*/
	OCR0A = (CLKRATE / PRESCALER64 / 1000)*TIMERMATCHINTERVAL;

	/*interrupt setting: enable match A*/
	TIMSK0 |= _BV(OCIE0A);
}

unsigned char getTimerRaw(void)
{
	return TCNT0;
}

/***
 *  getTimerUpdated
 *  inputs:
 *  	unsigned int * ms_count : milisecond counter is written here
 *  	unsigne int * sec_count: second counter is written here
 *
 *  return:
 *  	: nonzero if time updated
 */
unsigned char getTimerUpdated(unsigned int * l_ms_count, unsigned int * l_sec_count){
	/*single location: main thread accessing isr variable*/
	unsigned char tmp_cross_isr_flag = cross_isr_flag;

	if(tmp_cross_isr_flag){
		/*disable interrupt*/
		TIMSK0 &= ~(_BV(OCIE0A));
		/*clear flag*/
		cross_isr_flag = 0;
		/*update main thread time vars*/
		ms_count = isr_ms_count%1000;
		sec_count = isr_sec_count;

		/*enable interrupt*/
		TIMSK0 |= (_BV(OCIE0A));
	}

	if(l_ms_count != 0) *l_ms_count = ms_count;
	if(l_sec_count!= 0) *l_sec_count = sec_count;

	return tmp_cross_isr_flag;
}

ISR(TIMER0_COMPB_vect)
{
	return 1;
}
ISR(TIMER0_OVF_vect)
{
	return 1;
}

ISR(TIMER0_COMPA_vect)
{
	isr_ms_count = (++isr_ms_count)%1000;
	isr_sec_count = isr_ms_count==0?isr_sec_count+1: isr_sec_count;
	cross_isr_flag = 1;
	return 1;
}

