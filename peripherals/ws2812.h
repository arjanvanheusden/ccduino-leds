/*
 * ws2812.h
 *
 *  Created on: May 16, 2015
 *      Author: arjan
 */

#ifndef MODULES_WS2812_H_
#define MODULES_WS2812_H_
#include "../general.h"

void showPixel(ws2812led * pixels, unsigned char numLeds, unsigned int numBytes);

#endif /* MODULES_WS2812_H_ */
