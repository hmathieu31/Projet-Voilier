#include "stm32f10x.h"
#include "Acquisition_Girouette.h"
#include "MyTimer.h"

int angle;


void setTimerEncoderMode() {
	TIMER_ACQ->CNT=0;
	//On active le mode encoder qui permet de transformer le timer en compteur
	TIMER_ACQ->SMCR &= ~(1<<2);
	TIMER_ACQ->SMCR |= 3<<0;
	//On gere le registre CCER pour que les signaux soient captures sur un front montant
	TIMER_ACQ->CCER |= 1<<0;
	TIMER_ACQ->CCER |= 1<<4;
	//On enable le counter
	TIMER_ACQ->CR1 |= 1<<0;
	
	TIMER_ACQ->PSC = 0;
	TIMER_ACQ->ARR = 360;
}

void getAngle(){
	angle = TIMER_ACQ->CNT;
}


int interruptAngle(){
	MyTimer_Base_Init (TIMER_ACQ,36000,1000);
	MyTimer_Base_Start (TIMER_ACQ);
	MyTimer_ActiveIT(TIMER_ACQ, 1, getAngle);
	return angle;
}
