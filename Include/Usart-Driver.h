#include "stm32f10x.h"

#ifndef Clemou 
#define Clemou

void MyUSART_Init (USART_TypeDef * Usart);
void MyUSART_Send (USART_TypeDef * Usart, char Data);

#endif
