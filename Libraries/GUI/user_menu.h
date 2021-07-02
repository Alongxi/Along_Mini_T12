/*
------------------------------------------------------------
官方网址：www.alongxii.xyz
软件作者：Along
QQ：1259306443
邮箱：alongxii@outlook.com/1259306443@qq.com
硬件作者：LI JIAN
QQ：1557731308
邮箱：jian19990317@qq.com
源码底层采用逐飞科技开源库，在此基础上进行二次开发，代码全部开源至Github。
商用前请联系作者Along进行相关咨询。
------------------------------------------------------------
2021.7.2
源码最后更新至V1.3.1版本
功能包括：
1.参数整定
2.屏幕设置
3.基础设置
4.休眠时间设置
5.温度阈值设置
6.阻焊校准设置
7.电源协议管理设置
8.菜单UI设置
具体设置使用方法在www.alongxii.xyz中有详细介绍。
后续网址可能会更替为www.alongxii.com/www.alongxii.cn。
------------------------------------------------------------
源码相关文件介绍：
*user_gpio.h:引脚映射的头文件，可根据自己电路的布局修改引脚映射，除ADC接口需采用P1口以外，
IIC、SPI接口均采用模拟接口，理论上可任意映射。
main.c:此文件中主要提供软件初始化配置，及菜单等功能程序调用。
user_menu.c:此文件用于菜单UI使用。
user_adc.c:此文件用于ADC信号采集，电压值转换、温度转换。
烙铁温度读取采用分段一次函数，依次对每个100度分段的adc值进行运算得到对应温度值。
电压采集使用电阻分压。
user_pid.c:此文件采用位置式PID进行控温，如有更先进控制方案，可在此文件中修改控制函数。
user_button.c:此文件提供相关按键中断函数与操作逻辑函数，功能调用方式。
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
void data_restore(void);//数据还原

void data_init(void);


extern uint8 data save_data_A[32];
extern uint8 data save_data_B[32];
extern uint8 code page_one_num[page_max+1][4];
extern uint8 code page_two_num[page_max+1][10][4];
extern int16 xdata page_two_data[page_max+1][10];

extern int8 Strong_temp_flag;
extern int8 BEEP_flag;
#define TEMP_STEEP                page_two_data[4][3]//温度步进
#define IRON_TEMP_SET_MIN         page_two_data[4][0] //烙铁调温最大值
#define IRON_TEMP_SET_INIT        page_two_data[4][2]
#define IRON_TEMP_SET_MAX         page_two_data[4][1] //烙铁调温最小值 
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
//----------------------版本信息-----------------------//
#define INFO_VERSION              " Version:1.3.1.Alpha "
#define INFO_HARDWARE             "  Hardware:LI JIAN   "
#define INFO_SOFTWARE             "  Software: ALONG    "
#define INFO_WEBSITE              "  Web:ALONGXII.XYZ   "
//-----------------------------------------------------//

#endif


