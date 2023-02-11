/*
 * TIMER0_program.c
 *
 * Created: 1/30/2023 1:59:14 AM
 *  Author: On Store
 */ 
#include "TIMER0_interface.h"

void TIMER0_Normal_init(){
	TCCR0= (1<<FOC0) | (1<<CS02) | (1<<CS00);
	//SETBIT(TIMSK,TOIE0);
	sei();
}
void TIMER0_Compare_init(){
	TCCR0= (1<<FOC0) | (1<<CS02) | (1<<CS00) | (1<<WGM01);
	OCR0 =200;
	SETBIT(TIMSK,OCIE0);
	sei();
}