/*
 * tp4.c
 *
 * Created: 7/8/2025 12:49:53 PM
 * Author : Ivan
 */

#include <avr/io.h>
#define F_CPU 16000000UL // Definimos la frecuencia del CPU a 16MHz
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "adc.h"
#include "uart.h"
#include "serialPort.h"
#include "pwm.h"
#include "color.h"

volatile uint8_t command_buffer[CMD_BUFFER_SIZE];
volatile uint8_t cmd_index;
volatile uint8_t COMMAND_READY;
volatile uint8_t NEW_CHAR_RECEIVED;
volatile uint8_t NEW_CHAR_SENT;
uint8_t opacity;

uint8_t color_index = 0;
uint8_t cmd = 0;

void handle_new_color()
{
    cmd = command_buffer[cmd_index];
    uint8_t is_digit = command_buffer[cmd_index + 1] == '\0';
    if (is_digit && (cmd >= '1') && (cmd <= '8'))
    {
        color_index = cmd - '1';
        RGB_t new_color = colors_vec[color_index];
        PWM_Set_New_Color(new_color);
    }
    else
        SerialPort_Buffered_Send_String("Comando invalido. Ingrese un digito entre 1 y 8.\r\n");

    COMMAND_READY = 0;
}

void print_options()
{
    uint8_t message[] = "Bienvenido\r\Ingrese el color deseado:\r\n - RED: 1\r\n - GREEN: 2\r\n - BLUE: 3\r\n - CIAN: 4\r\n - YELLOW: 5\r\n - MAGENTA: 6\r\n - WHITE: 7\r\n - BLACK: 8\r\n";
    SerialPort_Buffered_Send_String(message);
}

int main(void)
{
    UART_init();
    ADC_Init();
    PWM_Init();

    _delay_ms(100); // Espera para que el UART se inicialice correctamente

    print_options();
    sei();
    /* Replace with your application code */
    while (1)
    {
        if (NEW_CHAR_RECEIVED)
            handle_received();
        if (NEW_CHAR_SENT)
            handle_send_char();
        if (COMMAND_READY)
            handle_new_color();

        opacity = ADC_Get_Value();
        PWM_Update_Opacity(opacity);
        PWM_Update_Red();
    }
}
