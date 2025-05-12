/**
 * @file mef.c
 * @brief Implementación de una Máquina de Estados Finitos (MEF) para un juego
 * de adivinanza de palabras.
 *
 * Este archivo contiene la lógica de una MEF que permite al usuario adivinar
 * palabras seleccionadas aleatoriamente de un diccionario. El juego incluye
 * estados para inicialización, mostrar la palabra, esperar la entrada del
 * usuario, manejar la victoria y manejar la derrota.
 *
 * @author Grupo 9
 * @date 2023
 */

#include "keypad.h"
#include "lcd.h"
#include "lcd_out.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief Maneja un error cometido por el usuario.
 *
 * Incrementa el contador de errores, actualiza la pantalla y verifica si
 * el usuario ha alcanzado el límite de errores permitidos.
 *
 * @param t Puntero a la variable de temporización.
 */
void miss();

#define WORD_COUNT (sizeof(dictionary) / sizeof(dictionary[0]))
#define GET_RANDOM_INDEX(min, max) ((rand() % ((max) - (min) + 1)) + (min))
#define SHOW_PASSWORD_KEY '*'
#define CHAR_END_KEY '#'
#define CHAR_TO_INT(c) c - '0'
#define UPDATE_CHAR(cchar, key) (cchar * 10 + CHAR_TO_INT(key))
#define LAST_MESSAGE_TIME 5
#define MAX_ERRORS 3

typedef enum { INIT, SHOW_PASSWORD, WAIT_INPUT, VICTORY, LOSE } state_t;
uint8_t *dictionary[] = {"Arbol", "Boton", "CDyMC", "ClavE", "Facil",
                         "Gafas", "Hojas", "LiBro", "Lanza", "Nieve",
                         "PeRro", "PecES", "PiAno", "PrYKe", "RUEDa",
                         "SERIE", "SalUd", "Salud", "Silla", "Tecla",
                         "Valor", "Verde", "YnHRz", "hARdD", "silla"};

state_t state;
uint8_t *word, guess[6];
uint8_t key = 0xFF, cur_char_index, current_char, errors, time_to_victory;
uint8_t random_index, first;
uint8_t set_seed = 1;
volatile uint8_t temporization_flag = 0;
volatile uint8_t tick = 0;
volatile uint8_t t = 0;

void MEF_init() {
  state = INIT;
  srand(time(NULL));
  LCDclr();
}

void MEF_update() {
  if (!temporization_flag)
    return;

  temporization_flag = 0;

  KEYPAD_scan(&key);

  switch (state) {
  case INIT:
    PRINT_word("Bienvenido", 0, 0);
    PRINT_word("Presione *", 0, 1);
    if (key == SHOW_PASSWORD_KEY) {
      if (set_seed) {
        srand(tick);
        set_seed = 0;
      }

      state = SHOW_PASSWORD;
      strcpy(guess, "*****");
      errors = 0;
      cur_char_index = 0;
      word = NULL;
      first = 1;

      _delay_us(5);
    }
    break;
  case SHOW_PASSWORD:
    if (word == NULL) {
      random_index = GET_RANDOM_INDEX(0, WORD_COUNT);
      word = dictionary[random_index];
      PRINT_word(word, 1, 0);
      t = 0;
    }
    if (t == 0x02) {
      state = WAIT_INPUT;
      LCDclr();
      current_char = 0;
      t = 0;
      PRINT_guess(guess);
      PRINT_error(errors);
    }
    break;
  case WAIT_INPUT:
    if (key == CHAR_END_KEY) {
      if (current_char == word[cur_char_index]) {
        guess[cur_char_index] = current_char;
        current_char = 0;
        PRINT_guess(guess);
        cur_char_index++;
        if (cur_char_index == 5) {
          state = VICTORY;
          time_to_victory = t;
          t = 0;
        }
      } else
        miss();
    } else if (key >= '0' && key <= '9') {
      if (UPDATE_CHAR(current_char, key) > 255)
        miss();
      else {
        current_char = UPDATE_CHAR(current_char, key);
        PRINT_ascii_num(current_char);
      }
    }
    break;
  case VICTORY:
    if (first == 1) {
      PRINT_victory(time_to_victory);
      first = 0;
    }
    if (t == LAST_MESSAGE_TIME) {
      state = INIT;
      LCDclr();
    }
    break;
  case LOSE:
    if (first == 1) {
      PRINT_lose();
      first = 0;
    }
    if (t == LAST_MESSAGE_TIME) {
      state = INIT;
      LCDclr();
    }
    break;
  }
}

void miss() {
  errors++;
  PRINT_error(errors);
  if (errors == MAX_ERRORS) {
    state = LOSE;
    t = 0;
  }
  current_char = 0;
  PRINT_ascii_num(current_char);
}
