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
        I2CMSST &= ~0x40;                       //���жϱ�־
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
    I2CMSCR = 0x01;                             //����START����
    user_iic_Wait();
}
void user_iic_SendData(char dat)
{
    I2CTXD = dat;                               //д���ݵ����ݻ�����
    I2CMSCR = 0x02;                             //����SEND����
    user_iic_Wait();
}
void user_iic_RecvACK()
{
    I2CMSCR = 0x03;                             //���Ͷ�ACK����
    user_iic_Wait();
}
char user_iic_RecvData()
{
    I2CMSCR = 0x04;                             //����RECV����
    user_iic_Wait();
    return I2CRXD;
}
void suer_iic_SendACK()
{
    I2CMSST = 0x00;                             //����ACK�ź�
    I2CMSCR = 0x05;                             //����ACK����
    user_iic_Wait();
}

void user_iic_SendNAK()
{
    I2CMSST = 0x01;                             //����NAK�ź�
    I2CMSCR = 0x05;                             //����ACK����
    user_iic_Wait();
}
void user_iic_Stop()
{
    I2CMSCR = 0x06;                             //����STOP����
    user_iic_Wait();
}
void user_iic_init()
{
  
	pca_delay_ms(100);
	I2CCFG|=0x40;//ʹ��I2C����
	I2CCFG|=0x20;//ʹ��I2C��ģʽ
	I2CCFG&=0xc0;
	I2CCFG|=0x08;//I2C Ƶ��400KHZ
  I2CMSST = 0x00;	//���I2C����æµ��־
		
}

void user_iic_write_reg(uint8 dev_add, uint8 reg, uint8 dat)//�豸��ַ���Ĵ�����ַ����������
{
	  P_SW2 = 0x80;
    user_iic_Start();                                    //������ʼ����
    user_iic_SendData(dev_add);                             //�����豸��ַ+д����
    user_iic_RecvACK();
    user_iic_SendData(reg);                             //���ʹ洢��ַ���ֽ�
    user_iic_RecvACK();
    user_iic_SendData(dat);                             //���ʹ洢��ַ���ֽ�
    user_iic_RecvACK();
    user_iic_Stop();
	  P_SW2 = 0x00;//�رշ�����չSFR 
}