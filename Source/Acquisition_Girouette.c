#include "stm32f10x.h"
#include "acquisition_Girouette.h"
#include "set_Sail.h"
#include "MyTimer.h"

int angleGLOBAL;


void acqGir_set_timer_encoderMode() {
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

void updateAngle(){
	angleGLOBAL = TIMER_ACQ->CNT;

	/* 
		Appel de la lib set_Sail pour émission de la PWM en fonction de l'angle obtenu
	 */
	
	sSail_set_servo(sSail_calc_angle(angleGLOBAL));
}

void acqGir_config_Gir(GPIO_TypeDef * GPIO, char pin){
	while ((GPIO->IDR >> pin) &1 == 0){
	}
	TIMER_ACQ->CNT = 0;
	angleGLOBAL = 0;
}


void acqGir_interrupt_angle(TIM_TypeDef * Timer){
	MyTimer_Base_Init (Timer,36000,1000);
	MyTimer_Base_Start (Timer);
	MyTimer_ActiveIT(Timer, 1, updateAngle);
}
