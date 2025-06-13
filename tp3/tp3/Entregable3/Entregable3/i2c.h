#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

/**
 * @brief Inicializa el bus I2C configurando la frecuencia y habilitando la interfaz.
 *
 * Configura los registros TWSR y TWBR para establecer la frecuencia de SCL en 100kHz.
 */
void I2C_init(void);

/**
 * @brief Genera una condición de inicio en el bus I2C.
 *
 * Envía la señal de inicio (START) y espera hasta que la operación se complete.
 */
void I2C_start(void);

/**
 * @brief Genera una condición de parada en el bus I2C.
 *
 * Envía la señal de parada (STOP) para finalizar la comunicación I2C.
 */
void I2C_stop(void);

/**
 * @brief Escribe un byte de datos en el bus I2C.
 *
 * @param data Dato a enviar por el bus I2C.
 */
void I2C_write(unsigned char data);

/**
 * @brief Lee un byte de datos del bus I2C.
 *
 * @param isLast Si es 0, envía ACK después de leer; si es distinto de 0, envía NACK.
 * @return El byte leído del bus I2C.
 */
unsigned char I2C_read(unsigned char isLast);

#endif