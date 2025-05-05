/*
 * TP2_Entregable_G9.c
 *
 * Created: 4/28/2025 7:03:57 PM
 * Author : Ivan Trolanis y Gonzalo Fiasco
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include "lcd.h"
#include "mef.h"
#include "timer.h"
#include "keypad.h"
#include <util/delay.h>

volatile uint8_t tick = 0, t = 0;
uint8_t key = 0xFF;

int main(void) {
  timer_init();
  LCD_Init();
  _delay_ms(100);
  
  
  keypad_init();
  MEF_init();
  
  while (1) {
    if (!KEYPAD_Scan(&key)) {
      key = 0xFF;
    }

    MEF_update(&t, key);
	_delay_ms(10);
  }
}

ISR(TIMER0_OVF_vect) {
  TCNT0 = 100; // Reinicia el timer para 10 ms
  tick++;
    
  if (tick == 100) { // Cada 100 ticks de 10 ms = 1 segundo
    t++;
    tick = 0;
  }
}
