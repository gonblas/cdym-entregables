#ifndef _UART_H
#define _UART_H
#include <sdtint.h>

void uart_init();
ISR(USART_RX_vect);
ISR(USART_TX_vect);

#endif