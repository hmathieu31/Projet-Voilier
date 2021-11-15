#include "stm32f10x.h" 
void (* pFnc1) (void) ; /* déclaration d’un pointeur de fonction */
void (* pFnc2) (void) ; /* déclaration d’un pointeur de fonction */
void (* pFnc3) (void) ; /* déclaration d’un pointeur de fonction */
void (* pFnc4) (void) ; /* déclaration d’un pointeur de fonction */


void MyTimer_Base_Init(TIM_TypeDef * Timer, int ARR , int PSC){
	/*Création Timer, et on lui donne une horloge*/
	if(Timer == TIM1){ //TIM1 est sur APB2 les autres sur APB1
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}
	
		if(Timer == TIM2){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	}
		
		if(Timer == TIM3){
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	}
		
		if(Timer == TIM4){
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	}
	
	/*Configuration Timer Registres*/
	Timer->ARR = ARR;
	Timer->PSC = PSC;
	
	/*Lancement Timer*/
	Timer->CR1 = Timer->CR1 | ( 1 << 0);
}

void MyTimer_Base_Start(TIM_TypeDef * Timer){
	Timer->CCR1 |= 1<<0; // CCR1 est pareil que CEN
}

void MyTimer_Base_Stop(TIM_TypeDef * Timer){
	Timer->CCR1 &= ~(1<<0);
}

void MyTimer_ActiveIT (TIM_TypeDef * Timer , char Prio, void (* IT_function ) ( void )) {
	// au niveau du timer
	// Mettre UIE a 1 ==> declenche l'interruption
	if(Timer == TIM1){
		Timer->DIER |= 1<<0 ; 
	
		// au niveau du coeur
		// Mettre a 1 le bit dans le bon ISER ==> autorise le periph a detourner le coeur 28 pour TIM2
		NVIC->ISER[0] = NVIC->ISER[0] | (1 << 25 );
		// Fixer une priorite dans IP[???]
		NVIC->IP[25] = (Prio << 4);
		
		pFnc1 = IT_function ;
	}
	else if(Timer == TIM2){
		Timer->DIER |= 1<<0 ; //
		
		// au niveau du coeur
		// Mettre a 1 le bit dans le bon ISER ==> autorise le periph a detourner le coeur 28 pour TIM2
		NVIC->ISER[0] = NVIC->ISER[0] | (1 << 28);
		// Fixer une priorite dans IP[???]
		NVIC->IP[28] = (Prio << 4); 
		pFnc2 = IT_function ;
	
	}// on pousse de 4 pour le mettre au bit de poids fort, 7 est la priorité 
	
	else if (Timer == TIM3) {
		Timer->DIER |= 1<<0 ; //
	
		// au niveau du coeur
		// Mettre a 1 le bit dans le bon ISER ==> autorise le periph a detourner le coeur 28 pour TIM2
		NVIC->ISER[0] = NVIC->ISER[0] | (1 << 29);
		// Fixer une priorite dans IP[???]
		NVIC->IP[29] = (Prio << 4);
		pFnc3 = IT_function ;
	}
	else {//TIM4 
		Timer->DIER |= 1<<0 ; //
	
		// au niveau du coeur
		// Mettre a 1 le bit dans le bon ISER ==> autorise le periph a detourner le coeur 28 pour TIM2
		NVIC->ISER[0] = NVIC->ISER[0] | (1 << 30);
		// Fixer une priorite dans IP[???]
		NVIC->IP[30] = (Prio << 4);
		pFnc4 = IT_function ;
	}
}



void TIM1_IRQHandler () {
	if (pFnc1 != 0)
		(*pFnc1) (); /* appel indirect de la fonction */
	//Rabaisser le flag d'interruption UIF
	TIM1->SR &= ~(1<<0); // UIF
}
		//Redéfinition du handler
void TIM2_IRQHandler () {
	if (pFnc2 != 0)
		(*pFnc2) (); /* appel indirect de la fonction */
	//Rabaisser le flag d'interruption UIF
	TIM2->SR &= ~(1<<0); // UIF
}
	
void TIM3_IRQHandler () {
	if (pFnc3!= 0)
		(*pFnc3) (); /* appel indirect de la fonction */
	//Rabaisser le flag d'interruption UIF
	TIM3->SR &= ~(1<<0); // UIF
}
	
void TIM4_IRQHandler () {
	if (pFnc4 != 0)
		(*pFnc4) (); /* appel indirect de la fonction */
	//Rabaisser le flag d'interruption UIF
	TIM4->SR &= ~(1<<0); // UIF
}
	

void Init_MyTimer_PWM (TIM_TypeDef * Timer, char Channel) {
	//Permet d'initialiser le timer en mode pwm
	//ne fait pas l'init des GPIO et la config des timers
	if (Channel == 1) {
		Timer->CCMR1 &= ~(7<<4); //110 en mode 1, chanel 1 donc CCMR1 et sur OC1M
		Timer->CCMR1 |= (6<<4);
		Timer->CCER |= 1<<0 ;
	}
	 else if (Channel == 2){
		 Timer->CCMR1 &= ~(7<<12); //110 en mode 1, chanel 2 donc CCMR1 et sur OC2M
		 Timer->CCMR1 |= (6<<12);
		 Timer->CCER |= 1<<4 ;
	 }
	 else if (Channel == 3){
		 Timer->CCMR2 &= ~(7<<4); //110 en mode 1, chanel 3 donc CCMR2 et sur OC3M
		 Timer->CCMR2 |= (6<<4);
		 Timer->CCER |= 1<<8 ;
	 }
	else {
		Timer->CCMR2 &= ~(7<<12); //110 en mode 1, chanel 4 donc CCMR2 et sur OC4M
		Timer->CCMR2 |= (6<<12);
		Timer->CCER |= 1<<12 ;
	}
	
	if (Timer==TIM1)
	{
		Timer->BDTR |= 1<<15;
	}
	
}
// On appelle MyGPIO_Init en demandant de configurer la pin en alternate

//CC3E

void Set_Duty_PWM (TIM_TypeDef * Timer, char Channel, int pourcent) { // Le pourcentage est donnée sous la forme: 90 veut dire 90%
	
	if (Channel == 1) {
		Timer -> CCR1 = (Timer -> ARR) * pourcent / 100 ;
	}
	 else if (Channel == 2){
		 Timer -> CCR2 = (Timer -> ARR) * pourcent / 100;
	 }
	 else if (Channel == 3){
		 Timer -> CCR3 = (Timer -> ARR) * pourcent / 100;
	 }
	else {
		Timer -> CCR4 = (Timer -> ARR) * pourcent / 100;
	}
	
	
}
