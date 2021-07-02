#ifndef USER_PID_H
#define USER_PID_H
#include "headfile.h"
#define  	       kP			(float)page_two_data[0][0]
#define 	       kI     (float)page_two_data[0][1]
#define 	       kD     (float)page_two_data[0][2]
extern float		Integration;	//积分量
extern float    Ek[3];//定义误差值
extern float		Temp_Set;					//设定值
extern float 	  Feedback;			//反馈值
extern float		Pwmduty_Out;					//输出的pwm占空比

extern uint8 pwm_flag;
extern float pwm_duty_out;


void ALL_PWM_init(void);
void pwm_out_get(void);




#endif

