#include "lcd.h"
#include <stdint.h>
#include <stdio.h>

void PRINT_word(uint8_t *word, uint8_t clr, uint8_t row)
{
  if (clr) LCDclr();
  uint8_t length = strlen((char *)word);
  uint8_t start_pos = 0;

  if (length < 16)
    start_pos = (16 - length) / 2;

  LCDGotoXY(start_pos, row);
  LCDstring(word, length);
}

void PRINT_ascii_num(uint8_t number)
{
  LCDGotoXY(13, 0);
  char message[4];
  int len = sprintf(message, "%3.d", number);
  LCDstring((uint8_t *)message, len);
}

void PRINT_guess(uint8_t *guess)
{
  LCDGotoXY(0, 0);

  LCDstring(guess, 5);
}

void PRINT_error(uint8_t error)
{
  LCDGotoXY(0, 1);
  char message[16];
  int len = sprintf(message, "Errores: %d", error);
  LCDstring((uint8_t *)message, len);
}

void PRINT_victory(uint8_t t)
{
  LCDclr();
  char message[16];
  sprintf(message, "Victoria: %d seg.", t);
  PRINT_word((uint8_t *)message, 0, 0);
}

void PRINT_lose()
{
  LCDclr();
  char message[16];
  sprintf(message, "Derrota.");
  PRINT_word((uint8_t *)message, 0, 0);
}
