#include <avr/io.h>
#include <avr/interrupt.h>

// Configura el timer para interrumpir cada 10 ms
void timer_init() {
  TCCR0A = 0x00; // Modo normal
  TCCR0B = (1 << CS02) | (1 << CS00); // Prescaler = 1024
  TCNT0 = 100; // Cuenta inicial para desbordar a 10ms

  TIMSK0 |= (1 << TOIE0); // Habilita interrupciones por overflow
  sei(); // Habilita interrupciones globales
}