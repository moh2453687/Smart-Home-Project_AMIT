/*
 * Bluetooth_HC_05.h
 *
 * Created: 2/5/2023 4:19:40 AM
 *  Author: On Store
 */ 


#ifndef BLUETOOTH_HC_05_H_
#define BLUETOOTH_HC_05_H_

#include "Types.h"
#include "Bluetooth_HC_05_confing.h"

void Blutooth_vidInit();
void Blutooth_vidSendData(u8 data);
u8 Blutooth_u8ReceivedData(void);


#endif /* BLUETOOTH_HC_05_H_ */