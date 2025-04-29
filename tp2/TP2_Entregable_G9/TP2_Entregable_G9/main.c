/*
 * TP2_Entregable_G9.c
 *
 * Created: 4/28/2025 7:03:57 PM
 * Author : Ivan Trolanis y Gonzalo Fiasco
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "timer.h"
#include "keypad.h"
#include "lcd.h"
#include "mef.h"



volatile uint8_t tick = 0, t = 0;

int main(void)
{
    timer_init();
    keypad_init();
    LCDinit();
    uint8_t key;

    while (1) 
    {
        if (!KEYPAD_Scan(&key)) {
            key = 0xFF;
        }
        _delay_ms(100);
        MEF_update(&t, key);
    }
}

ISR(TIMER0_COMPB_vect){
    tick++;
    if(tick == 100) {
        t++;
        tick = 0;
    }
    TCNT0 = 99;
}
