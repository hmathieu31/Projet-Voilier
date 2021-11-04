#include "stm32f10x.h"
#include "Driver_GPIO.h"

void MyGPIO_Init ( GPIO_TypeDef * GPIO , int GPIO_Pin, char CONF ){
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;

	if (GPIO_Pin < 8){ 
		GPIO->CRL &= ~(0xF << (GPIO_Pin*4));
		GPIO->CRL |= (CONF << (GPIO_Pin*4)) ;
		//GPIO->CRL |= (0x1 << (GPIO_Pin*4)) ;| (0x2 <<(GPIO_Pin*4+2));
	}else{ 
		GPIO->CRH &= ~(0xF << ((GPIO_Pin-8)*4));
		GPIO->CRH |= (CONF << ((GPIO_Pin-8)*4));
		//GPIO->CRH |= (0x1 << (GPIO_Pin*4));
	}
}  
/*
void MyGPIO_Init(MyGPIO_Struct * GPIOStructPtr) {
	char GPIO_Pin = GPIOStructPtr->GPIO_Pin;
	char GPIO_Conf = GPIOStructPtr->GPIO_Conf;
	RCC->APB2ENR |= (0x01 << 2)|(0x01 << 3)|(0x01<<4);
	
	if(GPIO_Pin < 8) { // Init for the first 8 pins
		GPIOStructPtr->GPIO->CRL &= ~(0xF << (GPIO_Pin * 4));// Resets the 4 control bits corresponding to the pin
		GPIOStructPtr->GPIO->CRL |= (GPIO_Conf << (GPIO_Pin * 4)); // Sets the mask
		
	} else { // Init for the remaining 8 pins
		GPIOStructPtr->GPIO->CRH &= ~(0xF << ((GPIO_Pin - 8)*4)); // Resets the 4 control bits corresponding to the pin
		GPIOStructPtr->GPIO->CRH |= (GPIO_Conf << ((GPIO_Pin - 8)*4)); // Sets the mask
	}
}
*/
// #TODO Check the bits in reading / writing
int MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_PIN) {
	return (GPIO->IDR << GPIO_PIN);
}


void My_GPIO_Set(GPIO_TypeDef * GPIO, char GPIO_PIN) {
	GPIO->BSRR |= 1<<GPIO_PIN;
}


void My_GPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_PIN) {
	GPIO->BRR |= 1<<GPIO_PIN;
}


void My_GPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_PIN) {
	if(GPIO->ODR << GPIO_PIN) My_GPIO_Reset(GPIO, GPIO_PIN); // If Pin is Set, Reset
	else My_GPIO_Set(GPIO, GPIO_PIN); // If Pin isn't Set, Set
}

