#include "stm32f10x.h"
#include "MyTimer.h"

void (* pFunc) (void);

void MyTimer_Base_Init ( TIM_TypeDef * Timer, unsigned short ARRarg, unsigned short PSCarg ){
	if (Timer==TIM1) RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	if (Timer==TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	if (Timer==TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	if (Timer==TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	Timer->ARR = ARRarg;
	Timer->PSC = PSCarg;
}
	void MyTimer_Base_Start (TIM_TypeDef * Timer){
		(Timer->CR1 |= 1<<0);
	}
	void MyTimer_Base_Stop (TIM_TypeDef * Timer){
		Timer->CR1 &= ~(1<<0);
	}
	
void MyTimer_ActiveIT (TIM_TypeDef * Timer, char Prio, void (*IT_function) (void)){
	Timer -> DIER |= 1<<0; //activation de l'interruption du timer
	if (Timer==TIM1){ NVIC -> ISER[0] |= 1<<25; NVIC -> IP[25] = Prio<<4;} //On autorise les interruption du timer x et on gere la prio
	if (Timer==TIM2){ NVIC -> ISER[0] |= 1<<28; NVIC -> IP[28] = Prio<<4;}
	if (Timer==TIM3){ NVIC -> ISER[0] |= 1<<29; NVIC -> IP[29] = Prio<<4;}
	if (Timer==TIM4){ NVIC -> ISER[0] |= 1<<30; NVIC -> IP[30] = Prio<<4;}
	
	pFunc = IT_function;
}

void TIM1_UP_IRQHandler(void){
	if (pFunc != 0) (*pFunc)();
	TIM1 -> SR &= ~(1<<0); //On reset le bit d'update d'interruption a zero	 
 }

void TIM2_IRQHandler(void){
	if (pFunc != 0) (*pFunc)();
	TIM2 -> SR &= ~(1<<0);
 }
 
void TIM3_IRQHandler(void){
	if (pFunc != 0) (*pFunc)();
	TIM3 -> SR &= ~(1<<0);
}
	
void TIM4_IRQHandler(void){
	if (pFunc != 0) (*pFunc)();
	TIM4 -> SR &= ~(1<<0);
}

/* Timer PWM Configuration */
void MyTimer_PWM(TIM_TypeDef * Timer, char Channel) {
	switch (Channel) {
		case 1:
			Timer->CCMR1 &= ~(0x01<<0); // Sets the Channel as Output (should already be default configuration)
			Timer->CCMR1 &= ~(0x7<<4);
			Timer->CCMR1 |= (0x01<<5) | (0x01<<6); // Sets 110 (mode 1) for the Channel 1
			Timer->CCMR1 |= (0x01<<3); // Enables the Channel's Preload Register
			Timer->CR1 |= (1<<7); // Sets the ARP bit

			Timer->CCER |= (0x01<<0); // Sets the CC1NE : OC1N signal is output
		
			if (Timer == TIM1) { // Special configuration for Timer 1
				Timer->BDTR |= (0x01<<15); // Sets the MOE bit (Main Output Enable)
			}
	
			break;
		
		case 2:
			Timer->CCMR1 &= ~(0x01<<8);
			Timer->CCMR1 &= ~(0x7<<12);
			Timer->CCMR1 |= (0x01<<13) | (0x01<<14);
			Timer->CCMR1 |= (0x01<<11);
			Timer->CCMR1 |= (0x01<<3);
		
			Timer->CCER |= (0x01<<4); // Sets the CC1NE : OC1N signal is output
		
		if (Timer == TIM1) { // Special configuration for Timer 1
				Timer->BDTR |= (0x01<<15); // Sets the MOE bit (Main Output Enable)
				
			}
		
			break;
		
		case 3:
			Timer->CCMR1 &= ~(0x01<<0);
			Timer->CCMR1 &= ~(0x7<<4);
			Timer->CCMR1 |= (0x01<<5) | (0x01<<6);
		
			Timer->CCER |= (0x01<<8); // Sets the CC1NE : OC1N signal is output
		
		if (Timer == TIM1) { // Special configuration for Timer 1
				Timer->BDTR |= (0x01<<15); // Sets the MOE bit (Main Output Enable)
			}
			break;
		
		case 4:
			Timer->CCMR2 &= ~(0x01<<8);
			Timer->CCMR2 &= ~(0x7<<12);
			Timer->CCMR2 |= (0x01<<13) | (0x01<<14);
			Timer->CCMR2 |= (0x01<<11);
		
			Timer->CCER |= (0x01<<12); // Sets the CC1NE : OC1N signal is output
		
		if (Timer == TIM1) { // Special configuration for Timer 1
				Timer->BDTR |= (0x01<<15); // Sets the MOE bit (Main Output Enable)
				
			}
			break;
	}
	Timer->EGR |= (0x01<<0); // Initializes all registers by setting UG
}


/* Timer PWM Start */
void MyTimer_PWM_StartPWM(TIM_TypeDef * Timer) {
	MyTimer_Base_Start (Timer);
}

/* Sets the duty cycle of PWM */
void MyTimer_PWM_SetDC(TIM_TypeDef * Timer, char Channel, unsigned short dc) {
	unsigned short arr = Timer->ARR;
	
	unsigned short compareval = (dc* arr) / 100;
	switch (Channel) {
		case 1:
			Timer->CCR1 = compareval;
			break;
		
		case 2:
			Timer->CCR2 = compareval;
			break;
		
		case 3:
			Timer->CCR3 = compareval;
			break;
		
		case 4:
			Timer->CCR4 = compareval;
			break;
	}
}
