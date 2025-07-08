#ifndef PWM_H_
#define PWM_H_
#include <avr/io.h>
#include <avr/interrupt.h>  
#include <stdint.h>
#include "color.h"

void TIMER1_Init();

void PWM_Init();

void PWM_Set_New_Color(RGB_t color);

void PWM_Update_Red();

#endif