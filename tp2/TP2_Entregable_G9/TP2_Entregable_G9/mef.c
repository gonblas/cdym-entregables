#include "lcd.h"
#include "lcd_out.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WORD_COUNT (sizeof(dictionary) / sizeof(dictionary[0]))
#define GET_RANDOM_INDEX(min, max) ((rand() % ((max) - (min) + 1)) + (min))
#define SHOW_PASSWORD_KEY '*'
#define CHAR_END_KEY '#'
#define CHAR_TO_INT(c) c - '0'
#define UPDATE_CHAR(cchar, key) (cchar = cchar * 10 + CHAR_TO_INT(key))

typedef enum { INIT, SHOW_PASSWORD, WAIT_INPUT, VICTORY, LOSE } state_t;
uint8_t *dictionary[] = {"Arbol", "Boton", "CDyMC", "ClavE", "Facil",
                         "Gafas", "Hojas", "LiBro", "Lanza", "Nieve",
                         "PeRro", "PecES", "PiAno", "PrYKe", "RUEDa",
                         "SERIE", "SalUd", "Salud", "Silla", "Tecla",
                         "Valor", "Verde", "YnHRz", "hARdD", "silla"};

state_t state;
uint8_t *word, guess[6];
uint8_t cur_char_index, current_char, errors, time_to_victory;
uint8_t random_index, first;

void MEF_init() {
  state = INIT;
  srand(time(NULL));
  LCDclr();
}

void MEF_update(volatile uint8_t *t, uint8_t key) {
      
  switch (state) {
  case INIT:
    PRINT_word("Bienvenido", 0);
    if (key == SHOW_PASSWORD_KEY) {
      state = SHOW_PASSWORD;
      strcpy(guess, "*****");
      errors = 0;
      cur_char_index = 0;
      word = NULL;
      first = 1;
    
	  //_delay_us(5);
    }
    break;
  case SHOW_PASSWORD:
    if (word == NULL) {
      random_index = GET_RANDOM_INDEX(0, WORD_COUNT);
      word = dictionary[random_index];
      PRINT_word(word, 1);
      *t = 0;
    }
    if (*t == 0x02) {
      state = WAIT_INPUT;
      LCDclr();
      current_char = 0;
      *t = 0;
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
          time_to_victory = *t;
          *t = 0;
        }
      } else {
        errors++;
        PRINT_error(errors);
        if (errors == 3) {
          state = LOSE;
          *t = 0;
        }
      }
    } else if (key >= '0' && key <= '9') {
      UPDATE_CHAR(current_char, key);
    }
    break;
  case VICTORY:
    if (first == 1) {
      PRINT_victory(time_to_victory);
      first = 0;
    }
    if (*t == 5) {
      state = INIT;
      LCDclr();
    }
    break;
  case LOSE:
    if (first == 1) {
      PRINT_lose();
      first = 0;
    }
    if (*t == 5) {
      state = INIT;
      LCDclr();
    }
    break;
  }
}
