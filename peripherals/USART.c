#include <avr/io.h>
#include <avr/interrupt.h>
#include "../peripherals/USART.h"


#define FOSC 16000000 // Clock Speed
#define BAUD 9600

#define RINGBUFSIZE 10
unsigned char rx_ringbuf[RINGBUFSIZE];
unsigned char rx_ringbuf_head=0,rx_ringbuf_tail=0;

unsigned char gl_intdriven = 0;

/*Initialize USART module*/
void USART_Init(unsigned char intdriven)
{
	/*declare baud register setting*/
	unsigned int ubrr = FOSC/16/BAUD-1;
	/*Set baud rate */
	UBRRnH = (unsigned char)(ubrr>>8);
	UBRRnL = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSRnB = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSRnC = (1<<USBS0)|(3<<UCSZ00);

	rx_ringbuf_head = 0;
	rx_ringbuf_tail = 0;

	/*enable receive interrupt*/
	gl_intdriven=intdriven;
	if(gl_intdriven){
		UCSRnB |= (1<<RXCIE0);
	}

}

ISR(USART_RX_vect)
{
	unsigned char tmp;
	/* if interrupt is ok*/
	if(UCSRnA & (1<<RXCn)){
		rx_ringbuf[rx_ringbuf_head] = UDRn;
		//move head index
		rx_ringbuf_head = (++rx_ringbuf_head)%RINGBUFSIZE;
	} else {
		tmp = UDRn;tmp=tmp;
	}



	/*if(PORTB & _BV(PORTB5)){
		PORTB &= ~(_BV(PORTB5));
	} else {
		PORTB |= _BV(PORTB5);
	}*/
	return 0;

}


/*USART Blocking transmit single character*/
void USART_Transmit( char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRnA & (1<<UDREn)) );
	/* Put data into buffer, sends the data */
	UDRn = data;
}

/*USART Blocking receive single character
 * returns 1 if character received*/
unsigned char USART_Receive( char *chr )
{
	unsigned char valReturned = 0;
	/* Wait for data to be received */
	if(gl_intdriven){
		UCSRnB &= ~(1<<RXCIE0);
		if(rx_ringbuf_head != rx_ringbuf_tail){
			if(chr)*chr = rx_ringbuf[rx_ringbuf_tail];
			rx_ringbuf_tail = (++rx_ringbuf_tail)%RINGBUFSIZE;
			valReturned = 1;
		}
		UCSRnB |= (1<<RXCIE0);


	}else{
		if ( (UCSRnA & (1<<RXCn)) ){
		/* Get and return received data from buffer */
		*chr = UDRn;
		return 1;
		}
	}
	return valReturned;
}

void USART_printf_len(char * str, unsigned int len)
{
	unsigned char i = 0;
	while(str[i] != '\0' && i<len)
	{
		USART_Transmit(str[i++]);
	}

}
void USART_printf(char * str)
{
	USART_printf_len(str, MAXSTRINGLEN);
}
