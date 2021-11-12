#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "Usart-Driver.h"

//int pourcent ;


int main(void){

	
	MyGPIO_Init( GPIOA , 8,  AltOut_Ppull ); // Correspond à l'USART

	MyGPIO_Init(GPIOB, 6, AltOut_Ppull); // Correspond à la PWM

	
	MyTimer_Base_Init(TIM4, 9999 , 3599); //ARR et PSC

	
	Init_MyTimer_PWM(TIM4,1);
	
	MyUSART_Init(USART1);

	
	
	/*
	//Appeler PWM avec comme argument rapport (qui est en valeur absolue)
	MyTimer_Base_Start(TIM4);
	Set_Duty_PWM(TIM4,1,80); //modulo 100 */
	
	
	while(1) {
		//if (GPIOC->IDR[]){
			//GPIOC->ODR |= (0x01 << 12);
		//}
		//Set_Duty_PWM(TIM1,1,pourcent);
		//TournerPlateau();
	}
	
}
