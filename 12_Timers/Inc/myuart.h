#include "stm32f4xx.h"

#ifndef MYUART_H_
#define MYUART_H_

void uart2_rxtx_init(void);
void uart2_tx_init(void);
char uart2_read(void);

#endif
