/*
 * Author: Rogerio Eduardo de Oliveira
 * Description: This program turn on/off de LED (User LD2 PA5) and sent by UART (UART2 PA2) the action
 * based on pressing (turn on) or release the button (B1 User PC13).
 */

#include "exti.h"
#include "myuart.h"
#include <stdio.h>

int main (void)
{

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	//Set PA5 as output
	GPIOA->MODER |=  GPIO_MODER_MODE5_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE5_1;

	pc13_exti_init();
	uart2_tx_init();
	while(1)
	{/*Wait for interrupts*/}
}

static void exti_callback (void)
{
	if ( GPIOC->IDR & GPIO_IDR_ID13 )
	{
		printf ("Button released...\n\r");
		GPIOA->BSRR = GPIO_BSRR_BR5;
	}
	else
	{
		printf ("Button pressed...\n\r");
		GPIOA->BSRR = GPIO_BSRR_BS5;
	}
}

void EXTI15_10_IRQHandler (void) {
	if ((EXTI->PR & EXTI_PR_PR13) != 0 )
	{
		//Clear PR flag
		EXTI->PR |= EXTI_PR_PR13;
		//Manage LED (on or off)
		exti_callback ();
	}
}
