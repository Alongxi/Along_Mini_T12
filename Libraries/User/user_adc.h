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
#ifndef USER_ADC_H
#define USER_ADC_H
#include "headfile.h"
extern float Iron_temp_now;
extern float SHOW_IRON_TEMP;


extern uint8 error_flag;//判断烙铁是否插入
extern uint8 low_battery_flag;
extern uint8 adc_iron_flag;

#define IRON_PARM_0                  (float)page_two_data[5][0]
#define IRON_PARM_100                (float)page_two_data[5][1]
#define IRON_PARM_200                (float)page_two_data[5][2]
#define IRON_PARM_300                (float)page_two_data[5][3]
#define IRON_PARM_400                (float)page_two_data[5][4]
#define IRON_PARM_500                (float)page_two_data[5][5]
#define IRON_PARM_600                (float)page_two_data[5][6]

void user_adc_init(void);
float adc_vin_get();
float adc_sys_temp_get();
void adc_iron_temp(uint16 temp_data);
uint16 adc_get_filter(uint16 get_init_data);

#endif





