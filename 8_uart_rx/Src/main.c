#include <stdio.h>
#include <stdint.h>

#include "myuart.h"

#define GPIOAEN	(1U<<0)
#define LED_PIN	(1U<<5)

volatile char key;

int main (void)
{
	/*Enable GPIO Port A*/
	RCC->AHB1ENR |=GPIOAEN;
	/*Set Port A pin 5 as output*/
	GPIOA->MODER |=  (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	uart2_rxtx_init();

	while (1)
	{
		key = uart2_read();
		if (key == '1')
			GPIOA->ODR |= LED_PIN;
		else
			GPIOA->ODR &= ~LED_PIN;
	}
}

