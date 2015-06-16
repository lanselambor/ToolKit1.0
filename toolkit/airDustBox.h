#ifndef _AIRDUSTBOX_H_
#define _AIRDUSTBOX_H_

#include "TM1637.h"

#define LOWPOWER         725    //3.4V
#define SHUTDOWN_POWER   705    //3.3v
#define AVERAGE_NUM      32

int BATTERY_ADC  = A2;
int BATTERY_LED  = A3;

int clk_pin  = 3;
int data_pin = 5;
int dustPin  = A5;
int ledPower = A4;

int   delayTime   = 280;
int   delayTime2  = 30;
int   offTime     = 9680;
float dustVal     = 0;
long sum_dustVal = 0;
  
TM1637 DustPPM_display(clk_pin, data_pin);  

void displayNumber(int number);
void airDustBoxInit();

void airDustBox()
{    
  static bool initFlag = false;
  if(!initFlag)
  {
    initFlag = true;
    airDustBoxInit();
  }
  
  for(int i=0;i<AVERAGE_NUM;i++)
  {
    digitalWrite(ledPower,HIGH); 
    delayMicroseconds(delayTime);
    dustVal=analogRead(dustPin); 
    delayMicroseconds(delayTime2);
    digitalWrite(ledPower,LOW); 
    delayMicroseconds(offTime);  
    sum_dustVal = sum_dustVal+dustVal;
    delay(40);
  } 
  
  dustVal = sum_dustVal/AVERAGE_NUM;
  sum_dustVal = 0;
  dustVal = dustVal*5/1024;
  dustVal = dustVal*1000/6-100;
  
  displayNumber(dustVal);
}
void airDustBoxInit()
{    
  //dislpay init
  DustPPM_display.init();
  DustPPM_display.set(BRIGHT_TYPICAL);    
  DustPPM_display.point(false);
  DustPPM_display.clearDisplay();  
}
void displayNumber(int number)
{
  int thousand = 0;
  int hundred = 0;
  int tens = 0;
  int units = 0;
  
  thousand = number / 1000;
  hundred = number % 1000 / 100;
  tens = number % 100 / 10;
  units = number % 10;   
  
  DustPPM_display.clearDisplay();  
  if(thousand != 0)  DustPPM_display.display(0,thousand);
  if((thousand != 0) || (hundred != 0))  DustPPM_display.display(1,hundred);
  if((thousand != 0) || (hundred != 0) || (tens != 0))  DustPPM_display.display(2,tens);
  DustPPM_display.display(3,units);
  
}
#endif

/* ------------- End of File ---------------------- */

