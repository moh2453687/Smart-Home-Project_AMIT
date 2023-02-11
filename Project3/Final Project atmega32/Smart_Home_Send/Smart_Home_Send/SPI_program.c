/*
 * SPI_program.c
 *
 * Created: 1/30/2023 2:01:25 AM
 *  Author: On Store
 */ 
#include "ATmega32_header.h"
#include "SPI_interface.h"
#define MOSI PB7
#define MISO PB6
#define CS	PB4
//#define CS2	PB3
#define CLK PB5

void SPI_master_init(){
	DDRB |= (1<<MOSI)|(1<<CS)|(1<<CLK);
	SPCR = 1<<MSTR | 1<<SPE;
}
void SPI_Slave_init(){
	SETBIT(DDRB,MISO);	// MISO
	SETBIT(SPCR,SPE);	// enable SPI
}
void SPI_send_char(uint8_t data){
	SPDR = data;
	while(GETBIT(SPSR,SPIF) == 0);
}
uint8_t SPI_receive_char(){
	while(GETBIT(SPSR,SPIF) == 0);
	return SPDR;
}