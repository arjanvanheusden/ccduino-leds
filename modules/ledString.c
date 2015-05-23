#include "../peripherals/ws2812.h"
#include "../modules/timing.h"

// TODO: add header
typedef struct
{

	unsigned char R;
	unsigned char G;
	unsigned char B;
} ws2812led;

#define LEDGREEN {255,0,0}
#define LEDRED {0,255,0}
#define LEDBLUE {0,0,255}
#define LEDWHITE {255,255,255}
#define LEDBLACK {0,0,0}



ws2812led leds[8] = {
		LEDRED,
		LEDGREEN,
		LEDBLUE,
		LEDWHITE,
		LEDBLACK,
		{128,128,128},
		LEDBLACK,
		{128,128,128}};

unsigned char ledStringTimer = INVALID_TIMERID;
unsigned char isrTimerExpired = 0;
unsigned char timerExpired =0;
unsigned char currentProgram = 0;
unsigned int programCounter = 0;

void setLed(unsigned char R, unsigned char G,unsigned char B, unsigned char scale, ws2812led *led)
{
	// missing one intensity now.. TODO
	unsigned int tmp;
	tmp = (R*scale);led->G = ((unsigned char *) &tmp)[1];
	tmp = (G*scale);led->R = ((unsigned char *) &tmp)[1];
	tmp = (B*scale);led->B = ((unsigned char *) &tmp)[1];
}

void ledStringInit()
{
	ledStringTimer = timer_register(0,0,0);
	if(ledStringTimer != INVALID_TIMERID)
			timer_update(0, 0,50, ledStringTimer);
	timer_start(ledStringTimer);
}

void clearAllLeds()
{
	unsigned char i;

	for(i=0;i<8;i++) //numleds =8, 3 bytes per led
	{
		leds[i].B = 0;
		leds[i].R = 0;
		leds[i].G = 0;

	}

}
/*alternate led blink*/
void ledStringDefault()
{
	if(programCounter%40 == 0)
	{
		setLed(255,255,255,255,&leds[0]);
		setLed(255,255,255,0,&leds[1]);
		setLed(255,255,255,255,&leds[2]);
		setLed(255,255,255,0,&leds[3]);
		setLed(255,255,255,255,&leds[4]);
		setLed(255,255,255,0,&leds[5]);
		setLed(255,255,255,255,&leds[6]);
		setLed(255,255,255,0,&leds[7]);
	}
	else if(programCounter%20 == 0)
	{
		setLed(255,255,255,0,&leds[0]);
		setLed(255,255,255,255,&leds[1]);
		setLed(255,255,255,0,&leds[2]);
		setLed(255,255,255,255,&leds[3]);
		setLed(255,255,255,0,&leds[4]);
		setLed(255,255,255,255,&leds[5]);
		setLed(255,255,255,0,&leds[6]);
		setLed(255,255,255,255,&leds[7]);
	}

}

/*alternate led blink*/
void ledStringRoundBlue()
{
	unsigned char i = ((programCounter/20)%8);
	if(programCounter%20 == 0)
	{
		clearAllLeds();
		setLed(255,255,255,255,&leds[i]);

	}
}



void ledStringProg1()
{
	unsigned char i;
	int val;
	for(i=0;i<8;i++)
	{
		val = ((programCounter+(7-i))%8)*32;
		setLed((unsigned char)(val),0,0,255,&leds[7-i]);
	}
}


void ledStringProcess()
{
	unsigned int locProgramCounter = timerGetNrOdExecs(ledStringTimer);
	/*invert, single instruction read of isr sharedvariable*/
	if(locProgramCounter != programCounter)
	{
		programCounter = locProgramCounter;


		/*reset singaling variable*/
		timerExpired != timerExpired;

		/*set previously defined image*/
		doLedEffect(leds, sizeof(leds)/sizeof(ws2812led), sizeof(leds));

		/*set next image*/
		switch(currentProgram)
		{
			case 1:
				ledStringProg1();
				break;
			case 2:
				ledStringRoundBlue();
				break;
			default:
				ledStringDefault();
				break;
		}
	}
}

void ledStringSetProgram(void ** args )
{
	unsigned int numArg = atoi(((unsigned char **) args)[1]);
	/*get sub command*/
	if(strcmp((((unsigned char **) args)[0]), "prog" )==0)
	{
		USART_printf("Setting ledString program...\r\n");
		currentProgram = numArg;
	}
	else if(strcmp((((unsigned char **) args)[0]), "speed" )==0)
	{
		USART_printf("Update speed ledString...\r\n");
		timer_update(0, 0,numArg, ledStringTimer);
	}
	else if(strcmp((((unsigned char **) args)[0]), "effect" )==0)
	{
		setLedEffect(numArg);
	}
	else
	{
		USART_printf("prog, speed, effect, are valid.");
	}

}

