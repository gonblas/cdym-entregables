
#ifndef TIMER_H
#define TIMER_H
#include <avr/io.h>

extern volatile uint8_t temporization_flag;
extern volatile uint8_t tick;
extern volatile uint8_t t;

/**
 * @brief Inicializa el Timer0 para generar interrupciones cada 10 ms.
 *
 * Configura el Timer0 en modo normal con un prescaler de 1024. La cuenta
 * inicial del temporizador se establece en 100 para que el desbordamiento
 * ocurra cada 10 ms. Habilita las interrupciones por desbordamiento del Timer0
 * y las interrupciones globales.
 */
void timer_init();

/**
 * @brief Rutina de servicio de interrupción (ISR) para el Timer0.
 *
 * Esta ISR se ejecuta cada vez que el Timer0 se desborda (cada 10 ms). Reinicia
 * la cuenta del temporizador, incrementa un contador de ticks y alterna el
 * estado de una bandera de temporización. Además, cada 100 ticks (1 segundo),
 * incrementa un contador de segundos.
 */
ISR(TIMER0_OVF_vect);

#endif
