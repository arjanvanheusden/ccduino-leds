#include <avr/io.h>
#include <util/delay.h>

/*peripheral includes*/
#include "peripherals/ISR.h"
#include "peripherals/USART.h"
#include "peripherals/EEPROM.h"
#include "modules/console.h"
#include "modules/shell.h"
#include "modules/timing.h"
#include "modules/led.h"

/*Local declarations*/
void init_main(void);

enum {
 BLINK_DELAY_MS = 2000,
};



int main (void)
{



	init_main();
	/*wait for first character to be received*/
	USART_Receive(0);

	/*print welcome string*/
	USART_printf("Hello there...\r\n->");
	DDRB |= _BV(DDB5);

	while(1)
	{
		/*exec shell*/
		shellProcess();

		/*exec timer process*/
		timing_process();

		/*exec led updater*/
		ledStringProcess();


/* set pin 5 of PORTB for output*/
 //


  /* set pin 5 high to turn led on */
  //PORTB |= _BV(PORTB5);
  //_delay_ms(BLINK_DELAY_MS*4);

  /* set pin 5 low to turn led off */
  //PORTB &= ~_BV(PORTB5);
  //_delay_ms(BLINK_DELAY_MS);


 }

 return 0;
}

void init_main()
{
	/*Initialize modules*/
	timer_init();
	led_init();

	/*Initialize peripherals*/
	USART_Init(1);
	TIMERS_Init();
	EEPROM_Init();
	ws2812Init();
	ledStringInit();
	ledEffectInit();
	ISR_init();

}

