#include "motor.h"
#include "tim.h"


//开始计算电机累计角度
void Motor_StartCalcAngle(Motor *motor)
{
	motor->TotalAngle=0;
	motor->LastAngle=motor->Angle;
	motor->TargetAngle=0;
}

//统计马达的角度和速度
void Motor_Cal(Motor *motor)
{
	int32_t dAngle=0;
	if(motor->Angle-motor->LastAngle<-30000)
		dAngle=motor->Angle+(65535-motor->LastAngle);
	else if(motor->Angle-motor->LastAngle>30000)
		dAngle=-motor->LastAngle-(65535-motor->Angle);
	else
		dAngle=motor->Angle-motor->LastAngle;
	//将角度增量加入计数器
	motor->TotalAngle+=dAngle;
	//计算速度
	motor->Speed = (float)dAngle/(4.0*13.0*48.0)*50*60;//rpm   *50*60与定时器频率匹配
	//记录角度
	motor->LastAngle=motor->Angle;
}




//设置马达pwm
void Motor_SetPWM(float PWM1,float PWM2)
{
	if(PWM1>0)
	{
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, PWM1);
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 0);
	}
	else 
	{
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,ABS(PWM1));
	}
	
	if(PWM2>0)
	{
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, PWM2);
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, 0);
	}
	else
	{
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, ABS(PWM2));
	}
}

