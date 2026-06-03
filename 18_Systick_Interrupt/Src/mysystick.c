#include "mysystick.h"

#define ONE_SEC_LOAD		16000000

void systick_1hz_interrupt()
{
	//Configure systick
	//Reload with number of clocks per second
	SysTick->LOAD = ONE_SEC_LOAD - 1;
	//Clear systick current value register
	SysTick->VAL = 0;
	//Enable systick and select internal clk src
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;
}
