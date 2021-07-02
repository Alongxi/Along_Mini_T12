/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		gpio
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK5.27
 * @Target core		STC8G8K64S4
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/


#ifndef __ZF_GPIO_H
#define __ZF_GPIO_H

#include "common.h"


typedef enum
{
	NOPULL = 0,
    PULLUP = 1,
}PULL_enum;


typedef enum
{
	P0_0 = 0x00, P0_1, P0_2, P0_3, P0_4, P0_5, P0_6, P0_7, 
	P1_0 = 0x10, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7, 
	P2_0 = 0x20, P2_1, P2_2, P2_3, P2_4, P2_5, P2_6, P2_7, 
	P3_0 = 0x30, P3_1, P3_2, P3_3, P3_4, P3_5, P3_6, P3_7, 
	P4_0 = 0x40, P4_1, P4_2, P4_3, P4_4, P4_5, P4_6, P4_7, 
	P5_0 = 0x50, P5_1, P5_2, P5_3, P5_4
}PIN_enum;

typedef enum
{
	//pnm1 pnm0
	GPIO = 0,			//׼˫���(������)
	GPO_PP = 1,			//�������
	GPI_IMPEDANCE = 2,	//��������
	GPI_OD = 3,			//��©���
}GPIOMODE_enum;






void  gpio_pull_set(PIN_enum pin, PULL_enum pull);
void  gpio_mode(PIN_enum pin, GPIOMODE_enum mode);







#endif
