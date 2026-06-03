#include "myadc.h"
#include "myuart.h"
#include "mysystick.h"
#include <stdio.h>
#include <inttypes.h>

volatile uint32_t read;

int main (void)
{
	uart2_tx_init();
	pa1_adc_init();
	start_conversion();
	systick_1hz_interrupt();

	while(1)
	{/*Wait systick interrupt*/}
}

void systick_callback(void)
{
	printf ("A second passed!\n\r");
	read = adc_read();
	printf("Sensor value: %"PRIu32"\n\r", read);
	printf("Wait one second for the next read (value)\n\r");
}

void SysTick_Handler(void)
{
	systick_callback();
}
