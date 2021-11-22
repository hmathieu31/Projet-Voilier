#include "Acquisition_Girouette.h"
#include "Usart-Driver.h"
#include "set_Sail.h"
#include "stm32f10x.h"

int main(void) {
//  gestionVoile_start();
		CapControl_start();
		MyUSART_Send(USART1);

	
    while (1) {

    }
}
