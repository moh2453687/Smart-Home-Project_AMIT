/*
 * Smart_Home_AVR_Atmega32.c
 *
 * Created: 2/3/2023 2:33:37 AM
 * Author : Mohamed Fadl
 */ 

/**********************************************_include_**************************************/
#define F_CPU   8000000UL
#include "util/delay.h"
#include "Types.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LED_interface.h"
#include "KPD_interface.h"
#include "LM35_interface.h"
#include "TMR0_interface.h"
#include "UART_interface.h"
#include "EEPROM_interface.h"
#include "ADC_interface.h"
#include "DC_interface.h"
#include "BUZZER_interface.h"
/************************************************************************************************/
u8 check_passsword();
void set_password();
void Enter_password();
void system_operations();
/**************************************************************************************************/
u8 counter =3;
u8 KEY_System,h[4],password[4];
u8 k=0,y=0,g;
u8 flag1,flag2;
u8 x[4],check_password[4];
// u8 LED_operations;
// u8 LED_control;
u16 temp;

/**************************************************************************************************/


int main(void)
{
	/*****************************************************_initialization_*******************************/
	LED_vidLEDInit(GPIOB, PIN0);
	
	LED_vidLEDInit(GPIOB, PIN1);
	
	LED_vidLEDInit(GPIOB, PIN2);
	
	LED_vidLEDInit(GPIOB, PIN3);
	
	BUZZER_vidLEDInit(GPIOB, PIN5);
	
	LCD_vidInit4bit(GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE);
	
	KPD_vidInit(GPIOC, LOW_NIBBLE, HIGH_NIBBLE);
	
	/*ADC_vidInit(ADC0_CHANNEL);*/
	
	LM35_vidInit(ADC0_CHANNEL);
	
	DC_vidInit(GPIOD,PIN2);
	
	USART_vidInit(9600);
	
	/**************************************************************************************************/
	flag1=EEPROM_voidRead(1);
	if (flag1==0xff)
	{
		LCD_voidDisplayString4bit(GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, "Smart Home");
	     _delay_ms(1000);
		 LCD_vidMoveCursor4bit(GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE,1,1);
		 
		LCD_voidDisplayString4bit(GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, "Set password:");
		LCD_vidSendCmd4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, 0xC0);
		set_password ();
	}
		else
		{
				for (k=0; k<4; k++)
				{
					password[k]=EEPROM_voidRead ((k + 1));
				}
				LCD_voidDisplayString4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, "Enter Pass :");
				LCD_vidSendCmd4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, 0xC0);
				Enter_password ();
				
				g=check_passsword();
				while (g==0)
		         {
					Enter_password ();
					g=check_passsword();
				}
		}
		
		while (1)
		{
			
		
	}
			
}

/********************************************_Function_***********************************/

void set_password(){
	while (y<4)
	{
	    KEY_System=KPD_u8GetPressedKey(GPIOC,LOW_NIBBLE,HIGH_NIBBLE);
		if (KEY_System !=0xff)
			{
				LCD_vidDisplayChar4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, KEY_System);
		
				_delay_ms (500);
		
				h[y] = KEY_System;
		
				EEPROM_voidWrite (y + 1, h[y]);
		
				password[y] = EEPROM_voidRead (y + 1);
		
				y++;
		
				LCD_vidSendCmd4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE,LCD_MOVE_CURSOR_LEFT);
		
				LCD_vidDisplayChar4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, '*');
		
				_delay_ms (100);
		
			}	
	}
	
	_delay_ms (10);
	
	LCD_vidClearScreen4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE);
	
	LCD_voidDisplayString4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, "Pass is set");
	
	_delay_ms (1000);
	
	Enter_password ();
	
	g = check_passsword();
	
	while (g==0)
	{
		Enter_password ();
		
		g = check_passsword();
	}
}


