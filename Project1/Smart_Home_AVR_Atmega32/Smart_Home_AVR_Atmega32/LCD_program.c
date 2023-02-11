#include "Types.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"

#define  F_CPU 8000000UL
#include "util/delay.h"

#include <stdio.h>

void LCD_vidInit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum)
{
    DIO_vidSetPortMode(enuDataPortNum, OUTPUT);
    DIO_vidSetPinMode(enuRSPortNum, enuRSPinNum, OUTPUT);    
    DIO_vidSetPinMode(enuENPortNum, enuENPinNum, OUTPUT);
    _delay_ms(200);
    LCD_vidSendCmd(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, LCD_Function_8BIT_2Lines);
    _delay_ms(1);
    LCD_vidSendCmd(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, LCD_DISP_ON_CURSOR_ON);
    _delay_ms(1);
    LCD_vidSendCmd(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, LCD_CLEAR_SCREEN);
    _delay_ms(2);
    LCD_vidSendCmd(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, LCD_ENTRY_MODE);
    _delay_ms(10);

    
}



void LCD_vidSendCmd(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum, u8 u8Cmd)
{
    DIO_vidWritePin(enuRSPortNum, enuRSPinNum, LOW);
    DIO_vidWritePort(enuDataPortNum, u8Cmd);
    LCD_vidSendEnablePulse(enuENPortNum, enuENPinNum);
}

static void LCD_vidSendEnablePulse(_enuGPIOX enuENPortNum, _enuPINX enuENPinNum)
{
    DIO_vidWritePin(enuENPortNum, enuENPinNum, HIGH);
    _delay_ms(2);
    DIO_vidWritePin(enuENPortNum, enuENPinNum, LOW);
}

void LCD_vidDisplayChar(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum, u8 u8char)
{
    DIO_vidWritePort(enuDataPortNum, u8char);
    DIO_vidWritePin(enuRSPortNum, enuRSPinNum, HIGH);
    LCD_vidSendEnablePulse(enuENPortNum, enuENPinNum);
}

void LCD_vidDisplayString(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum, u8 *ptru8String)
{
	while((*ptru8String) != '\0')
	{
		LCD_vidDisplayChar(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, *ptru8String);
		ptru8String++;
	}
}

void LCD_vidClearScreen(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum)
{
	LCD_vidSendCmd(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, LCD_CLEAR_SCREEN);
	_delay_ms(10);
}

void LCD_vidMoveCursor(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum , _enuPINX enuENPinNum, u8 u8Line, u8 u8Position)
{
	u8 u8data =0;
	if(u8Line < 1 || u8Line > 2 || u8Position < 1 || u8Position > 16)
	{
		u8data = 0x80;
	}
	else if(u8Line == 1)
	{
		u8data = 0x80 + (u8Position - 1);
	}
	else if(u8Line == 2)
	{
		u8data = 0xC0 + (u8Position - 1);
	}
	LCD_vidSendCmd(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, u8data);
	_delay_ms(1);
}

void LCD_vidDisplayNumber(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum , _enuPINX enuENPinNum, u32 copy_u32Number)
{
	u8 str[7];
	sprintf(str,"%d",copy_u32Number);
	LCD_vidDisplayString(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, str);
}

void LCD_vidDisplayRealNumber(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum , _enuPINX enuENPinNum, double Number)
{
	u8 str [16];
	u8 *tmpsign = (Number < 0)? "-" : "";
	float tmpval = (Number < 0)? -Number : Number;
	u16 tmpint1 = (u16)tmpval;
	float tmpfrac = tmpval - (float)tmpint1;
	u16 tmpint2 = tmpfrac * 10000;
	sprintf(str,"%s%d.%04d", tmpsign, tmpint1, tmpint2);
	LCD_vidDisplayString(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, str);
}


void LCD_vidInit4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum, _enuNIBBLE enuNibble)
{
	_delay_ms(200);
	DIO_vidSetPinMode(enuRSPortNum, enuRSPinNum, OUTPUT);    
   	DIO_vidSetPinMode(enuENPortNum, enuENPinNum, OUTPUT);
	if(enuNibble == LOW_NIBBLE)
	{
		DIO_vidSetLowNibbleMode(enuDataPortNum, OUTPUT);
		LCD_vidSendCmd4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, LOW_NIBBLE,LCD_RETURN_HOME);
		_delay_ms(15);
		LCD_vidSendCmd4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, LOW_NIBBLE,LCD_Function_4BIT_2Lines);
		_delay_ms(1);
		LCD_vidSendCmd4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, LOW_NIBBLE,LCD_DISP_ON_CURSOR_ON);
		_delay_ms(1);
		LCD_vidSendCmd4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, LOW_NIBBLE,LCD_CLEAR_SCREEN);
		_delay_ms(10);
		LCD_vidSendCmd4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, LOW_NIBBLE,LCD_ENTRY_MODE);
		_delay_ms(1);
	}
	else
	{
		DIO_vidSetHighNibbleMode(enuDataPortNum, OUTPUT);
		LCD_vidSendCmd4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, HIGH_NIBBLE,LCD_RETURN_HOME);
		_delay_ms(15);
		LCD_vidSendCmd4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, HIGH_NIBBLE,LCD_Function_4BIT_2Lines);
		_delay_ms(1);
		LCD_vidSendCmd4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, HIGH_NIBBLE,LCD_DISP_ON_CURSOR_ON);
		_delay_ms(1);
		LCD_vidSendCmd4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, HIGH_NIBBLE,LCD_CLEAR_SCREEN);
		_delay_ms(10);
		LCD_vidSendCmd4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, HIGH_NIBBLE,LCD_ENTRY_MODE);
		_delay_ms(1);
	}
}

