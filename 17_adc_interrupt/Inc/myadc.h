#ifndef MYADC_H_
#define MYADC_H_
#include "stm32f4xx.h"
#include <stdint.h>

void pa1_adc_interrupt_init(void);
void start_conversion(void);
#endif
