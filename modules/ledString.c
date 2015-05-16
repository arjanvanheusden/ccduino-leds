#include "../peripherals/ws2812.h"


// TODO: add header
typedef struct
{

	unsigned char R;
	unsigned char G;
	unsigned char B;
} ws2812led;

ws2812led leds[6] = {
		{128,128,128},
		{128,128,128},
		{128,128,128},
		{128,128,128},
		{128,128,128},
		{128,128,128}};


void ledStringInit()
{

}

unsigned char i;
void ledStringProcess()
{
	//Todo: update timing
	if(i++%100 == 0)
		showPixel(leds, sizeof(leds));
}
