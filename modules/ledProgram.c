#include "../peripherals/ws2812.h"
#include "../modules/timing.h"




// TODO: add header
typedef struct
{

	unsigned char R;
	unsigned char G;
	unsigned char B;
} ws2812led;



struct
{
	ws2812led y[8];
	ws2812led xZMinOne[8];
	ws2812led xZMinTwo[8];
	ws2812led yZMinOne[8];
	ws2812led yZMinTwo[8];
}ledHist;


void (*doLedEffectFunc)(unsigned char * pixels, unsigned char numLeds, unsigned int numBytes);

void ledEffectInit()
{

	doLedEffectFunc = &showPixel;
}


void doLedEffect(ws2812led * pixels, unsigned char numLeds, unsigned int numBytes)
{
	doLedEffectFunc(pixels, numLeds, numBytes);

}


void ledEffectPostGlow(ws2812led * pixels, unsigned char numLeds, unsigned int numBytes)
{
	unsigned char i,j;
	for(i=0;i<numLeds;i++)
	{
		/*do postglow function Y = Y(z-1) + () */
		#define alphaTen 97


		/*calculate oRutput: in*(1-a) + out-1*(a)*/
		ledHist.y[i].R = (unsigned char)(((unsigned int)(pixels[i].R)*(100-alphaTen))/100)
				+ (unsigned char)(((unsigned int)(ledHist.y[i].R) * alphaTen)/100 );
		ledHist.y[i].G = (unsigned char)(((unsigned int)(pixels[i].G)*(100-alphaTen))/100)
				+ (unsigned char)(((unsigned int)(ledHist.y[i].G) * alphaTen)/100 );
		ledHist.y[i].B = (unsigned char)(((unsigned int)(pixels[i].B)*(100-alphaTen))/100)
				+ (unsigned char)(((unsigned int)(ledHist.y[i].B) * alphaTen)/100 );




			/*set xZminones*//*
			if(pixels[i].B > ledHist.xZMinOne[i].B && 0)
			{
				ledHist.xZMinOne[i].B;
				((unsigned char *)pixels[i])[];
			}*/

	}
	/*put output in output function*/
	showPixel((ledHist.y),numLeds,numBytes);

}


void setLedEffect(unsigned char effectNr)
{
	USART_printf("setting effect:");
	USART_printf(itoa(effectNr));
	switch(effectNr)
	{
		case 1:
			doLedEffectFunc = ledEffectPostGlow;
			break;
		default:
			/*directly forward*/
			doLedEffectFunc = showPixel;
			break;
	}
}
