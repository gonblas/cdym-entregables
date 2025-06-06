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
#include "rtc.h"

#define CMP_STR(str1, str2) strcmp((char *)str1, (char *)str2) == 0

// ====================
// BUFFER
// ====================

#define CMD_BUFFER_SIZE 64
volatile uint8_t command_buffer[CMD_BUFFER_SIZE];
volatile uint8_t cmd_index = 0;
volatile uint8_t command_ready = 0;
uint8_t ON_FLAG = 0;
uint8_t WAITING_TIME = 0;
uint8_t WAITING_ALARM = 0;

date_t date, alarm;

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

#include <stdlib.h> // atoi
#include <ctype.h>  // isdigit

void compare_command(uint8_t *command_buffer)
{
    command_ready = 0;

    if (WAITING_TIME)
    {
        // Separar fecha y hora
        const char *date_str = (char *)command_buffer;
        const char *time_str = (char *)(&command_buffer[9]);

        if (command_buffer[8] != ' ')
        {
            SerialPort_Send_String("Falta espacio separador\r\n");
            return;
        }

        if (!is_valid_date_format(date_str) || !is_valid_time_format(time_str))
        {
            SerialPort_Send_String("Formato de fecha u hora invalido. Use DD/MM/YY HH:MM:SS\r\n");
            return;
        }

        // Parsear y guardar
        date.day = atoi((char[]){date_str[0], date_str[1], '\0'});
        date.month = atoi((char[]){date_str[3], date_str[4], '\0'});
        date.year = atoi((char[]){date_str[6], date_str[7], '\0'});
        date.hour = atoi((char[]){time_str[0], time_str[1], '\0'});
        date.minute = atoi((char[]){time_str[3], time_str[4], '\0'});
        date.second = atoi((char[]){time_str[6], time_str[7], '\0'});

        SerialPort_Send_String("Fecha y hora actualizadas\r\n");

        RTC_SetDateTime(date);
        WAITING_TIME = 0;
        return;
    }

    if (WAITING_ALARM)
    {
        // Si está esperando la alarma, recibí los datos
        if (!is_valid_time_format(command_buffer))
        {
            SerialPort_Send_String("Formato de hora invalido. Use HH:MM:SS\r\n");
            return;
        }

        // Parsear y guardar
        alarm.day = date.day;
        alarm.month = date.month;
        alarm.year = date.year;
        alarm.hour = atoi((char[]){command_buffer[0], command_buffer[1], '\0'});
        alarm.minute = atoi((char[]){command_buffer[3], command_buffer[4], '\0'});
        alarm.second = atoi((char[]){command_buffer[6], command_buffer[7], '\0'});
        WAITING_ALARM = 0;

        SerialPort_Send_String("Alarma BEEP BEEP BEEP\r\n");
        SerialPort_Send_String(format_time(alarm));

        return;
    }

    if (CMP_STR(command_buffer, "ON"))
    {
        // Activá la transmisión de hora
        SerialPort_Send_String("Comando ON recibido\r\n");
        // FECHA: 10/06/25 HORA:15:30:56\r\n

        SerialPort_Send_String(format_date(date));
        ON_FLAG = 1;
    }
    else if (CMP_STR(command_buffer, "OFF"))
    {
        // Cortá la transmisión
        ON_FLAG = 0;
        SerialPort_Send_String("Comando OFF recibido\r\n");
    }
    else if (CMP_STR(command_buffer, "SET TIME"))
    {
        // Pedí la hora nueva
        WAITING_TIME = 1;
        SerialPort_Send_String("Esperando la nueva fecha (DD/MM/YY HH:MM:SS)...\r\n");
    }
    else if (CMP_STR(command_buffer, "SET ALARM"))
    {
        WAITING_ALARM = 1;
        SerialPort_Send_String("Esperando datos de alarma (HH:MM:SS)...\r\n");
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
    RTC_Init();
    _delay_ms(100); // Esperar un poco para que el RTC se inicialice correctamente
    RTC_SetDateTime(date); // Configurar el RTC con la fecha y hora actual
    sei();                 // Habilita interrupciones globales
    while (1)
    {
        if (command_ready)
            compare_command(command_buffer);
        RTC_GetDateTime(&date);
        _delay_ms(100); // Esperar 1 segundo
    }
}
