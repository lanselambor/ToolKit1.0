#ifndef DIGITALSANDCLOCK_H
#define DIGITALSANDCLOCK_H

#include "MyTM1637.h"
#include "TimerOne.h"



static void SandClockTimingISR();

class SandClock
{
    public:
      bool initFlag             = false;
      
      void deleteInterrupt();
      void run();
    private:
          //attribution
      unsigned char MinuteMax   = 25;
      int8_t TimeDisp[4]         = {0,0,0,0};          
      unsigned char halfsecond  = 0;
      unsigned char second      = 0;
      unsigned char minute      = 0;
      unsigned char displayflag = 0;
      unsigned char tilt_value;
      const int clk_pin         = 3;
      const int data_pin        = 5;
      const int TILT_PIN        = A5;       
      MyTM1637 tm1637 = MyTM1637(clk_pin, data_pin);
      
      //method
      void init();
      void TimeUpdate(void);     
};

extern SandClock digitalSandClock;




#endif