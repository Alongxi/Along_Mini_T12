/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		pwm
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK5.27
 * @Target core		STC8G8K64S4
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/

#include "zf_pwm.h"
#include "board.h"
#include "zf_gpio.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM��ʼ��
//  @param      pwmch       PWMͨ���ż�����
//  @param      freq        PWMƵ��(64Hz-3MHz)
//  @param      duty        PWMռ�ձ�
//  @return     void
//  Sample usage:           pwm_init(PWM0_P00, 100, 5000);     //��ʼ��PWM0  ʹ������P0.0  ���PWMƵ��100HZ   ռ�ձ�Ϊ�ٷ�֮ 5000/PWM_DUTY_MAX*100
//							PWM_DUTY_MAX��fsl_pwm.h�ļ��� Ĭ��Ϊ10000
//-------------------------------------------------------------------------------------------------------------------
void pwm_init(PWMCH_enum pwmch,uint32 freq, uint16 duty)
{
	uint16 match_temp;
    uint16 period_temp; 
	uint8 freq_div = 0;
	
	gpio_mode(pwmch,GPO_PP);					//����Ϊ�������
	
	PWMSET |= 1 << (pwmch>>4);
	
	P_SW2 |= 0x80;
	
	freq_div = (sys_clk/freq)>>15;
	
//	if(freq_div >= 15) printf("Ƶ��̫��");
	
	period_temp = sys_clk/freq/(freq_div + 1);		//����
	match_temp = period_temp*((float)duty/PWM_DUTY_MAX);	//ռ�ձ�

	if(pwmch < PWM3_P30)
	{
		(*(unsigned char volatile xdata *)(0xFF02 + 0x50 * (pwmch>>4))) = freq_div;									//����pwmnƵ��Ϊ ϵͳʱ��/freq_div
		(*(unsigned int  volatile xdata *)(0xFF00 + 0x50 * (pwmch>>4))) = (uint16)period_temp; 						//����PWMn����Ϊperiod_temp�� PWM ʱ��
		(*(unsigned int  volatile xdata *)(0xFF10 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = (uint16)match_temp; // �ڼ���ֵΪ match_temp �ط� pwmch ͨ������͵�ƽ
		//(*(unsigned int  volatile xdata *)(0xFF12 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = 0;				// �ڼ���ֵΪ 0 �ط� pwmch ͨ������ߵ�ƽ
		(*(unsigned char volatile xdata *)(0xFF14 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) |= 0x80;				// ʹ�� pwmch ���
	}
	else
	{
		(*(unsigned char volatile xdata *)(0xFC02 + 0x50 * ((pwmch-PWM3_P30)>>4))) = freq_div;							//����pwmnƵ��Ϊ ϵͳʱ��/freq_div
		(*(unsigned int  volatile xdata *)(0xFC00 + 0x50 * ((pwmch-PWM3_P30)>>4))) = period_temp; 						//����PWMn����Ϊperiod_temp�� PWM ʱ��
		(*(unsigned int  volatile xdata *)(0xFC10 + 0x50 * ((pwmch-PWM3_P30)>>4) + (pwmch&0X0F) * 0x08)) = match_temp; 	// �ڼ���ֵΪ match_temp �ط� pwmch ͨ������͵�ƽ
		//	(*(unsigned int  volatile xdata *)(0xFF12 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = 0;					// �ڼ���ֵΪ 0 �ط� pwmch ͨ������ߵ�ƽ
		(*(unsigned char volatile xdata *)(0xFC14 + 0x50 * ((pwmch-PWM3_P30)>>4) + (pwmch&0X0F) * 0x08)) |= 0x80;		// ʹ�� pwmch ���
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
//  @brief      PWMռ�ձ�����
//  @param      pwmch       PWMͨ���ż�����
//  @param      duty        PWMռ�ձ�
//  @return     void
//  Sample usage:           pwm_duty(PWM0_P00, 5000);     //��ʼ��PWM0  ʹ������P0.0  ���PWMƵ��50HZ   ռ�ձ�Ϊ�ٷ�֮ 5000/PWM_DUTY_MAX*100
//							PWM_DUTY_MAX��fsl_pwm.h�ļ��� Ĭ��Ϊ50000
//-------------------------------------------------------------------------------------------------------------------
void pwm_duty(PWMCH_enum pwmch, uint16 duty)
{
	uint16 match_temp;
	
	P_SW2 |= 0x80;
	

	
	if(pwmch < PWM3_P30)
	{
		match_temp = (uint16)(*(unsigned int volatile xdata *)(0xFF00 + 0x50 * (pwmch>>4))) * ((float)duty/PWM_DUTY_MAX);				//ռ�ձ�
		(*(unsigned int  volatile xdata *)(0xFF10 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = match_temp;								// �ڼ���ֵΪ 0H �ط� pwmch ͨ������͵�ƽ
	}
	else
	{
		match_temp = (uint16)(*(unsigned int volatile xdata *)(0xFC00 + 0x50 * ((pwmch-PWM3_P30)>>4))) * ((float)duty/PWM_DUTY_MAX);	//ռ�ձ�
		(*(unsigned int volatile xdata *)(0xFC10 + 0x50 * ((pwmch-PWM3_P30)>>4) + (pwmch&0X0F) * 0x08)) = match_temp;					// �ڼ���ֵΪ 0H �ط� pwmch ͨ������͵�ƽ
	}
	


//	(*(unsigned int  volatile xdata *)(0xFF12 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = 0;				// �ڼ���ֵΪ duty �ط� pwmch ͨ������ߵ�ƽ
	P_SW2 &= ~0x80;
	
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWMƵ������
//  @param      pwmch       PWMͨ���ż�����
//  @param      freq        PWMƵ��
//  @param      duty        PWMռ�ձ�
//  @return     void
//  Sample usage:           pwm_freq(PWM0_P00, 50, 5000);     //�޸Ļ�PWM0  ʹ������P0.0  ���PWMƵ��50HZ   ռ�ձ�Ϊ�ٷ�֮ 5000/PWM_DUTY_MAX*100
//-------------------------------------------------------------------------------------------------------------------
void pwm_freq(PWMCH_enum pwmch, uint32 freq, uint16 duty)
{
	uint32 match_temp;
    uint32 period_temp; 
	uint8 freq_div = 0;
	
	freq_div = (sys_clk/freq)>>15;
	period_temp = sys_clk/freq/(freq_div + 1);		//����
	match_temp = period_temp*((float)duty/PWM_DUTY_MAX);	//ռ�ձ�
	
	P_SW2 |= 0x80;
	
	
	if(pwmch < PWM3_P30)
	{
		(*(unsigned char volatile xdata *)(0xFF02 + 0x50 * (pwmch>>4))) = freq_div;							//����pwmnƵ��Ϊ ϵͳʱ��/freq_div
		(*(unsigned int  volatile xdata *)(0xFF00 + 0x50 * (pwmch>>4))) = period_temp; 						//����PWMn����Ϊperiod_temp�� PWM ʱ��
		(*(unsigned int  volatile xdata *)(0xFF10 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = match_temp; // �ڼ���ֵΪ match_temp �ط� pwmch ͨ������͵�ƽ
		//	(*(unsigned int  volatile xdata *)(0xFF12 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = 0;			// �ڼ���ֵΪ 0 �ط� pwmch ͨ������ߵ�ƽ
	}
	else
	{
		(*(unsigned char volatile xdata *)(0xFC02 + 0x50 * ((pwmch-PWM3_P30)>>4))) = freq_div;							//����pwmnƵ��Ϊ ϵͳʱ��/freq_div
		(*(unsigned int  volatile xdata *)(0xFC00 + 0x50 * ((pwmch-PWM3_P30)>>4))) = period_temp; 						//����PWMn����Ϊperiod_temp�� PWM ʱ��
		(*(unsigned int  volatile xdata *)(0xFC10 + 0x50 * ((pwmch-PWM3_P30)>>4) + (pwmch&0X0F) * 0x08)) = match_temp; // �ڼ���ֵΪ match_temp �ط� pwmch ͨ������͵�ƽ
		//	(*(unsigned int  volatile xdata *)(0xFF12 + 0x50 * (pwmch>>4) + (pwmch&0X0F) * 0x08)) = 0;					// �ڼ���ֵΪ 0 �ط� pwmch ͨ������ߵ�ƽ
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


