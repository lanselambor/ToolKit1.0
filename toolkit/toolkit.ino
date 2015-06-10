#include "TM1637.h"
#include "GroveJoint.h"
#include <TimerOne.h>
#include <EEPROM.h>
#include <Wire.h>
#include "toolkit.h"


void setup() 
{      
  joint.initHardware();
  
  #if DEBUG 
  Serial.begin(9600);
  LOG("begin....");      
  #endif
  
  //initialize CurrentProgramNumber
  CurrentProgramNumber = readProgramNumberFromEeprom();
  showNumberTo4DigitDisplay(CurrentProgramNumber);
  
  attachInterrupt(0, keyRoutine, RISING);   
}

void loop() 
{
  /* ------------- 2.Program configuration ----------- */  
  CurrentProgramNumber = getCurrentProgramNumber();
  
  if( (NULL != CurrentProgramNumber) && !PowerOffFlag )
  {    
    programConfigLedBlink();
    
    #if DEBUG
    LOG_VALUE("CurrentProgramNumber is ", CurrentProgramNumber);    
    #endif
    /* -------------- 3.battery check ------------ */
    int battery = joint.getBattery_value();
    #if DEBUG
    LOG_VALUE("battery is ", battery);    
    #endif    
    /* -------------- 4.Main process ---------------- */
    switch(CurrentProgramNumber)
    {
      case 1:
        logicDirect();
        break;
      case 2:
        logicAnd();
        break;
      case 3:
        logicOr();
        break;
      case 4:
        logicNot();
        break;
      case 5:
        ultrasonicTones();
        break;
      case 6:
        colorRGBLed();
        break; 
      default:
        break;
    }    
  }
  else
  {
    programConfigLedOn(0);
  }
}









