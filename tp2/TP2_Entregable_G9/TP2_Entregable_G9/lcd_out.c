#include "lcd.h"
#include <stdio.h>
#include <stdint.h>


void PRINT_word(char *word)
{
  LCDGotoXY(0, 0);
  LCDstring(word, strlen(word)+1);
}

void PRINT_guess(char *guess)
{
  LCDGotoXY(0, 0);
  LCDstring(guess, 5);
}

void PRINT_error(uint8_t error)
{
  LCDGotoXY(0, 1);
  char message[16];
  int len = sprintf(message, "Errores: %d", error);
  LCDstring(message, len);
}

void PRINT_victory(uint8_t t)
{
  LCDclr();
  char message[16];
  sprintf(message, "victoria: %d seg.", t);
  LCDstring(message, strlen(message));
}

void PRINT_lose()
{
  LCDclr();
  char message[16];
  sprintf(message, "derrota");
  LCDstring(message, strlen(message));
}