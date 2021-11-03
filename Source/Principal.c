#include "../Drivers/MyTimer.h" 
#include "../Drivers/MyGPIO.h" 
#include "stm32f10x.h" 
#include "../Drivers/ADC.h" 

void Ma_Fonction_IT (){//fonction callback
	//utiliser le toggle de gpio
	MyGPIO_Toggle(GPIOA,5);
}

int pourcent ;




signed int recu ;
void MyUSART_Init (USART_TypeDef * Usart) {
	
	//conf des GPIO
	//MyGPIO_Init(GPIOA,10
	
	
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	
	//Mettre le bit UE de USART_CR1 à 1
	Usart->CR1 &= ~(0x1 << 13);
	Usart->CR1 |= (1<<13); 
	//Programmer le nb de bits pour la longueur du mot envoyé, on met à 0
	Usart->CR1 &= ~(0x1 << 12);
	//Programmer le nb de bits stop (1 pour nous)
	Usart->CR2 &= ~(0x3 << 12);
	//desired baud rate
	Usart->BRR &= ~(0x1FF << 4); //511 en décimal : 1 pour 9 bits
	Usart->BRR |= (0x2BF << 4); //703 en décimal : val de la doc pour f=72MHz pour avoir 9601 Bd
	//first transmission an idle frame TE
	/*Usart->CR1 &= ~(0x1 << 3);
	Usart->CR1 |= (1 << 3); */
	recu = 0 ;
	Usart->CR1 |= 1<<5 ; // RXNEIE 
	NVIC->ISER[1] |= 1<< (37-32);
	NVIC->IP[USART1_IRQn] = 1<<4 ;
	
}




int main ( void )
{
	/*
	pourcent =0;	
	-------PARTIE SUR LE GPIO et Timer et Interruptions la PWM---------*/
	//MyGPIO_Init(GPIOA,5,Out_Ppull);
	/*MyGPIO_Init(GPIOC,13,In_Floating);
		
	MyTimer_Base_Init (TIM2, 9999 , 3599 ) ;

	MyTimer_Base_Start(TIM2) ;
	Init_MyTimer_PWM(TIM2,2); */
		
	//MyTimer_ActiveIT (TIM2 , 7, Ma_Fonction_IT) ;
		
	/*	while (1)
			{
		if (MyGPIO_Read(GPIOC,13)==0) {
			MyGPIO_Set(GPIOA,5);
		}
		else {
			MyGPIO_Reset(GPIOA,5);
		}
			}*/
	
		/*-------PARTIE SUR ADC---------*/
	
	/*//configuration de la PWM
	MyTimer_Base_Init(TIM3, 9999 , 3599); //ARR et PSC
	MyGPIO_Init( GPIOA , 6,  AltOut_Ppull );
	Init_MyTimer_PWM(TIM3,1);
	Set_Duty_PWM(TIM3,1,pourcent);
	
	//configuration ADC
	MyGPIO_Init( GPIOB , 0,  In_Analog );
	configure_adc_in(8);
	
	//démarrage PWM
	MyTimer_Base_Start(TIM3);
	*/
	
	MyGPIO_Init( GPIOA ,10 ,In_Floating );
	MyUSART_Init(USART1);
	
	while(1){
		//pourcent = convert_single(); //conversion
		//Set_Duty_PWM(TIM3,1, pourcent *100 /4095); //car on ramène les valeurs entre 0 et 4095 car l'adc est sur 12 bits soit 2^^12 = 4096
	}
	
}

void USART1_IRQHandler(void)
{
	recu = USART1->DR ;
 }	
