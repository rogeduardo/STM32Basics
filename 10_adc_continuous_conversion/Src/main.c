#include "myadc.h"
#include "myuart.h"
#include <stdio.h>
#include <inttypes.h>

volatile uint32_t read;

int main (void)
{
	uart2_tx_init();
	pa1_adc_init();
	start_conversion();

	while(1)
	{
		read = adc_read();
		printf("Sensor value: %"PRIu32"\n\r", read);
		for (int i=0;i<1000000;i++){}
	}
}
