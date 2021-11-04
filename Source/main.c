#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "Usart-Driver.h"

void Ma_Fonction_IT (){//fonction callback
	//utiliser le toggle de gpio
	My_GPIO_Toggle(GPIOA,5);
}

//int pourcent ;


int main(void){
	
	/* Initialization of GPIOC 13 as Ouput OpenDrain 
	MyGPIO_Struct gp = {GPIOC, 10, AltOut_Ppull};
	MyGPIO_Init(&gp);
	
	// Initialization of Timer1 with period 500ms invoking function Callback /
	MyTimer_Base_Init (TIM1,36000,1000);
	MyTimer_Base_Start (TIM1);
	MyTimer_ActiveIT(TIM1, 1, CallBack);

	*/
	//MyUSART_Init(USART1);
	//MyUSART_Send(USART1,70);
/*	MyTimer_PWM_StartPWM(TIM1);
	MyTimer_PWM_SetDC(TIM1, 1, 70);
	Communication();*/
	// configurer la PWM
	
	MyGPIO_Init( GPIOA ,10 ,In_Floating );
	MyUSART_Init(USART1);
	
	MyTimer_Base_Init(TIM1, 9999 , 3599); //ARR et PSC
	MyGPIO_Init( GPIOA , 8,  AltOut_Ppull );
	Init_MyTimer_PWM(TIM1,1);
	//MyTimer_ActiveIT (TIM1 , 1, Ma_Fonction_IT);
	
	
	while(1) {
		//if (GPIOC->IDR[]){
			//GPIOC->ODR |= (0x01 << 12);
		//}
		//Set_Duty_PWM(TIM1,1,pourcent);
		TournerPlateau();
	}
	
}
