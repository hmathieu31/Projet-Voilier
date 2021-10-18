#include "Acquisition_Girouette.h"
#include "set_Sail.h"
#include "stm32f10x.h"


int main(void) {

    setTimerEncoderMode();
    configGir(GPIOA, 8);

}