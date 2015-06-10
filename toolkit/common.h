#ifndef _COMMON_H_
#define _COMMON_H_

extern volatile int CurrentProgramNumber;

enum PROGRAM_INDEX : int{
   LOGICDIRECT = 1,
   LOGICAND,
   LOGICOR,
   LOGICNOT,
   ULTRASONICTONES,
   COLORRGBLED
};


#endif