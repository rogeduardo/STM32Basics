#include "tim.h"

void tim2_1hz_interrupt_init(void)
{
	//Enable clock access to TIM2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//Set prescaler value
	TIM2->PSC = 1600 - 1;
	//Set auto-reload value
	TIM2->ARR = 10000 - 1;
	//Clear counter
	TIM2->CNT = 0;
	//Enable timer
	TIM2->CR1 |= TIM_CR1_CEN;
	//Enable TIM interrupt
	TIM2->DIER |= TIM_DIER_UIE;
	//Enable TIM interrupt in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
}
