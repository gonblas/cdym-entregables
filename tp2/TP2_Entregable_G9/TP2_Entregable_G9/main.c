/*
 * TP2_Entregable_G9.c
 *
 * Created: 4/28/2025 7:03:57 PM
 * Author : Ivan Polanis y Gonzalo Blasco 
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include "lcd.h"
#include "mef.h"
#include "timer.h"
#include "keypad.h"
#include <util/delay.h>

uint8_t key = 0xFF;
int main(void) {
  timer_init();
  LCD_Init();
  _delay_ms(100);
  
  keypad_init();
  MEF_init();
  
  while (1) {


    MEF_update(&t, key);
  }
}

