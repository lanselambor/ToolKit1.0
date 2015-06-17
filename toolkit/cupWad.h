#ifndef CUPWAD_H
#define CUPWAD_H

#define LINE_FINDER_FIND       (LOW == digitalRead(A5))   //something cover the sensor
#define LINE_FINDER_NOTFIND    (HIGH == digitalRead(A5)) //nothing cover the sensor
#define TIME_TO_DRINK          2700000   //unit: Ms. 2700000 Ms = 45 Min, time to drink water 
#define SPEAK_DURATION         4         //4 s

class CupWad
{
  public:
    void run()
    {      
      static bool cupWadInitOK = false;
      static volatile long clock;    
      static volatile bool readyTiming = true;
      
      if(cupWadInitOK)
      {
        cupWadInitOK = true;
        cupWadInit();
      }
      
      if (LINE_FINDER_FIND)
      {   
        if(readyTiming)
        {
          readyTiming = false;
          speak(1, SPEAK_DURATION);
          clock = millis();        
        }
      }
      else if(LINE_FINDER_NOTFIND)
      {
        readyTiming = true;
        clock = millis();
      } 
      
      if( millis() - clock > TIME_TO_DRINK )
      {
        speak(1, SPEAK_DURATION); 
        clock = millis();
      }
    }            
    
    
  private:
    const int linefinder  = A5;
    const int recorder    = 3;
    
    void cupWadInit()
    {   
      //initial devices
      pinMode(linefinder,INPUT);    
      pinMode(recorder, OUTPUT);
      digitalWrite(recorder, LOW);
    }
    
    void speak(int times, int seconds)
    {
      for(int i=0; i<times; i++)
      {
        digitalWrite(recorder, HIGH);
        delaySeconds(seconds);    
        digitalWrite(recorder, LOW);
        delaySeconds(1);
        if(LINE_FINDER_NOTFIND)
        {
          i = times;      
        }
      }
    }
    
    void delaySeconds(int seconds)
    {
      for(int j=0; j<seconds; j++)  //delay seconds
      {        
        delay(1000);
      }
    }    
};

#endif