#include "TM1637.h"
#include "GroveJoint.h"


#define TRIGGERED_BY_BUTTON      false
#define TRIGGERED_BY_LIGHTSENSOR true

#define BUTTON_SHORT_PRESS       300  //300ms
#define BUTTON_NORMAL_PRESS      1000 //1000ms
#define BUTTON_LONG_PRESS        3000 //3000ms

Grove_Joint joint;

volatile int CurrentProgramNumber       = 0;
volatile bool Interrupt_0_flag = false;

void setup() 
{      
  #if DEBUG 
  Serial.begin(9600);
  delay(1000);
  LOG("begin....");      
  #endif 

  joint.initHardware();
  attachInterrupt(0, keyRoutine, RISING);  
}

void loop() 
{
  
  /* ------------- 1.Program configuration ----------- */
  if(Interrupt_0_flag)
  {
    int downDuration = joint.checkButtonDown();
    CurrentProgramNumber = programConfig(downDuration); 
    Interrupt_0_flag = false;
  }

  if(NULL != CurrentProgramNumber)
  {
    #if DEBUG
    LOG_VALUE("CurrentProgramNumber is ", CurrentProgramNumber);    
    #endif
    
  }
  /* -------------- 2.Main Routine ---------------- */
  //mainRoutine(CurrentProgramNumber);
  /* ------------- 3. ---------------------------- */
  //delay(1000);
  
}

/* Function   : void keyRoutine()
 * Description: deal with key action
 * Parameter  : 
 * Return     : 
 */
void keyRoutine()
{
  Interrupt_0_flag = true;
}

/* Function   : programConfig(int config)
 * Description: 
 * Parameter  : 
 * Return     :
 */
int programConfig(int downDuration)
{
  int ret = NULL;  
  if(downDuration <= BUTTON_SHORT_PRESS)  //POWER_OFF
  {
    #if DEBUG
    LOG("power off...");
    #endif
    joint.powerOff();
    ret = NULL;
  }
  else if(downDuration <= BUTTON_NORMAL_PRESS)
  {
    ret = NULL;
  }
  else if(downDuration <= BUTTON_LONG_PRESS)  //PROGRAM_CONFIG
  {
    #if DEBUG
    LOG("4 digit display...");
    #endif
    
    TM1637 tm1637(joint.getOUT_PIN1(), joint.getOUT_PIN2());
    tm1637.init();
    tm1637.set(BRIGHT_TYPICAL);    
    tm1637.point(false);
    tm1637.clearDisplay();
    
    tm1637.display(2,0);    
    tm1637.display(3,0);

    int programNumber = 0;
    int tens = 0;
    int units = 0;
    
    while( !(HIGH==digitalRead(joint.getBUTTON())) ) 
    {
#if TRIGGERED_BY_BUTTON      
      if( joint.checkButtonDown() )
      {
#elif TRIGGERED_BY_LIGHTSENSOR
      if(joint.isLightSensorTriggered())
      {
#endif
        programNumber++;
        if(16 < programNumber) programNumber = 1;
        tens = programNumber / 10;
        units = programNumber % 10;                       
        tm1637.display(2,tens);
        tm1637.display(3,units);
      }
      LOG("Configuring program number");
      delay(1000);
    }
    
    ret = programNumber;    
  }
  
  return ret;
  
}











