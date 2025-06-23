#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define BAUD_RATE_CONFIG 103

volatile char tx_buffer[CMD_BUFFER_SIZE];
volatile uint8_t tx_head = 0;
volatile uint8_t tx_tail = 0;
volatile uint8_t tx_busy = 0;

void UART_init()
{
  SerialPort_Init(BAUD_RATE_CONFIG); // Configura UART a 9600bps, 8N1 @ F_CPU = 16MHz
  SerialPort_TX_Enable();            // habilita el transmisor
  SerialPort_TX_Interrupt_Enable();  // habilita el transmisor
  SerialPort_RX_Enable();            // habilita el receptor
  SerialPort_RX_Interrupt_Enable();  // habilita la interrupción de recepción
}

ISR(USART_RX_vect) 
{
  NEW_CHAR_RECEIVED = 1;
}


void handle_received() 
{
  uint8_t received = UDR0;
  NEW_CHAR_RECEIVED = 0; // Resetea la bandera de nuevo carácter recibido
  if ((received == '\b' || received == 0x7F) && cmd_index > 0)
  {
    cmd_index--;
  }
  else if (received == '\r' || received == '\n')
  {
    command_buffer[cmd_index] = '\0'; // Terminás el string
    cmd_index = 0;
    COMMAND_READY = 1; // Señalás que hay un comando listo
  }
  else if (cmd_index < CMD_BUFFER_SIZE - 1)
  {
    command_buffer[cmd_index++] = received;
  }
}


void UART_Buffered_Send_Char(uint8_t data)
{
  uint8_t next_head = (tx_head + 1) % CMD_BUFFER_SIZE;

  // Esperar si el buffer está lleno
  while (next_head == tx_tail)
    ; // bloqueante, o podés implementar timeout

  tx_buffer[tx_head] = data;
  tx_head = next_head;

  // Habilitar interrupción de transmisión si no está activa
  if (!tx_busy)
  {
    tx_busy = 1;
    UCSR0B |= (1 << UDRIE0); // Habilita interrupción de buffer vacío
  }
}


ISR(USART_UDRE_vect)
{
  // Si el buffer está vacío, desactivar interrupción
  if (tx_tail == tx_head)
  {
    tx_busy = 0;
    UCSR0B &= ~(1 << UDRIE0); // Deshabilita interrupción de transmisión
    return;
  }

  // Enviar siguiente carácter del buffer
  UDR0 = tx_buffer[tx_tail];
  tx_tail = (tx_tail + 1) % CMD_BUFFER_SIZE;
}

