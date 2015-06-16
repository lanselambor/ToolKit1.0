#ifndef PIRNIGHTLED_H
#define PIRNIGHTLED_H


#define LIGHT_UP_TIME 60000//10*60*1000  1 minute delay

int led = 3;  //led control output pin
int pir = A5;   //PIR_Sensor input pin

void pirNightLedInit();
long cal_circle_y(long x, long r);
void ledOnOrOff(int status);

void pirNightLed()
{
  static bool pirNightLedInitOK = false;
  static bool ledOnFlag = false;
  static long begin = 0;
  int on = 1, off = 0;
  
  if(!pirNightLedInitOK)
  {
    pirNightLedInitOK = true;
    pirNightLedInit();
  }
  
  if(digitalRead(pir))
  {
    begin = millis();
    if(!ledOnFlag)
    {
      ledOnOrOff(on);
      ledOnFlag = true;
    }
  }
  if(millis() - begin >= LIGHT_UP_TIME)
  {    
    if(ledOnFlag)
    {
      ledOnOrOff(off);
      ledOnFlag = false;
    }
  }         
}

//preparation initialization
void pirNightLedInit()
{
  pinMode(led, OUTPUT);
  pinMode(pir, INPUT);
  analogWrite(led,255);
}

void ledOnOrOff(int status)
{
  if(status)
  {
    //turn on the light
    for(int i=255; i >= 0; i--)
    {
      long y = cal_circle_y(i, 255);   
      analogWrite(led,y);      
      delay(10);      
    }
  }
  else
  {
    //Turn off the light
    for(int i = 0; i<=255; i++)
    {
      long y = cal_circle_y(i, 255);    
      analogWrite(led,y);     
      delay(10);      
    }
  }
}

//r * r = (x-r)*(x-r) + y * y 
long cal_circle_y(long x, long r)
{
    return sqrt((r * r) - (x - r) * (x - r));
}
#endif