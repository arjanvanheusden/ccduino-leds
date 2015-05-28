/*
 * adc.c
 *
 *  Created on: May 16, 2015
 *      Author: arjan
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#define ADCNUMSAMPLES 10

#define ADREFAVDD 0x40
#define ADADLARRIGHT 0x00
#define ADMUXADC0 0x00

#define ADENABLED 0x80
#define ADSTARTCONV 0x40
#define ADADATE 0x20
#define ADADIE 0x10
#define ADINTENABLE 0x08
#define ADPRESCALER128 0x07

void adcInit()
{
	/*set up AD mux register*/
	ADMUX = ADREFAVDD | ADADLARRIGHT | ADMUXADC0;

	/*set up control and status registers*/
	ADCSRA = ADENABLED | ADINTENABLE | ADPRESCALER128;
	ADCSRB = 0; // no external trigger source

	/*set digital inputs to 0*/
	DIDR0 = 0;
}

unsigned int adcSampleBlocking()
{
	unsigned int retval = 0;

	unsigned char prevAdcsra = ADCSRA;
	/* turn off interrupt and start conversion*/
	ADCSRA = (prevAdcsra & ~ADINTENABLE) | ADSTARTCONV;

	/*wait until done*/
	while(ADCSRA & ADSTARTCONV);

	/*clear isr flag*/
	ADCSRA &= ~ADADIE;

	/*copy result*/
	*((unsigned char*)&retval) = ADCH;
	*(((unsigned char*)&retval)+1) = ADCH;

	/*restore interrupt setting*/
	ADCSRA = prevAdcsra;
}

void adcSample()
{
	/* if no conversion in progress: start conversion*/
	if((ADCSRA & ADADIE)==0){
		ADCSRA |=  ADSTARTCONV;

	}
}

unsigned int adcSamples[ADCNUMSAMPLES];
unsigned char adcSamplesHead = 0;
unsigned char adcSamplesTail = 0;

/*ADC complete */
ISR(ADC_vect)
{
	*((unsigned char *)&(adcSamples[adcSamplesHead])) = ADCH;
	*(((unsigned char *)&(adcSamples[adcSamplesHead]))+1) = ADCL;
	adcSamplesHead = ((++adcSamplesHead)% ADCNUMSAMPLES);
}
