#ifndef _ULTRASONICTONES_H_
#define _ULTRASONICTONES_H_

#include "Ultrasonic.h"
#include "DigitalTones.h"
#include "common.h"

#define DEFAULT_DISTANCE  5
#define DISTANCE1         DEFAULT_DISTANCE * 0
#define DISTANCE2         DEFAULT_DISTANCE * 1
#define DISTANCE3         DEFAULT_DISTANCE * 2
#define DISTANCE4         DEFAULT_DISTANCE * 3
#define DISTANCE5         DEFAULT_DISTANCE * 4
#define DISTANCE6         DEFAULT_DISTANCE * 5
#define DISTANCE7         DEFAULT_DISTANCE * 6
#define DISTANCE8         DEFAULT_DISTANCE * 7
#define DISTANCE9         DEFAULT_DISTANCE * 8

void Gamut_Play(unsigned char data);

bool playBack  = false;
int noteDuration   = 200;
  
void ultrasonicTones()
{  
  unsigned char airGamutValue = 0;
  unsigned int ultrasonicAirDistance = 0;

  Ultrasonic ultrasonicAir(A5);    
  ultrasonicAirDistance = ultrasonicAir.MeasureInCentimeters(); 
  
  if     ((ultrasonicAirDistance>DISTANCE1)&&(ultrasonicAirDistance<=DISTANCE2))airGamutValue = 1, playBack = true;
  else if((ultrasonicAirDistance>DISTANCE2)&&(ultrasonicAirDistance<=DISTANCE3))airGamutValue = 2, playBack = true;
  else if((ultrasonicAirDistance>DISTANCE3)&&(ultrasonicAirDistance<=DISTANCE4))airGamutValue = 3, playBack = true;
  else if((ultrasonicAirDistance>DISTANCE4)&&(ultrasonicAirDistance<=DISTANCE5))airGamutValue = 4, playBack = true;
  else if((ultrasonicAirDistance>DISTANCE5)&&(ultrasonicAirDistance<=DISTANCE6))airGamutValue = 5, playBack = true;
  else if((ultrasonicAirDistance>DISTANCE6)&&(ultrasonicAirDistance<=DISTANCE7))airGamutValue = 6, playBack = true;
  else if((ultrasonicAirDistance>DISTANCE7)&&(ultrasonicAirDistance<=DISTANCE8))airGamutValue = 7, playBack = true;
  else if((ultrasonicAirDistance>DISTANCE8)&&(ultrasonicAirDistance<=DISTANCE9))airGamutValue = 8, playBack = true;
  else airGamutValue = 0, playBack = false; 
 
  Gamut_Play(airGamutValue);
}

void Gamut_Play(unsigned char data)
{
  if(playBack)
  {
    DigitalTones dTone(3);
    switch(data)
    {      
      case 1:
        dTone.toneManual(dTone.tones[0], noteDuration);//Do(523Hz)NOTE_C5
        break;        
      case 2:
        dTone.toneManual(dTone.tones[1], noteDuration);//Re(587Hz)NOTE_D5
        break;        
      case 3:
        dTone.toneManual(dTone.tones[2], noteDuration);//Mi(659Hz)NOTE_E5
        break;        
      case 4:
        dTone.toneManual(dTone.tones[3], noteDuration);//Fa(698Hz)NOTE_F5
        break;        
      case 5:
        dTone.toneManual(dTone.tones[4], noteDuration);//So(784Hz)NOTE_G5
        break;        
      case 6:
        dTone.toneManual(dTone.tones[5], noteDuration);//La(880Hz)NOTE_A5
        break;       
      case 7:
        dTone.toneManual(dTone.tones[6], noteDuration);//Si(988Hz)NOTE_B5
        break;       
      case 8:
        dTone.toneManual(dTone.tones[7], noteDuration);//Do(1047Hz)NOTE_C6
        break;             
      default:
        dTone.toneManual(0,10);
        break;         
    }
  }
}

#endif
