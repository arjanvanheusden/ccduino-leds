/*
 * general.h
 *
 *  Created on: Dec 14, 2014
 *      Author: arjan
 */

#ifndef GENERAL_H_
#define GENERAL_H_

#define bool unsigned char
#define true (1 == 1)
#define false (1 == 0)

#include "./peripherals/USART.h"
#define DBG(str) USART_printf(str);

typedef struct
{

	unsigned char R;
	unsigned char G;
	unsigned char B;
} ws2812led;


char* itoa(int i);
int atoi(char *);
#endif /* GENERAL_H_ */
