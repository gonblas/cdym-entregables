/*
 * tp4.c
 *
 * Created: 7/8/2025 12:49:53 PM
 * Author : Ivan
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "uart.h"
#include "serialPort.h"
#include "timer1.h"

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RGB_t;

RGB_t colors[] = {
    {0, 255, 255},   // RED
    {255, 0, 255},   // GREEN
    {255, 255, 0},   // BLUE
    {255, 0, 0},     // CIAN
    {0, 0, 255},     // YELLOW
    {0, 255, 0},     // MAGENTA
    {0, 0, 0}        // WHITE
    {255, 255, 255}, // BLACK
}

typedef enum {RED = 0, GREEN, BLUE, CIAN, YELLOW, MAGENTA, WHITE, BLACK} color_t;
color_t color_index;

volatile uint8_t command_buffer[CMD_BUFFER_SIZE];
volatile uint8_t cmd_index;
volatile uint8_t COMMAND_READY;
volatile uint8_t NEW_CHAR_RECEIVED;
volatile uint8_t NEW_CHAR_SENT;

void print_options()
{
    uint8_t message[] = "Bienvenido\r\Ingrese el color deseado:\r\n - RED : 1\r\n - GREEN : 2\r\n - BLUE : 3\r\n - CIAN : 4\r\n - YELLOW : 5\r\n - MAGENTA : 6\r\n - WHITE : 7\r\n - BLACK : 8\r\n";
    SerialPort_Buffered_Send_String(message);
}

int main(void)
{
    UART_init();
    TIMER1_init();
    sei();
    DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB5);
    /* Replace with your application code */
    while (1)
    {
        if (NEW_CHAR_RECEIVED)
        {
            handle_received();
        }
        if (COMMAND_READY)
        {
            color_index = atoi();
            // Hago cosas
        }
    }
}
