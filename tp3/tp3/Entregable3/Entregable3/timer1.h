#ifndef _TIMER1_H_
#define _TIMER1_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "date.h"

extern volatile uint8_t ON_FLAG, WAITING_TIME, WAITING_ALARM, SECOND_ELAPSED_FLAG;
extern volatile date_t date, alarm;

/**
 * @brief Inicializa el temporizador 1 (Timer1) del microcontrolador.
 *
 * Configura los registros necesarios para poner en funcionamiento el Timer1,
 * permitiendo su uso para medición de tiempo, generación de retardos o interrupciones.
 */
void TIMER1_init();

#endif