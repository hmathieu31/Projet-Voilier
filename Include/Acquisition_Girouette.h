/**
 * @file acquisition_Girouette.h
 * @author Antoine Alaverdov (@Piazo)
 * @brief 
 * @version 0.1
 * @date 2021-10-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "stm32f10x.h"

/**
 * @brief Timer Used for the interruptions of angleGLOBAL aquisition
 * 
 */
#define TIMER_ACQ TIM3

#ifndef acqGirouette
#define acqGirouette

/**
 * @brief Setup the Timer TIMER_ACQ in Encoder mode. \n
 * Channel 1 and 2 are used. \n
 * Cf. STM32F103RB p.28 & following for Channels pinouts.
 */
void acqGir_set_timer_encoderMode();

/**
 * @brief Initializes Timer to generate interruptions every 0.5s
 * to acquire the angle from the weathercock and generate the PWM
 * accordingly.
 * 
 * @param Timer
 */
void acqGir_interrupt_angle(TIM_TypeDef * Timer);

/**
 * @brief Waits for the weathercock to turn 360° to finish config.
 * ! Not functional/tested in current state
 * @param GPIO Row on which I is plugged
 * @param pin Pin on which I is plugged
 */
void acqGir_config_Gir(GPIO_TypeDef * GPIO, char pin);

#endif
