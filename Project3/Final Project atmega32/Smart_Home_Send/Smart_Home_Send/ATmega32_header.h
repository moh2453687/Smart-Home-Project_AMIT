/*
 * ATmega32_header.h
 *
 * Created: 1/30/2023 12:19:46 AM
 *  Author: On Store
 */ 


#ifndef ATMEGA32_HEADER_H_
#define ATMEGA32_HEADER_H_
#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#define SETBIT(REG,BIT) (REG |= (1<<BIT))  //set bit (0xff)
#define CLRBIT(REG,BIT) (REG &=~(1<<BIT)) //clear bit(0x00)
#define TOGBIT(REG,BIT) (REG ^=(1<<BIT)) //toggle bit(0xff=0x00 || 0x00=0xff)
#define GETBIT(REG,BIT) ((REG>>BIT)&1) //read bit (bit is (output && input))
uint32_t result_func(uint8_t*);



#endif /* ATMEGA32_HEADER_H_ */