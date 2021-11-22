#include "Acquisition_Girouette.h"

#include "Driver_GPIO.h"
#include "MyADC.h"
#include "MyTimer.h"
#include "set_Sail.h"
#include "stm32f10x.h"

int angleGLOBAL;
int interruptGlobal = 0;

void acqGir_set_timer_encoderMode() {
    MyTimer_Base_Init(TIMER_ACQ, 1439, 0);
    //On active le mode encoder qui permet de transformer le timer en compteur
    TIMER_ACQ->SMCR |= 3 << 0;
    //On gere le registre CCER pour que les signaux soient captures sur un front montant
    TIMER_ACQ->CCER &= ~(0xAA);  //TI1 and TI2 polarity
    //On enable le counter
    TIMER_ACQ->CR1 |= 1 << 0;

    TIMER_ACQ->CCMR1 &= ~(0xf << 4);
    TIMER_ACQ->CCMR1 &= ~(0xf << 12);  //Compte tous les fronts
    TIMER_ACQ->CCMR1 |= 2;             // T1FP1 mapped on TI1
    TIMER_ACQ->CCMR1 |= (2 << 8);      // T2FP2 mapped on TI2

    TIMER_ACQ->CNT = 0;
}

void interruptFunc() {
    angleGLOBAL = (TIMER_ACQ->CNT) / 4;

    interruptGlobal++;
    if (interruptGlobal == 10) {
        ADC_Start_Conversion();
        interruptGlobal = 0;
    }

    sSail_set_servo(sSail_calc_angle(angleGLOBAL));
}

void acqGir_config_Gir(GPIO_TypeDef* GPIO, char pin) {
    MyGPIO_Init(GPIO, pin, In_PullUp);
    while (!MyGPIO_Read(GPIO, pin)) {
    }
    MyTimer_Base_Start(TIMER_ACQ);
    TIMER_ACQ->CNT = 0;
    angleGLOBAL = 0;
}

void acqGir_interrupt_angle(TIM_TypeDef* Timer) {
    MyTimer_Base_Init(Timer, 7100, 1000);
    MyTimer_Base_Start(Timer);
    MyTimer_ActiveIT(Timer, 1, interruptFunc);
}

void gestionVoile_start() {
    acqGir_set_timer_encoderMode();
    acqGir_config_Gir(GPIO_INIT, PIN_INIT);
    acqGir_interrupt_angle(TIM_INTERRUPT_ACQ);
}
