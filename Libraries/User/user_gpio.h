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
#ifndef USER_GPIO_H
#define USER_GPIO_H

#define Product//�޸İ����޸��������ã�Ŀǰ��������Ϊ��Ʒ��
//�����Զ����������ã�������µİ��ţ����޸Ĵ�����Ϊ�Զ������
//���ʹ�õ���Demo��
#ifdef  Demo
#define key_up       P36
#define key_mode     P35
#define key_down     P51

#define key_up_pin           P3_6//P36
#define key_mode_pin         P3_5//P35
#define key_down_pin         P5_1//P51

#define PWM_control  PWM0_P06
#define SLEEP        P53
#define BEEP         PWM5_P50

#define ADC_VIN            ADC_P12
#define ADC_IRON_TEMP      ADC_P10
#define ADC_SYS_TEMP       ADC_P17
#endif
//���ʹ�õ��ǲ�Ʒ��
#ifdef  Product
#define CFG1           P22//P36
#define CFG2           P20//P35
#define CFG3           P21//P51

#define key_up           P02//P36
#define key_mode         P04//P35
#define key_down         P05//P51
#define key_sleep        P37

#define key_up_pin           P0_2
#define key_mode_pin         P0_4
#define key_down_pin         P0_5
#define key_sleep_pin        P3_7

#define PWM_control      PWM1_P17

#define BEEP             PWM0_P00

#define ADC_VIN            ADC_P12
#define ADC_IRON_TEMP      ADC_P11
#define ADC_SYS_TEMP       ADC_P10
#endif

#ifdef  Product_V2
#define CFG1           P22//P36
#define CFG2           P20//P35
#define CFG3           P21//P51

#define key_up           P02//P36
#define key_mode         P04//P35
#define key_down         P05//P51
#define key_sleep        P37

#define key_up_pin           P0_2//P36
#define key_mode_pin         P0_4//P35
#define key_down_pin         P0_5//P51
#define key_sleep_pin        P3_7//P51

#define PWM_control      PWM1_P17

#define BEEP             PWM0_P00

#define ADC_VIN            ADC_P12
#define ADC_IRON_TEMP      ADC_P11
#define ADC_SYS_TEMP       ADC_P10
#endif
#endif