#ifndef ANALOGMOTOR_H
#define ANALOGMOTOR_H

#include "drv8830.h"

#define DEV0 0xC0
#define DEV1 0xC4

MOTOR anolog_motor_CH1(DEV0);
MOTOR anolog_motor_CH2(DEV1);

void motorRun(int speed);
void analogMotorInit();

void analogMotor()
{
  int Ain = A5;
  static bool initFlag = false;
  static float analog_value = analogRead(Ain);
  static float last_value = 0;
  
  if(!initFlag)
  {
    initFlag = true;
    analogMotorInit();
  }
  
  analog_value=last_value*0.9 + analogRead(Ain)*0.1;
  
  motorRun(map(analog_value, 0, 1023, 0, 63));
  
  last_value = analog_value;
  
}

void analogMotorInit()
{    

}

void motorRun(int speed)
{
  anolog_motor_CH1.drive(speed);
  anolog_motor_CH2.drive(speed);  
}
#endif