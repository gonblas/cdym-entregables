#ifndef LCDOUT_H
#define LCDOUT_H
#include <stdint.h>

void PRINT_word(char *);
void PRINT_guess(char *);
void PRINT_error(uint8_t );
void PRINT_victory(uint8_t );
void PRINT_lose();

#endif