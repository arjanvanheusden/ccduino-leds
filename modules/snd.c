/*
 * snd.c
 *
 *  Created on: May 17, 2015
 *      Author: arjan
 */
#include "../modules/timing.h"

void funcSndSample(unsigned int execNr, unsigned int totalExecs);

unsigned char sndTimerId = INVALID_TIMERID;
void sndStartSampling(unsigned int intervalMs)
{
	sndTimerId = timer_register(0,0,0);
	if(sndTimerId != INVALID_TIMERID)
		timer_update(&funcSndSample, 0,intervalMs, sndTimerId);

}


void funcSndSample(unsigned int execNr, unsigned int totalExecs)
{
	/*todo: if so many samples valid, do processing of sime kind..*/
	timerClrNrOfExecs(sndTimerId);
	/*do adc sample*/
	adcSample();
}
