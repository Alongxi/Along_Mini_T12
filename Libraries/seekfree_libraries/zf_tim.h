/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		ctime
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK5.27
 * @Target core		STC8G8K64S4
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/

#ifndef __ZF_TIM_H
#define __ZF_TIM_H
#include "common.h"



//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��ADCͨ��
{
    CTIM0_P34=0,    
	CTIM1_P35,    	
	CTIM2_P12,     	
	CTIM3_P04,
	CTIM4_P06,
}CTIMN_enum;
       
//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��ADCͨ��
{
    TIM_0,    
	TIM_1,    	
	TIM_2,     	
	TIM_3,
	TIM_4,
}TIMN_enum;


void ctimer_count_init(CTIMN_enum tim_n);
uint16 ctimer_count_read(CTIMN_enum tim_n);
void ctimer_count_clean(CTIMN_enum tim_n);


void pit_timer_ms(TIMN_enum tim_n,uint16 time_ms);

#endif
