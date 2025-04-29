#include <avr/io.h>
#include <avr/interrupt.h>

// Configura el timer para interrumpir cada 10 ms
void timer_init() {
  TCCR0A &= ~((1 << COM0A0) | (1 << COM0A1)); // Seteamos el timer en normal mode.
  TCCR0A = (TCCR0A | (1 << CS02) | (1 << CS00)) &  ~(1 << CS01); // Seteamos el prescaler de 1024.

  TCNT0 = 99; // Seteamos el punto de inicio del timer

  TIMSK0 |= (1 << TOIE0); // Habilitamos las interrupciones por overflow

  sei();
}