/*
 * shell.c
 *
 *  Created on: Dec 10, 2014
 *      Author: arjan
 */

#include "../general.h"
#include "../modules/console.h"
#include "../modules/led.h"
#include "../modules/ledString.h"
#include "../modules/shell.h"
#include "../peripherals/TIMERS.h"
#include "../peripherals/USART.h"
#include "../peripherals/adc.h"

#define MAXNROFINPS 10
#define SHELL_CMDLEN 6



char tmp_str[5];
void ** dummy[1][1];
void shell_HandleCommand(char ** inp);
struct tdShellInput shellInputInfo;


/*Command structure typedef*/
typedef struct
{
	char cmd[SHELL_CMDLEN];
	unsigned char (*doCmd)(void **);
	char descr[40];
} t_command;

/*Command handler functions*/
unsigned char handleCmd_adc(void **);
unsigned char handleCmd_help(void **);
unsigned char handleCmd_timer(void **);

/*Command definitions*/
t_command commandList[] ={
		{"help",handleCmd_help, "you get this view"}, /*Must be first*/
		{"led",handleCmd_led, "do led stuff"},
		{"tim", handleCmd_timer, "do timer stuff"},
		{"adc", handleCmd_adc, "adc test function"},
		{"leds", ledStringSetProgram, "Set Ledstring program"}

};

char input_str[CONSOLE_MAXLEN];
void shellProcess()
{
	if(console_process(CONSOLE_NON_BLOCKING,input_str, CONSOLE_MAXLEN)) {
		USART_printf("\r\n");
		shell_process(input_str);
		USART_printf("->");
	}
}


/***
 *  shell_process:	processes the input string.
 *  				input string interpreted as one command and MAXNROFINPS-1 parameters
 *  				command and parameters are space separated
 */
void shell_process(char * str)
{
	unsigned int i = 0;
	unsigned inp_nr = 0;
	char * inp[MAXNROFINPS];
	char prev_char = -1;

	/*store command*/
	inp[inp_nr++] = str;

	/*store parameters: continue as long as the char processed is not eol*/
	/*MAXNROFINPUTS: one is used for cmd, last is used for end of argument list*/
	while(prev_char!= '\0' && (inp_nr < (MAXNROFINPS-2)) && i<(CONSOLE_MAXLEN))
	{
		prev_char = str[i];

		switch(str[i])
		{

			case console_ENTER:
			case '\n':
				/*the end of line is indicated with 0 pointer :)*/
				break;
			case '\0':
				/*write string pointer 0 to indicate end of args list*/
				inp[inp_nr] = 0;
				break;
			case console_SPACE:
				str[i] = '\0';
				/*set new storage location*/
				inp[inp_nr++] = str+i+1;
				break;
			default:
				break;
		}
		i++;
	}

	shell_HandleCommand(inp);
	shellInputInfo.inputStringArray = inp;
}

/*
 *  inp = array of strings
 */
void shell_HandleCommand( char ** inp)
{
	int i;
	bool bMatchFound = false;
	t_command *checkCommand = &(commandList[0]);


	/*cycle all commands*/
	i=0;
	bMatchFound = false;
	while( i< (sizeof(commandList)/sizeof(t_command)) && strcmp(commandList[i].cmd, inp[0]) != 0)
		i++;

	/*check if found cmd*/
	if(i< (sizeof(commandList)/sizeof(t_command)))
	{
		/*exec cmd handler*/
		commandList[i].doCmd(&(inp[1]));
	} else {
		/*run help*/
		commandList[0].doCmd(dummy);
	}
}

unsigned char handleCmd_timer(void ** args)
{
	USART_printf("Timer raw val: ");
	USART_printf(itoa(getTimerRaw()));
	USART_printf("\r\n");
	return 0;
}



unsigned char handleCmd_help(void ** args)
{
	unsigned char i;
	for(i=0; i< (sizeof(commandList)/sizeof(t_command)); i++)
	{
		USART_printf(&(commandList[i]).cmd);
		USART_printf(": ");
		USART_printf(&(commandList[i]).descr);
		USART_printf("\r\n");
	}

	return 0;
}

unsigned char handleCmd_adc(void ** args)
{
	unsigned int i;

	/*get first argument as string*/
	unsigned char * arg1 = (unsigned char *)args[0];

	if(!strcmp(arg1, "test")) {

		USART_printf("ADC sample: ");
		for(i=0;i< 1000; i++)
		{
			USART_printf(itoa(adcSampleBlocking()));
			USART_printf("\r\n");
		}
	} else if(!strcmp(arg1, "cont")) {
		/*install timer which calls adc continuously.*/

		/*install timer which handles chunk of samples*/
	}
	else
		USART_printf("argument 'test' or 'cont' expected \r\n");

	return 0;
}

