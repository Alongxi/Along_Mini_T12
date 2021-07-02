/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		pit
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK5.27
 * @Target core		STC8G8K64S4
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/

#ifndef __ZF_CPA_PIT_H
#define __ZF_CPA_PIT_H
#include "common.h"


//���PCA��־λ
#define PCA_CLEAR_FLAG(x)	(CCON = ~(1<<x))


//��ȡPCA�жϱ�־λ
#define PCA0_GET_FLAG		CCF0
#define PCA1_GET_FLAG		CCF1
#define PCA2_GET_FLAG		CCF2


//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��PCAͨ��
{
	PCA_0,
	PCA_1,
	PCA_2, 	//�ѱ���ʱռ��

}PCAN_enum;


//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��PCA ģʽ
{
	NONE,							//�޲���
	PWM_MODE_N0_ISR,				//6/7/8/10 λ PWM ģʽ�����ж�
	PWM_MODE_RISING_EDGE_ISR,		//6/7/8/10 λ PWM ģʽ�������������ж�
	PWM_MODE_FALLING_EDGE_ISR,		//6/7/8/10 λ PWM ģʽ�������½����ж�
	PWM_MODE_BOTH_EDGE_ISR,			//6/7/8/10 λ PWM ģʽ�����������ж�
	RISING_EDGE_CAPTURE,			//16 λ�����ز���
	FALLING_EDGE_CAPTURE,			//16 λ�½��ز���
	BOTH_EDGE_CAPTURE,				//16 λ���ز���
	SOFT_TIMER,						//16 λ�����ʱ��
	HIGH_SPEED_PULSE_OUTPUT,		//16 Ϊ�����������
}PCAMODE_enum;



extern uint16 ccp_value[3];
extern uint16 pca_time_ms[3];

void pca_reload_counter(PCAN_enum pca_n);

//-------------------�����ж�----------------------//
void pca_init_interrupt_ms(PCAN_enum pca_n,uint16 time_ms);







#endif
