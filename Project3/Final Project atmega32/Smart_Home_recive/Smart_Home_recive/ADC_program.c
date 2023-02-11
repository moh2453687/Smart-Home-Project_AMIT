/*
 * ADC_program.c
 *
 * Created: 1/30/2023 3:23:03 AM
 *  Author: On Store
 */ 
#include "ADC_interface.h"

void ADC_init(){
	SETBIT(ADMUX,REFS0);
	SETBIT(ADCSRA,ADEN);
	SETBIT(ADCSRA,ADPS0);
	SETBIT(ADCSRA,ADPS1);
	SETBIT(ADCSRA,ADPS2);
}

uint16_t ADC_read(){

	SETBIT(ADCSRA,ADSC); // start conversion
	while(GETBIT(ADCSRA,ADSC) == 1){}
	return ADC;
}