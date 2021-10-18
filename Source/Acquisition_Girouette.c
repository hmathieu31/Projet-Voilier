#include "stm32f10x.h"
#include "Acquisition_Girouette.h"
#include "set_Sail.h"
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

int sail_angle;

// ON RENTRE PAS DEDANS A REGLER VOIR SI ON FAIT LINTERRUPTION
void updateAngle(){
	angle = TIMER_ACQ->CNT;

	/* 
		Appel de la lib set_Sail pour config de la PWM
	 */
	sail_angle = sSail_calc_angle(angle);
	sSail_set_servo(sail_angle);
}

void configGir(GPIO_TypeDef * GPIO, char pin){
	while ((GPIO->IDR >> pin) &1 == 0){
	}
	TIMER_ACQ->CNT = 0;
	angle = 0;
}


void interruptAngle(){
	MyTimer_Base_Init (TIM4,36000,1000);
	MyTimer_Base_Start (TIM4);
	MyTimer_ActiveIT(TIM4, 1, updateAngle);
}
