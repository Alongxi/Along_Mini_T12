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
#include "headfile.h"
#include "user_gpio.h"

void main()
{
    DisableGlobalIRQ();	//关闭总中断
    board_init();
    user_adc_init();//ADC初始化
    button_init();//按键初始化
    ALL_PWM_init();//PWM初始化
		#ifdef HARDWARE_IIC
		//iic_change_pin(IIC_1,IIC1_SCL_P15,IIC1_SDA_P14);
	  //iic_init(IIC_1,IIC1_SCL_P15,IIC1_SDA_P14,0);
	  user_iic_init();
		#endif
    OLED_Init();//OLED初始化
    pit_timer_ms(TIM_1, 10);//10ms中断
    pit_timer_ms(TIM_4, 10);//10ms中断
    pit_timer_ms(TIM_3, 10);//10ms中断

    CFG1 = 1;
    CFG2 = 0;
    CFG3 = 0;
    EnableGlobalIRQ();	//开启总中断
    eeprom_read(0x00,save_data_A,32);
    eeprom_read(0x20,save_data_B,32);
    data_restore();
    //data_init();
    Function_init();

    while(1)
    {
        top_menu(Temp_Set,SHOW_IRON_TEMP, (uint8)adc_sys_temp_get(), (uint8)adc_vin_get(), (int)((pwm_duty_out)*100/PWM_DUTY_MAX));
        show_menu();
        key_press();
        key_press_handler();
        OLED_sleep_handle();
        adc_iron_get_handle();
        adc_iron_temp(adc_get_filter(iron_ad));//获取AD值

//        printf("sleep_cont:%d\r\n",sleep_cont);
//        printf("sleep_second:%d\r\n",sleep_second);
//        printf("Temp_init_flag:%bd\r\n",TEMP_SET_INIT_FLAG);
        printf("%d,%d\n",adc_get_filter(iron_ad),(uint16)Iron_temp_now);
//        printf("Vin:%f v\r\n",adc_vin_get());
//        printf("Res_temp:%f oC\r\n",adc_sys_temp_get());

    }
}











