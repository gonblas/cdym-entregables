/*
 * Microchip.c
 *
 * Created: 2/6/2025 14:40:23
 * Author : Ivan Trolanis y Gonzalo Fiasco
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#define F_CPU 16000000UL // Definimos la frecuencia del reloj a 16MHz
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "i2c.h"
#include "serialPort.h"
#define BAUD_RATE_CONFIG 103
#include "date.h"

// ====================
// BUFFER
// ====================

#define CMD_BUFFER_SIZE 16
volatile uint8_t command_buffer[CMD_BUFFER_SIZE];
volatile uint8_t cmd_index = 0;
volatile uint8_t command_ready = 0;
int8_t ON_FLAG = 0;

date_t date;

void usart_init()
{
    SerialPort_Init(BAUD_RATE_CONFIG); // Configura UART a 9600bps, 8N1 @ F_CPU = 16MHz
    SerialPort_TX_Enable();            // habilita el transmisor
    SerialPort_RX_Enable();            // habilita el receptor
    SerialPort_RX_Interrupt_Enable();  // habilita la interrupción de recepción
}

ISR(USART_RX_vect)
{
    uint8_t received = UDR0;

    if (received == '\r' || received == '\n')
    {
        command_buffer[cmd_index] = '\0'; // Terminás el string
        cmd_index = 0;
        command_ready = 1; // Señalás que hay un comando listo
    }
    else
    {
        if (cmd_index < CMD_BUFFER_SIZE - 1)
        {
            command_buffer[cmd_index++] = received;
        }
        // Si se llena el buffer, podrías tirar un error o resetear
    }
}

void print_welcome()
{
    uint8_t message[] = "Bienvenido\r\nCOMANDOS:\r\n - ON\r\n - OFF\r\n - SET TIME\r\n - SET ALARM\r\n";
    SerialPort_Send_String(message);
}





void compare_command(command_buffer)
{
    command_ready = 0;

    if (strcmp((char *)command_buffer, "ON") == 0)
    {
        // Activá la transmisión de hora
        SerialPort_Send_String("Comando ON recibido\r\n");
        // FECHA: 10/06/25 HORA:15:30:56\r\n
        char date_string[50];
        snprintf(date_string, sizeof(date_string), "FECHA: %02u/%02u/%02u HORA:%02u:%02u:%02u\r\n",
                 date.day, date.month, date.year, date.hour, date.minute, date.second);
        SerialPort_Send_String(date_string);
        ON_FLAG = 1;
    }
    else if (strcmp((char *)command_buffer, "OFF") == 0)
    {
        // Cortá la transmisión
        ON_FLAG = 0;
        SerialPort_Send_String("Comando OFF recibido\r\n");
    }
    else if (strcmp((char *)command_buffer, "SET TIME") == 0)
    {
        // Pedí la hora nueva
        SerialPort_Send_String("Esperando datos de hora...\r\n");
    }
    else if (strcmp((char *)command_buffer, "SET ALARM") == 0)
    {
        SerialPort_Send_String("Esperando datos de alarma...\r\n");
    }
    else
    {
        SerialPort_Send_String("Comando no reconocido. Intente nuevamente\r\n");
    }
}

int main(void)
{
    usart_init();
    print_welcome();
    date = get_date(); // Obtener la fecha y hora actual
    sei(); // Habilita interrupciones globales
    while (1)
    {
        if (command_ready)
            compare_command(command_buffer);
    }
}
