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
#ifndef USER_BUTTON_H
#define USER_BUTTON_H
#include "headfile.h"

extern uint8  select_flag;
extern uint8  mode_flag;//ģʽ��־λ
extern uint8  enter_flag;
extern uint8  quit_flag;//�˳���־λ
extern uint8  up_flag;//�ϼ�
extern uint8  up_short_flag;//�ϼ�����
extern uint8  up_long_flag;//�ϼ�����
extern uint8  down_flag;//�¼�
extern uint8  down_short_flag;//�¼�����
extern uint8  down_long_flag;//�¼�����
extern uint8  sleep_flag;//�¼�
extern uint8  sleep_short_flag;//�¼�����
extern uint8  sleep_long_flag;//�¼�����



extern uint8 auto_power_off_flag;
extern uint8 oled_handle_flag;
extern uint8 auto_oled_off_flag;
extern uint8 oled_light_flag;

extern int8 SLEEP_INIT_FLAG;

extern int16 sleep_cont;
extern int16 sleep_second;

extern int iron_ad;

void button_init(void);
void key_press_handler(void);
void adc_iron_get_handle(void);
void OLED_sleep_handle(void);
#endif


