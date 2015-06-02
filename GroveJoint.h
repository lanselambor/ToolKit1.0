#ifndef _GROVEJOINT_H_
#define _GROVEJOINT_H_

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
class Grove_Joint
{
  public:
    //Attributions
    int AmbientLight = 0;
    
    
    Grove_Joint();
    
    /* Function: void initHardware()
     * Description: 
     * Parameter: 
     * Return:
     */
    void initHardware();
    
    /* Function   : int initLightSensor(void)
     * Description: 
     * Parameter  : 
     * Return     : Ambient light value
     */
    int initLightSensor(void);
    
    /* Function   : int isLightSensorTriggered(void)
     * Description: 
     * Parameter  : 
     * Return     : 
     */
    bool isLightSensorTriggered(void);
    
    /* Function   : programConfig(int config)
     * Description: 
     * Parameter  : 
     * Return     : duration of button press down (Ms)
     */
    uint16_t checkButtonDown();    

    
    /* Function   : powerOff()
     * Description: software power off, 
     * Parameter  :  
     * Return     :
     */
    void powerOff();

    /* Function   : softwareReset()
     * Description: board reset by software, SP point to zero address
     * Parameter  : 
     * Return     :
     */
    void softwareReset();
    
    /* Function   : 
     * Description: return pins on joint board
     * Parameter  : 
     * Return     :
     */
     
    int getBUTTON(void);  
    int getLIGHT_SENSOR(void);
    int getCHRG_LED(void);
    int getPWR_HOLD(void);
    int getPWR(void);
    int getKEY(void);
    int getLED(void);
    int getOUT_PIN1(void);
    int getOUT_PIN2(void);
    int getIN_PIN1(void);
    int getIN_PIN2(void);
#if 0    
    void settingStrongLightTrigger(bool mode = false);
    bool isStrongLightTrigger();
#endif    
  private:
    //hardware IO definition                              
    int BUTTON       = 2;
    int LIGHT_SENSOR = A0;
    int CHRG_LED     = A3;  //low-level work
    int PWR_HOLD     = A1;  
    int PWR          = 6;   //low-level work
    int KEY          = 2;
    int LED          = 10;  
    int OUT_PIN1     = 3;   //normal output pin
    int OUT_PIN2     = 5;
    int IN_PIN1      = A5;  //normal input pin
    int IN_PIN2      = A4;
    
    bool STRONG_LIGHT_TRIGGER = false;
};

#endif

