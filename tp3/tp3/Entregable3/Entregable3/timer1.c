#include "timer1.h"

void timer1_init(void)
{
  // F_CPU = 16 MHz
  // Prescaler = 1024 → tick = 64 µs
  // 1 segundo = 15625 ticks

  TCCR1B |= (1 << WGM12);              // Modo CTC
  OCR1A = 15625 - 1;                   // TOP
  TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024
  TIMSK1 |= (1 << OCIE1A);             // Habilita interrupción por comparación A
}

ISR(TIMER1_COMPA_vect)
{
  RTC_GetDateTime(&date);

  if (ON_FLAG)
  {
    SerialPort_Buffered_Send_String(format_date(date));
  }

  CheckAlarm();
}

void CheckAlarm()
{
  static uint8_t alarm_triggered = 0;
  static uint8_t counter = 0;
  if (!alarm_triggered &&
      date.hour == alarm.hour &&
      date.minute == alarm.minute &&
      date.second == alarm.second)
  {
    alarm_triggered = 1;
    counter = 5;
  }

  if (alarm_triggered)
  {
    SerialPort_Buffered_Send_String("Alarma\r\n");
    alarm_triggered = (--counter > 0) ? 1 : 0;
  }
}