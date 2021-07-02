/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		eeprom
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK5.27
 * @Target core		STC8G8K64S4
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/


#ifndef __ZF_EEPROM_H
#define __ZF_EEPROM_H

#include "common.h"





void iap_init(void);
void iap_idle(void);
void iap_set_tps(void);
uint8 iap_get_cmd_state(void);
void iap_read_bytes(uint16 addr, uint8 *buf, uint8 len);
void iap_write_bytes(uint16 addr, uint8 *buf, uint8 len);
void iap_erase_page(uint16 addr);





#endif