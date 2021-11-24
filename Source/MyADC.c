#include "stm32f10x.h"
#include "MyADC.h"
#include "MyTimer.h"
#include "Acquisition_Girouette.h"
#include "Usart-Driver.h"
#include "Driver_GPIO.h";

ADC_TypeDef *ADC;
int conversionADC;

void Setup_ADC(){
	if (ADC==ADC1) RCC->APB2ENR |= (1<<9); // Activates clock for peripheral
	if (ADC==ADC2) RCC->APB2ENR |= (1<<10);
	RCC->CFGR |= 2<< 14 ; //prescaler 
	ADC->CR2 |= (1<<0);				//on enable la conversion
	ADC->CR2 |= (7<<12);			//On met la SWS pour le declenchement de la conversion
	ADC->SQR3 |= 5<<0;				//on regle sur le channel 5
	ADC->CR2 |= 1<<20;				// Sets the ADC in external trigger mode
	MyGPIO_Init(GPIOA, 5, AltOut_Ppull); // Inits the Pin corresponding to channel 5 in ADC1
}

void ADC_Start_Conversion(){
	ADC->CR2 |= (1<<22);
//	while ((ADC->SR & ADC_SR_EOC) != ADC_SR_EOC){}
	conversionADC = (ADC->DR); //valeur max conversionADC = FFF soit 4095 en decimal
	if(conversionADC < 2730){
		MyUSART_Send(USART1);
	}
	//il reste plus qu'a transformer conversion ADC en % de la puissance qu'on veut
	// et le tour est joue les bg
}



void init_ADC(ADC_TypeDef *ADCmain){
	ADC=ADCmain;
	Setup_ADC();
}

