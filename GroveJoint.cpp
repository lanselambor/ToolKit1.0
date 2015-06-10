#include <Arduino.h>
#include "GroveJoint.h"


Grove_Joint::Grove_Joint()
{
  
}

/* Function: void initHardware()
 * Description: 
 * Parameter: 
 * Return:
 */
void Grove_Joint::initHardware()
{
  //pin initial
  pinMode(CHRG_LED, OUTPUT);     
  pinMode(PWR, OUTPUT);  
  pinMode(LED , OUTPUT);
  pinMode(KEY, INPUT);
  pinMode(PWR_HOLD, OUTPUT);   
  pinMode(LIGHT_SENSOR, INPUT);
  pinMode(BATTERY_ADC, INPUT);
  
  digitalWrite(PWR, LOW);      //power led  
  digitalWrite(CHRG_LED, HIGH); 
  digitalWrite(PWR_HOLD, LOW);  //hold the power so the button can be used    
  
  AmbientLight = initLightSensor();

  
  //starting shining   
  analogWrite(LED, 5);
  delay(500);
  analogWrite(LED, 0);
  delay(500);
  analogWrite(LED, 5);
  delay(500);
  analogWrite(LED, 0); 
  
}

/* Function   : int initLightSensor(void)
 * Description: 
 * Parameter  : 
 * Return     : Ambient light value
 */
int Grove_Joint::initLightSensor(void)
{
  long tmp = 0;
  for(int i=0;i<100;i++){
    tmp += analogRead(LIGHT_SENSOR);
  } 
  tmp /= 100;
  #if DEBUG
  LOG_VALUE(" Read Light Sensor: ", tmp);  
  #endif
  
  return tmp;
} 

/* Function   : int isLightSensorTriggered(void)
 * Description: 
 * Parameter  : 
 * Return     : 
 */
bool Grove_Joint::isLightSensorTriggered(void)
{
  long ambient_light = 0;
  for(int i=0;i<20;i++){
    ambient_light += analogRead(LIGHT_SENSOR);
    delayMicroseconds(10);
  } 
  ambient_light /= 20; 
  
  if(STRONG_LIGHT_TRIGGER) { //program configured by strong light sensor        
    if( (AmbientLight*2) < ambient_light ) {
        return true;
    }
  }    
  else {
    if( (AmbientLight/2) > ambient_light ) {
      return true;
    }
  }
  
  return false;
}

/* Function   : programConfig(int config)
 * Description: 
 * Parameter  :  
 * Return     : duration of button press down (Ms)
 */
uint16_t Grove_Joint::checkButtonDown()
{  
  uint16_t ret = 0;
  uint16_t blockCountermillis = 0;
  uint16_t time_duration = 0;
  
  if((HIGH==digitalRead(BUTTON)))
  {
    delay(5);
    if((HIGH==digitalRead(BUTTON)))
    {      
      while((HIGH==digitalRead(BUTTON)))
      {
        delayMicroseconds(998);
        blockCountermillis++;        
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


/* Function   : powerOff()
 * Description: software power off, 
 * Parameter  :  
 * Return     :
 */
void Grove_Joint::powerOff()
{
  detachInterrupt(0);  
  digitalWrite(PWR_HOLD, HIGH);	      
  pinMode(BUTTON, OUTPUT);    
  digitalWrite(BUTTON, LOW);    
  delay(20);
  digitalWrite(BUTTON, HIGH);  
  pinMode(BUTTON, INPUT);    

}

/* Function   : softwareReset()
 * Description: board reset by software, SP point to zero address
 * Parameter  : 
 * Return     :
 */
void Grove_Joint::softwareReset() 
{
  asm volatile ("jmp 0");
}

/* Function   : 
 * Description: return pins on joint board
 * Parameter  : 
 * Return     :
 */

int Grove_Joint::getPinNumberBUTTON(void)
{
  return BUTTON;
}

int Grove_Joint::getPinNumberLIGHT_SENSOR(void)
{
  return LIGHT_SENSOR;
}

int Grove_Joint::getPinNumberCHRG_LED(void)
{
  return CHRG_LED;
}

int Grove_Joint::getPinNumberPWR_HOLD(void)
{
  return PWR_HOLD;
}

int Grove_Joint::getPinNumberPWR(void)
{
  return PWR;
}

int Grove_Joint::getPinNumberKEY(void)
{
  return KEY;
}

int Grove_Joint::getPinNumberLED(void)
{
  return LED;
}

int Grove_Joint::getPinNumberOUT_PIN1(void)
{
  return OUT_PIN1;
}

int Grove_Joint::getPinNumberOUT_PIN2(void)
{
  return OUT_PIN2;
}

int Grove_Joint::getPinNumberIN_PIN1(void)
{
  return IN_PIN1;
}

int Grove_Joint::getPinNumberIN_PIN2(void)
{
  return IN_PIN2;
}

int Grove_Joint::getPinNumberBATTERY_ADC(void)
{
  return BATTERY_ADC;
}

int Grove_Joint::getPinNumberBATTERY_LED(void)
{
  return BATTERY_LED;
}

int Grove_Joint::getBattery_value(void)
{
  return analogRead(BATTERY_ADC);
}

void Grove_Joint::settingStrongLightTrigger(bool mode)
{
  STRONG_LIGHT_TRIGGER = mode;  
}

bool Grove_Joint::isStrongLightTrigger()
{
  return STRONG_LIGHT_TRIGGER;
}
/* --------------end of file ------------------ */
