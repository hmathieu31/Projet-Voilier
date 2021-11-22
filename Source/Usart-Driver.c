#include "Usart-Driver.h"

#include "Driver_GPIO.h"
#include "MyTimer.h"
#include "stm32f10x.h"
#include "stdio.h"

signed char recu;

void MyUSART_Init(USART_TypeDef* Usart) {
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    //Mettre le bit UE de USART_CR1 a 1
    Usart->CR1 &= ~(0x1 << 13);
    Usart->CR1 |= (1 << 13);
    //Programmer le nb de bits pour la longueur du mot envoy�, on met � 0
    Usart->CR1 &= ~(0x1 << 12);
    //Programmer le nb de bits stop (1 pour nous)
    //Usart->CR2 &= ~(0x3 << 12);
    //desired baud rate
    Usart->BRR &= ~(0x1FF << 4);  //511 en decimal : 1 pour 9 bits
    Usart->BRR |= (0x1D6 << 4);   //703 en decimal : val de la doc pour f=72MHz pour avoir 9601 Bd
    //first transmission an idle frame TE
    Usart->CR1 &= ~(0x1 << 3);
    Usart->CR1 |= (1 << 3);
	
    recu = 0;
	
    Usart->CR1 |= 1 << 5;  // RXNEIE
    NVIC->ISER[1] |= 1 << (37 - 32);
    NVIC->IP[USART1_IRQn] = 1 << 4;
	
    //mettre le bit RE a 1 pour activer le recepteur
    Usart->CR1 &= ~(0x1 << 2);
    Usart->CR1 |= (1 << 2);

    // Set bit TE to enable transmitter
    //Usart->CR1 |= (0x1 << 3);
}

void MyUSART_Send(USART_TypeDef* Usart) {  //Data sur 8 bits
		uint8_t length = 30;
		char buff[length];
		sprintf(buff, "Batterie à niveau : %d", 1000);
		for(int i = 0; i < length ; i++) {
			Usart->DR = buff[i];
			while ((Usart->SR & USART_SR_TXE) != USART_SR_TXE)                           // Polling on TXE to check if data was tranfered
			{
			}
		}
}

void USART1_IRQHandler(void) {
    recu = (signed char)USART1->DR;
    TournerPlateau(recu);
}

/** Appel�e par l'interruption */
void TournerPlateau(signed char valRecue) {
    //r�cup�rer la valeur du module Xbee
    //signed int rapport = USART1->DR;
    //si rapport >0 alors bit PC7 mis � 1
    if (valRecue > 0) {
        My_GPIO_Reset(GPIO_TURN_DIR, PIN_TURN_DIR);
        Set_Duty_PWM(TIM_PWM_TURN, CH_PWM_TURN, (valRecue % 101));  //modulo 100
    } else if (valRecue < 0) {                                      //si rapport <0 alors bit PC7 mis � 0 et rapport = -rapport
        My_GPIO_Set(GPIO_TURN_DIR, PIN_TURN_DIR);                   //bit de sens
        valRecue = -valRecue;
        Set_Duty_PWM(TIM_PWM_TURN, CH_PWM_TURN, (valRecue % 101));  //modulo 100
    } else {
        Set_Duty_PWM(TIM_PWM_TURN, CH_PWM_TURN, 0);
    }
    //Appeler PWM avec comme argument rapport (qui est en valeur absolue)
}

void CapControl_start() {
    MyGPIO_Init(GPIO_USART_RX, PIN_USART_RX, In_Floating);  // Correspond a l'USART en RX
    MyGPIO_Init(GPIO_USART_TX, PIN_USART_TX, 0xA);    // Correspond a l'USART en TX
    MyGPIO_Init(GPIO_PWM_TURN, PIN_PWM_TURN, AltOut_Ppull);  // Correspond a la PWM
    MyGPIO_Init(GPIO_PWM_TURN, PIN_TURN_DIR, Out_Ppull);     // Correspond au bit de direction

    MyTimer_Base_Init(TIM_PWM_TURN, 359, 9);  //ARR et PSC pour g�n�rer une PWM de 20 kHz
    Init_MyTimer_PWM(TIM_PWM_TURN, CH_PWM_TURN);
    MyTimer_Base_Start(TIM_PWM_TURN);

    MyUSART_Init(USART1);
}
