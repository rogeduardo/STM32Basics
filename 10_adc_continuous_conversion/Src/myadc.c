#include "myadc.h"

//To enable ADC module
#define ADC_SEQ_LEN 0x00

void pa1_adc_init(void)
{
	//Configure the ADC GPIO pin

	//Enable clock access to GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	//Set the mode of PA1 to analog
	GPIOA->MODER |= GPIO_MODER_MODE1_0;
	GPIOA->MODER |= GPIO_MODER_MODE1_1;

	//Configure the ADC module
	//Enable clock access to ADC
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	//Conversion sequence start
	ADC1->SQR3 |= ADC_SQR3_SQ1_0;
	//Clean register
	ADC1->SQR1 = ADC_SEQ_LEN;
	//Enable ADC module
	ADC1->CR2 |= ADC_CR2_ADON;
}

void start_conversion(void)
{
	//Enable continuous conversion
	ADC1->CR2 |= ADC_CR2_CONT;
	//Start adc conversion
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t adc_read(void)
{
	//Wait for conversion to be complete
	while ( !(ADC1->SR & ADC_SR_EOC)){}
	//Read converted result
	return ADC1->DR;
}
