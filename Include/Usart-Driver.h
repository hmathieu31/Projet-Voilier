#include "stm32f10x.h"

#ifndef Clemou 
#define Clemou

void MyUSART_Init (USART_TypeDef * Usart);
void MyUSART_Send (USART_TypeDef * Usart, char Data);
void USART1_IRQHandler(void);
void TournerPlateau(signed char recu);

void CapControl_start(void);

#endif
