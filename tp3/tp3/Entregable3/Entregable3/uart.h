#ifndef _UART_H
#define _UART_H

#include <stdint.h>

#define CMD_BUFFER_SIZE 128 
extern volatile uint8_t command_buffer[CMD_BUFFER_SIZE];
extern volatile uint8_t cmd_index;
extern volatile uint8_t command_ready;

void uart_init();
ISR(USART_RX_vect);
ISR(USART_TX_vect);

#endif