/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		spi
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK5.27
 * @Target core		STC8G8K64S4
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/

#ifndef __ZF_SPI_H
#define __ZF_SPI_H
#include "common.h"




//��ö�����ֹ�û��޸�
typedef enum
{
    SPI_1=0,
    SPI_2,  
    SPI_3,	
    SPI_4,	
	
	//����SS�������������
} SPIN_enum;


//��ö�����ֹ�û��޸�
typedef enum
{
	SPI1_SCLK_P15 = 0x00,SPI1_MOSI_P13,SPI1_MISO_P14, //SPIֻ��ʹ��ͬһ�����ţ��������������
	
	SPI2_SCLK_P25 = 0x10,SPI2_MOSI_P23,SPI2_MISO_P24, //SPIֻ��ʹ��ͬһ�����ţ��������������
	
	SPI3_SCLK_P43 = 0x20,SPI3_MOSI_P40,SPI3_MISO_P41, //SPIֻ��ʹ��ͬһ�����ţ��������������
	
	SPI4_SCLK_P32 = 0x30,SPI4_MOSI_P34,SPI4_MISO_P33, //SPIֻ��ʹ��ͬһ�����ţ��������������
	
	//����CS�������������
} SPI_PIN_enum;


//��ö�����ֹ�û��޸�
typedef enum
{
    MASTER = 0,	 //����
    SLAVE, //�ӻ�
} SPI_MSTR_enum;

//��ö�����ֹ�û��޸�
typedef enum
{
	SPI_SYSclk_DIV_4 = 0,
	SPI_SYSclk_DIV_8,
	SPI_SYSclk_DIV_16,
	SPI_SYSclk_DIV_32,
}SPI_BAUD_enum;


void spi_init(SPIN_enum spi_n,
			  SPI_PIN_enum sck_pin, 
			  SPI_PIN_enum mosi_pin, 
			  SPI_PIN_enum miso_pin, 
			  uint8 mode,
			  SPI_MSTR_enum mstr,
			  SPI_BAUD_enum baud);

void spi_change_pin(SPIN_enum spi_n, 
					SPI_PIN_enum sck_pin, 
					SPI_PIN_enum mosi_pin, 
					SPI_PIN_enum miso_pin);

void spi_change_mode(uint8 mode);

uint8 spi_mosi(uint8 dat);




#endif


