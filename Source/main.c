#include "Acquisition_Girouette.h"
#include "set_Sail.h"
#include "stm32f10x.h"

int sailAngleGLOBAL;

int main(void) {

    int windAngle = acqGir_get_angle(260);

    sailAngleGLOBAL = sSail_calc_angle(windAngle);
    sSail_set_servo(sailAngleGLOBAL);

    while (1) {
        ;
    }
}
