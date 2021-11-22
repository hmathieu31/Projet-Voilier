#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h" 

/*
*****************************************************************************************
* @brie f
* @param -> Paramè t r e sous forme d ’ une s t r u c t u r e ( son a d re s se ) con ten an t l e s
i n f o rm a ti o n s de base
* @Note -> F onc ti on à l a n c e r s y s t ématiquement avan t d ’ a l l e r pl u s en dé t a i l dans l e s
con f pl u s f i n e s (PWM, codeur i n c . . . )
*************************************************************************************************
*/
void MyTimer_Base_Init (TIM_TypeDef * Timer, unsigned short ARR , unsigned short PSC) ;

void MyTimer_Base_Start(TIM_TypeDef * Timer) ;

void MyTimer_Base_Stop(TIM_TypeDef * Timer);


/*
**************************************************************************************************
* @brie f
* @param : - TIM_TypeDef * Timer : Timer conce rne
- cha r P ri o : de 0 a 15
* @Note : La f o n c ti o n MyTime r_Base_ Ini t d oi t a v oi r e te l a n cee au p r e al a bl e
**************************************************************************************************
*/
void MyTimer_ActiveIT (TIM_TypeDef * Timer , char Prio, void (* IT_function ) ( void )) ;
void Init_periph (void (* ptrFonction) (void));

void Init_MyTimer_PWM (TIM_TypeDef * Timer, char Channel);
void Set_Duty_PWM (TIM_TypeDef * Timer, char Channel, unsigned short pourcent);


#endif
