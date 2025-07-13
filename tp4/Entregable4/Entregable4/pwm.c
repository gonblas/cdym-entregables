#include "pwm.h"

#define PIN_RED PB5
#define GREEN_OCR OCR1B
#define BLUE_OCR OCR1A
#define PWM_OFF PORTB &= ~(1 << PIN_RED)
#define PWM_ON PORTB |= (1 << PIN_RED)
#define CALC_OPACITY(color_component, adc_value) (255 - ((255 - (color_component)) * (adc_value)) / 255)
RGB_t cur_color = {0, 0, 0};
uint8_t red = 0;

// TIMER1 con frecuencia mayor o igual a 50Hz
void TIMER1_Init()
{
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10); // SETEAMOS OC1A y OC1B en modo FAST PWM 8 BIT NO INVERTIDO
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);     // FAST PWM 8 BIT, prescaler 1024
}

void PWM_Init()
{
  DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB5);
  TIMER1_Init();
  RGB_t default_color = {0, 0, 0};
  PWM_Set_New_Color(default_color);
}

void PWM_Set_New_Color(RGB_t color)
{
  cur_color = color;
}

void PWM_Update_Opacity(uint8_t adc_value)
{

  red = CALC_OPACITY(cur_color.red, adc_value);
  uint8_t green = CALC_OPACITY(cur_color.green, adc_value);
  uint8_t blue = CALC_OPACITY(cur_color.blue, adc_value);
  GREEN_OCR = green;
  BLUE_OCR = blue;
}

void PWM_Update_Red()
{
  if (TCNT1 < red)
    PWM_ON;
  else
    PWM_OFF;
}