#include "stm32f10x.h"
#include "MyTimer.h"
#include "Driver_GPIO.h"
#include "Acquisition_Girouette.h"
#include "set_Sail.h"


int sailAngleGLOBAL;

int main(void){

	int windAngle = getAngle(275);

	sailAngleGLOBAL = calcSailsAngle(windAngle);
	
	while(1) {
		;
	}
}
