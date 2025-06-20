#ifndef DATE_H_
#define DATE_H_

#include "date.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
    uint8_t day;    // 1-31
    uint8_t month;  // 1-12
    uint8_t year;   // 0-99
    uint8_t hour;   // 0-23
    uint8_t minute; // 0-59
    uint8_t second; // 0-59
} date_t;

/**
 * @brief Convierte una cadena de mes en inglés a su valor numérico.
 *
 * @param month_str Cadena de tres letras representando el mes (ej: "Jan").
 * @return Número de mes (1-12), o 0 si la cadena no es válida.
 */
uint8_t month_str_to_num(const char *month_str);

/**
 * @brief Obtiene la fecha y hora de compilación del programa.
 *
 * Utiliza las macros __DATE__ y __TIME__ para obtener la fecha y hora.
 *
 * @return Estructura date_t con la fecha y hora actual.
 */
date_t get_date();

/**
 * @brief Verifica si un año es bisiesto (válido solo para 2000-2099).
 *
 * @param year Año en formato dos dígitos (0-99).
 * @return 1 si es bisiesto, 0 si no lo es.
 */
uint8_t is_leap_year(uint8_t year);

/**
 * @brief Devuelve la cantidad de días de un mes determinado.
 *
 * @param month Mes (1-12).
 * @param year Año en formato dos dígitos (0-99).
 * @return Número de días del mes, o 0 si el mes es inválido.
 */
uint8_t days_in_month(uint8_t month, uint8_t year);

/**
 * @brief Verifica si una cadena tiene el formato de fecha válido "DD/MM/YY".
 *
 * @param str Cadena a verificar.
 * @return 1 si el formato es válido, 0 si no lo es.
 */
int is_valid_date_format(const char *str);

/**
 * @brief Verifica si una cadena tiene el formato de hora válido "HH:MM:SS".
 *
 * @param str Cadena a verificar.
 * @return 1 si el formato es válido, 0 si no lo es.
 */
int is_valid_time_format(const char *str);

#endif