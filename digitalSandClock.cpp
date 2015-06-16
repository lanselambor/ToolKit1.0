#include "digitalSandClock.h"


SandClock digitalSandClock;

volatile int T25Minutes = 25*60;
volatile bool clockPoint = false;

static void SandClockTimingISR()
{  
  if(!clockPoint) T25Minutes--;
  if(T25Minutes <= 0)   T25Minutes = 0;
  clockPoint = !clockPoint;  
}

void SandClock::deleteInterrupt()
{
  Timer1.stop();
  Timer1.detachInterrupt();
  initFlag = false;
}

void SandClock::run()
{  
  if(!initFlag)
  {
    initFlag = true;
    init();
  }
  
  if(tilt_value != digitalRead(TILT_PIN))
  {
    tilt_value = digitalRead(TILT_PIN);
    T25Minutes = 25*60;
    displayflag = 1;
  }
  
  TimeUpdate();
  if(tilt_value == 0) tm1637.display(TimeDisp,DISPLAY_FLAG_F);
  if(tilt_value == 1) tm1637.display(TimeDisp,DISPLAY_FLAG_B);
}
void SandClock::init()
{
  pinMode(TILT_PIN,INPUT_PULLUP);
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);  
  tm1637.clearDisplay();  
  
  Timer1.initialize(500000);  //500ms freq
  Timer1.attachInterrupt(SandClockTimingISR);  
}

void SandClock::TimeUpdate(void)
{
  
  minute = T25Minutes/60;
  second = T25Minutes%60;
  if(clockPoint)tm1637.point(POINT_ON);
  else tm1637.point(POINT_OFF); 
  TimeDisp[0] = minute / 10;
  TimeDisp[1] = minute % 10;
  TimeDisp[2] = second / 10;
  TimeDisp[3] = second % 10;
}


