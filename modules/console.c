#include "../peripherals/USART.h"
#include "../modules/console.h" 

static unsigned char i = 0;
/*blocking console, returns when Enter is pressed


*/

unsigned char console_process(unsigned char blocking, unsigned char *result, unsigned int maxlen)
{
	unsigned char * console_input;
	char cur_char = 0;
	
	/*set result pointer*/
	console_input = result;
	
	/* declare function pointer*/
	unsigned char (*GetChar)(char *);
	
	if(blocking){
		/*todo: replace by blocking function*/
		GetChar = &USART_Receive;
	} else {
		GetChar = &USART_Receive;
	}

	
	/*get next char*/
	if((*GetChar)(&cur_char)){
		//USART_printf(itoa((unsigned int)cur_char));
		
		/*handle buffer full, in case of new char*/
		if(i==(maxlen-1)){
			if(cur_char != console_BACKSPACE && cur_char != console_ENTER){
				/*decrement counter*/
				i--;
				/*output backspace*/
				USART_Transmit(console_BACKSPACE);
			}
		}
		
		switch(cur_char){
			case console_BACKSPACE:
				/*if able to backspace*/
				if(i>0){
					USART_Transmit(cur_char);
					i--;
				}
				break; 
			case console_ENTER:
				console_input[i] = '\0';
				break;
		
			default:
				console_input[i] = cur_char;
				/*echo char*/
				USART_Transmit(cur_char);
				i++;
				break;
		}
		
		
		/* complete string received, return 1*/
		if(cur_char == console_ENTER){
			i=0;
			return 1;
		}
	}
	return 0;
}
