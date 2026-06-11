#include "myadc.h"
#include "myuart.h"
#include <stdio.h>
#include <inttypes.h>
#include "tim.h"

volatile uint32_t read;

int main (void)
{
	uart2_tx_init();
	pa1_adc_init();
	tim2_1hz_interrupt_init();
	start_conversion();

	while(1)
	{/*Wait the timer interrupt*/}
}

void tim2_callback(void)
{
	read = adc_read();
	printf("Sensor value: %"PRIu32"\n\r", read);
	printf("Wait one second for the next read (value)\n\r");
}

void TIM2_IRQHandler(void)
{
	//Clear update interrupt flag
	TIM2->SR &= TIM_SR_UIF;
	//Do the action
	tim2_callback();

}
