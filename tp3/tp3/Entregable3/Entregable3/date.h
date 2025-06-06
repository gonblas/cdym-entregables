#ifndef DATE_H_
#define DATE_H_

#include "date.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


typedef struct
{
    uint8_t day;    // 1-31
    uint8_t month;  // 1-12
    uint8_t year;   // 0-99
    uint8_t hour;   // 0-23
    uint8_t minute; // 0-59
    uint8_t second; // 0-59
} date_t;

uint8_t month_str_to_num(const char *month_str);

date_t get_date();

// Función para verificar si un año es bisiesto (solo válido de 2000 a 2099)
uint8_t is_leap_year(uint8_t year);

uint8_t days_in_month(uint8_t month, uint8_t year);

void updateDate(date_t *date);

int is_valid_date_format(const char *str);
int is_valid_time_format(const char *str);

#endif