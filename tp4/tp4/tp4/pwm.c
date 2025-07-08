#include "pwm.h"

#define RED OCR1A
#define GREEN OCR1B
#define BLUE PORTB5
#define PWM_OFF PORTB &= ~(1 << PORTB5)
#define PWM_ON PORTB |= (1 << PORTB5)
#define PWM_START DDRB |= (1 << PORTB5)

void TIMER1_Init()
{
  TCCR1A = (1 << WGM10);
  TCCR1B = (1 << WGM12) | (1 << CS01) | (1 << CS00); // FAST PWM 8 BIT, prescaler 64
}