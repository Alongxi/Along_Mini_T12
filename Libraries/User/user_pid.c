#include "headfile.h"
#include "user_pid.h"

uint8 pwm_flag = 0;
float pwm_duty_out = 0;

//定义初始值

float		Integration = 0;	//积分量
float   Ek[3];//定义误差值
float		Temp_Set;					//设定值
float 	Feedback = 0;			//反馈值
float		Pwmduty_Out = 0;					//输出的pwm占空比

void ALL_PWM_init(void)
{
    pwm_init(PWM_control, 400, 0);
    pwm_init(BEEP, 4000, 0);
}


float iron_temp_control(float set_temp,float get_temp)//
{
    float pwm_out;//由于
    if(get_temp < set_temp*0.9)
    {
        pwm_out = 10000;
    }
    else
    {
        Ek[0] = set_temp - get_temp;
        Integration += Ek[0];
        if(Integration > 100) Integration = 100;//对积分值限幅
        if(Integration <=100) Integration = -100;
        pwm_out = 100*(kP*Ek[0] + (kI/10)*Integration + (kD/10)*(Ek[1] -Ek[0]));//位置式PID

        //pwm_out = kP*Ek[0] + kI*Ek[1] + kD*Ek[2];
        //(kP * Ek[0]) - (kI * Ek[1]) + (kD * Ek[2])
        Ek[2] = Ek[1];//上上次误差值
        Ek[1] = Ek[0];//将本次误差值赋值到上一次误差
    }
    if(pwm_out > 10000)
    {
        pwm_out = 10000.0;
    }
    else if(pwm_out < 0)
    {
        pwm_out = 0;
    }
    return pwm_out;
}
void pwm_out_get(void)
{
    pwm_duty_out = iron_temp_control(Temp_Set,Iron_temp_now);

    if(pwm_flag == 1)
    {
        pwm_duty(PWM_control, (int)pwm_duty_out);

    }
    else if(pwm_flag == 0)
    {
        pwm_duty(PWM_control, 0);

    }

}