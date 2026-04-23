#include <stdio.h>
#include <stdint.h>

#include "myuart.h"

#define SYS_FREQ		16000000U
#define APB1_CLK		SYS_FREQ

#define UART_BAUDRATE	115200

void uart2_write(int ch);
static void uart_set_baudrate ();
static uint32_t compute_uart_bd();

//Character output used by printf via Syscalls hook
int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}

void uart2_tx_init(void)
{
	//Configure uart2 GPIO pin
	//Enable clock access to GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//Set PA2 mode to alternate function mode
	GPIOA->MODER &= ~GPIO_MODER_MODE2_0;
	GPIOA->MODER |= GPIO_MODER_MODE2_1;
	//Set PA2 alternate function type to UART_TX (AF07)
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL2_0;
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL2_1;
	GPIOA->AFR[0] |= GPIO_AFRL_AFRL2_2;
	GPIOA->AFR[0] &=~GPIO_AFRL_AFRL2_3;
	//Configure uart module
	//Enable clock access to uart2
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	//Configure baudrate
	uart_set_baudrate ();
	//Configure the transfer direction
	USART2->CR1 = USART_CR1_TE;
	//Enable uart module
	USART2->CR1 |= USART_CR1_UE;
}

void uart2_write(int ch)
{
	//Make sure the transmit data register is empty
	while ( !(USART2->SR & USART_CR1_TXEIE) ){}
	//Write to transmit data register
	USART2->DR = (uint8_t)ch;
}

static void uart_set_baudrate ()
{
	USART2->BRR = compute_uart_bd ();
}

static uint32_t compute_uart_bd()
{
	return ((APB1_CLK + (UART_BAUDRATE/2U))/UART_BAUDRATE);
}
