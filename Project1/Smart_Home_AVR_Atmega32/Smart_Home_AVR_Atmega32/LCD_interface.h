#ifndef _HAL_LCD_INTERFACE_H_
#define _HAL_LCD_INTERFACE_H_
#include "DIO_interface.h"

void LCD_vidInit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum);

void LCD_vidSendCmd(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum, u8 u8Cmd);

void LCD_vidDisplayChar(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum, u8 u8char);

void LCD_voidDisplayString(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum, u8 *ptru8String);

void LCD_vidClearScreen(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum);

void LCD_vidMoveCursor(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum , _enuPINX enuENPinNum, u8 u8Line, u8 u8Position);

void LCD_vidDisplayNumber(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum , _enuPINX enuENPinNum, u32 copy_u32Number);

void LCD_vidDisplayRealNumber(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum , _enuPINX enuENPinNum, double Number);


void LCD_vidInit4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum, _enuNIBBLE enuNibble);

void LCD_vidSendCmd4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum,_enuNIBBLE enuNibble, u8 u8Cmd);

void LCD_vidDisplayChar4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum,_enuNIBBLE enuNibble, u8 u8char);

void LCD_voidDisplayString4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum,_enuNIBBLE enuNibble, u8 *ptru8String);

void LCD_vidClearScreen4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum, _enuPINX enuENPinNum,_enuNIBBLE enuNibble);

void LCD_vidMoveCursor4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum , _enuPINX enuENPinNum,_enuNIBBLE enuNibble, u8 u8Line, u8 u8Position);

void LCD_vidDisplayNumber4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum , _enuPINX enuENPinNum, _enuNIBBLE enuNibble, u32 copy_u32Number);

void LCD_vidDisplayRealNumber4bit(_enuGPIOX enuDataPortNum, _enuGPIOX enuRSPortNum, _enuPINX enuRSPinNum, _enuGPIOX enuENPortNum , _enuPINX enuENPinNum, _enuNIBBLE enuNibble, double Number);

#endif