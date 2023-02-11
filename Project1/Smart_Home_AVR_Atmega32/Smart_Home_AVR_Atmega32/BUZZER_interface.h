/*
 * BUZZER_interface.h
 *
 * Created: 2/6/2023 4:31:00 AM
 *  Author: On Store
 */ 


#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_

#include "DIO_interface.h"

void BUZZER_vidLEDInit(_enuGPIOX enuPortNum, _enuPINX enuPinNum);

void BUZZER_vidLEDOn(_enuGPIOX enuPortNum, _enuPINX enuPinNum);

void BUZZER_vidLEDOff(_enuGPIOX enuPortNum, _enuPINX enuPinNum);

void BUZZER_vidLEDToggle(_enuGPIOX enuPortNum, _enuPINX enuPinNum);




#endif /* BUZZER_INTERFACE_H_ */