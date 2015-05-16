/*
 * EEPROM.h
 *
 *  Created on: Dec 29, 2014
 *      Author: arjan
 */

#ifndef PERIPHERALS_EEPROM_H_
#define PERIPHERALS_EEPROM_H_


void EEPROM_Init(void);
void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);

#endif /* PERIPHERALS_EEPROM_H_ */
