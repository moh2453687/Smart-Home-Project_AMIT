/*
 * SPI_interface.h
 *
 * Created: 1/30/2023 1:59:53 AM
 *  Author: On Store
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "ATmega32_header.h"
void SPI_master_init(); 
void SPI_Slave_init();
void SPI_send_char(uint8_t data);
uint8_t vidSPI_receive_char();





#endif /* SPI_INTERFACE_H_ */