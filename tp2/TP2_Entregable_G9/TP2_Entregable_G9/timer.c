/**
 * @file timer.c
 * @brief Implementación de un temporizador utilizando el Timer0 del microcontrolador AVR.
 *
 * Este archivo contiene las funciones necesarias para inicializar y manejar un temporizador
 * que genera interrupciones cada 10 ms. Además, se utiliza una variable de bandera para
 * realizar tareas temporizadas y un contador para medir intervalos de tiempo más largos.
 *
 * @author Grupo 9
 * @date Fecha de entrega
 */

 /**
	* @brief Inicializa el Timer0 para generar interrupciones cada 10 ms.
	*
	* Configura el Timer0 en modo normal con un prescaler de 1024. La cuenta inicial del
	* temporizador se establece en 100 para que el desbordamiento ocurra cada 10 ms.
	* Habilita las interrupciones por desbordamiento del Timer0 y las interrupciones globales.
	*/
void timer_init();

/**
 * @brief Rutina de servicio de interrupción (ISR) para el Timer0.
 *
 * Esta ISR se ejecuta cada vez que el Timer0 se desborda (cada 10 ms). Reinicia la cuenta
 * del temporizador, incrementa un contador de ticks y alterna el estado de una bandera
 * de temporización. Además, cada 100 ticks (1 segundo), incrementa un contador de segundos.
 */
ISR(TIMER0_OVF_vect);
#include <avr/io.h>
#include <avr/interrupt.h>
#include "mef.h"
#include "timer.h"

uint8_t tick = 0;

// Configura el timer para interrumpir cada 10 ms
void timer_init() {
  TCCR0A = 0x00; // Modo normal
  TCCR0B = (1 << CS02) | (1 << CS00); // Prescaler = 1024
  TCNT0 = 100; // Cuenta inicial para desbordar a 10ms

  TIMSK0 |= (1 << TOIE0); // Habilita interrupciones por overflow
  sei(); // Habilita interrupciones globales
}

ISR(TIMER0_OVF_vect) {
	TCNT0 = 100; // Reinicia el timer para 10 ms
	tick++;
	temporization_flag ^= 1;
	if (tick == 100) { // Cada 100 ticks de 10 ms = 1 segundo
		t++;
		tick = 0;
	}
}
