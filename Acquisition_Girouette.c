#include "stm32f10x.h"
#include "Acquisition_Girouette.h"
#include "MyTimer.h"

int angle;

void setTimerEncoderMode(TIM_TypeDef * Timer) {
	Timer->CNT=0;
	//On active le mode encoder qui permet de transformer le timer en compteur
	Timer->SMCR &= ~(1<<2);
	Timer->SMCR |= 3<<0;
	//On gere le registre CCER pour que les signaux soient captures sur un front montant
	Timer->CCER |= 1<<0;
	Timer->CCER |= 1<<4;
	//On enable le counter
	Timer->CR1 |= 1<<0;
	
	Timer->PSC = 0;
	Timer->ARR = 360;
}

void getAngle(){
	angle = TIM2->CNT;
}


int interruptAngle(TIM_TypeDef * Timer){
	MyTimer_Base_Init (TIM1,36000,1000);
	MyTimer_Base_Start (TIM1);
	MyTimer_ActiveIT(TIM1, 1, getAngle);
	return angle;
}