#include "i2c.h"

void i2c_init(void)
{
    TWSR = 0x00;
    TWBR = 72;   // scl frecuecnia 100kHz
    TWCR = 0x04; // habilita Two-Wire Interface
}

void i2c_start(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA); // TWI start, habilita la interrupción
    while ((TWCR & (1 << TWINT)) == 0);
}

void i2c_stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); // TWI stop
}

void i2c_write(unsigned char data)
{
    TWDR = data;                       // cargar dato
    TWCR = (1 << TWINT) | (1 << TWEN); // Limpia TWINT para empezar transmisión y habilita TWI
    while ((TWCR & (1 << TWINT)) == 0);
}

unsigned char i2c_read(unsigned char isLast)
{
    if (isLast == 0)
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // send ACK
    else
        TWCR = (1 << TWINT) | (1 << TWEN); // send NACK
    while ((TWCR & (1 << TWINT)) == 0)
        ;
    return TWDR;
}
