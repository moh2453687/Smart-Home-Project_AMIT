/*
 * main.c
 *
 * Created: 2/5/2023 7:48:49 PM
 *  Author: On Store
 */ 
#define F_CPU   8000000UL
#include "util/delay.h"
#include "Types.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "Bluetooth_HC_05.h"
#include "SPI_interface.h"
#include "LCD_interface.h"

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

volatile u8 data ;
int main(void)
{
	USART_vidInit(9600);
	SPI_vidInit();
	Blutooth_vidInit();
	LCD_vidInit4bit(GPIOA,GPIOA,PIN7,GPIOA,PIN5,LOW_NIBBLE);
	LCD_voidDisplayString4bit(GPIOA,GPIOA,PIN7,GPIOA,PIN5,LOW_NIBBLE,"Welcome");
	_delay_ms(1000);
	LCD_vidClearScreen4bit(GPIOA,GPIOA,PIN7,GPIOA,PIN5,LOW_NIBBLE);
	LCD_voidDisplayString4bit(GPIOA,GPIOA,PIN7,GPIOA,PIN5,LOW_NIBBLE,"Welcome TO");
	LCD_vidMoveCursor4bit(GPIOA,GPIOA,PIN7,GPIOA,PIN5,LOW_NIBBLE,1,1);
	LCD_voidDisplayString4bit(GPIOA,GPIOA,PIN7,GPIOA,PIN5,LOW_NIBBLE,"Smart Home");
	LCD_vidMoveCursor4bit(GPIOA,GPIOA,PIN7,GPIOA,PIN5,LOW_NIBBLE,2,2);
	/* Replace with your application code */
	while (1)
	{
	}
}

ISR(SPI_STC_vect){
	data = Blutooth_u8ReceivedData();
	SPI_u8SendReceive(data);
}
