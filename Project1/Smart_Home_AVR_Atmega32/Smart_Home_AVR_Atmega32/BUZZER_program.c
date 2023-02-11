/*
 * BUZZER_program.c
 *
 * Created: 2/6/2023 4:36:11 AM
 *  Author: On Store
 */ 
#include "Types.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "BUZZER_interface.h"


void BUZZER_vidLEDInit(_enuGPIOX enuPortNum, _enuPINX enuPinNum)
{
	DIO_vidSetPinMode(enuPortNum, enuPinNum, OUTPUT);
}

void BUZZER_vidLEDOn(_enuGPIOX enuPortNum, _enuPINX enuPinNum)
{
	DIO_vidWritePin(enuPortNum, enuPinNum, HIGH);
}

void BUZZER_vidLEDOff(_enuGPIOX enuPortNum, _enuPINX enuPinNum)
{
	DIO_vidWritePin(enuPortNum, enuPinNum, LOW);
}

void BUZZER_vidLEDToggle(_enuGPIOX enuPortNum, _enuPINX enuPinNum)
{
	_enuOUTPUT enuOUTPUT;
	enuOUTPUT = DIO_enuReadPin(enuPortNum, enuPinNum);
	if(enuOUTPUT == HIGH)
	{
		DIO_vidWritePin(enuPortNum, enuPinNum, LOW);
	}
	else
	{
		DIO_vidWritePin(enuPortNum, enuPinNum, HIGH);
	}
}