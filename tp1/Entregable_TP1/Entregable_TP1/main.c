/* Inclusión de bibliotecas de código */
#include <avr/io.h>       // Registros del microcontrolador
#define F_CPU 16000000UL  // Defino la frecuencia de oscilador en 16MHz
#include <util/delay.h>   // Retardos por software
#include <stdint.h>       // Defino los tipos de datos para trabajar con enteros

#define DELAY 100         // Definido en ms

/* Definición de prototipos de funciones */
void seq_1(uint8_t first);
void seq_2(uint8_t first);
void seq_3(uint8_t first);

/* Función main */
int main(void) {
  /* Setup */
  DDRB |= (1 << PORTB3 | 1 << PORTB4);    // Configuro bit3 y bit4 del puerto B como salida
  DDRC &= ~(1 << PORTC0 | 1 << PORTC1);   // Configuro bit0 y bit1 del puerto C como entrada
  DDRD = 0xFF;                            // Configuro Puerto D como salida
  PORTC |= (1 << PORTC0 | 1 << PORTC1);   // Habilito Pull-Up en bit0 y bit1 del puerto C

  uint8_t state = 1;                      // Estado que indica la secuencia a ejecutar
  uint8_t pushed_c0 = 0;                  // Variable que indica si se ha presionado el botón correspondiente a PORTC0
  uint8_t first = 1;                      // Variable que indica si es la primera vez que se ejecuta la secuencia

  /* Loop */
  while (1) {
    /* Si el botón de PORTC0 deja de ser presionado */
    if (pushed_c0 && (PINC & (1 << PINC0))) {
      pushed_c0 = 0;
    }

    /* Si el botón no fue presionado y esta siendo presionado */
    if (!pushed_c0 && (~PINC & (1 << PINC0))) {
      pushed_c0 = 1;  // Se presionó el botón
      state = (state + 1) % 4 == 0 ? 1 : state + 1; // Cambia de estado
      first = 1;  // Indicar que es la primera vez que se ejecuta la secuencia nueva
    }

    /* Si el botón de PORTC1 no está presionado */
    if (PINC & (1 << PINC1)) {
      PORTB &= ~(1 << PORTB3 | 1 << PORTB4); // Apago ambos LEDs
    } else {
      PORTB = (PORTB & ~(1 << PORTB3 | 1 << PORTB4)) | (state << PORTB3); // Enciendo el LED correspondiente al estado
    }

    /* Ejecuto un paso de la secuencia correspondiente */
    switch (state) {
    case 1:
      seq_1(first);
      break;
    case 2:
      seq_2(first);
      break;
    case 3:
      seq_3(first);
      break;
    }

    _delay_ms(DELAY); // Retardo de 100ms
    first = 0;        // Indicar que no es la primera vez que se ejecuta la secuencia
  }
  /* Punto de finalización del programa (NO se debe llegar a este lugar) */
  return 0;
}

/*
  * Funciones de secuencias
  * Secuencia 1. Enciende LED pares y luego impares de forma repetitiva.
  * Secuencia 2. Enciende un LED a la vez y lo hace desde el LSB hacia el MSB repetitivamente.
  * Secuencia 3. Enciende un LED a la vez empezando desde el MSB y rebotando en los extremos repetitivamente
*/
void seq_1(uint8_t first) { PORTD = first ? 0b01010101 : ~PORTD; }

void seq_2(uint8_t first) {
  // Desplazo a izquierda salvo que sea la primera vez ó el bit7 esté encendido
  PORTD = (first || PORTD & (1 << PORTD7)) ? (0b00000001) : (PORTD << 1);
}

void seq_3(uint8_t first) {
  static uint8_t moving_left = 0; // 0: izquierda, 1: derecha

  // Invertir dirección si se llega a un extremo
  if (PORTD == 0b00000001 || PORTD == 0b10000000) {
    moving_left ^= 0x01;
  }

  if (first) {
    PORTD = 0b00000001; // Inicia con el primer bit encendido
    moving_left = 0;    // Reinicia la dirección de movimiento
    return;
  }

  // Desplazamiento hacia la izquierda o derecha
  PORTD = moving_left ? (PORTD << 1) : (PORTD >> 1);
}
