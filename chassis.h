#ifndef __CHASSIS_H
#define __CHASSIS_H
#include "motor.h"

typedef struct
{
  Motor motor[2];
  
}Chassis;



void Chassis_init(void);

#endif


