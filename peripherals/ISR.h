/*
 * ISR.h
 *
 *  Created on: Dec 16, 2014
 *      Author: arjan
 */

#ifndef PERIPHERALS_ISR_H_
#define PERIPHERALS_ISR_H_
#include <avr/interrupt.h>
void ISR_init(void);
ISR(USART_RXC);

#define ISR_enable() sei()
#define ISR_disable() cli()

#endif /* PERIPHERALS_ISR_H_ */
