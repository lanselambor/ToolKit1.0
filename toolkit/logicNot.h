#ifndef _LOGICNOT_H_
#define _LOGICNOT_H_



void logicNot()
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
  
  int analog = analogRead(in1); 
  int analogOut = map(255-analog, 0, 1023, 0, 255);  
  analogWrite(out1, analogOut);
  analogWrite(out2, analogOut);
  delay(20);
}

#endif