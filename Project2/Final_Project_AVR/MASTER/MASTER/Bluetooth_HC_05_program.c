/*
 * Bluetooth_HC_05_program.c
 *
 * Created: 2/5/2023 5:43:17 AM
 *  Author: Mohamed Fadl
 */ 

#include "Bluetooth_HC_05.h"
#include "UART_interface.h"


void Blutooth_vidInit(){
	
	USART_vidInit(9600);			/* Initialize UART Communication Protocol */
	
}

void Blutooth_vidSendData(u8 data){
	
	USART_vidSendByte( data);		/* Transmit Data Using UART Protocol */
	
    USART_vidEnableTXInterrupt();

    USART_vidEnableRXInterrupt();

    USART_vidEnableUDREInterrupt();
}

u8 Blutooth_u8ReceivedData(void){
	
	u8 data = 0 ;			/* Initialize a variable to Save the Data Coming From Bluetooth */
	data = USART_u8RecieveByte();		/* Receive the Data Using UART Protocol */
	
	return data;
}