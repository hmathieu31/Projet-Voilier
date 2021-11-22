/**
 * @file Usart-Driver.h
 * @author @Clemence-Lemeilleur @MaCarina
 * @brief 
 * @version 1.0
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "stm32f10x.h"

#ifndef Clemou 
#define Clemou


#define GPIO_TURN_DIR GPIOC
#define PIN_TURN_DIR 7

#define TIM_PWM_TURN TIM2
#define CH_PWM_TURN 2
#define GPIO_PWM_TURN GPIOA
#define PIN_PWM_TURN 1

#define GPIO_USART_RX GPIOA
#define PIN_USART_RX 10
#define GPIO_USART_TX GPIOA
#define PIN_USART_TX 9


void MyUSART_Init (USART_TypeDef * Usart);
void MyUSART_Send (USART_TypeDef * Usart, char Data);
void USART1_IRQHandler(void);
void TournerPlateau(signed char recu);

void CapControl_start(void);

void MyUSART_Test_Send(void);

#endif
