/**
 * @file timer.c
 * @brief Implementación de un temporizador utilizando el Timer0 del
 * microcontrolador AVR.
 *
 * Este archivo contiene las funciones necesarias para inicializar y manejar un
 * temporizador que genera interrupciones cada 10 ms. Además, se utiliza una
 * variable de bandera para realizar tareas temporizadas y un contador para
 * medir intervalos de tiempo más largos.
 *
 * @author Grupo 9
 * @date Fecha de entrega
 */

#include "timer.h"
#include "mef.h"
#include <avr/interrupt.h>
#include <avr/io.h>

uint8_t tick = 0;

void timer_init() {
  TCCR0A = 0x00;                      // Modo normal
  TCCR0B = (1 << CS02) | (1 << CS00); // Prescaler = 1024
  TCNT0 = 100;                        // Cuenta inicial para desbordar a 10ms

  TIMSK0 |= (1 << TOIE0); // Habilita interrupciones por overflow
  sei();                  // Habilita interrupciones globales
}

ISR(TIMER0_OVF_vect) {
  TCNT0 = 100; // Reinicia el timer para 10 ms
  tick++;
  temporization_flag = 1;
  if (tick == 100) { // Cada 100 ticks de 10 ms = 1 segundo
    t++;
    tick = 0;
  }
}
