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

