/****************************************************************************/	
//	Hardware: Grove - I2C Color Sensor
//  Arduino IDE: Arduino-1.6
//  
//  Author: Isaac Drafton
//	Version: 0.9
//  Refactored version of the library by FrankieChu - www.seeedstudio.com
//	
/******************************************************************************/

#ifndef GROVECOLORSENSOR
#define GROVECOLORSENSOR

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include <Registers.h>

class GroveColorSensor
{
public:

	// Default constructor
	GroveColorSensor(); 
#if 0  
	// Constructor with parameters
	GroveColorSensor(
		  const int& triggerMode
		, const int& interruptSource
		, const int& interruptMode
		, const int& gainAndPrescaler
		, const int& sensorAddress);
#endif
	
	void readRGB();
//	void calculateCoordinate();
	void clearInterrupt();
	
private:	 
#if 0	 
	// Set trigger mode. Including free mode, manually mode, single synchronization mode or so.
	void setTimingReg();
	// Set interrupt source
	void setInterruptSourceReg();
	// Set interrupt mode
	void setInterruptControlReg();
	// Set gain value and pre-scaler value
	void setGain();
	// Start ADC of the colour sensor
	void setEnableADC();
#endif	
  void i2cWriteReg(uint8_t addr, uint8_t reg, uint8_t value);
	// Used for storing the colour data
	int readingdata_[8];
	int green_;
	int red_;
	int blue_;
	int clear_;
	
	int triggerMode_;	
	int interruptSource_;
	int interruptMode_;
	int gainAndPrescaler_;
	int sensorAddress_;
	
};

#endif