#ifndef _TIMER1_H_
#define _TIMER1_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "date.h"

extern volatile uint8_t ON_FLAG, WAITING_TIME, WAITING_ALARM, SECOND_ELAPSED_FLAG;
extern volatile date_t date, alarm;

void timer1_init();
void RTC_CheckAlarm(date_t date, date_t alarm_date);

#endif