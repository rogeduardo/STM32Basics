#include <stdio.h>
#include <stdint.h>

#include "myuart.h"

#define GPIOAEN			(1U<<0)
#define LED_PIN_SET		(1U<<5)
#define LED_PIN_RESET	(1U<<21)

int main (void)
{
	volatile char key;
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
			GPIOA->BSRR = LED_PIN_SET;
		else
			GPIOA->BSRR = LED_PIN_RESET;
		printf ( "Esse foi o caractere pressionado %c\r\n", key );
	}
}

