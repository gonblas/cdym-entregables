#include "adc.h"

static uint8_t adc_value = 0; // Variable para almacenar el valor del ADC

void ADC_Init()
{
	DDRC &= ~(1 << PORTC3);
	// Configuro el pin PC3 (ADC3) como entrada
	DIDR0 |= (1 << ADC3D);
	// Deshabilita la entrada digital del puerto ADC3 haciendo que únicamente funcione en modo analógico.
	ADMUX |= (1 << MUX0) | (1 << MUX1) | (1 << REFS0) | (1 << ADLAR);
	// Selecciona el canal 3 del ADC (MUX1,MUX0) para que trabaje con el voltaje de referencia a VCC (REFS0) y para que la salida se justifique a la izquierda (ADLAR).
	// De este modo, la salida se encontrará justificada en ADCH
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
	// Configuro el preescalador del ADC para que trabaje a 125kHz (ADPS), y habilitando el ADC (ADEN).
	ADCSRA |= (1 << ADSC);
	// Manda la instrucción para convertir el primer valor medido por el ADC.
}

uint8_t ADC_Get_Value()
{
	ADCSRA |= (1 << ADSC); // Inicia la conversión del ADC
	while (!(ADCSRA & (1 << ADIF)))
		;												// Espera a que el flag ADIF sea 1, indicando que la conversión del valor a medir está completa.
	adc_value = ADCH; // Guarda el valor del ADC; el flag de fin de conversión se borra al leer el registro
	ADCSRA |= (1 << ADIF);		// Limpia el flag ADIF escribiendo un 1 en él
	return adc_value;					// Devuelve el valor actual
}
