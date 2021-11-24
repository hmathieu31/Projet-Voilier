#include "Acquisition_Girouette.h"
#include "Usart-Driver.h"
#include "set_Sail.h"
#include "stm32f10x.h"
#include "MyADC.h"

int main(void) {
	gestionVoile_start();
    CapControl_start();
    init_ADC(ADC1);
	
    while (1) {
    }
}
