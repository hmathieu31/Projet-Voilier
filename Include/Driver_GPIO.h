/**
 * @file Driver_GPIO.h
 * @author Hugo Mathieu (hmathieu@insa-toulouse.fr)
 * @brief Driver to control GPIOs
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"


typedef struct {
	GPIO_TypeDef * GPIO;
	char GPIO_Pin;
	char GPIO_Conf;
} MyGPIO_Struct;

/**
 * @brief Input - Floating mode
 * 
 */
#define In_Floating 0x4
/** @brief Input - Pull-Down mode (<b> ODR bit corresponding to the Pin MUST be SET aswell </b>) */
#define In_PullDown 0x8
/** @brief Input - Pull-up mode (<b> ODR bit corresponding to the Pin MUST be RESET aswell </b>) */
#define In_PullUp 0x8
/** @brief Input - Analogic mode */
#define In_Analog 0x0
/** @brief Output - Push & Pull mode */
#define Out_Ppull 0x1
/** @brief Output - Open Drain mode */
#define Out_OD 0x5
/** @brief Output - Alternate Push & Pull mode */
#define AltOut_Ppull 0x9
/** @brief Ouput - Alternate Open Drain mode */
#define AltOut_OD 0xD 

/**
 * @brief Initializes the GPIO in chosen configuration
 * 
 * @param GPIOStruct Struct containing the Pin and chosen Configuration 
 */
void MyGPIO_Init(MyGPIO_Struct * GPIOStruct);

/**
 * @brief Reads the value on GPIO (INPUT mode only)
 * 
 * @param GPIO Struct containing all GPIO registers
 * @param GPIO_PIN Pin to be read
 * @return Binary value on the GPIO Pin
 */
int MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_PIN);

/**
 * @brief Sets the GPIO (OUTPUT mode only)
 * 
 * @param GPIO Struct containing all GPIO registers
 * @param GPIO_PIN Pin to be written on
 */
void My_GPIO_Set(GPIO_TypeDef * GPIO, char GPIO_PIN);

/**
 * @brief Resets the GPIO (OUTPUT mode only)
 * 
 * @param GPIO Struct containing all GPIO registers
 * @param GPIO_PIN Pin to be written on
 */
void My_GPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_PIN);

/**
 * @brief Change GPIO's state. If SET == 0, resets it ; else, sets it \n
 * (OUTPUT mode only) 
 * 
 * @param GPIO Struct containing all GPIO registers
 * @param GPIO_PIN Pin to be written on
 */
void My_GPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_PIN);

#endif
