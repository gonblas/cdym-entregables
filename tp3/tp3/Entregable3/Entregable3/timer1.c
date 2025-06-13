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
  SECOND_ELAPSED_FLAG = 1; // Indica que ha pasado un segundo
}