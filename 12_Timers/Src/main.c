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
	tim2_1hz_init();
	start_conversion();

	while(1)
	{
		read = adc_read();
		printf("Sensor value: %"PRIu32"\n\r", read);
		printf("Wait one second for the next read (value)\n\r");
		//Wait for UIF
		while (!(TIM2->SR & SR_UIF)){}
		//Clear UIF
		TIM2->SR &= ~SR_UIF;
	}
}
