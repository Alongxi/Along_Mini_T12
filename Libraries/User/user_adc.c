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
#include "user_adc.h"
/*float temp_res[30] =//热敏电阻在0-29度时的电阻值(单位：kΩ)
{
	27.65, 26.47, 25.34, 24.27, 23.25, 22.27, 21.35, 20.47, 19.63, 18.83,
	18.06, 17.34, 16.64, 15,98, 15.35, 14.74, 14.17, 13.62, 13.09, 12.59,
  12.11, 11.65, 11.21, 10.79, 10.39, 10.00, 9.569, 9.158, 8.768, 8.396,
};*/
uint8 error_flag = 1;
uint8 low_battery_flag = 0;
uint8 adc_iron_flag = 0;
float SHOW_IRON_TEMP;
float Iron_temp_now;
float Iron_temp_last;
float iron_k[4];//近似烙铁温度变化曲线为一个一次函数：y = kx + b
float iron_b[4];

void user_adc_init(void)
{
    adc_init(ADC_VIN, ADC_SYSclk_DIV_8);	//初始化24V电压获取
    adc_init(ADC_IRON_TEMP, ADC_SYSclk_DIV_8);	//初始化烙铁电压
    adc_init(ADC_SYS_TEMP, ADC_SYSclk_DIV_8);	//初始化室温检测
}

float adc_vin_get()//获取系统电压
{
    float vin_ad,temp = 0;
    float ad_array[51];
    int vin_data,i,j = 0;
    vin_data = adc_once(ADC_VIN, ADC_10BIT);
#ifdef Demo
    vin_ad = ((float)vin_data/1024.0)*(32.2/2.2)*3.3;//定义一个初始电压值
#endif
#ifdef Product
    vin_ad = ((float)vin_data/1024.0)*(28.7/4.7)*3.3;
#endif
#ifdef Product_V2
    vin_ad = ((float)vin_data/1024.0)*(51.7/4.7)*3.3;
#endif
    for(i = 0; i<51; i++)
    {
        ad_array[i] = vin_ad;//将连续50次电压检测的ad值赋值到数组中
    }
    for (j=0; j<50; j++) //采用冒泡排序
    {
        for (i=0; i<50-j; i++)
        {
            if ( ad_array[i]>ad_array[i+1] )
            {
                temp = ad_array[i];//将值赋予给临时变量
                ad_array[i] = ad_array[i+1];
                ad_array[i+1] = temp;
            }
        }
    }
    return ad_array[25];
}

float adc_sys_temp_get()//获取整个系统的温度
{
    float temp,resister = 0;
    int temp_data_sys = adc_once(ADC_SYS_TEMP, ADC_10BIT);
    resister = 75.0f/((1024/(float)temp_data_sys) - 1);
    temp = -1.42f*resister + 39.16f;//此函数只在0-30度之间近似准确
    return temp;
}
#define FILTER_A
#define FILTER_N 12
uint16 filter_buf[FILTER_N + 1];

//新建一个滤波算法
uint16 adc_get_filter(uint16 get_init_data)
{
//递推平均滤波法
#ifdef FILTER_A
    //uint8 filter_i = 0;
    uint8 filter_count = 0;
    int filter_sum = 0;
    filter_buf[FILTER_N] = get_init_data;
    for(filter_count = 0; filter_count < FILTER_N; filter_count++)
    {
       // filter_sum += filter_buf[filter_count];
			    filter_buf[filter_count] = filter_buf[filter_count + 1]; // 所有数据左移，低位仍掉
          filter_sum += filter_buf[filter_count];
    }
    return (uint16)(filter_sum / FILTER_N);

#endif
//
#ifdef FILTER_B
		
#endif

}

















//读取烙铁的AD值，将其转化为温度
void adc_iron_temp(uint16 temp_data)
{
    float temp = 0;

    if(temp_data < IRON_PARM_600)
    {
			  adc_iron_flag = 1;
        if(temp_data <= IRON_PARM_0)//在0-200度时
        {

            temp = 0;
        }
        else if((IRON_PARM_0 <= temp_data)&&(temp_data <= IRON_PARM_200))//在0-200度时
        {
            iron_k[0] = (200 - 0)/(IRON_PARM_200 - IRON_PARM_0);
            iron_b[0] = 200 - iron_k[0]*IRON_PARM_200;
            temp = iron_k[0]*(float)temp_data +  iron_b[0];
        }
        else if((IRON_PARM_200 < temp_data)&&(temp_data <= IRON_PARM_400))//在200-400度时
        {
            iron_k[1] = (400 - 200)/(IRON_PARM_400 - IRON_PARM_200);
            iron_b[1] = 400 - iron_k[1]*IRON_PARM_400;
            temp = iron_k[1]*(float)temp_data +  iron_b[1];
        }
        else if((IRON_PARM_400 < temp_data)&&(temp_data <= IRON_PARM_500))//在400-500度时
        {
            iron_k[2] = (500 - 400)/(IRON_PARM_500 - IRON_PARM_400);
            iron_b[2] = 500 - iron_k[2]*IRON_PARM_500;
            temp = iron_k[2]*(float)temp_data +  iron_b[2];
        }
        else if((IRON_PARM_500 < temp_data)&&(temp_data <= IRON_PARM_600))//在500-600度时
        {
            iron_k[3] = (600 - 500)/(IRON_PARM_600 - IRON_PARM_500);
            iron_b[3] = 600 - iron_k[3]*IRON_PARM_600;
            temp = iron_k[3]*(float)temp_data +  iron_b[3];
        }
        Iron_temp_now  = temp + adc_sys_temp_get();//获取当前烙铁温度
        //if((Iron_temp_last - Iron_temp_now> 150)||((Iron_temp_last - Iron_temp_now < -150)))//
        //{
        //Iron_temp_now = Iron_temp_last;
        //}

        if((SHOW_IRON_TEMP > Temp_Set - 10)&&(SHOW_IRON_TEMP < Temp_Set + 10))
        {
            SHOW_IRON_TEMP = Temp_Set;
        }
        else
        {
            SHOW_IRON_TEMP = Iron_temp_now;
        }
        Iron_temp_last = Iron_temp_now;
    }
		else
		{
			adc_iron_flag = 0;
            pwm_flag = 0;//在这里面
		}
}
