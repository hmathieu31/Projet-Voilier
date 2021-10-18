#include "stm32f10x.h"

#define TIMER_ACQ TIM3

#ifndef acqGirouette
#define acqGirouette

void setTimerEncoderMode();
void interruptAngle();
void configGir(GPIO_TypeDef * GPIO, char pin);

#endif
