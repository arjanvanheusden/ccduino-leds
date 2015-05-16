#ifndef __usart_h
#define __usart_h

void USART_Init(unsigned char intdriven);
void USART_Transmit( char);
unsigned char USART_Receive( char * );

void USART_printf_len(char * str, unsigned int len);
void USART_printf(char * str);


/* Register names USART0*/
	#define UBRRnH	UBRR0H
	#define UBRRnL	UBRR0L

	#define UCSRnA	UCSR0A
	#define UCSRnB	UCSR0B
	#define UCSRnC	UCSR0C

	#define UDRn	UDR0
	#define UDREn	UDRE0
	#define UPEn	UPE0

	#define DORn	DOR0
	#define FEn	FE0
	#define RXCn	RXC0
	#define TXB8	TXB80

#define MAXSTRINGLEN 200

#endif
