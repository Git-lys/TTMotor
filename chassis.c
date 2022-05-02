#include "chassis.h"
#include "tim.h"

Chassis chassis;

/***************内部函数声明****************/
void Chassis_PIDInit(void);
/******************初始化*****************/
void Chassis_init()
{
  HAL_TIM_Base_Start_IT(&htim6);                  
	HAL_TIM_Base_Start_IT(&htim7);
  
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);			//电机pwm
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);

	
	HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_ALL);	//电机编码器
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
  
   Chassis_PIDInit();
}
/***************内部函数********************/
//PID初始化
void Chassis_PIDInit()
{
	PID_Init(&chassis.motor[0].SpeedPID,200,0.005,0,10000,10000);
	PID_Init(&chassis.motor[1].SpeedPID,200,0.006,1,10000,10000);
	
	PID_Init(&chassis.motor[0].AnglePID.inner,200,0.005,0,10000,10000);
	PID_Init(&chassis.motor[1].AnglePID.inner,200,0.006,1,10000,10000);
                   
	PID_Init(&chassis.motor[0].AnglePID.outer,0.2,0,0.5,40,40);
	PID_Init(&chassis.motor[1].AnglePID.outer,0.2,0,0.5,40,40);
}	


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef*htim)
{
	if(htim==&htim6)
	{
    chassis.motor[0].Angle=__HAL_TIM_GET_COUNTER(&htim1);
    chassis.motor[1].Angle=__HAL_TIM_GET_COUNTER(&htim2);
    Motor_Cal(&chassis.motor[0]);
    Motor_Cal(&chassis.motor[1]);
	}
  
  if(htim==&htim7)
  {
    for(uint8_t i=0;i<2;i++)
    {
      PID_SingleCalc(&chassis.motor[i].SpeedPID,chassis.motor[i].TargetSpeed,chassis.motor[i].Speed);
    }
    Motor_SetPWM(chassis.motor[0].SpeedPID.output,chassis.motor[1].SpeedPID.output);
    
//       for(uint8_t i=0;i<2;i++)
//    {
//       PID_CascadeCalc(&chassis.motor[i].AnglePID,chassis.motor[i].TargetAngle,chassis.motor[i].TotalAngle,chassis.motor[i].Speed);
//    }
//    Motor_SetPWM(chassis.motor[0].AnglePID.output,chassis.motor[1].AnglePID.output);
    
  }
}
