/*
 * Author: Rogerio Eduardo de Oliveira
 * Description: This program turn on/off de LED (User LD2 PA5) based on character (1 turn on any other, off)
 * received by UART (PA3).
 */
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

	uart2_rx_interrupt_init();

	while (1)
	{/*Wait interrupt*/}
}

void USART2_IRQHandler()
{
	//Check if RXNE is set
	if (USART2->SR & USART_SR_RXNE)
	{
		key = USART2->DR;
		if (key == '1')
			GPIOA->ODR |= GPIO_ODR_OD5;
		else
			GPIOA->ODR &= ~GPIO_ODR_OD5;
	}
}
