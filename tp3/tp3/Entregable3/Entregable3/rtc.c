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
  i2c_init();  
  i2c_start(); 

  i2c_write(DS3231_WRITE_MODE);    
  i2c_write(REG_ADDRESS_DS3231_CONTROL_U8);

  i2c_write(0x00);

  i2c_stop(); 
}

void RTC_SetDateTime(date_t date)
{
  i2c_start();

  i2c_write(DS3231_WRITE_MODE);             
  i2c_write(REG_ADDRESS_DS3231_SECONDS_U8); 

  i2c_write(int_to_bcd(date.second) & MASK_SEC);  
  i2c_write(int_to_bcd(date.minute) & MASK_MIN);  
  i2c_write(int_to_bcd(date.hour) & MASK_HOUR); 
                                             
  i2c_stop(); 

  i2c_start(); 

  i2c_write(DS3231_WRITE_MODE);          
  i2c_write(REG_ADDRESS_DS3231_DAYS_U8); 

  i2c_write(int_to_bcd(date.day) & MASK_DAY);  
  i2c_write(int_to_bcd(date.month) & MASK_MONTH); 
  i2c_write(int_to_bcd(date.year) & MASK_YEAR); 

  i2c_stop(); 
}

void RTC_GetDateTime(date_t *date)
{
  i2c_start();

  i2c_write(DS3231_WRITE_MODE);             
  i2c_write(REG_ADDRESS_DS3231_SECONDS_U8); 

  i2c_stop();

  i2c_start();                
  i2c_write(DS3231_READ_MODE); 

  date->second = bcd_to_int(i2c_read(0));  
  date->minute = bcd_to_int(i2c_read(0));  
  date->hour = bcd_to_int(i2c_read(1)); 

  i2c_stop(); 

  i2c_start(); 

  i2c_write(DS3231_WRITE_MODE);          
  i2c_write(REG_ADDRESS_DS3231_DAYS_U8); 

  i2c_stop(); 

  i2c_start();               
  i2c_write(DS3231_READ_MODE); 

  date->day = bcd_to_int(i2c_read(0));  
  date->month = bcd_to_int(i2c_read(0)); 
  date->year = bcd_to_int(i2c_read(1)); 

  i2c_stop(); 
}