#ifndef _DRV8830_H_
#define _DRV8830_H_

class MOTOR
{
  public:	
    MOTOR(unsigned char addr);
	  void drive(int speed);
    unsigned char getFault(void);
	  void stop();
	  void brake();
    void clearFault();
  private:
    void I2CWriteReg(unsigned char reg,unsigned char value);  
	  void I2CReadReg(unsigned char reg);
	  unsigned char _addr;
};

#endif