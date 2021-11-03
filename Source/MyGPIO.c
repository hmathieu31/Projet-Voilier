#include "stm32f10x.h"

void MyGPIO_Init ( GPIO_TypeDef * GPIO , char GPIO_Pin, char CONF ){
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
int MyGPIO_Read ( GPIO_TypeDef * GPIO , char GPIO_Pin ) { // renvoie 0 ou autre chose different de 0 
	return (GPIO->IDR >> GPIO_Pin) & 1;
}
void MyGPIO_Set ( GPIO_TypeDef * GPIO , char GPIO_Pin ) { //allumer la diode
	GPIO->BSRR = (1 << GPIO_Pin);
}
void MyGPIO_Reset ( GPIO_TypeDef * GPIO , char GPIO_Pin ) { //éteindre la diode
	GPIO->BRR = (1 << GPIO_Pin);
}
void MyGPIO_Toggle ( GPIO_TypeDef * GPIO , char GPIO_Pin ) { //interrupteur : eteint quand allumé et allume quand eteint
	
	if ((GPIO->ODR & (1<<GPIO_Pin )) == (1 << GPIO_Pin)) 
		MyGPIO_Reset (GPIO,GPIO_Pin);
	else
		MyGPIO_Set (GPIO,GPIO_Pin);
	
	/*if (((GPIO->ODR >> GPIO_Pin) & 1 ) == 0) { //lampe éteinte //le 1 sert au masque 
		MyGPIO_Set (GPIO,GPIO_Pin); // IDR et ODR ne sont pas des "cases" pour chaque pin, ce sont des chiffres écrit en binaire et on lit les bits qui nous interessent (en fonction des pins)
		//ODR on déclale à droite pour ensuite lire à droite ce qui nous interesse, et IDR on écrit et on le place au bon endroit avec un masque pour pas effacer le reste (complément pour les & et rien pour les |).
	}
	else { //lampe allumée
		MyGPIO_Reset (GPIO,GPIO_Pin);
	}*/
}
