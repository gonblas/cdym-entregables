#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_Init();
uint8_t ADC_Get_Value();
#endif