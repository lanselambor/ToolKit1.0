#ifndef GROOT_H
#define GROOT_H

#include <Arduino.h>
#include <Servo.h>                  

class Groot
{
  public:
    void run()
    {
      static bool initOK = false;
      if(!initOK)
      {
        initOK = true;
        grootInit();
      }
      
      val_sound = average_filter(pin_sound, 50);       
      int threshold = val_sound - quiet_value;
      if(threshold > thershold_off)
      {
        Serial.println(threshold);
        servoRun(threshold);
      }                  
      delay(200);  
    }
    
  private:
    void grootInit()
    { 
      //get quiet sound value
      delay(500);
      long tmp = 0;
      for(int i = 0;i<1000;i++)
      {
        tmp += analogRead(pin_sound);
      }
      quiet_value = tmp / 1000;  

      myservo.attach(3);  //    mini fan use pin 9   joint use pin 3  
      myservo.write(90); 

    }
    
    void servoRun(int analog)
    {
      int dec = 0;
      if(analog < 200)
      {  
        dec = map(analog, thershold_off, 200, 2, 30);
      }
      else
      {
        dec = 30;
      }
      myservo.write(original_pos - dec);
      delay(200);
      myservo.write(original_pos + dec);
      delay(200);
    }
    
    int mid_filter(int analog_pin)
    {
      int a = analogRead(analog_pin);
      delayMicroseconds(10);
      int b = analogRead(analog_pin);
      delayMicroseconds(10);
      int c = analogRead(analog_pin);
      delayMicroseconds(10);
      
      return midNum(&a, &b, &c);
    }

    int average_filter(int analog_pin, int num)
    {
      long temp = 0;
      for(int i=0;i<num;i++)
      {
        //temp += analogRead(analog_pin);    
        temp += mid_filter(analog_pin);    
      }
      return temp/num;
    }

    int midNum(int *a, int *b, int *c)
    {
      int tmp = 0;
      if(*a > *b){
        tmp = *a;
        *a = *b;
        *b = tmp;
      }
      if(*b > *c){
        tmp = *b;
        *b = *c;
        *c = tmp;
      }
      if(*b > *c){
        tmp = *b;
        *b = *c;
        *c = tmp;
      }
      return *b;
    }
    
    //parameters
    Servo myservo;       
    const int pin_sound      = A5;    
    volatile int quiet_value = 0; 
    int val_sound            = 0;    
    const int thershold_off  = 50; 
    const int original_pos   = 90;     
    int Threshold[5] = {
      40 + thershold_off, 
      60 + thershold_off, 
      80 + thershold_off,
      100 + thershold_off, 
      120 + thershold_off };
  
};
#endif
