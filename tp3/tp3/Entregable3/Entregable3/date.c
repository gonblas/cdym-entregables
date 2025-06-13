#include "date.h"

uint8_t month_str_to_num(const char *month_str) {
    if      (strcmp(month_str, "Jan") == 0) return 1;
    else if (strcmp(month_str, "Feb") == 0) return 2;
    else if (strcmp(month_str, "Mar") == 0) return 3;
    else if (strcmp(month_str, "Apr") == 0) return 4;
    else if (strcmp(month_str, "May") == 0) return 5;
    else if (strcmp(month_str, "Jun") == 0) return 6;
    else if (strcmp(month_str, "Jul") == 0) return 7;
    else if (strcmp(month_str, "Aug") == 0) return 8;
    else if (strcmp(month_str, "Sep") == 0) return 9;
    else if (strcmp(month_str, "Oct") == 0) return 10;
    else if (strcmp(month_str, "Nov") == 0) return 11;
    else if (strcmp(month_str, "Dec") == 0) return 12;
    else return 0; // valor inválido
}

date_t get_date()
{
    uint16_t year_full;
    date_t date;
    char month_str[4]; // "Jan", "Feb", etc.

    char date_string[] = __DATE__; // Ejemplo: "Jul 27 2012"
    char time_string[] = __TIME__; // Ejemplo: "21:06:19"

    sscanf(time_string, "%hhu:%hhu:%hhu", &date.hour, &date.minute, &date.second);
    sscanf(date_string, "%3s %hhu %hu", month_str, &date.day, &year_full);

    date.month = month_str_to_num(month_str);
    date.year = year_full % 100;

    // (Opcional) imprimir
    printf("Fecha: %02u/%02u/%02u - Hora: %02u:%02u:%02u\n",
           date.day, date.month, date.year, date.hour, date.minute, date.second);
    
    
    return date;
}

// Función para verificar si un año es bisiesto (solo válido de 2000 a 2099)
uint8_t is_leap_year(uint8_t year)
{
    // Año completo = 2000 + year
    return ((year % 4) == 0); // porque entre 2000–2099 todos los bisiestos son múltiplos de 4
}

uint8_t days_in_month(uint8_t month, uint8_t year)
{
    switch (month)
    {
        case 1:  return 31;
        case 2:  return is_leap_year(year) ? 29 : 28; 
        case 3:  return 31;
        case 4:  return 30;
        case 5:  return 31;
        case 6:  return 30;
        case 7:  return 31;
        case 8:  return 31;
        case 9:  return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;  // mes inválido
    }
}

void updateDate(date_t *date)
{
    if (++date->second < 60) return;
    date->second = 0;

    if (++date->minute < 60) return;
    date->minute = 0;

    if (++date->hour < 24) return;
    date->hour = 0;

    if (++date->day <= days_in_month(date->month, date->year)) return;
    date->day = 1;

    if (++date->month <= 12) return;
    date->month = 1;

    if (++date->year <= 99) return;
    date->year = 0;
}


int is_valid_date_format(const char *str)
{
    // Verifica longitud
    if (!str || !(str[8] == ' ' || str[8] == '\r'))
        return 0;

    for (int i = 0; i < 8; i++)
    {
        if (i == 2 || i == 5)
        {
            if (str[i] != '/')
                return 0;
        }
        else
        {
            if (!isdigit(str[i]))
                return 0;
        }
    }

    int d = atoi((char[]){str[0], str[1], '\0'});
    int m = atoi((char[]){str[3], str[4], '\0'});
    int y = atoi((char[]){str[6], str[7], '\0'});

    if (m < 1 || m > 12)
        return 0;

    uint8_t max_day = days_in_month(m, y);
    if (d < 1 || d > max_day)
        return 0;

    return 1;
}

int is_valid_time_format(const char *str)
{
    if (!str || str[8] != '\0')
        return 0;

    for (int i = 0; i < 8; i++)
    {
        if (i == 2 || i == 5)
        {
            if (str[i] != ':')
                return 0;
        }
        else
        {
            if (!isdigit(str[i]))
                return 0;
        }
    }

    int h = atoi((char[]){str[0], str[1], '\0'});
    int m = atoi((char[]){str[3], str[4], '\0'});
    int s = atoi((char[]){str[6], str[7], '\0'});

    if (h < 0 || h > 23)
        return 0;
    if (m < 0 || m > 59)
        return 0;
    if (s < 0 || s > 59)
        return 0;

    return 1;
}


uint8_t* format_time(date_t date) {
    static uint8_t formatted_time[11]; // "HH:MM:SS\0"
    snprintf((char *)formatted_time, sizeof(formatted_time), "%02u:%02u:%02u\r\n",
             date.hour, date.minute, date.second);
    return formatted_time;
}

uint8_t* format_date(date_t date) {
    static uint8_t formatted_date[22]; // "DD/MM/YY HH:MM:SS\0"
    snprintf((char *)formatted_date, sizeof(formatted_date), "%02u/%02u/%02u %s\r\n",
             date.day, date.month, date.year, format_time(date));
    return formatted_date;
}
