#include "stm32f4xx.h"

#define GPIOAEN			(1U<<0)
#define GPIOCEN			(1U<<2)

#define LED_PIN_SET		(1U<<5)
#define LED_PIN_RESET	(1U<<21)
#define BTN_INPUT		(1U<<13)

int main (void)
{
	/*Enable GPIO Port A and C*/
	RCC->AHB1ENR |=GPIOAEN;
	RCC->AHB1ENR |=GPIOCEN;

	/*Set Port A pin 5 as output*/
	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);

	/*Set Port C pin 13 as input*/
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	while (1)
	{
		if (GPIOC->IDR & BTN_INPUT)
			GPIOA->BSRR = LED_PIN_SET;
		else
			GPIOA->BSRR = LED_PIN_RESET;
	}
}
