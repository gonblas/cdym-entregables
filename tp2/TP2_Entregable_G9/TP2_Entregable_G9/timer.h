
#ifndef TIMER_H
#define TIMER_H
#include <avr/io.h>

extern volatile uint8_t temporization_flag;
extern volatile uint8_t t;

void timer_init();

#endif