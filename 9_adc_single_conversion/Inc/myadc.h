#ifndef MYADC_H_
#define MYADC_H_
#include "stm32f4xx.h"
#include <stdint.h>

void pa1_adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);
#endif
