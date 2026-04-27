#include <stdio.h>
#include <stdint.h>

#include "myuart.h"

volatile char key;

int main (void)
{
	/*Enable GPIO Port A*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	/*Set Port A pin 5 as output*/
	GPIOA->MODER |=  GPIO_MODER_MODE5_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE5_1;

	uart2_rxtx_init();

	while (1)
	{
		key = uart2_read();
		if (key == '1')
			GPIOA->ODR |= GPIO_ODR_OD5;
		else
			GPIOA->ODR &= ~GPIO_ODR_OD5;
	}
}

