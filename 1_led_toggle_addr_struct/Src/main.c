#include <stdint.h>

//Setting the gpio addresses
#define PERIPH_BASE 		(0x40000000UL)
#define AHB1PERIPH_OFFSET 	(0x00020000UL)
#define AHB1PERIPH_BASE		(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET		(0x0000UL)

#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET			(0x3800UL)
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIOAEN				(1U<<0) //Shift one to position 0

#define LED_PIN				(1U<<5)

typedef struct
{
	volatile uint32_t DUMMY[12]; //Fill the space to match the AHB1ENR position memory
	volatile uint32_t AHB1ENR;   //!< RCC AHB1 peripheral clock register, address offset: 0x30
} RCC_TypeDef;

typedef struct
{
	volatile uint32_t MODER;     //!< GPIO port mode register, Address offset:0x00
	volatile uint32_t DUMMY[4]; //Fill the space to match the ODRJ position memory
	volatile uint32_t ODR;       //!< GPIO port output data register, Address offset: 0x14
} GPIO_TypeDef;

#define RCC   ((RCC_TypeDef*) RCC_BASE)
#define GPIOA ((GPIO_TypeDef*) GPIOA_BASE)

int main (void)
{
	/*1. Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*2. Set PA5 as output pin*/
	GPIOA->MODER |= (1U<<10); //Set bit 10 to 1
	GPIOA->MODER &=~(1U<<11); //Set bit 11 to 0

	while (1)
	{
		/*4. Experiment 2 : toggle PA5*/
		GPIOA->ODR ^= LED_PIN;
		for ( int i =0; i<100000; i++){}
	}
}
