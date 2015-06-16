#ifndef COINCOUNTER_H
#define COINCOUNTER_H

#include "TM1637.h"
#include <EEPROM.h>

uint16_t coinNumber = 0;
TM1637 coinCounterDisplay(3, 5);  //clk = 3, dio = 5;

void zeroCoinNumberOnEeprom();
void writeCoinNumberToEeprom(uint16_t num);
uint16_t readCoinNumberFromEeprom(void);
void coinCounterInit();
void displayCoinNumber(uint16_t num);

void coinCounter()
{
  static bool initFlag = false;
  int lineFiner = A5;  
  
  if(!initFlag)
  {
    initFlag = true;
    coinCounterInit();
  }

  coinNumber = readCoinNumberFromEeprom();
  
  if(digitalRead(lineFiner) == LOW)
  {       
    long begin = 0;
    
    begin = millis();      
    coinNumber++;
    writeCoinNumberToEeprom(coinNumber);
    displayCoinNumber(coinNumber);
    
    while(digitalRead(lineFiner) == LOW)
    {
      if(millis() - begin >= 3000)
      {
        coinNumber = 0;
        begin = millis();
        zeroCoinNumberOnEeprom();        
        displayCoinNumber(coinNumber);
      }
      //delay(10);
    }
    displayCoinNumber(coinNumber);
  }  
  writeCoinNumberToEeprom(coinNumber);
  displayCoinNumber(coinNumber);
  //delay(10);
}

void displayCoinNumber(uint16_t num)
{    
  uint8_t thousand = num/1000;
  uint8_t hundred = num%1000/100;
  uint8_t tens = num%100/10;
  uint8_t unit = num%10;
   
  coinCounterDisplay.clearDisplay(); 
  if(thousand != 0)
  {    
    coinCounterDisplay.display(0,thousand);
  }
  if((thousand != 0) || (hundred != 0))                
  {
    coinCounterDisplay.display(1,hundred);
  }
  if((thousand != 0) || (hundred != 0) || (tens != 0)) 
  {
    coinCounterDisplay.display(2,tens);
  }
  coinCounterDisplay.display(3,unit);  
}

void coinCounterInit()
{
  int lineFiner = A5;  
  pinMode(lineFiner, INPUT);
  digitalWrite(lineFiner, HIGH);
  
  coinCounterDisplay.init();
  coinCounterDisplay.set(BRIGHT_TYPICAL);  
  coinCounterDisplay.clearDisplay();
  coinCounterDisplay.display(3,0);
}
uint16_t readCoinNumberFromEeprom(void)
{
  return (uint16_t)( EEPROM.read(1) + EEPROM.read(2) * 256 );
}

void writeCoinNumberToEeprom(uint16_t num)
{
  EEPROM.write(1, num%256);
  EEPROM.write(2, num/256);  
}

void zeroCoinNumberOnEeprom()
{
  EEPROM.write(1, 0);
  EEPROM.write(2, 0);  
}
#endif


