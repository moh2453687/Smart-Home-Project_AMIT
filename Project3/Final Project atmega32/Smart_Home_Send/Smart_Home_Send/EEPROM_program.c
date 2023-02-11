/*
 * EEPROM_program.c
 *
 * Created: 1/30/2023 12:18:17 AM
 *  Author: On Store
 */ 

#include "EEPROM_interface.h"

uint8_t EEPROM_read(uint16_t Copy_add){
	while(GETBIT(EECR,EEWE)==1){};
	EEAR =Copy_add;
	SETBIT(EECR,EERE);
	return EEDR;
}
void EEPROM_write(uint16_t Copy_add , uint8_t Copy_data){
	while(GETBIT(EECR,EEWE)==1){};
	EEAR =Copy_add;
	EEDR =Copy_add;
	SETBIT(EECR,EEMWE);
	SETBIT(EECR,EEWE);
}
