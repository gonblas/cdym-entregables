#ifndef RTC_H_
#define RTC_H_

#include <avr/io.h>
#include "date.h"


#define REG_ADDRESS_DS3231_CONTROL_U8 0x68		//Dirección de Control del RTC DS3231
#define DS3231_READ_MODE   ( REG_ADDRESS_DS3231_CONTROL_U8 << 1) | 0x01
#define DS3231_WRITE_MODE  ( REG_ADDRESS_DS3231_CONTROL_U8 << 1)
#define REG_ADDRESS_DS3231_SECONDS_U8 0x00	//Dirección donde se guardan los segundos en el RTC DS3231
#define REG_ADDRESS_DS3231_MINUTES_U8 0x01	//Dirección donde se guardan los minutos en el RTC DS3231
#define REG_ADDRESS_DS3231_HOURS_U8 0x02	//Dirección donde se guardan los horas en el RTC DS3231
#define REG_ADDRESS_DS3231_DAYS_U8 0x04	//Dirección donde se guardan los dias en el RTC DS3231
#define REG_ADDRESS_DS3231_MONTHS_U8 0x05	//Dirección donde se guardan los meses en el RTC DS3231
#define REG_ADDRESS_DS3231_YEARS_U8 0x06	//Dirección donde se guardan los años en el RTC DS3231


//En cada dirección, los datos a buscar se encuentran en bits específicos de la dirección.
//Para filtrar bits que no sean necesarios, se utilizan las siguientes máscaras
#define MASK_SEC 0b01111111
#define MASK_MIN 0b01111111
#define MASK_HOUR 0b00111111
#define MASK_DAY 0b00111111
#define MASK_MONTH 0b00011111
#define MASK_YEAR 0b11111111

void RTC_Init(void);

void RTC_SetDateTime(date_t);

void RTC_GetDateTime(date_t *);

#endif /* RTC_H_ */