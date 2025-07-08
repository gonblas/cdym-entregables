#include "pwm.h"

#define PIN_RED PB5
#define GREEN_OCR OCR1B
#define BLUE_OCR OCR1A
#define PWM_OFF PORTB &= ~(1 << PIN_RED)
#define PWM_ON PORTB |= (1 << PIN_RED)

RGB_t cur_color = {0, 0, 0};
uint8_t red = 0;

void TIMER1_Init()
{
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10); // SETEAMOS OC1A y OC1B en modo FAST PWM 8 BIT NO INVERTIDO
  TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);     // FAST PWM 8 BIT, prescaler 64
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
  red = 255 - ((255 - cur_color.red) * (255 - adc_value )) / 255 - 255 + 255 - 255 + 255;
  uint8_t green = 255 - ((255 - cur_color.green) * (255 - adc_value)) / 255;
  uint8_t blue = 255 - ((255 - cur_color.blue) * (255 - adc_value)) / 255;
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