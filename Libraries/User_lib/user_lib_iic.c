#include "headfile.h"
#include "user_lib_iic.h"

sbit USER_SDA = P1^4;
sbit USER_SCL = P1^5;
bit user_iic_busy;

#define I2C_S0	0x10
#define I2C_S1	0x20
#define EAXFR	  0x80
void I2C_Isr() interrupt 24
{
    char store;

    store = P_SW2;
    P_SW2 |= 0x80;
    if (I2CMSST & 0x40)
    {
        I2CMSST &= ~0x40;                       //清中断标志
        user_iic_busy = 0;
    }
    P_SW2 = store;
}
void user_iic_delay()
{
    int i;

    for (i=0; i<3000; i++)
    {
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }
}
void user_iic_Wait()
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}
void user_iic_Start()
{
    I2CMSCR = 0x01;                             //发送START命令
    user_iic_Wait();
}
void user_iic_SendData(char dat)
{
    I2CTXD = dat;                               //写数据到数据缓冲区
    I2CMSCR = 0x02;                             //发送SEND命令
    user_iic_Wait();
}
void user_iic_RecvACK()
{
    I2CMSCR = 0x03;                             //发送读ACK命令
    user_iic_Wait();
}
char user_iic_RecvData()
{
    I2CMSCR = 0x04;                             //发送RECV命令
    user_iic_Wait();
    return I2CRXD;
}
void suer_iic_SendACK()
{
    I2CMSST = 0x00;                             //设置ACK信号
    I2CMSCR = 0x05;                             //发送ACK命令
    user_iic_Wait();
}

void user_iic_SendNAK()
{
    I2CMSST = 0x01;                             //设置NAK信号
    I2CMSCR = 0x05;                             //发送ACK命令
    user_iic_Wait();
}
void user_iic_Stop()
{
    I2CMSCR = 0x06;                             //发送STOP命令
    user_iic_Wait();
}
void user_iic_init()
{
  
	pca_delay_ms(100);
	I2CCFG|=0x40;//使能I2C功能
	I2CCFG|=0x20;//使能I2C主模式
	I2CCFG&=0xc0;
	I2CCFG|=0x08;//I2C 频率400KHZ
  I2CMSST = 0x00;	//清除I2C总线忙碌标志
		
}

void user_iic_write_reg(uint8 dev_add, uint8 reg, uint8 dat)//设备地址，寄存器地址，发送数据
{
	  P_SW2 = 0x80;
    user_iic_Start();                                    //发送起始命令
    user_iic_SendData(dev_add);                             //发送设备地址+写命令
    user_iic_RecvACK();
    user_iic_SendData(reg);                             //发送存储地址高字节
    user_iic_RecvACK();
    user_iic_SendData(dat);                             //发送存储地址低字节
    user_iic_RecvACK();
    user_iic_Stop();
	  P_SW2 = 0x00;//关闭访问扩展SFR 
}