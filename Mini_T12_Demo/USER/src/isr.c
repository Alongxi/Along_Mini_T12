/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		isr
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK5.27
 * @Target core		STC8G8K64S4
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/
#include "headfile.h"

//UART1中断
void UartIsr() interrupt 4
{
    uint8 res;
    static uint8 dwon_count;
    if(TI)
    {
        TI = 0;
        busy[1] = 0;
    }
    if (RI)
    {
        RI = 0;
        res = SBUF;
        //程序自动下载
        if(res == 0x7F || res == 0x80)
        {
            if(dwon_count++ > 20)
                IAP_CONTR = 0x60;
        }
        else
        {
            dwon_count = 0;
        }
    }
}

//UART2中断
void Uart2Isr() interrupt 8
{
    if (S2CON & 0x02)
    {
        S2CON &= ~0x02;
        busy[2] = 0;
    }
    if (S2CON & 0x01)
    {
        S2CON &= ~0x01;
        //S2BUF;

    }
}


//UART3中断
void Uart3Isr() interrupt 17
{
    if (S3CON & 0x02)
    {
        S3CON &= ~0x02;
        busy[3] = 0;
    }
    if (S3CON & 0x01)
    {
        S3CON &= ~0x01;
        //S3BUF;

    }
}


//UART4中断

void Uart4Isr() interrupt 18
{
    if (S4CON & 0x02)
    {
        S4CON &= ~0x02;
        busy[4] = 0;
    }
    if (S4CON & 0x01)
    {
        S4CON &= ~0x01;

        //S4BUF;

    }
}
//PCA周期定时器中断
void PCA_Isr() interrupt 7
{

    if(CCF0 == 1)
    {
        //清除中断标志位
        CCF0 = 0;
        //重载计数器
        CCAP0L = ccp_value[0];
        CCAP0H = ccp_value[0] >> 8;
        ccp_value[0] += pca_time_ms[0];


    }

    if(CCF1 == 1)
    {
        //清除中断标志位
        CCF1 = 0;
        //重载计数器
        CCAP1L = ccp_value[1];
        CCAP1H = ccp_value[1] >> 8;
        ccp_value[1] += pca_time_ms[1];

    }



//	PCA_2已做延时
//	if(CCF2 == 1)
//	{
//		//清除中断标志位
//		CCF2 = 0;
//		//重载计数器
//		CCAP2L = ccp_value[2];
//		CCAP2H = ccp_value[2] >> 8;
//		ccp_value[2] += pca_time_ms[2];
//	}

}



void INT0_Isr() interrupt 0
{

}
void INT1_Isr() interrupt 2
{

}
void INT2_Isr() interrupt 10
{

}
void INT3_Isr() interrupt 11
{

}

void INT4_Isr() interrupt 16
{

}


