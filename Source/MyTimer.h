#include "stm32f10x.h"

#ifndef Raymond
#define Raymond

void MyTimer_Base_Init ( TIM_TypeDef * Timer, unsigned short ARRarg, unsigned short PSCarg );

void MyTimer_Base_Start (TIM_TypeDef * Timer);
void MyTimer_Base_Stop (TIM_TypeDef * Timer);

#endif

#ifndef Didier
#define Didier

void MyTimer_ActiveIT (TIM_TypeDef * Timer, char Prio, void (*IT_function) (void));

#endif
