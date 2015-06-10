#ifndef _COLORRGBLED_H_
#define _COLORRGBLED_H_

#include "GroveColorSensor.h"
#include "Adafruit_NeoPixel.h"

class MyColorSensor : public GroveColorSensor
{
  public:
    int r, g, b, c;
    void readRGB()
    {
      uint8_t dataRead[8];
      Wire.beginTransmission(COLOR_SENSOR_ADDR);
      Wire.write(REG_BLOCK_READ);
      Wire.endTransmission();
  	
      Wire.beginTransmission(COLOR_SENSOR_ADDR);
      Wire.requestFrom(COLOR_SENSOR_ADDR, 8);
      delay(100);
      
      if(8 <= Wire.available())
      {
        int i;
        for(i = 0; i < 8; ++i)
        {
          dataRead[i] = Wire.read();	
        }
      }
      g = (int)(dataRead[1]*256 + dataRead[0]);
      r = (int)(dataRead[3]*256 + dataRead[2]);
      b = (int)(dataRead[5]*256 + dataRead[4]);
      c = (int)(dataRead[7]*256 + dataRead[6]);
    }
};



void colorRGBLed()
{
  static bool initialized = false;
  int ledNum = 20;

  Adafruit_NeoPixel pixels = Adafruit_NeoPixel(ledNum, 3, NEO_GRB + NEO_KHZ800);
  pixels.begin();
  MyColorSensor colorSensor;

  if(CurrentProgramNumber == COLORRGBLED) 
  {      
    colorSensor.readRGB();    
    for(int i = 0;i<ledNum; i++)
    {
      pixels.setPixelColor(i, pixels.Color(colorSensor.r, colorSensor.g, colorSensor.b));      
    }
    pixels.show();
    colorSensor.clearInterrupt();
  }    
  
}

#endif