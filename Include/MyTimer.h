/**
 * @file MyTimer.h
 * @author Hugo Mathieu (hmathieu@insa-toulouse.fr)
 * @brief Driver to control Timers and PWMs
 * @version 0.1
 * @date 2021-10-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "stm32f10x.h"

#ifndef Raymond
#define Raymond

/**
 * @brief Initializes the selected Timer
 * 
 * @param Timer
 * @param ARRarg Value for the Auto Reload Register
 * @param PSCarg Value for the Prescaler
 */
void MyTimer_Base_Init ( TIM_TypeDef * Timer, unsigned short ARRarg, unsigned short PSCarg );

/**
 * @brief Starts the timer
 * 
 * @param Timer 
 */
void MyTimer_Base_Start (TIM_TypeDef * Timer);

/**
 * @brief Stops the timer
 * 
 * @param Timer 
 */
void MyTimer_Base_Stop (TIM_TypeDef * Timer);

/**
	* @brief Active le chanel spécifié sur Timer \n
	* Ne configure pas l'I/O ni ne règle la période de la PWM
	* @param Timer Timer1..4 to be configured
	* @param Channel Channel spécifié à activer
	*/
void MyTimer_PWM(TIM_TypeDef * Timer, char Channel);

/**
 * @brief Starts the PWM on selected Timer
 * 
 * @param Timer 
 */
void MyTimer_PWM_StartPWM(TIM_TypeDef * Timer);

/**
 * @brief Sets the duty cycle of PWM
 * 
 * @param Timer Timer on which the PWM is based
 * @param Channel Channel used by the PWM
 * @param dc Duty cycle to set
 */
void MyTimer_PWM_SetDC(TIM_TypeDef * Timer, char Channel, unsigned short dc);

/**
 * @brief Calls the function on Timer's interruption
 * 
 * @param Timer 
 * @param Prio Priority of the interruption
 * @param IT_function Function called on interrupt
 */
void MyTimer_ActiveIT (TIM_TypeDef * Timer, char Prio, void (*IT_function) (void));

#endif
