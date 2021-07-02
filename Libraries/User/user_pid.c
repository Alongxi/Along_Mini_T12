#include "headfile.h"
#include "user_pid.h"

uint8 pwm_flag = 0;
float pwm_duty_out = 0;

//�����ʼֵ

float		Integration = 0;	//������
float   Ek[3];//�������ֵ
float		Temp_Set;					//�趨ֵ
float 	Feedback = 0;			//����ֵ
float		Pwmduty_Out = 0;					//�����pwmռ�ձ�

void ALL_PWM_init(void)
{
    pwm_init(PWM_control, 400, 0);
    pwm_init(BEEP, 4000, 0);
}


float iron_temp_control(float set_temp,float get_temp)//
{
    float pwm_out;//����
    if(get_temp < set_temp*0.9)
    {
        pwm_out = 10000;
    }
    else
    {
        Ek[0] = set_temp - get_temp;
        Integration += Ek[0];
        if(Integration > 100) Integration = 100;//�Ի���ֵ�޷�
        if(Integration <=100) Integration = -100;
        pwm_out = 100*(kP*Ek[0] + (kI/10)*Integration + (kD/10)*(Ek[1] -Ek[0]));//λ��ʽPID

        //pwm_out = kP*Ek[0] + kI*Ek[1] + kD*Ek[2];
        //(kP * Ek[0]) - (kI * Ek[1]) + (kD * Ek[2])
        Ek[2] = Ek[1];//���ϴ����ֵ
        Ek[1] = Ek[0];//���������ֵ��ֵ����һ�����
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