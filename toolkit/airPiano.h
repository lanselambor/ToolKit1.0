#ifndef AIRPIANO_H
#define AIRPIANO_H

#include "Tone.h"
#include "Ultrasonic.h"

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

int notes[] = { NOTE_C5,
                NOTE_D5,
                NOTE_E5,
                NOTE_F5,
                NOTE_G5,
                NOTE_A5,
                NOTE_B5,
                NOTE_C6 };
                
Tone notePlayer; 

void airPianoInit();

void airPiano()
{
  static bool initOK = false;
  const int duration = 50;
  if(!initOK)
  {
    initOK = true;
    airPianoInit();
  }
  
  static bool playBack  = false;
  unsigned char airGamutValue = 0;
  unsigned int ultrasonicAirDistance = 0;

  Ultrasonic ultrasonicAir(A5);    
  ultrasonicAirDistance = ultrasonicAir.MeasureInCentimeters(); 
  
  if     ((ultrasonicAirDistance>=DISTANCE1)&&(ultrasonicAirDistance<DISTANCE2))airGamutValue = 1;
  else if((ultrasonicAirDistance>=DISTANCE2)&&(ultrasonicAirDistance<DISTANCE3))airGamutValue = 2;
  else if((ultrasonicAirDistance>=DISTANCE3)&&(ultrasonicAirDistance<DISTANCE4))airGamutValue = 3;
  else if((ultrasonicAirDistance>=DISTANCE4)&&(ultrasonicAirDistance<DISTANCE5))airGamutValue = 4;
  else if((ultrasonicAirDistance>=DISTANCE5)&&(ultrasonicAirDistance<DISTANCE6))airGamutValue = 5;
  else if((ultrasonicAirDistance>=DISTANCE6)&&(ultrasonicAirDistance<DISTANCE7))airGamutValue = 6;
  else if((ultrasonicAirDistance>=DISTANCE7)&&(ultrasonicAirDistance<DISTANCE8))airGamutValue = 7;
  else if((ultrasonicAirDistance>=DISTANCE8)&&(ultrasonicAirDistance<DISTANCE9))airGamutValue = 8;
  else airGamutValue = 0;
  
  if(airGamutValue > 0)  
  {
    switch(airGamutValue)
    {      
      case 1: 
        notePlayer.play(notes[0], 50);//Do(523Hz)NOTE_C5
        break;        
      case 2:
        notePlayer.play(notes[1], 50);//Re(587Hz)NOTE_D5
        break;        
      case 3:
        notePlayer.play(notes[2], 50);//Mi(659Hz)NOTE_E5
        break;        
      case 4:
        notePlayer.play(notes[3], 50);//Fa(698Hz)NOTE_F5
        break;        
      case 5:
        notePlayer.play(notes[4], 50);//So(784Hz)NOTE_G5
        break;        
      case 6:
        notePlayer.play(notes[5], 50);//La(880Hz)NOTE_A5
        break;       
      case 7:
        notePlayer.play(notes[6], 50);//Si(988Hz)NOTE_B5
        break;       
      case 8:
        notePlayer.play(notes[7], 50);//Do(1047Hz)NOTE_C6
        break;             
      default:
        break;         
    }
    delay(30);
  }  
}

void airPianoInit()
{
  notePlayer.begin(3);
}
#endif