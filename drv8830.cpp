#include "drv8830.h"
#include <Wire.h>
#include "SoftI2CMaster.h"

SoftI2CMaster i2c(3, 5, 1);

MOTOR::MOTOR(unsigned char addr)
{	
  _addr = addr>>1;	
}
void MOTOR::drive(int speed)
{
  unsigned char regValue = 0x80;
  I2CWriteReg(0x01, regValue);
  regValue = (unsigned char)abs(speed);
  if (regValue > 63) regValue = 63;
  regValue = regValue<<2;
  if (speed < 0) regValue |= 0x01;
  else           regValue |= 0x02;
  I2CWriteReg(0x00,regValue);
}
unsigned char MOTOR::getFault(void)
{
  unsigned char buffer = 0;
  unsigned char clearFault = 0x80;
  //I2CReadBytes(0x01, &buffer, 1);
  I2CWriteReg(0x01, clearFault);
  return buffer;
}
void MOTOR::I2CWriteReg(unsigned char reg,unsigned char value)
{
  i2c.beginTransmission(_addr);
  i2c.write(reg);
  i2c.write(value);
  i2c.endTransmission();  
}
void MOTOR::I2CReadReg(unsigned char addr)
{
  
}
 
