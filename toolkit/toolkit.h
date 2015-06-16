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
//#include "UltrasonicTones.h"
#include "colorRGBLed.h"
#include "airDustBox.h"
#include "digitalSandClock.h"
#include "pirNightLed.h"
#include "coinCounter.h"
#include "IRCarReceive.h"
#include "analogMotor.h"
#include "airPiano.h"

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
#define TOTAL_PROGRAM_NUMBER     12


TM1637 tm1637(joint.getPinNumberOUT_PIN1(), joint.getPinNumberOUT_PIN2());
    
extern volatile bool Interrupt_0_flag = false;
extern volatile bool PowerOffFlag = false;

/* -----------Functions ------------ */
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
void batteryManager();

/* Function   : void keyRoutine()
 * Description: deal with key action
 * Parameter  : 
 * Return     : 
 */
void keyRoutine()
{
  cli();
  Interrupt_0_flag = true;
  programConfigLedOn(OFF);
  sei();
}

/* Function   : programConfig(int config)
 * Description: 
 * Parameter  : 
 * Return     :
 */
int programConfig(int downDuration)
{
  int ret = NULL;  
  programConfigLedOn(ON);
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
        //shine once
        programConfigLedOn(ON);
        delay(100);
        programConfigLedOn(OFF);
        
        programNumber++;
        if(programNumber > TOTAL_PROGRAM_NUMBER) programNumber = 1;
        //showNumberTo4DigitDisplay(programNumber);        
      }
      showNumberTo4DigitDisplay(programNumber);
      #if DEBUG
      LOG_VALUE("Configuring program number is ", programNumber);
      #endif
      delay(1000);
    }    
    ret = programNumber;
  }
  programConfigLedOn(OFF);
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
          programConfigLedOn(ON);
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
    analogWrite(joint.getPinNumberLED(), 5);
  }
}

void programConfigLedBlink()
{
  static bool LedStatus = false;
  static long clock = millis();
  if(millis() - clock >= 200)
  {
    clock = millis();
    LedStatus ^= 0x1;
  }
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
  
  TM1637 tm1637(joint.getPinNumberOUT_PIN1(), joint.getPinNumberOUT_PIN2());  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);    
  tm1637.point(false);
  tm1637.clearDisplay();
    
  tens = number / 10;
  units = number % 10;
  if(tens != 0) 
  {
    tm1637.display(2,tens);
  }
  tm1637.display(3,units);  
}

void enablePowerOffFlag()
{
  PowerOffFlag = true;
}

void batteryManager()
{
  static long clock = millis();
  
  if( (millis()-clock) > 500)
  {
    clock = millis();
    //Battery detecting and protecting 
    float battery = joint.BatteryManager();
    //float battery = joint.getBatteryLevel();
    
    #if DEBUG
    LOG_VALUE("battery is ", battery); 
    #endif   
  }
}
#endif








