#include "stm32f10x.h"
#include "Usart-Driver.h"

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
	Usart->CR1 &= ~(0x1 << 3);
	Usart->CR1 |= (1 << 3); 
	//mettre le bit RE à 1 pour activer le récepteur
	Usart->CR1 &= ~(0x1 << 2);
	Usart->CR1 |= (1<<2);
}

void MyUSART_Send (USART_TypeDef * Usart, char Data) { //Data sur 8 bits
	Usart->DR &= ~(0xFF << 0); //255 en décimal
	Usart->DR |= (Data << 0); 
}

