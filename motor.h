#ifndef __MOTOR_H
#define __MOTOR_H
#include "main.h"
#include "pid.h"

#define  ABS(x)  ((x)>0?(x):-(x))
typedef struct
{
 int16_t Angle;
 int16_t LastAngle;
  
 float Speed;
 int16_t TargetSpeed;
  
 int32_t TotalAngle;
 int32_t TargetAngle;
  
 PID SpeedPID;
 CascadePID AnglePID;
  
}Motor;


//开始计算电机累计角度
void Motor_StartCalcAngle(Motor *motor);
//统计马达的角度和速度
void Motor_Cal(Motor *motor);
//设置马达pwm
void Motor_SetPWM(float PWM1,float PWM2);

#endif


