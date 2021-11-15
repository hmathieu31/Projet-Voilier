#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"

#define In_Floating 4 //0x0100  a comple te r
#define In_PullDown 8 //0x1000 a comple te r
#define In_PullUp 8 //0x1000 a comple te r
#define In_Analog 0 //0x0000 a comple te r
#define Out_Ppull 2 //0x0010 a comple te r
#define Out_OD 6 //0x0110 a comple te r
#define AltOut_Ppull 10 //0x1010 a comple te r
#define AltOut_OD 14 //0x1110 a comple te r
void MyGPIO_Init (GPIO_TypeDef *  GPIO, int pin, char CONF ) ;
int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ; // renv oie 0 ou a u t re chose d i f f e r e n t de 0
void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) ;
#endif
