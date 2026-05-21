#include "myadc.h"
#include "myuart.h"
#include <stdio.h>
#include <inttypes.h>

volatile uint32_t read;

int main (void)
{
	uart2_tx_init();
	pa1_adc_interrupt_init();
	start_conversion();

	while(1)
	{/*Wait for interrupt*/	}
}

void ADC_IRQHandler(void)
{
	//Check for eoc in SR
	if ( ADC1->SR & ADC_SR_EOC )
	{
		//Clear EOC
		ADC1->SR &= ~ADC_SR_EOC;

		read = ADC1->DR;
		printf ("Sensor value: %"PRIu32"\n\r", read);
	}
}
