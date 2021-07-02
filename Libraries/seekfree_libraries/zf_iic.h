/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		iic
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK5.27
 * @Target core		STC8G8K64S4
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/

#ifndef __ZF_IIC_H
#define __ZF_IIC_H


#include "common.h"

typedef enum
{
    IIC_1 = 0,
	
    IIC_2 = 1,
	
    IIC_3 = 2,	//STC8Gû�и�������,�����ռλ
	
    IIC_4 = 3,
	
} IICN_enum;

typedef enum
{
    IIC1_SCL_P15 = 0x00, IIC1_SDA_P14,
    IIC2_SCL_P25 = 0x10, IIC2_SDA_P24,
    //IIC3_SCL_P77 = 0x20, IIC3_SDA_P76,	//STC8Gû�и������š�
    IIC4_SCL_P32 = 0x30, IIC4_SDA_P33,
} IIC_PIN_enum;






#define IIC_SEND_OK 	0
#define IIC_SEND_FAIL	1



void  iic_init(IICN_enum iic_n, IIC_PIN_enum scl_pin, IIC_PIN_enum sda_pin, uint32 wait_time);
uint8 iic_write_reg(IICN_enum iic_n, uint8 dev_add, uint8 reg, uint8 dat);
uint8 iic_read_reg(IICN_enum iic_n, uint8 dev_add, uint8 reg, uint8 *dat);
uint8 iic_read_reg_bytes(IICN_enum iic_n, uint8 dev_add, uint8 reg, uint8 *dat, uint8 num);
void iic_change_pin(IICN_enum iic_n,IIC_PIN_enum scl_pin,IIC_PIN_enum sda_pin);



#endif