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

#ifndef __ZF_PWM_H
#define __ZF_PWM_H
#include "common.h"


#define PWM_DUTY_MAX 10000




typedef enum
{
	PWM0_P00 = 0x00,PWM0_P01,PWM0_P02,PWM0_P03,PWM0_P04,PWM0_P05,PWM0_P06,PWM0_P07,
	                                     
	PWM1_P10 = 0x10,PWM1_P11,PWM1_P12,PWM1_P13,PWM1_P14,PWM1_P15,PWM1_P16,PWM1_P17,
	                                     
	PWM2_P20 = 0x20,PWM2_P21,PWM2_P22,PWM2_P23,PWM2_P24,PWM2_P25,PWM2_P26,PWM2_P27,
	                                     
	PWM3_P30 = 0x30,PWM3_P31,PWM3_P32,PWM3_P33,PWM3_P34,PWM3_P35,PWM3_P36,PWM3_P37,
	                                     
	PWM4_P40 = 0x40,PWM4_P41,PWM4_P42,PWM4_P43,PWM4_P44,PWM4_P45,PWM4_P46,PWM4_P47,
	                                     
	PWM5_P50 = 0x50,PWM5_P51,PWM5_P52,PWM5_P53,PWM5_P54,

}PWMCH_enum;


void pwm_init(PWMCH_enum pwmch,uint32 freq, uint16 duty);
void pwm_duty(PWMCH_enum pwmch, uint16 duty);
void pwm_freq(PWMCH_enum pwmch, uint32 freq, uint16 duty);


#endif
