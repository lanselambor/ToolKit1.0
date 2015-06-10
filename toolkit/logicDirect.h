#ifndef _LOGICDIRECT_H_
#define _LOGICDIRECT_H_



void logicDirect()
{
  int out1 = 3;
  int out2 = 5;
  int in1  = A5;
  int in2  = A4;
  static bool initialized = false;
  
  if(!initialized)
  {
    initialized = true;
    
    pinMode(out1, OUTPUT);
    pinMode(out2, OUTPUT);
    pinMode(in1, INPUT);
    pinMode(in2, INPUT);
  }  
  
  analogWrite(out1, map(analogRead(in1), 0, 1023, 0, 255));
  analogWrite(out2, map(analogRead(in2), 0, 1023, 0, 255));
  delay(20);
}

#endif