void Enter_password(){
	
	_delay_ms(1000);
	
	LCD_vidClearScreen4bit(GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE);
	
	LCD_voidDisplayString4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, "Enter pass:");
	
	_delay_ms(200);
	
	LCD_vidSendCmd4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, 0xC0);
	
	for (k=0; k<4; k++)
	{
		do 
		{
			KEY_System = KPD_u8GetPressedKey(GPIOC,LOW_NIBBLE,HIGH_NIBBLE);
			
		} while (KEY_System == 0xff);
		LCD_vidDisplayChar4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, KEY_System);
		
		_delay_ms (500);
		
		check_password[k] = KEY_System;
		
		LCD_vidSendCmd4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, LCD_MOVE_CURSOR_LEFT);
		
		LCD_vidDisplayChar4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE,'*');
		
		_delay_ms (100);
		
	}
}

u8 check_passsword()
{
	if (check_password[0] == password[0] && check_password[1] == password[1] && check_password[2] == password[2] && check_password[3] == password[3])
	{
		LCD_vidClearScreen4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE);
		
		LCD_voidDisplayString4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, "Pass is right ");
		
		_delay_ms(500);
		
		 LCD_vidMoveCursor4bit(GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE,1,1);
		 
		LCD_vidClearScreen4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE);
		
		_delay_ms(1000);
		
		LCD_voidDisplayString4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, "The door is open ");
		
		LCD_vidSendCmd4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, 0xC0);
		
		
		_delay_ms(1000);
		
		LCD_vidClearScreen4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE);
		
		LCD_voidDisplayString4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, "Welcome Mohamed ");
		_delay_ms(1000);
		LCD_vidClearScreen4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE);
		g = 1;
		
		system_operations();
		
	} 
	else
	{
		if (counter > 0)
		
		{
			
			LCD_vidClearScreen4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE);
			
			LCD_voidDisplayString4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, "Pass is wrong ");
			
			_delay_ms (1000);
			
			LCD_vidSendCmd4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE,0xC0);
			
			LCD_voidDisplayString4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, "Try again:");
			
			LCD_vidDisplayNumber4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, counter);
			
			_delay_ms (1000);
			
			counter--;
			
			LCD_vidClearScreen4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE);
			
			g = 0;
		}
		
		else
		
		{
			
			LCD_vidClearScreen4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE);
			
			LCD_voidDisplayString4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, "System Blocked");
			
			_delay_ms (1000);
			
			g = 1;
			
		}
		
		
	}
	
	return g;
	
	}
	
	
	
void system_operations()
{
	temp = LM35_u8Read();

if (temp<=25)
{
	DC_vidStart(GPIOD, PIN2, OUTPUT);
	
	USART_vidSendString("The condition of the house is bad");
	
	LED_vidLEDToggle(GPIOB, PIN0);
	
	LCD_voidDisplayString4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, " unstable ");
	
	BUZZER_vidLEDOn(GPIOB,PIN5);
	
	_delay_ms(1000);
	
	BUZZER_vidLEDOff(GPIOB,PIN5);
	
}
else if((temp > 25 )&& (temp >= 44))
{
	
	LCD_vidClearScreen4bit(GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE);
	
	DC_vidStart(GPIOD, PIN2, OUTPUT);
	
	USART_vidSendString("The house temperature is stable");
	
	LED_vidLEDOn(GPIOB, PIN1);
	_delay_ms(500);
	LED_vidLEDOff(GPIOB, PIN1);
	
	LED_vidLEDOn(GPIOB, PIN2);
	_delay_ms(500);
	LED_vidLEDOff(GPIOB, PIN2);
	
	LCD_voidDisplayString4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, " stable ");
	
	
}

else if((temp>45))
{
	LCD_vidClearScreen4bit(GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE);
	
	DC_vidStart(GPIOD, PIN2, OUTPUT);
	
	USART_vidSendString("The condition of the house is bad");
	
	LED_vidLEDToggle(GPIOB, PIN2);
	
	LCD_voidDisplayString4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, " unstable ");
	
	BUZZER_vidLEDOn(GPIOB,PIN5);
	
	_delay_ms(1000);
	
	BUZZER_vidLEDOff(GPIOB,PIN5);
	

}

else
{
	LCD_vidClearScreen4bit(GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE);
	
	USART_vidSendString("Don't worry, The house is safe");
	
	LCD_voidDisplayString4bit (GPIOA, GPIOA, PIN3, GPIOA, PIN2, HIGH_NIBBLE, " The house is safe ");
	
	DC_vidStart(GPIOD, PIN2, OUTPUT);
}

}
