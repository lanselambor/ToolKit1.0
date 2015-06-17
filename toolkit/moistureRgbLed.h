#ifndef MOISTURERGBLED_H
#define MOISTURERGBLED_H

#include "Adafruit_NeoPixel.h"

class MoistureRgbLed
{
  public:
    void run()
    {
      static bool initOK = false;
      if(!initOK)
      {
        initOK = true;
        MoistureRgbLedInit();
      }
      
      uint16_t val = analogRead(moisturePin);
      uint8_t phase =  map(val, 0, 700, 1, 80);
      showColor(phase);
    }
    
  private:
    const int moisturePin = A5;
    const int ledPin      = 3;
    const int ledNum      = 1; 
    const int lightness   = 2;    
    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(ledNum, ledPin, NEO_GRB + NEO_KHZ800);
    
    void MoistureRgbLedInit()
    {
      pinMode(ledPin, OUTPUT);
      pixels.begin();
    }
    
    void showColor(uint8_t phase)
    {
      float h = phase / 256.0;
      float s = 1.0;
      float v = 1.0;

      int i_ = floor(h * 6);
      float f = h * 6 - i_;
      float p = v * (1 - s);
      float q = v * (1 - f * s);
      float t = v * (1 - (1 - f) * s);
      float r = 0, g = 0, b = 0;

      switch(i_ % 6)
      {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
      }  

      uint8_t  rgb_color[3];
      rgb_color[0] = r * 255;
      rgb_color[1] = g * 255;  
      rgb_color[2] = b * 255;  

      rgb_color[0] = rgb_color[0] >>lightness;
      rgb_color[1] = rgb_color[1] >>lightness;  
      rgb_color[2] = rgb_color[2] >>lightness;  

      for(int i=0;i<ledNum;i++)
      {        
        pixels.setPixelColor(i, pixels.Color(rgb_color[0],rgb_color[1],rgb_color[2]));        
        pixels.show();
      }
    }
};


#endif