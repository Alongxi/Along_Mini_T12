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
#ifndef USER_MENU_H
#define USER_MENU_H
#include "headfile.h"
#define page_min 0
#define page_max 8




extern uint8 menu_flag;
extern int8 page_flag;
extern uint8 enter_flag;
extern uint8 TEMP_SET_INIT_FLAG;

void show_menu(void);
void top_menu(uint16 set_temp,uint16 iron_temp, uint8 sys_temp, uint8 vin, uint8 pwm_duty);
void key_press(void);
void Function_init(void);
void data_restore(void);//���ݻ�ԭ

void data_init(void);


extern uint8 data save_data_A[32];
extern uint8 data save_data_B[32];
extern uint8 code page_one_num[page_max+1][4];
extern uint8 code page_two_num[page_max+1][10][4];
extern int16 xdata page_two_data[page_max+1][10];

extern int8 Strong_temp_flag;
extern int8 BEEP_flag;
#define TEMP_STEEP                page_two_data[4][3]//�¶Ȳ���
#define IRON_TEMP_SET_MIN         page_two_data[4][0] //�����������ֵ
#define IRON_TEMP_SET_INIT        page_two_data[4][2]
#define IRON_TEMP_SET_MAX         page_two_data[4][1] //����������Сֵ 
#define IRON_TEMP_SET_STRONG      page_two_data[4][4]
#define IRON_TEMP_SET_SLEEP       page_two_data[4][5]
#define BEEP_VOLUME               page_two_data[2][3]*100

#define ICON_SIZE_FLAG            page_two_data[7][0]
#define ICON_ROW_FLAG             page_two_data[7][1]

#define BEEP_ON_FLAG              page_two_data[2][2]
#define SLEEP_ON_FLAG             page_two_data[3][2]
#define SET_SLEEP_MINUTE          page_two_data[3][0]
#define SET_SLEEP_SECOND          page_two_data[3][1]
#define LOW_BATTERY_ON_FLAG       page_two_data[6][2]
#define LOW_BATTERY_VOLTAGE       page_two_data[6][1]
#define AUTO_SHUTDOWN_MINUTE      page_two_data[3][3]
#define AUTO_SHUTDOWN_ON_FLAG     page_two_data[3][4]
//----------------------�汾��Ϣ-----------------------//
#define INFO_VERSION              " Version:1.3.1.Alpha "
#define INFO_HARDWARE             "  Hardware:LI JIAN   "
#define INFO_SOFTWARE             "  Software: ALONG    "
#define INFO_WEBSITE              "  Web:ALONGXII.XYZ   "
//-----------------------------------------------------//

#endif


