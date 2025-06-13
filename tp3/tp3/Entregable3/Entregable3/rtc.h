#ifndef RTC_H_
#define RTC_H_

#include <avr/io.h>
#include "date.h"

#define REG_ADDRESS_DS3231_CONTROL_U8 0x68 // Dirección de Control del RTC DS3231
#define DS3231_READ_MODE (REG_ADDRESS_DS3231_CONTROL_U8 << 1) | 0x01
#define DS3231_WRITE_MODE (REG_ADDRESS_DS3231_CONTROL_U8 << 1)
#define REG_ADDRESS_DS3231_SECONDS_U8 0x00 // Dirección donde se guardan los segundos en el RTC DS3231
#define REG_ADDRESS_DS3231_MINUTES_U8 0x01 // Dirección donde se guardan los minutos en el RTC DS3231
#define REG_ADDRESS_DS3231_HOURS_U8 0x02   // Dirección donde se guardan los horas en el RTC DS3231
#define REG_ADDRESS_DS3231_DAYS_U8 0x04    // Dirección donde se guardan los dias en el RTC DS3231
#define REG_ADDRESS_DS3231_MONTHS_U8 0x05  // Dirección donde se guardan los meses en el RTC DS3231
#define REG_ADDRESS_DS3231_YEARS_U8 0x06   // Dirección donde se guardan los años en el RTC DS3231

// En cada dirección, los datos a buscar se encuentran en bits específicos de la dirección.
// Para filtrar bits que no sean necesarios, se utilizan las siguientes máscaras
#define MASK_SEC 0b01111111
#define MASK_MIN 0b01111111
#define MASK_HOUR 0b00111111
#define MASK_DAY 0b00111111
#define MASK_MONTH 0b00011111
#define MASK_YEAR 0b11111111

/**
 * @brief Inicializa el módulo RTC DS3231.
 *
 * Configura la comunicación y prepara el RTC para su uso.
 */
void RTC_Init(void);

/**
 * @brief Establece la fecha y hora en el RTC DS3231.
 *
 * @param date Estructura de tipo date_t con la fecha y hora a establecer.
 */
void RTC_SetDateTime(date_t);

/**
 * @brief Obtiene la fecha y hora actual del RTC DS3231.
 *
 * @param date Puntero a una estructura date_t donde se almacenará la fecha y hora leída.
 */
void RTC_GetDateTime(date_t *);

#endif /* RTC_H_ */