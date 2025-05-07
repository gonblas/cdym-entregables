#ifndef KEYPAD_H
#define KEYPAD_H

#include <avr/io.h>

/**
 * @brief Actualiza el estado del teclado y detecta si se presionó una tecla.
 * 
 * @return uint8_t Índice de la tecla presionada en el mapa de teclas (KeyMap),
 * o 0xFF si no se presionó ninguna tecla.
 */
uint8_t KEYPAD_update(void);

/**
 * @brief Escanea el teclado y detecta si se presionó una tecla nueva.
 * 
 * @param pkey Puntero donde se almacenará la tecla presionada.
 * @return uint8_t 1 si se detectó una nueva tecla, 0 en caso contrario.
 */
uint8_t KEYPAD_scan(uint8_t *pkey);

/**
 * @brief Inicializa el teclado matricial configurando las filas como salidas
 * y las columnas como entradas con resistencias pull-up.
 */
void KEYPAD_init(void);

#endif // KEYPAD_H