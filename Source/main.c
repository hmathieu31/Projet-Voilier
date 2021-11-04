#include "Acquisition_Girouette.h"
#include "set_Sail.h"
#include "stm32f10x.h"


int main(void) {

  acqGir_set_timer_encoderMode();
  //CONFIGURER LE GPIO acqGir_config_Gir(GPIOA, 8);
	acqGir_interrupt_angle(TIM4);

	while(1){
	}
	}