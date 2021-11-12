/**
 * @file set_Sail.h
 * @author Hugo Mathieu (hmathieu@insa-toulouse.fr)
 * @brief Lib to trim the sail according to a given angle
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "stm32f10x.h"

#define TIMER_PWM TIM2
#define CHANNEL_PWM 1
#define GPIO_PWM GPIOA
#define PIN_PWM 0

/**
 * @brief Calculates the angle to trim the sails in function of wind angle
 * 
 * @param girAngle Wind angle returned by acq_Girouette
 * @return int Angle of sails
 */
int sSail_calc_angle(int girAngle);

/**
 * @brief Emits the PWM to set the servomotor to angle according to sailsAngle
 * 
 * @param sailsAngle Angle to trim the sails to
 */
void sSail_set_servo(int sailsAngle);
