/*
------------------------------------------------------------
�ٷ���ַ��www.alongxii.xyz
������ߣ�Along
QQ��1259306443
���䣺alongxii@outlook.com/1259306443@qq.com
Ӳ�����ߣ�LI JIAN
QQ��1557731308
���䣺jian19990317@qq.com
Դ��ײ������ɿƼ���Դ�⣬�ڴ˻����Ͻ��ж��ο���������ȫ����Դ��Github��
����ǰ����ϵ����Along���������ѯ��
------------------------------------------------------------
2021.7.2
Դ����������V1.3.1�汾
���ܰ�����
1.��������
2.��Ļ����
3.��������
4.����ʱ������
5.�¶���ֵ����
6.�躸У׼����
7.��ԴЭ���������
8.�˵�UI����
��������ʹ�÷�����www.alongxii.xyz������ϸ���ܡ�
������ַ���ܻ����Ϊwww.alongxii.com/www.alongxii.cn��
------------------------------------------------------------
Դ������ļ����ܣ�
*user_gpio.h:����ӳ���ͷ�ļ����ɸ����Լ���·�Ĳ����޸�����ӳ�䣬��ADC�ӿ������P1�����⣬
IIC��SPI�ӿھ�����ģ��ӿڣ������Ͽ�����ӳ�䡣
main.c:���ļ�����Ҫ�ṩ�����ʼ�����ã����˵��ȹ��ܳ�����á�
user_menu.c:���ļ����ڲ˵�UIʹ�á�
user_adc.c:���ļ�����ADC�źŲɼ�����ѹֵת�����¶�ת����
�����¶ȶ�ȡ���÷ֶ�һ�κ��������ζ�ÿ��100�ȷֶε�adcֵ��������õ���Ӧ�¶�ֵ��
��ѹ�ɼ�ʹ�õ����ѹ��
user_pid.c:���ļ�����λ��ʽPID���п��£����и��Ƚ����Ʒ��������ڴ��ļ����޸Ŀ��ƺ�����
user_button.c:���ļ��ṩ��ذ����жϺ���������߼����������ܵ��÷�ʽ��
------------------------------------------------------------
*/
#ifndef USER_PID_H
#define USER_PID_H
#include "headfile.h"
#define  	       kP			(float)page_two_data[0][0]
#define 	       kI     (float)page_two_data[0][1]
#define 	       kD     (float)page_two_data[0][2]
extern float		Integration;	//������
extern float    Ek[3];//�������ֵ
extern float		Temp_Set;					//�趨ֵ
extern float 	  Feedback;			//����ֵ
extern float		Pwmduty_Out;					//�����pwmռ�ձ�

extern uint8 pwm_flag;
extern float pwm_duty_out;


void ALL_PWM_init(void);
void pwm_out_get(void);




#endif

