#include "stm32h723xx.h"
#include "stm32h7xx.h"


#define GPIOCEN			(1U<<2)
#define SYSCFGEN		(1U<<1)


void pc13_exti_init(void)
{
	/*Enable clock access to PORTC*/
	RCC->AHB4ENR |=GPIOCEN;

	/*Set PC13 to input*/
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	/*Enable clock access to SYSCFG module*/
	RCC->APB4ENR |=SYSCFGEN;

	/*Clear port selection for EXTI13*/
	SYSCFG->EXTICR[3] &=~(1U<<4);
	SYSCFG->EXTICR[3] &=~(1U<<5);
	SYSCFG->EXTICR[3] &=~(1U<<6);
	SYSCFG->EXTICR[3] &=~(1U<<7);

	/*Select PORTC for EXTI13*/
	SYSCFG->EXTICR[3] |=(1U<<5);

	/*Unmask EXTI13*/
	EXTI->IMR1 |=(1U<<13);

	/*Select falling edge trigger*/
	EXTI->FTSR1 |=(1U<<13);

	/*Enable EXTI13 in NVIC*/
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

