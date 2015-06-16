#ifndef IRCARRECEIVE_H
#define IRCARRECEIVE_H

#include "IRSendRev.h"
#include "drv8830.h"

#define SERIAL_OUT    0

#define DEV0 0xC0
#define DEV1 0xC4

MOTOR motor_CH1(DEV0);
MOTOR motor_CH2(DEV1);

struct car{
  const int throttleUp   = 87;
  const int throttleDown = 111;
  const int ahead        = 231;
  const int left         = 239;
  const int stop         = 199;
  const int right        = 165;
  const int back         = 181;
  int status;  
}CarMotion;

int IRPin = A5;
uint8_t Throttle = 32;

void carRun(int direction);

void IRCarReceive()
{
  static bool initFlag = false;
  uint8_t dta[10];
   
  if(!initFlag)
  {
    initFlag = true;
    motor_CH1.drive(0);
    motor_CH2.drive(0);
    IR.Init(IRPin);
    #if SERIAL_OUT
    Serial.begin(9600);    
    #endif
  }
  if(IR.IsDta())
  {       
      int length= IR.Recv(dta);
      for (int i =0;i<length;i++)
      {
        #if SERIAL_OUT
        Serial.print(dta[i]);
        Serial.print("\t");
        #endif
      }
      #if SERIAL_OUT
      Serial.println();
      #endif
      
      carRun(dta[9]);
  }
}

void carRun(int direction)
{
  //direction: 
  //VOL-:throttleDown  VOL+:throttleUp  2:go ahead  4:go Left , 5:Stop  6:go Right, 8:go back
  //uint8_t Codes[6] = {87, 111, 231, 239, 199, 165, 181}; //VOL-, VOL+., 2, 4, 5, 6, 8
  switch(direction)
  {
    case 87:
      Throttle -= 2;
      if(Throttle <= 0) Throttle = 0;  
      #if SERIAL_OUT      
      Serial.println("throttleDown");
      #endif
      break;
    case 111:
      Throttle += 2;      
      if(Throttle >= 63) Throttle = 63;
      #if SERIAL_OUT
      Serial.println("throttleUp");
      #endif
      break;
    case 231:
      CarMotion.status = CarMotion.ahead;
      #if SERIAL_OUT
      Serial.println("go ahead");
      #endif
      break;
    case 239:    
      CarMotion.status = CarMotion.left;
      #if SERIAL_OUT
      Serial.println("go Left");
      #endif
      break;
    case 199:        
      CarMotion.status = CarMotion.stop;
      #if SERIAL_OUT
      Serial.println("stop");
      #endif
      break;    
    case 165:   
      CarMotion.status = CarMotion.right;
      #if SERIAL_OUT
      Serial.println("go Right");
      #endif
      break;
    case 181:    
      CarMotion.status = CarMotion.back;
      #if SERIAL_OUT
      Serial.println("go back");
      #endif
      break; 
      
    default:
      break;
  }
  
  //update motor motion
  if(CarMotion.status == CarMotion.back){
    motor_CH1.drive(0-Throttle);
    motor_CH2.drive(0-Throttle);
  }
  else if(CarMotion.status == CarMotion.ahead){
    motor_CH1.drive(Throttle);
    motor_CH2.drive(Throttle);
  }
  else if(CarMotion.status == CarMotion.left){
    motor_CH1.drive(0);
    motor_CH2.drive(Throttle);
  }
  else if(CarMotion.status == CarMotion.right){
    motor_CH1.drive(Throttle);
    motor_CH2.drive(0);
  }
  else if(CarMotion.status == CarMotion.stop){
    motor_CH1.drive(0);
    motor_CH2.drive(0);
  }
  
}


#endif