#include "i2c.h"
#include "rtc.h"

static uint8_t bcd_to_int(uint8_t bcd)
{
  int tens = (bcd >> 4) & 0x0F;
  int ones = bcd & 0x0F;
  return tens * 10 + ones;
}

static uint8_t int_to_bcd(uint8_t in)
{ // Convierte un número entero a BCD (Binary-Coded Decimal)
  uint8_t ans;
  ans = ((in / 10) << 4) & (0xF0);
  ans |= in % 10;
  return ans;
}

void RTC_Init(void)
{
  I2C_init();
  I2C_start();

  I2C_write(DS3231_WRITE_MODE);
  I2C_write(REG_ADDRESS_DS3231_CONTROL_U8);

  I2C_write(0x00); // Configura el registro de control del DS3231 para desactivar la alarma y habilitar el oscilador

  I2C_stop();
}

void RTC_SetDateTime(date_t date)
{
  I2C_start();

  I2C_write(DS3231_WRITE_MODE);             // Inicia la comunicación con el DS3231 en modo escritura
  I2C_write(REG_ADDRESS_DS3231_SECONDS_U8); // Dirección del registro de segundos

  I2C_write(int_to_bcd(date.second) & MASK_SEC); // Convierte los segundos a BCD y aplica la máscara
  I2C_write(int_to_bcd(date.minute) & MASK_MIN); // Convierte los minutos a BCD y aplica la máscara
  I2C_write(int_to_bcd(date.hour) & MASK_HOUR);

  I2C_stop();

  I2C_start();
  I2C_write(DS3231_WRITE_MODE); // Inicia la comunicación con el DS3231 en modo escritura
  I2C_write(REG_ADDRESS_DS3231_DAYS_U8);

  I2C_write(int_to_bcd(date.day) & MASK_DAY);
  I2C_write(int_to_bcd(date.month) & MASK_MONTH);
  I2C_write(int_to_bcd(date.year) & MASK_YEAR);

  I2C_stop();
}

void RTC_GetDateTime(date_t *date)
{
  I2C_start();

  I2C_write(DS3231_WRITE_MODE);
  I2C_write(REG_ADDRESS_DS3231_SECONDS_U8);

  I2C_stop();

  I2C_start();
  I2C_write(DS3231_READ_MODE);

  date->second = bcd_to_int(I2C_read(0));
  date->minute = bcd_to_int(I2C_read(0));
  date->hour = bcd_to_int(I2C_read(0));

  I2C_read(0); // Se leen los dias de la semana, pero no se usan

  date->day = bcd_to_int(I2C_read(0));
  date->month = bcd_to_int(I2C_read(0));
  date->year = bcd_to_int(I2C_read(1)); // NACK

  I2C_stop();
}
