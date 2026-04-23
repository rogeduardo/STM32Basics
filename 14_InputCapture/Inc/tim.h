#ifndef TIM_H_
#define TIM_H_
#include "stm32f4xx.h"
#define SR_UIF 		(1U<<0)
#define SR_CC1IF 	(1U<<1)

void tim2_pa5_output_compare(void);
void tim3_pa6_input_capture(void);

#endif
