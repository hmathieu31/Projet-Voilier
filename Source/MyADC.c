#include "stm32f10x.h"
#include "MyADC.h"
#include "MyTimer.h"
#include "Acquisition_Girouette.h"

ADC_TypeDef *ADC;
int conversionADC;

void Setup_ADC(){
	if (ADC==ADC1) RCC->APB2ENR |= (1<<9); // Activates clock for peripheral
	if (ADC==ADC2) RCC->APB2ENR |= (1<<10);
	RCC->CFGR |= 2<< 14 ; //prescaler 
	ADC->CR2 |= (1<<0);				//on enable la conversion
	ADC->CR2 |= (7<<12);			//On met la SWS pour le declenchement de la conversion
	ADC->SQR3 |= 1<<0;				//on regle sur le channel 1
	ADC->CR2 |= 1<<20;
}

void ADC_Start_Conversion(){
	ADC->CR2 |= (1<<22);
//	while ((ADC->SR & ADC_SR_EOC) != ADC_SR_EOC){}
	conversionADC = (ADC->DR);
	if(conversionADC < 1365){
		//messageErreur();
	}
	//il reste plus qu'a transformer conversion ADC en % de la puissance qu'on veut
	// et le tour est joué les bg
}



void init_ADC(ADC_TypeDef *ADCmain){
	ADC=ADCmain;
	Setup_ADC();
}

