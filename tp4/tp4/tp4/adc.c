#include "adc.h"

void ADC_init() {
	DDRC &= ~(1 << PORTC3);																
	// Configuro el pin PC3 (ADC3) como entrada
	DIDR0 |= (1 << ADC3D); 
	//Deshabilita la entrada digital del puerto ADC3 haciendo que únicamente funcione en modo analógico.
	ADMUX |= (1 << MUX0) | (1 << MUX1) | (1 << REFS0) | (1 << ADLAR);					  
	// Selecciona el canal 3 del ADC (MUX1,MUX0) para que trabaje con el voltaje de referencia a VCC (REFS0) y para que la salida se justifique a la izquierda (ADLAR).
	//De este modo, la salida se encontrará justificada en ADCH
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN); 
	// Configuro el preescalador del ADC para que trabaje a 125kHz (ADPS), y habilitando el ADC (ADEN).
	ADCSRA |= (1<<ADSC);
	//Manda la instrucción para convertir el primer valor medido por el ADC.
}