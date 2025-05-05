#ifndef LCD_H
#define LCD_H
#include <stdint.h>

void keypad_init(void);
uint8_t KEYPAD_Scan(volatile uint8_t *pkey);
#endif
