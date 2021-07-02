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
#ifndef USER_GPIO_H
#define USER_GPIO_H

#define Product//修改板编号修改引脚配置，目前引脚配置为产品板
//如需自定义引脚配置，可添加新的版编号，再修改此名称为自定义版编号
//如果使用的是Demo板
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
//如果使用的是产品板
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