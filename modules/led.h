/*
 * led.h
 *
 *  Created on: Dec 17, 2014
 *      Author: arjan
 */

#ifndef MODULES_LED_H_
#define MODULES_LED_H_


typedef enum
{
	e_ledmode_Blink_heartbeat,
}e_ledMode;

void led_init(void);
unsigned char handleCmd_led(void **);

#endif /* MODULES_LED_H_ */
