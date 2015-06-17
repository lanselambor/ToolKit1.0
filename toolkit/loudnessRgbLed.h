#ifndef LOUDNESSRGBLED_H
#define LOUDNESSRGBLED_H


#include <Adafruit_NeoPixel.h>



#define MOTOR_SPEED 5
#define THRESHOLD 30

#define NUMPIXELS      20
#define LIGHT_PIN      3
#define PIN            LIGHT_PIN

class LoudnessRgbLed
{
  public:
    void run() 
    {
      sound_value = analogRead(sound_pin);
      if(40 < (sound_value - last_value))
      {
        action_rgbled_on ();    
        action_rgbled_off();
      }
      last_value = sound_value; 
    }  
  private:
    const int sound_pin      = A5;
    const int ledPin         = 3;
    volatile int sound_value = 0;
    volatile int last_value  = 0;
    const int ledNum         = 20;
    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(ledNum, ledPin, NEO_GRB + NEO_KHZ800);
    
    void init() 
    {   
      pinMode(sound_pin, INPUT);      
    }

    void action_rgbled_on()
    {
      //set different color data ,so that each time it display different color
      int i = 0;
      int j = 0;
      uint32_t time = millis();       
      uint8_t phase = (time >> 4) ;                          
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
                    
      uint8_t  rgb_color[3] ;
      rgb_color[0] = r * 255;
      rgb_color[1] = g * 255;  
      rgb_color[2] = b * 255;  
      
      rgb_color[0] = rgb_color[0] >>LIGHT_PIN;
      rgb_color[1] = rgb_color[1] >>LIGHT_PIN;  
      rgb_color[2] = rgb_color[2] >>LIGHT_PIN;    
      
      for(int move_num = 0; move_num<NUMPIXELS+1; move_num++)     //"NUMPIXELS+1"    do not forget  +1
      {
        for(j = 0; j < move_num; j++)
        {
                pixels.setPixelColor(j, pixels.Color(0,0,0)); // Moderately bright green color.
                pixels.show(); // This sends the updated pixel color to the hardware.    
        }                        
        for(i = move_num; i<NUMPIXELS; i++)
                    {        
                pixels.setPixelColor(i, pixels.Color(rgb_color[0],rgb_color[1],rgb_color[2])); // Moderately bright green color.
                pixels.show(); // This sends the updated pixel color to the hardware.          
        }                    
        delay(1);
      }     
    }

    void action_rgbled_off ()
    {
            for(int i=0;i<NUMPIXELS;i++)
      {
                    // Moderately bright green color.
              pixels.setPixelColor(i, pixels.Color(0,0,0)); 
                    // This sends the updated pixel color to the hardware.  
              pixels.show();   
            }  
    }    
};

#endif