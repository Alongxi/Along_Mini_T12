/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		delay
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK5.27
 * @Target core		STC8G8K64S4
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/


#include "zf_delay.h"




//-------------------------------------------------------------------------------------------------------------------
//  @brief      软件延时函数//内部时钟频率33.1776Mhz
//  @param      x            	需要延时的时间（ms）
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
void delay_ms(uint16 x)
{
    uint8 i,j;
    while(x--)
    {
		_nop_();
		_nop_();
		i = 44;
		j = 19;
		do
		{
			while (--j);
		} while (--i);
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      软件延时函数//内部时钟频率33.1776Mhz
//  @param      x            	需要延时的时间（us）
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
void delay_us(uint16 x)
{
    uint8 i;
    while(x--)
    {
		i = 9;
		while (--i);
    }
}



