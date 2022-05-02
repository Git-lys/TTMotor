#include "motor.h"
#include "tim.h"


//��ʼ�������ۼƽǶ�
void Motor_StartCalcAngle(Motor *motor)
{
	motor->TotalAngle=0;
	motor->LastAngle=motor->Angle;
	motor->TargetAngle=0;
}

//ͳ�����ĽǶȺ��ٶ�
void Motor_Cal(Motor *motor)
{
	int32_t dAngle=0;
	if(motor->Angle-motor->LastAngle<-30000)
		dAngle=motor->Angle+(65535-motor->LastAngle);
	else if(motor->Angle-motor->LastAngle>30000)
		dAngle=-motor->LastAngle-(65535-motor->Angle);
	else
		dAngle=motor->Angle-motor->LastAngle;
	//���Ƕ��������������
	motor->TotalAngle+=dAngle;
	//�����ٶ�
	motor->Speed = (float)dAngle/(4.0*13.0*48.0)*50*60;//rpm   *50*60�붨ʱ��Ƶ��ƥ��
	//��¼�Ƕ�
	motor->LastAngle=motor->Angle;
}




//�������pwm
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

