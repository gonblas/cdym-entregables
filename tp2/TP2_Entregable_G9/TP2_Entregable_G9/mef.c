#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "lcd.h"
#include "lcd_out.h"

#define WORD_COUNT (sizeof(dictionary) / sizeof(dictionary[0]))
#define GET_RANDOM_INDEX(min, max) (rand() + min + rand() % (max - min + 1))
#define SHOW_PASSWORD_KEY '*'
#define CHAR_END_KEY '#'
#define CHAR_TO_INT(c) c - '0'
#define UPDATE_CHAR(cchar, key) (cchar = cchar * 10 + CHAR_TO_INT(key))

typedef enum
{
  INIT,
  SHOW_PASSWORD,
  WAIT_INPUT,
  VICTORY,
  LOSE
} state_t;
char *dictionary[] = {
    "Arbol", "Boton", "CDyMC", "ClavE", "Facil", "Gafas", "Hojas", "LiBro",
    "Lanza", "Nieve", "PeRro", "PecES", "PiAno", "PrYKe", "RUEDa", "SERIE",
    "SalUd", "Salud", "Silla", "Tecla", "Valor", "Verde", "YnHRz", "hARdD", "silla"};

state_t state;
char *word, guess[6];
uint8_t cur_char_index, current_char, errors, time_to_victory;

void MEF_init()
{
  LCD_Init();
  state = INIT;
  srand(time(NULL));
  PRINT_word("Bienv");
}

void MEF_update(uint8_t t, uint8_t key)
{
  switch (state)
  {
  case INIT:
    if (key == SHOW_PASSWORD_KEY)
    {
      state = SHOW_PASSWORD;
      *guess = "*****\0";
      t = 0;
      errors = 0;
      cur_char_index = 0;
      word = NULL;
    }
    break;
  case SHOW_PASSWORD:
    if (word == NULL)
    {
      word = dictionary[GET_RANDOM_INDEX(0, WORD_COUNT)];
      PRINT_word(word);
    }
    if (t == 2)
    {
      state = WAIT_INPUT;
      LCDclr();
      t = 0;
      current_char = 0;
    }
    break;
  case WAIT_INPUT:
    if (key == CHAR_END_KEY)
    {
      if (current_char == word[cur_char_index])
      {
        strcpy(guess[cur_char_index], current_char);
        PRINT_guess(guess);
        cur_char_index++;
        if (cur_char_index == 5)
        {
          state = VICTORY;
          time_to_victory = t;
          t = 0;
        }
      }
      else
      {
        errors++;
        PRINT_error(errors);
        if (errors == 3)
        {
          state = LOSE;
          t = 0;
        }
      }
    }
    else if (key >= '0' && key <= '9')
    {
      UPDATE_CHAR(current_char, key);
    }
    break;
  case VICTORY:
    PRINT_victory(time_to_victory);
    if (t == 5)
    {
      state = INIT;
    }
    break;
  case LOSE:
    PRINT_lose();
    if (t == 5)
    {
      state = INIT;
    }
    break;
  }
}