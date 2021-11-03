#ifndef ADC_H
#define ADC_H
#include "MyGPIO.h"
#include "stm32f10x.h"

void configure_adc_in( char voie);
int convert_single(void);
#endif
