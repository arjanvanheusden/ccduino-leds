#include "../general.h"
#include "../peripherals/ws2812.h"
#include "../modules/timing.h"

struct
{
	ws2812led y[8];
	ws2812led xZMinOne[8];
	ws2812led xZMinTwo[8];
	ws2812led yZMinOne[8];
	ws2812led yZMinTwo[8];
}ledHist;

unsigned char globalEffectArgument = 0;

void (*doLedEffectFunc)(ws2812led * pixels, unsigned char numLeds, unsigned int numBytes);

void ledEffectInit()
{
	globalEffectArgument = 1;
	doLedEffectFunc = &showPixel;
}


void doLedEffect(ws2812led * pixels, unsigned char numLeds, unsigned int numBytes)
{
	doLedEffectFunc(pixels, numLeds, numBytes);

}


void ledEffectPostGlow(ws2812led * pixels, unsigned char numLeds, unsigned int numBytes)
{
	unsigned char i;


	for(i=0;i<numLeds;i++)
	{
		/*calculate oRutput: in*(1-a) + out-1*(a)*/
		ledHist.y[i].R = (unsigned char)(((unsigned int)(pixels[i].R)*(100-globalEffectArgument))/100)
				+ (unsigned char)(((unsigned int)(ledHist.y[i].R) * globalEffectArgument)/100 );
		ledHist.y[i].G = (unsigned char)(((unsigned int)(pixels[i].G)*(100-globalEffectArgument))/100)
				+ (unsigned char)(((unsigned int)(ledHist.y[i].G) * globalEffectArgument)/100 );
		ledHist.y[i].B = (unsigned char)(((unsigned int)(pixels[i].B)*(100-globalEffectArgument))/100)
				+ (unsigned char)(((unsigned int)(ledHist.y[i].B) * globalEffectArgument)/100 );

	}
	/*put output in output function*/
	showPixel((ledHist.y),numLeds,numBytes);

}

void ledEffectFade(ws2812led * pixels, unsigned char numLeds, unsigned int numBytes)
{
	unsigned char i, argCopy;
	for(i=0;i<numLeds;i++)
	{
		/*prevent overflows*/

		if(pixels[i].R > ledHist.y[i].R)
		{
			if(globalEffectArgument > pixels[i].R - ledHist.y[i].R) globalEffectArgument = pixels[i].R - ledHist.y[i].R;
			ledHist.y[i].R +=globalEffectArgument;

		}
		else if (pixels[i].R < ledHist.y[i].R)
		{
			if(globalEffectArgument > ledHist.y[i].R - pixels[i].R) globalEffectArgument = ledHist.y[i].R - pixels[i].R;
			ledHist.y[i].R -=globalEffectArgument;

		}
		if(pixels[i].G > ledHist.y[i].G)
			{
				if(globalEffectArgument > pixels[i].G - ledHist.y[i].G) globalEffectArgument = pixels[i].G - ledHist.y[i].G;
				ledHist.y[i].G +=globalEffectArgument;
			}
		else if (pixels[i].G < ledHist.y[i].G)
			{
			if(globalEffectArgument > ledHist.y[i].G - pixels[i].G) globalEffectArgument = ledHist.y[i].G - pixels[i].G;
			ledHist.y[i].G -=globalEffectArgument;
			}
		if(pixels[i].B > ledHist.y[i].B)
			{
			if(globalEffectArgument > pixels[i].B - ledHist.y[i].B) globalEffectArgument = pixels[i].B - ledHist.y[i].B;
			ledHist.y[i].B +=globalEffectArgument;
			}
		else if (pixels[i].B < ledHist.y[i].B)
			{
			if(globalEffectArgument > ledHist.y[i].B - pixels[i].B) globalEffectArgument = ledHist.y[i].B - pixels[i].B;
			ledHist.y[i].B -=globalEffectArgument;
			}

	}
	/*put output in output function*/
	showPixel((ledHist.y),numLeds,numBytes);

}

void setLedEffect(unsigned char effectNr, unsigned char argument)
{
	USART_printf("setting effect:");
	USART_printf(itoa(effectNr));
	switch(effectNr)
	{
		case 1:
			if(globalEffectArgument > 99)
			{
				USART_printf(itoa(argument));
				USART_printf("?, prog needs arg < 100...");
			}
			else
			{
				globalEffectArgument = argument;
				doLedEffectFunc = ledEffectPostGlow;
			}
			break;
		case 2:
			if(globalEffectArgument > 10)
			{
				USART_printf(itoa(argument));
				USART_printf("?, prog needs arg < 10...");
			}
			else
			{
				doLedEffectFunc = ledEffectFade;
				globalEffectArgument = argument;
			}
			break;
		default:
			/*directly forward*/
			doLedEffectFunc = showPixel;
			break;
	}
}
