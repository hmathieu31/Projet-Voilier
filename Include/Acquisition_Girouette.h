#include "stm32f10x.h"


#ifndef acqGirouette
#define acqGirouette

void setTimerEncoderMode(TIM_TypeDef * Timer);
int interruptAngle(TIM_TypeDef * Timer);
void getAngle();

#endif