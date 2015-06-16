#ifndef _COMMON_H_
#define _COMMON_H_

#include <Arduino.h>
#include "GroveJoint.h"

extern volatile bool toUseTones;
extern volatile bool toUseInfrared;
extern Grove_Joint joint;
extern volatile int CurrentProgramNumber;


enum PROGRAM_INDEX : int{
   LOGICDIRECT = 1,
   LOGICAND,
   LOGICOR,
   LOGICNOT,
   ULTRASONICTONES,
   COLORRGBLED,
   AIR_DUST_BOX,
   DIGITAL_SAND_CLOCK,
   PIR_NIGHT_LED,
   COIN_COUNTER,
   IR_CAR_RECEIVE,
   ANALOG_MOTOR
};

#endif