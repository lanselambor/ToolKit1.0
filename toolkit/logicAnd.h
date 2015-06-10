#ifndef _LOGICAND_H_
#define _LOGICAND_H_



void logicAnd()
{
  int out1 = 3;
  int out2 = 5;
  int in1  = A5;
  int in2  = A4;
  static bool initialized = false;
  static const int analogThreshold = 800;
  
  if(!initialized)
  {
    initialized = true;
    
    pinMode(out1, OUTPUT);
    pinMode(out2, OUTPUT);
    pinMode(in1, INPUT);
    pinMode(in2, INPUT);
  } 
  
  int analog1 = analogRead(in1);
  int analog2 = analogRead(in2);
  if( (analog1 > analogThreshold) && (analog2 > analogThreshold) )
  {
    analogWrite(out1, map(analog1, 0, 1023, 0, 255));
    analogWrite(out2, map(analog2, 0, 1023, 0, 255));
  }
  else
  {
    analogWrite(out1, 0);
    analogWrite(out2, 0);
  }
  delay(20);
}

#endif