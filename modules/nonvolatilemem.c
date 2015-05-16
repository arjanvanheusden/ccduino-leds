/*
 * nonvolatilemem.c
 *
 *  Created on: Dec 29, 2014
 *      Author: arjan
 */

#include "../modules/nonvolatilemem.h"
#include "../peripherals/EEPROM.h"
#include "../peripherals/USART.h"

typedef struct{
	unsigned char identifier;
	unsigned char ee_address;
	unsigned char *loc_address;
	unsigned char len;
	unsigned char valid;
}t_nvmem_entry;

#define NVMEM_IDSTRING_L 16
unsigned char NVMEM_idstring_dat[NVMEM_IDSTRING_L];
/*
t_nvmmem_entry nvmem_entries[] = {
		{NVMEM_ID_IDSTRING,  				this entry is identified hereby
				0,							ee address
				NVMEM_idstring_dat,			container pointer, uninitialised
				NVMEM_IDSTRING_L,			length
				0,							valid
			}
};
*/



void NVMEM_init()
{
	unsigned int i;
	/*read valid byte for id string*/
	//nvmem_entries[NVMEM_ID_IDSTRING].valid = EEPROM_read();

	/*read id string from eeprom*/
	//for(i=0;i<NVMEM_IDSTRING_L;i++){
	//	NVMEM_idstring_dat[i] = EEPROM_read(NVMEM_IDSTRING_A + i);
	//}
	USART_printf("NVMEM_idstring read: ");
	USART_printf(NVMEM_idstring_dat);
	USART_printf("\r\n");
}

