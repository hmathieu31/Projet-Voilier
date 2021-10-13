#include "stm32f10x.h"
#include "MyADC.h"

float Init_ADC_Single_Conv(ADC_TypeDef *ADC, char Channel){
	if (ADC==ADC1) RCC->APB2ENR |= (1<<9);
	if (ADC==ADC2) RCC->APB2ENR |= (1<<10);
	
	ADC->CR2 |= (1<<0);
	
	
}
