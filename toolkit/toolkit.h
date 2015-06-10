#ifndef _TOOLKIT_H_
#define _TOOLKIT_H_

#include "TM1637.h"
#include "GroveJoint.h"
#include <TimerOne.h>
#include <EEPROM.h>
#include <Wire.h>

#include "common.h"
#include "logicDirect.h"
#include "logicAnd.h"
#include "logicOr.h"
#include "logicNot.h"
#include "UltrasonicTones.h"
#include "colorRGBLed.h"

#define DEBUG          1
#define LOG(message)   Serial.print("[ ");       \
                       Serial.print(millis());   \
                       Serial.print(" ms] ");    \
                       Serial.println(message);                                    

#define LOG_VALUE(message, value)   Serial.print("[ ");       \
                                    Serial.print(millis());   \
                                    Serial.print(" ms] ");    \
                                    Serial.print(message);    \
                                    Serial.println(value);
                                    
#define TRIGGERED_BY_BUTTON      false
#define TRIGGERED_BY_LIGHTSENSOR true

#define BUTTON_SHORT_PRESS       300  //300ms
#define BUTTON_NORMAL_PRESS      1000 //1000ms
#define BUTTON_LONG_PRESS        3000 //3000ms
#define EXCEPTION_PROGRAM_NUMBER 99

Grove_Joint joint;
TM1637 tm1637(joint.getPinNumberOUT_PIN1(), joint.getPinNumberOUT_PIN2());
    
extern volatile bool Interrupt_0_flag = false;
extern volatile bool PowerOffFlag = false;

/* -----------Function Declare------------ */
void loopEnable(int programNumber);
int programConfig(int downDuration);
uint16_t checkJointButtonDown();
int getCurrentProgramNumber();
void CurrentProgramNumberZero();
void programConfigLedOn(int status);
void programConfigLedBlink();
void saveProgramNumberToEeprom(int number);
int readProgramNumberFromEeprom();
void showNumberTo4DigitDisplay(int number);
void enablePowerOffFlag();

/* Function   : void keyRoutine()
 * Description: deal with key action
 * Parameter  : 
 * Return     : 
 */
void keyRoutine()
{
  Interrupt_0_flag = true;
  programConfigLedOn(0);
}

/* Function   : programConfig(int config)
 * Description: 
 * Parameter  : 
 * Return     :
 */
int programConfig(int downDuration)
{
  int ret = NULL;  
  programConfigLedOn(1);
  if(downDuration <= BUTTON_SHORT_PRESS)  //POWER_OFF
  {
    #if DEBUG
    LOG("power off...");
    #endif
    joint.powerOff();
    enablePowerOffFlag();
    ret = EXCEPTION_PROGRAM_NUMBER;
  }
  else if(downDuration <= BUTTON_NORMAL_PRESS)
  {
    ret = EXCEPTION_PROGRAM_NUMBER;
  }
  else if(downDuration <= BUTTON_LONG_PRESS)  //PROGRAM_CONFIG
  {
    #if DEBUG
    LOG("4 digit display...");
    #endif    
    int programNumber = readProgramNumberFromEeprom();
    showNumberTo4DigitDisplay(programNumber);
    
    while( !(HIGH==digitalRead(joint.getPinNumberBUTTON())) ) 
    {
#if TRIGGERED_BY_BUTTON      
      if( joint.checkButtonDown() )
      {
#elif TRIGGERED_BY_LIGHTSENSOR
      if(joint.isLightSensorTriggered())
      {
#endif
        programNumber++;
        if(programNumber > 16) programNumber = 0;
        showNumberTo4DigitDisplay(programNumber);        
      }
      LOG_VALUE("Configuring program number is ", programNumber);
      delay(1000);
    }    
    ret = programNumber;
  }
  programConfigLedOn(0);
  return ret;
  
}

uint16_t checkJointButtonDown()
{  
  uint16_t ret = 0;
  uint16_t blockCountermillis = 0;
  uint16_t time_duration = 0;
  
  if((HIGH==digitalRead(joint.getPinNumberBUTTON()))) 
  {
    delay(5);
    if((HIGH==digitalRead(joint.getPinNumberBUTTON())))
    {      
      while((HIGH==digitalRead(joint.getPinNumberBUTTON())))
      {
        delayMicroseconds(998);
        blockCountermillis++; 
        if(blockCountermillis > BUTTON_NORMAL_PRESS)
        {
          programConfigLedOn(1);
        }
      }
      time_duration = blockCountermillis;
      ret = time_duration;
      
      #if DEBUG        
        LOG_VALUE("time_duration: ", time_duration);
      #endif      
    }
  }
  
  return ret;
}

int getCurrentProgramNumber()
{
  static int ret = readProgramNumberFromEeprom();  
  if(Interrupt_0_flag)
  {    
    #if DEBUG
    LOG("Begin Program configuration...");    
    #endif    
    int downDuration = checkJointButtonDown();
    int tmp = programConfig(downDuration); 
    if(tmp != EXCEPTION_PROGRAM_NUMBER)
    {
      ret = tmp;
    }
    
    //store programNumber to EEPROM
    saveProgramNumberToEeprom(ret);
    Interrupt_0_flag = false;
  }  
  
  return ret;
}

void CurrentProgramNumberZero()
{
  CurrentProgramNumber = NULL;
  saveProgramNumberToEeprom(CurrentProgramNumber);
}

void programConfigLedOn(int status)
{
  pinMode(joint.getPinNumberLED(), OUTPUT);
  if(0 == status){
    analogWrite(joint.getPinNumberLED(), 0);
  }
  else{
    analogWrite(joint.getPinNumberLED(), 10);
  }
}

void programConfigLedBlink()
{
  static int LedStatus = 1;
  LedStatus = !LedStatus;
  programConfigLedOn(LedStatus);
}

void saveProgramNumberToEeprom(int number)
{
  EEPROM.write(0, number);
}

int readProgramNumberFromEeprom()
{
  return EEPROM.read(0);
}

void showNumberTo4DigitDisplay(int number)
{
  int tens = 0;
  int units = 0;  
  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);    
  tm1637.point(false);
  tm1637.clearDisplay();
    
  tens = number / 10;
  units = number % 10;                       
  tm1637.display(2,tens);
  tm1637.display(3,units);  
}

void enablePowerOffFlag()
{
  PowerOffFlag = true;
}
#endif








