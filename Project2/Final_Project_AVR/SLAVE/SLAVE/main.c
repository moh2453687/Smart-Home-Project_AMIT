/*
 * SLAVE.c
 *
 * Created: 2/5/2023 6:08:15 AM
 * Author : On Store
 */ 


#define F_CPU   8000000UL
#include "util/delay.h"
#include "Types.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LED_interface.h"
#include "SPI_interface.h"
#include "Bluetooth_HC_05.h"

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

volatile u8 data ;
u8 g;
int main(void)
{
	SPI_vidInit();
	LED_vidLEDInit(GPIOC,PIN0);
	LED_vidLEDInit(GPIOC,PIN2);
	LED_vidLEDInit(GPIOC,PIN4);
	LED_vidLEDInit(GPIOC,PIN6);
	LED_vidLEDInit(GPIOC,PIN7);
	/*g=DIO_enuReadPin(GPIOB,PIN4);*/
    /* Replace with your application code */
    while (1) 
    {
    }
}

ISR(SPI_STC_vect){
	data = SPI_u8SendReceive(Blutooth_u8ReceivedData());
	switch (data)
	{
	    case 'a':
		LED_vidLEDOn(GPIOC, PIN0);
		_delay_ms(1000);
		LED_vidLEDOff(GPIOC, PIN0);
		break;
		case 'b':
		LED_vidLEDOn(GPIOC, PIN2);
		_delay_ms(1000);
		LED_vidLEDOff(GPIOC, PIN2);
		break;
		case 'c':
		LED_vidLEDOn(GPIOC, PIN4);
		_delay_ms(1000);
		LED_vidLEDOff(GPIOC, PIN4);
		break;
		case 'h':
		LED_vidLEDOn(GPIOC, PIN6);
		_delay_ms(1000);
		LED_vidLEDOff(GPIOC, PIN6);
		break;
		case 'f':
		LED_vidLEDOn(GPIOC, PIN7);
		_delay_ms(1000);
		LED_vidLEDOff(GPIOC, PIN7);
		break;
	}
}
