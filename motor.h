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


//��ʼ�������ۼƽǶ�
void Motor_StartCalcAngle(Motor *motor);
//ͳ�����ĽǶȺ��ٶ�
void Motor_Cal(Motor *motor);
//�������pwm
void Motor_SetPWM(float PWM1,float PWM2);

#endif


