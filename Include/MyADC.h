#include "stm32f10x.h"



#ifndef Roger
#define Roger

	void Setup_ADC();

	/**
	 * @brief Reads the ADC value then signals to the USART it has to be sent
	 * 
	 */
	void ADC_Start_Conversion();
	
	void init_ADC(ADC_TypeDef *ADC);
	void declenchementConversionInterrupt(TIM_TypeDef * Timer);
		
#endif

