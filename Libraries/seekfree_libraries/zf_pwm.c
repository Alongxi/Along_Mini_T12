/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		pwm
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK5.27
 * @Target core		STC8G8K64S4
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/

#include "zf_pwm.h"
#include "board.h"
#include "zf_gpio.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM初始化
//  @param      pwmch       PWM通道号及引脚
//  @param      freq        PWM频率(64Hz-3MHz)
//  @param      duty        PWM占空比
//  @return     void
//  Sample usage:           pwm_init(PWM0_P00, 100, 5000);     //初始化PWM0  使用引脚P0.0  输出PWM频率100HZ   占空比为百分之 5000/PWM_DUTY_MAX*100
//							PWM_DUTY_MAX在fsl_pwm.h文件中 默认为10000
//-------------------------------------------------------------------------------------------------------------------
void pwm_init(PWMCH_enum pwmch,uint32 freq, uint16 duty)
{
	uint16 match_temp;
    uint16 period_temp; 
	uint8 freq_div = 0;
	
	gpio_mode(pwmch,GPO_PP);					//设置为推挽输出
	
	PWMSET |= 1 << (pwmch>>4);
	
	P_SW2 |= 0x80;
	
	freq_div = (sys_clk/freq)>>15;
	
//	if(freq_div >= 15) printf("频率太低");
	
	period_temp = sys_clk/freq/(freq_div + 1);		//周期
	match_temp = period_temp*((float)duty/PWM_DUTY_MAX);	//占空比

	if(pwmch < PWM3_P30)
	{
		(*(unsigned char volatile xdata *)(0xFF02 + 0x50 * (pwmch>>4))) = freq_div;									//设置pwmn频率为 系统时钟/freq_div
		(*(unsigned int  volatile xdata *)(0xFF00 + 0x50 * (pwmch>>4))) = (uint16)period_temp; 						//设置PWMn周期为period_temp个 PWM 时钟
		(*(unsigned int  volatile xdata *)(0xFF10 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = (uint16)match_temp; // 在计数值为 match_temp 地方 pwmch 通道输出低电平
		//(*(unsigned int  volatile xdata *)(0xFF12 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = 0;				// 在计数值为 0 地方 pwmch 通道输出高电平
		(*(unsigned char volatile xdata *)(0xFF14 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) |= 0x80;				// 使能 pwmch 输出
	}
	else
	{
		(*(unsigned char volatile xdata *)(0xFC02 + 0x50 * ((pwmch-PWM3_P30)>>4))) = freq_div;							//设置pwmn频率为 系统时钟/freq_div
		(*(unsigned int  volatile xdata *)(0xFC00 + 0x50 * ((pwmch-PWM3_P30)>>4))) = period_temp; 						//设置PWMn周期为period_temp个 PWM 时钟
		(*(unsigned int  volatile xdata *)(0xFC10 + 0x50 * ((pwmch-PWM3_P30)>>4) + (pwmch&0X0F) * 0x08)) = match_temp; 	// 在计数值为 match_temp 地方 pwmch 通道输出低电平
		//	(*(unsigned int  volatile xdata *)(0xFF12 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = 0;					// 在计数值为 0 地方 pwmch 通道输出高电平
		(*(unsigned char volatile xdata *)(0xFC14 + 0x50 * ((pwmch-PWM3_P30)>>4) + (pwmch&0X0F) * 0x08)) |= 0x80;		// 使能 pwmch 输出
	}
	switch(pwmch>>4)
	{
		case 0:
			PWMCFG01 |= 0x01; 
			break;
		case 1:
			PWMCFG01 |= 0x01<<4; 
			break;
		case 2:
			PWMCFG23 |= 0x01; 
			break;
		case 3:
			PWMCFG23 |= 0x01<<4; 
			break;
		case 4:
			PWMCFG45 |= 0x01; 
			break;
		case 5:
			PWMCFG45 |= 0x01<<4; 
			break;
	}	
	P_SW2 &= ~0x80;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM占空比设置
//  @param      pwmch       PWM通道号及引脚
//  @param      duty        PWM占空比
//  @return     void
//  Sample usage:           pwm_duty(PWM0_P00, 5000);     //初始化PWM0  使用引脚P0.0  输出PWM频率50HZ   占空比为百分之 5000/PWM_DUTY_MAX*100
//							PWM_DUTY_MAX在fsl_pwm.h文件中 默认为50000
//-------------------------------------------------------------------------------------------------------------------
void pwm_duty(PWMCH_enum pwmch, uint16 duty)
{
	uint16 match_temp;
	
	P_SW2 |= 0x80;
	

	
	if(pwmch < PWM3_P30)
	{
		match_temp = (uint16)(*(unsigned int volatile xdata *)(0xFF00 + 0x50 * (pwmch>>4))) * ((float)duty/PWM_DUTY_MAX);				//占空比
		(*(unsigned int  volatile xdata *)(0xFF10 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = match_temp;								// 在计数值为 0H 地方 pwmch 通道输出低电平
	}
	else
	{
		match_temp = (uint16)(*(unsigned int volatile xdata *)(0xFC00 + 0x50 * ((pwmch-PWM3_P30)>>4))) * ((float)duty/PWM_DUTY_MAX);	//占空比
		(*(unsigned int volatile xdata *)(0xFC10 + 0x50 * ((pwmch-PWM3_P30)>>4) + (pwmch&0X0F) * 0x08)) = match_temp;					// 在计数值为 0H 地方 pwmch 通道输出低电平
	}
	


//	(*(unsigned int  volatile xdata *)(0xFF12 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = 0;				// 在计数值为 duty 地方 pwmch 通道输出高电平
	P_SW2 &= ~0x80;
	
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM频率设置
//  @param      pwmch       PWM通道号及引脚
//  @param      freq        PWM频率
//  @param      duty        PWM占空比
//  @return     void
//  Sample usage:           pwm_freq(PWM0_P00, 50, 5000);     //修改化PWM0  使用引脚P0.0  输出PWM频率50HZ   占空比为百分之 5000/PWM_DUTY_MAX*100
//-------------------------------------------------------------------------------------------------------------------
void pwm_freq(PWMCH_enum pwmch, uint32 freq, uint16 duty)
{
	uint32 match_temp;
    uint32 period_temp; 
	uint8 freq_div = 0;
	
	freq_div = (sys_clk/freq)>>15;
	period_temp = sys_clk/freq/(freq_div + 1);		//周期
	match_temp = period_temp*((float)duty/PWM_DUTY_MAX);	//占空比
	
	P_SW2 |= 0x80;
	
	
	if(pwmch < PWM3_P30)
	{
		(*(unsigned char volatile xdata *)(0xFF02 + 0x50 * (pwmch>>4))) = freq_div;							//设置pwmn频率为 系统时钟/freq_div
		(*(unsigned int  volatile xdata *)(0xFF00 + 0x50 * (pwmch>>4))) = period_temp; 						//设置PWMn周期为period_temp个 PWM 时钟
		(*(unsigned int  volatile xdata *)(0xFF10 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = match_temp; // 在计数值为 match_temp 地方 pwmch 通道输出低电平
		//	(*(unsigned int  volatile xdata *)(0xFF12 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = 0;			// 在计数值为 0 地方 pwmch 通道输出高电平
	}
	else
	{
		(*(unsigned char volatile xdata *)(0xFC02 + 0x50 * ((pwmch-PWM3_P30)>>4))) = freq_div;							//设置pwmn频率为 系统时钟/freq_div
		(*(unsigned int  volatile xdata *)(0xFC00 + 0x50 * ((pwmch-PWM3_P30)>>4))) = period_temp; 						//设置PWMn周期为period_temp个 PWM 时钟
		(*(unsigned int  volatile xdata *)(0xFC10 + 0x50 * ((pwmch-PWM3_P30)>>4) + (pwmch&0X0F) * 0x08)) = match_temp; // 在计数值为 match_temp 地方 pwmch 通道输出低电平
		//	(*(unsigned int  volatile xdata *)(0xFF12 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = 0;					// 在计数值为 0 地方 pwmch 通道输出高电平
	}
	switch(pwmch>>4)
	{
		case 0:
			PWMCFG01 |= 0x01; 
			break;
		case 1:
			PWMCFG01 |= 0x01<<4; 
			break;
		case 2:
			PWMCFG23 |= 0x01; 
			break;
		case 3:
			PWMCFG23 |= 0x01<<4; 
			break;
		case 4:
			PWMCFG45 |= 0x01; 
			break;
		case 5:
			PWMCFG45 |= 0x01<<4; 
			break;
	}	
	
	P_SW2 &= ~0x80;
}


