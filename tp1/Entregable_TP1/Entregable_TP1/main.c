/* Inclusión de bibliotecas de código */
#include <avr/io.h>      // Registros del microcontrolador
#define F_CPU 16000000UL // Defino la frecuencia de oscilador en 8MHz
#include <stdint.h>
#include <util/delay.h> // Retardos por software

#define DELAY 100 // Definido en ms

void seq_1(uint8_t first);
void seq_2(uint8_t first);
void seq_3(uint8_t first);

/* Función main */
int main(void) {
  /* Setup */
  DDRB &= (1 << PORTB3 |
           1 << PORTB4); // Configuro bit3 y bit4 del puerto B como salida
  DDRC &= ~(1 << PORTC0 |
            1 << PORTC1); // Configuro bit0 y bit1 puerto C como entrada
  DDRD = 0xFF;            // Configuro Puerto D como salida
  PORTC |=
      (1 << PORTC0 | 1 << PORTC1); // Habilito Pull-Up en bit0 y bit1 puerto C

  uint8_t state = 1;
  uint8_t pushed_c0 = 0;
  uint8_t first = 1;

  /* Loop */
  while (1) {
    if (pushed_c0 && ~(PINC & (1 << PINC0))) {
      pushed_c0 = 0;
    }

    if (!pushed_c0 && ~(PINC | ~(1 << PINC0))) {
      pushed_c0 = 1;
      state = (state + 1) % 4 == 0 ? 1 : state + 1;
      first = 1;
    }

    if (PINC & (1 << PINC1)) {
      PORTB &= ~(1 << PORTB3 | 1 << PORTB4);
    } else {
      PORTB = (PORTB & ~(1 << PORTB3 | 1 << PORTB4)) | (state << PORTB3);
    }

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

    _delay_ms(DELAY);

    first = 0;
  }
  /* Punto de finalización del programa (NO se debe llegar a este lugar) */
  return 0;
}

void seq_1(uint8_t first) { PORTD = first ? 0b01010101 : ~PORTD; }

void seq_2(uint8_t first) { PORTD = (first || PORTD & (1 << PORTD7) ? (0b00000001) : (PORTD << 1);
}

void seq_3(uint8_t first) { PORTD = first ? 0b10000000 : ~PORTD & 0b10000001; }
