#ifndef LCDOUT_H
#define LCDOUT_H
#include <stdint.h>

void PRINT_word(uint8_t *, uint8_t);
void PRINT_guess(uint8_t *);
void PRINT_error(uint8_t );
void PRINT_victory(uint8_t );
void PRINT_lose();

#endif