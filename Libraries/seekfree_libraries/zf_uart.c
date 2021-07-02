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

#include "zf_uart.h"
#include "board.h"

uint8 busy[5];				 //����æ��־λ

uint8 xdata uart1_tx_buff[UART1_TX_BUFFER_SIZE];	//���ͻ���
uint8 xdata uart1_rx_buff[UART1_RX_BUFFER_SIZE];	//���ջ���


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ڳ�ʼ��
//  @param      uart_n          ����ģ���(USART_1,USART_2,USART_3,USART_4)
//  @param      uart_rx_pin     ���ڲ�����
//  @param      uart_tx_pin     ���ڽ��շ�������
//  @param      baud      		���ڽ��շ�������
//  @param      tim_n      		ʹ��tim_n��Ϊ���ڲ����ʷ�����(TIM1-TIM4)
//  @return     NULL          	
//  Sample usage:               uart_init(USART_1,115200,UART1_RX_P30_TX_P31);       // ��ʼ������1 ������115200 ��������ʹ��P31 ��������ʹ��P30
//  @note                       ����1ʹ�� ��ʱ��1���߶�ʱ��2 ��Ϊ�����ʷ�������
//								����2ʹ�� ��ʱ��2 			 ��Ϊ�����ʷ�������
//								����3ʹ�� ��ʱ��3���߶�ʱ��2 ��Ϊ�����ʷ�������
//								����4ʹ�� ��ʱ��4���߶�ʱ��2 ��Ϊ�����ʷ�������
//                              STC8G���� ��ʱ��0-��ʱ��4����5����ʱ����
//								�������ɼ�����Ҳ��Ҫ��ʱ����Ϊ�ⲿ������
//-------------------------------------------------------------------------------------------------------------------
void uart_init(UARTN_enum uart_n, UARTPIN_enum uart_rx_pin, UARTPIN_enum uart_tx_pin, uint32 baud, TIMN_enum tim_n)
{
    uint16 brt;
    //65536-SYSclk/baud/4=brt
    brt = 65536 - sys_clk/baud/4;

	switch(uart_n)
	{
		case UART_1:
		{
			if(TIM_1 == tim_n)
			{
				SCON |= 0x50;
				TMOD |= 0x00;
				TL1 = brt;
				TH1 = brt >> 8;
				AUXR |= 0x40;
				TR1 = 1;
				busy[1] = 0;
			}
			else if(TIM_2 == tim_n)
			{
				SCON |= 0x50;
				T2L = brt;
				T2H = brt >> 8;
				AUXR |= 0x15;
			}
			P_SW1 &= ~(0x03<<6);
			if((UART1_RX_P30 == uart_rx_pin) && (UART1_TX_P31 == uart_tx_pin))
			{
				P_SW1 |= 0x00;
			}
			else if((UART1_RX_P36 == uart_rx_pin) && (UART1_TX_P37 == uart_tx_pin))
			{
				P_SW1 |= 0x40;
			}
			else if((UART1_RX_P16 == uart_rx_pin) && (UART1_TX_P17 == uart_tx_pin))
			{
				P_SW1 |= 0x80;
			}
			else if((UART1_RX_P43 == uart_rx_pin) && (UART1_TX_P44 == uart_tx_pin))
			{
				P_SW1 |= 0xc0;
			}
			busy[1] = 0;
			ES = 1;
			break;
		}
		
		case UART_2:
		{
			if(TIM_2 == tim_n)
			{
				S2CON |= 0x10;
				T2L = brt;
				T2H = brt >> 8;
				AUXR |= 0x14;
			}
			
			P_SW2 &= ~(0x01<<0);
			if((UART2_RX_P10 == uart_rx_pin) && (UART2_TX_P11 == uart_tx_pin))
			{
				P_SW2 |= 0x00;
			}
			else if((UART2_RX_P46 == uart_rx_pin) && (UART2_TX_P47 == uart_tx_pin))
			{
				P_SW2 |= 0x01;
			}
			
			IE2 |= 0x01 << 0;	//�����п�2�ж�
			busy[2] = 0;
			break;
		}
		
		case UART_3:
		{
			if(TIM_2 == tim_n)
			{
				S2CON |= 0x10;
				T2L = brt;
				T2H = brt >> 8;
				AUXR |= 0x14;
			}
			else if(TIM_3 == tim_n)
			{
				S3CON |= 0x50;
				T3L = brt;
				T3H = brt >> 8;
				T4T3M |= 0x0a;
			}
			
			P_SW2 &= ~(0x01<<1);
			if((UART3_RX_P00 == uart_rx_pin) && (UART3_TX_P01 == uart_tx_pin))
			{
				P_SW2 |= 0x00;
			}
			else if((UART3_RX_P50 == uart_rx_pin) && (UART3_TX_P51 == uart_tx_pin))
			{
				P_SW2 |= 0x02;
			}
			
			IE2 |= 0x01<<3;	//�����п�3�ж�
			busy[3] = 0;
			break;
		}
		
		case UART_4:
		{
			if(TIM_2 == tim_n)
			{
				S4CON |= 0x10;
				T2L = brt;
				T2H = brt >> 8;
				AUXR |= 0x14;
			}
			else if(TIM_4 == tim_n)
			{
				S4CON |= 0x50;
				T4L = brt;
				T4H = brt >> 8;
				T4T3M |= 0xa0;
			}

			P_SW2 &= ~(0x01<<2);
			if((UART4_RX_P02 == uart_rx_pin) && (UART4_TX_P03 == uart_tx_pin))
			{
				P_SW2 |= 0x00;
			}
			else if((UART4_RX_P52 == uart_rx_pin) && (UART4_TX_P53 == uart_tx_pin))
			{
				P5M0 = 0x00;
				P5M1 = 0x01<<2;//P5.2 ��Ҫ����Ϊ����
				P_SW2 |= 0x04;
			}
			IE2 |= 0x01<<4;	//�����п�4�ж�
			busy[4] = 0;
			break;
		}	
	}
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����ֽ����
//  @param      uart_n          ����ģ���(USART_1,USART_2,USART_3,USART_4)
//  @param      dat             ��Ҫ���͵��ֽ�
//  @return     void        
//  Sample usage:               uart_putchar(UART_1,0xA5);       // ����1����0xA5
//-------------------------------------------------------------------------------------------------------------------
void uart_putchar(UARTN_enum uart_n,uint8 dat)
{
	switch(uart_n)
	{
		case UART_1:
			while (busy[1]);
			busy[1] = 1;
			SBUF = dat;
		    break;
		case UART_2:
			while (busy[2]);
			busy[2] = 1;
			S2BUF = dat;
		    break;
		case UART_3:
			while (busy[3]);
			busy[3] = 1;
			S3BUF = dat;
		    break;
		case UART_4:
			while (busy[4]);
			busy[4] = 1;
			S4BUF = dat;
		    break;
	}
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ڷ�������
//  @param      uart_n          ����ģ���(USART_1,USART_2,USART_3,USART_4)
//  @param      *buff           Ҫ���͵������ַ
//  @param      len             ���ͳ���
//  @return     void
//  Sample usage:               uart_putbuff(UART_1,&a[0],5);
//-------------------------------------------------------------------------------------------------------------------
void uart_putbuff(UARTN_enum uart_n,uint8 *p,uint16 len)
{
    while(len--)
        uart_putchar(uart_n,*p++);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ڷ����ַ���
//  @param      uart_n          ����ģ���(USART_1,USART_2,USART_3,USART_4)
//  @param      *str            Ҫ���͵��ַ�����ַ
//  @return     void
//  Sample usage:               uart_putstr(UART_1,"i lvoe you"); 
//-------------------------------------------------------------------------------------------------------------------
void uart_putstr(UARTN_enum uart_n,uint8 *str)
{
    while(*str)
    {
        uart_putchar(uart_n,*str++);
    }
}
