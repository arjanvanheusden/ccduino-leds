/*
 * led.c
 *
 *  Created on: Dec 17, 2014
 *      Author: arjan
 */
#include <avr/io.h>
#include "../general.h"
#include "../modules/led.h"
#include "../modules/timing.h"

void func_ledMode_Blink_heartbeat(unsigned int, unsigned int);
void startLedMode(e_ledMode ledmode, unsigned int arg1, unsigned int arg2);

unsigned char timer_id = 255;

void led_init(void)
{
	timer_id = timer_register(0,0,0);
}
unsigned char handleCmd_led(void ** args)
{
	unsigned char numargs;

	USART_printf("Program LEDCMD, Welcome.");

	for(numargs=0;((char **)args)[numargs] != 0;numargs++);

	if(numargs != 2)
	{
		USART_printf("X - args, need 2, got "); USART_printf(itoa(numargs));
		return 0;
	}

	startLedMode(e_ledmode_Blink_heartbeat,atoi(args[0]), atoi(args[1]));
	/*USART_printf("{}");
	USART_printf(itoa(atoi(arg1)));
	USART_printf("{}");
	USART_printf(( char *) arg2);
	USART_printf("{}");*/
	return 0;
}

struct
{
	unsigned int time1;
	unsigned int time2;
}heartbeat ;

void startLedMode(e_ledMode ledmode, unsigned int arg1, unsigned int arg2){

	DBG("Started Ledmode: ");
	switch(ledmode)
	{
		case e_ledmode_Blink_heartbeat:
			DBG("Heartbeat ");
			DBG("Time 1: ");
			DBG(itoa(arg1));
			DBG("Time 2:");
			DBG(itoa(arg2));
			heartbeat.time1 = arg1;
			heartbeat.time2 = arg2;
			timer_update((&func_ledMode_Blink_heartbeat),
							0, /*number of execs*/
							1, /*exec interval*/
							timer_id);
			timer_start(timer_id);
			break;
		default:
			break;
	}
}

/*
 * Just a demo function: time1 = on time, time2 is offtime
 */
void func_ledMode_Blink_heartbeat(unsigned int execNr, unsigned int totalExecs)
{
	unsigned int execNr_t = execNr % (heartbeat.time1 + heartbeat.time2);
	if(execNr_t / (heartbeat.time1)){
			PORTB &= ~(_BV(PORTB5));
	} else {
		PORTB |= _BV(PORTB5);
	}

}
