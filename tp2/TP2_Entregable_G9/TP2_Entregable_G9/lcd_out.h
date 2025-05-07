#ifndef LCDOUT_H
#define LCDOUT_H
#include <stdint.h>

/**
 * @brief Muestra una palabra en la pantalla LCD.
 *
 * Esta función muestra una palabra en la pantalla LCD. Si la palabra tiene menos
 * de 16 caracteres, se centrará. Opcionalmente, se puede limpiar la pantalla antes
 * de mostrar la palabra.
 *
 * @param word Puntero a la palabra a mostrar (cadena terminada en null).
 * @param clr Si es distinto de cero, la pantalla se limpiará antes de mostrar la palabra.
 * @param row La posición vertical (fila) en la pantalla LCD donde se mostrará la palabra.
 */
void PRINT_word(uint8_t *word, uint8_t clr, uint8_t row);

/**
 * @brief Muestra un número en formato ASCII en la pantalla LCD.
 *
 * Esta función muestra un número de tres dígitos en la pantalla LCD en una posición
 * fija (columna 13, fila 0).
 *
 * @param number El número a mostrar (0-255).
 */
void PRINT_ascii_num(uint8_t number);

/**
 * @brief Muestra un intento en la pantalla LCD.
 *
 * Esta función muestra un intento (de hasta 5 caracteres) en la pantalla LCD
 * comenzando en la esquina superior izquierda (columna 0, fila 0).
 *
 * @param guess Puntero al intento a mostrar (cadena terminada en null).
 */
void PRINT_guess(uint8_t *guess);

/**
 * @brief Muestra el número de errores en la pantalla LCD.
 *
 * Esta función muestra el número de errores en la segunda fila de la pantalla LCD
 * en el formato "Errores: X".
 *
 * @param error El número de errores a mostrar.
 */
void PRINT_error(uint8_t error);

/**
 * @brief Muestra un mensaje de victoria en la pantalla LCD.
 *
 * Esta función limpia la pantalla y muestra un mensaje de victoria junto con
 * el tiempo tomado para lograrla.
 *
 * @param t El tiempo tomado para lograr la victoria (en segundos).
 */
void PRINT_victory(uint8_t t);

/**
 * @brief Muestra un mensaje de derrota en la pantalla LCD.
 *
 * Esta función limpia la pantalla y muestra un mensaje de derrota.
 */
void PRINT_lose();

#endif
