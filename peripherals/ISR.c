/*
 * ISR.cpp
 *
 *  Created on: Dec 16, 2014
 *      Author: arjan
 */
#include <avr/interrupt.h>
#include "../peripherals/USART.h"
#include "../peripherals/ISR.h"

void ISR_init(void)
{


	/*enable interrupt global*/
	ISR_enable();
}

void ExtIntInit(void)
{
	//EICRA = 0x03; //ising edge of int0 generates interrupt
	//EIMSK = 0x01; //only enable int0

}

ISR(INT0_vect)
{

}

