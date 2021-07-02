/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		uart
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK5.27
 * @Target core		STC8G8K64S4
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/

#ifndef __ZF_UART_H
#define __ZF_UART_H


#include "common.h"
#include "zf_tim.h"

#define UART1_RX_BUFFER_SIZE	100
#define UART1_TX_BUFFER_SIZE	100

#define	UART1_CLEAR_RX_FLAG (SCON  &= ~0x01)
#define	UART2_CLEAR_RX_FLAG (S2CON &= ~0x01)
#define	UART3_CLEAR_RX_FLAG (S3CON &= ~0x01)
#define	UART4_CLEAR_RX_FLAG (S4CON &= ~0x01)

#define	UART1_CLEAR_TX_FLAG (SCON  &= ~0x02)
#define	UART2_CLEAR_TX_FLAG (S2CON &= ~0x02)
#define	UART3_CLEAR_TX_FLAG (S3CON &= ~0x02)
#define	UART4_CLEAR_TX_FLAG (S4CON &= ~0x02)


#define UART1_GET_RX_FLAG   (SCON  & 0x01)
#define UART2_GET_RX_FLAG   (S2CON & 0x01)
#define UART3_GET_RX_FLAG   (S3CON & 0x01)
#define UART4_GET_RX_FLAG   (S4CON & 0x01)
						    
#define UART1_GET_TX_FLAG   (SCON  & 0x02)
#define UART2_GET_TX_FLAG   (S2CON & 0x02)
#define UART3_GET_TX_FLAG   (S3CON & 0x02)
#define UART4_GET_TX_FLAG   (S4CON & 0x02)


//��ö�ٶ��岻�����û��޸�
typedef enum //ö�ٴ��ں�
{
    UART_1,
    UART_2,
    UART_3,
    UART_4,
}UARTN_enum;


//��ö�ٶ��岻�����û��޸�
typedef enum //ö�ٴ�������
{
	UART1_RX_P30, UART1_TX_P31,		//ֻ��ʹ��ͬһ�е�RX��TX���źš����������
	UART1_RX_P36, UART1_TX_P37,		//����:UART1_RX_P30,UART1_TX_P37���������С�
	UART1_RX_P16, UART1_TX_P17,
	UART1_RX_P43, UART1_TX_P44,
	
	UART2_RX_P10, UART2_TX_P11,
	UART2_RX_P46, UART2_TX_P47,
	
	UART3_RX_P00, UART3_TX_P01,
	UART3_RX_P50, UART3_TX_P51,
	
	UART4_RX_P02, UART4_TX_P03,
	UART4_RX_P52, UART4_TX_P53,	

}UARTPIN_enum;





extern uint8 xdata uart1_tx_buff[UART1_TX_BUFFER_SIZE];	//���ͻ���
extern uint8 xdata uart1_rx_buff[UART1_RX_BUFFER_SIZE];	//���ջ���
extern uint8 busy[5];


void uart_init(UARTN_enum uart_n, UARTPIN_enum uart_rx_pin, UARTPIN_enum uart_tx_pin, uint32 baud, TIMN_enum tim_n);
void uart_putchar(UARTN_enum uart_n,uint8 dat);
void uart_putstr(UARTN_enum uart_n,uint8 *str);
void uart_putbuff(UARTN_enum uart_n,uint8 *p,uint16 len);

#endif