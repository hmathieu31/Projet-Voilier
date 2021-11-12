#include "stm32f10x.h"
#include "Usart-Driver.h"
#include "Driver_GPIO.h"
#include "MyTimer.h"

signed int recu ;

void MyUSART_Init (USART_TypeDef * Usart) {
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
	//Usart->CR1 &= ~(0x1 << 3);
	//Usart->CR1 |= (1 << 3); 
	recu = 0 ;
	Usart->CR1 |= 1<<5 ; // RXNEIE 
	NVIC->ISER[1] |= 1<< (37-32);
	NVIC->IP[USART1_IRQn] = 1<<4 ;
	//mettre le bit RE à 1 pour activer le récepteur
	Usart->CR1 &= ~(0x1 << 2);
	Usart->CR1 |= (1<<2);
}

void MyUSART_Send (USART_TypeDef * Usart, char Data) { //Data sur 8 bits
	Usart->DR &= ~(0xFF << 0); //255 en décimal
	Usart->DR |= (Data << 0); 
}

void USART1_IRQHandler(void)
{

	recu = USART1->DR ;
}	


void TournerPlateau(void) {
	//récupérer la valeur du module Xbee
	//signed int rapport = USART1->DR;
	//si rapport >0 alors bit PC7 mis à 1
	if (recu >= 0) {
		My_GPIO_Reset(GPIOC,7);
	}
	else { //si rapport <0 alors bit PC7 mis à 0 et rapport = -rapport
		My_GPIO_Set(GPIOC,7); //bit de sens
		recu = -recu;
	}
	//Appeler PWM avec comme argument rapport (qui est en valeur absolue)
	Set_Duty_PWM(TIM1,1,(recu % 100));//modulo 100
}
