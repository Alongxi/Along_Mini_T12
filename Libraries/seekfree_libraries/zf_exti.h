/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		exti
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK5.27
 * @Target core		STC8G8K64S4
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/


#ifndef __ZF_EXTI_H
#define __ZF_EXTI_H
#include "common.h"






//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��ADCͨ��
{
	INT0_P32 = 0,	//֧�ֱ��أ��½����ж�
	INT1_P33,		//֧�ֱ��أ��½����ж�
	INT2_P36,		//֧���½����ж�		
 	INT3_P37,		//֧���½����ж�
	INT4_P30,		//֧���½����ж�
}INTN_enum;


typedef enum    // ö��ADCͨ��
{
	BOTH,			//����
	FALLING_EDGE,	//�½���
//	RISING_EDGE,	//��֧��������

}INT_MODE_enum;


void exit_init(INTN_enum int_n,INT_MODE_enum mode);


#endif