void LCD_vidSendCmd4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum,_enuNIBBLE enuNibble, u8 u8Cmd)
{
	if(enuNibble == LOW_NIBBLE)
	{
		DIO_vidWriteLowNibble(enuDataPortNum, u8Cmd>>4);
		DIO_vidWritePin(enuRSPortNum, enuRSPinNum, LOW);
		LCD_vidSendEnablePulse(enuENPortNum, enuENPinNum);
		DIO_vidWriteLowNibble(enuDataPortNum, u8Cmd);
		DIO_vidWritePin(enuRSPortNum, enuRSPinNum, LOW);
		LCD_vidSendEnablePulse(enuENPortNum, enuENPinNum);
		_delay_ms(2);
	}
	else
	{
		DIO_vidWriteHighNibble(enuDataPortNum, u8Cmd);
		DIO_vidWritePin(enuRSPortNum, enuRSPinNum, LOW);
		LCD_vidSendEnablePulse(enuENPortNum, enuENPinNum);
		DIO_vidWriteHighNibble(enuDataPortNum, u8Cmd<<4);
		DIO_vidWritePin(enuRSPortNum, enuRSPinNum, LOW);
		LCD_vidSendEnablePulse(enuENPortNum, enuENPinNum);
		_delay_ms(2);
	}
}

void LCD_vidDisplayChar4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum,_enuNIBBLE enuNibble, u8 u8char)
{
	if(enuNibble == LOW_NIBBLE)
	{
		DIO_vidWriteLowNibble(enuDataPortNum, u8char>>4);
		DIO_vidWritePin(enuRSPortNum, enuRSPinNum, HIGH);
		LCD_vidSendEnablePulse(enuENPortNum, enuENPinNum);
		DIO_vidWriteLowNibble(enuDataPortNum, u8char);
		DIO_vidWritePin(enuRSPortNum, enuRSPinNum, HIGH);
		LCD_vidSendEnablePulse(enuENPortNum, enuENPinNum);
		_delay_ms(2);
	}
	else
	{
		DIO_vidWriteHighNibble(enuDataPortNum, u8char);
		DIO_vidWritePin(enuRSPortNum, enuRSPinNum, HIGH);
		LCD_vidSendEnablePulse(enuENPortNum, enuENPinNum);
		DIO_vidWriteHighNibble(enuDataPortNum, u8char<<4);
		DIO_vidWritePin(enuRSPortNum, enuRSPinNum, HIGH);
		LCD_vidSendEnablePulse(enuENPortNum, enuENPinNum);
		_delay_ms(2);
	}
}

void LCD_voidDisplayString4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum,_enuNIBBLE enuNibble, u8 *ptru8String)
{
	while((*ptru8String) != '\0')
	{
		LCD_vidDisplayChar4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, enuNibble, *ptru8String);
		ptru8String++;
	}
}

void LCD_vidClearScreen4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum,_enuNIBBLE enuNibble)
{
	LCD_vidSendCmd4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, enuNibble ,LCD_CLEAR_SCREEN);
	_delay_ms(10);
}

void LCD_vidMoveCursor4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum , _enuPINX enuENPinNum,_enuNIBBLE enuNibble, u8 u8Line, u8 u8Position)
{
	u8 u8data =0;
	if(u8Line < 1 || u8Line > 2 || u8Position < 1 || u8Position > 16)
	{
		u8data = 0x80;
	}
	else if(u8Line == 1)
	{
		u8data = 0x80 + (u8Position - 1);
	}
	else if(u8Line == 2)
	{
		u8data = 0xC0 + (u8Position - 1);
	}
	LCD_vidSendCmd4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, enuNibble, u8data);
	_delay_ms(1);
}

void LCD_vidDisplayNumber4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum , _enuPINX enuENPinNum, _enuNIBBLE enuNibble, u32 copy_u32Number)
{
	u8 str[7];
	sprintf(str,"%d",copy_u32Number);
	LCD_voidDisplayString4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, enuNibble, str);
}

void LCD_vidDisplayRealNumber4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum , _enuPINX enuENPinNum, _enuNIBBLE enuNibble, double Number)
{
	u8 str [16];
	u8 *tmpsign = (Number < 0)? "-" : "";
	float tmpval = (Number < 0)? -Number : Number;
	u16 tmpint1 = (u16)tmpval;
	float tmpfrac = tmpval - (float)tmpint1;
	u16 tmpint2 = tmpfrac * 10000;
	sprintf(str,"%s%d.%04d", tmpsign, tmpint1, tmpint2);
	LCD_voidDisplayString4bit(enuDataPortNum, enuRSPortNum, enuRSPinNum, enuENPortNum, enuENPinNum, enuNibble , str);
}