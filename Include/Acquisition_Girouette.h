/**
 * @file acquisition_Girouette.h
 * @author Antoine Alaverdov (@Piazo)
 * @brief Lib to acquire the wind angle. (calls set_Sail)
 * @version 1.0
 * @date 2021-10-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "stm32f10x.h"

#ifndef acqGirouette
#define acqGirouette

/**
 * @brief Timer Used for the interruptions of angleGLOBAL aquisition
 * 
 */
#define TIMER_ACQ TIM3

#define TIMER_PWM TIM2
#define CHANNEL_PWM 1

#define GPIO_PWM GPIOA
#define PIN_PWM 0

#define GPIO_INIT GPIOA
#define PIN_INIT 8

#define TIM_INTERRUPT_ACQ TIM4


/**
 * @brief Setup the Timer TIMER_ACQ in Encoder mode. \n
 * Channel 1 and 2 are used. \n
 * Cf. STM32F103RB p.28 & following for Channels pinouts.
 */
void acqGir_set_timer_encoderMode(void);

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
 * @param GPIO Row on which I is plugged
 * @param pin Pin on which I is plugged
 */
void acqGir_config_Gir(GPIO_TypeDef * GPIO, char pin);

/**
 * @brief Enables the sails tacking functionnality on the ship.
 * 
 */
void gestionVoile_start(void);


void updateAngle(void);

#endif
