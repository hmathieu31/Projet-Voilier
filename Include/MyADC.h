#include "stm32f10x.h"



#ifndef Roger
#define Roger

	void Setup_ADC();
	void ADC_Start_Conversion();
	void init_ADC(ADC_TypeDef *ADC);
	void declenchementConversionInterrupt(TIM_TypeDef * Timer);
		
#endif

