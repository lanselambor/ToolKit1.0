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
  delay(1000);
}

void loop() 
{      
    
  /* ------------- 1.Battery management ----------- */
  batteryManager();
  /* ------------- 2.Program configuration ----------- */  
  CurrentProgramNumber = getCurrentProgramNumber();
  
  if( (NULL != CurrentProgramNumber) && !PowerOffFlag )
  {    
    programConfigLedBlink();    
    #if DEBUG
    //LOG_VALUE("CurrentProgramNumber is ", CurrentProgramNumber);    
    #endif
    
   
    /* -------------- 3.Main process ---------------- */
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
        toUseTones = true;
        toUseInfrared = false;        
        airPiano();
        break;
      case 6:        
        colorRGBLed();        
        break;
      case 7:
        airDustBox();
        break;
      case 8:        
        digitalSandClock.run();
        break;
      case 9:
        pirNightLed();
        break;
      case 10:
        coinCounter();
        break;
      case 11:     
        toUseTones = false;
        toUseInfrared = true;
        IRCarReceive();
        break;
      case 12:
        analogMotor();      
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









