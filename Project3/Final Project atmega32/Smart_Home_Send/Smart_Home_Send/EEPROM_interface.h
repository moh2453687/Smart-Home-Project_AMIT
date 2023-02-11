/*
 * EEPROM_interface.h
 *
 * Created: 1/30/2023 12:17:08 AM
 *  Author: On Store
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

//header
#include "ATmega32_header.h"
uint8_t EEPROM_read(uint16_t Copy_add); // add from 0 to 1023 in atmega 32
void EEPROM_write(uint16_t Copy_add , uint8_t Copy_data);



#endif /* EEPROM_INTERFACE_H_ */