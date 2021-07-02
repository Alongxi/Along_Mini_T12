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

#include "zf_iic.h"



//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ�ʹ���û��������
//  @param      NULL            	
//  @return     void
//  Sample usage:               �����û����ã��û���ʹ��h�ļ��еĺ궨��
//-------------------------------------------------------------------------------------------------------------------
void iic_delay_us(uint16 x)	//33.1776Mhz
{
    uint8 i;
    while(x--)
    {
		i = 9;
		while (--i);
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ�ʹ���û��������
//  @param      NULL            	
//  @return     void
//  Sample usage:               �����û����ã��û���ʹ��h�ļ��еĺ궨��
//-------------------------------------------------------------------------------------------------------------------
uint8 wait(void)
{
    uint16 count = 0;
    uint8 ret = IIC_SEND_OK;
    while (!(I2CMSST & 0x40))
    {
        iic_delay_us(1);
        if(count++ >= 30)//�ȴ�����30us�����˳��ȴ���
        {
            ret = IIC_SEND_FAIL;
            break;
        }
    }
    I2CMSST &= ~0x40;
    return ret;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ�ʹ���û��������
//  @param      NULL            	
//  @return     void
//  Sample usage:               �����û����ã��û���ʹ��h�ļ��еĺ궨��
//-------------------------------------------------------------------------------------------------------------------
uint8 start(void)
{
    uint8 ret;
    I2CMSCR = 0x01;                             //����start����
    ret = wait();
    return ret;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ�ʹ���û��������
//  @param      NULL            	
//  @return     void
//  Sample usage:               �����û����ã��û���ʹ��h�ļ��еĺ궨��
//-------------------------------------------------------------------------------------------------------------------
uint8 send_data(char dat)
{
    uint8 ret;
    I2CTXD = dat;                               //д���ݵ����ݻ�����
    I2CMSCR = 0x02;                             //����SEND����
    ret = wait();
    return ret;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ�ʹ���û��������
//  @param      NULL            	
//  @return     void
//  Sample usage:               �����û����ã��û���ʹ��h�ļ��еĺ궨��
//-------------------------------------------------------------------------------------------------------------------
uint8 recv_ack(void)
{
    uint8 ret;
    I2CMSCR = 0x03;                             //���Ͷ�ACK����
    ret = wait();
    return ret;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ�ʹ���û��������
//  @param      NULL            	
//  @return     void
//  Sample usage:               �����û����ã��û���ʹ��h�ļ��еĺ궨��
//-------------------------------------------------------------------------------------------------------------------
char recv_data(void)							//��������
{
    I2CMSCR = 0x04;                             //����RECV����
    wait();
    return I2CRXD;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ�ʹ���û��������
//  @param      NULL            	
//  @return     void
//  Sample usage:               �����û����ã��û���ʹ��h�ļ��еĺ궨��
//-------------------------------------------------------------------------------------------------------------------
uint8 send_ack(void)
{
	uint8 ret;
    I2CMSST = 0x00;                             //����ACK�ź�
    I2CMSCR = 0x05;                             //����ACK����
    ret = wait();
    return ret;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ�ʹ���û��������
//  @param      NULL            	
//  @return     void
//  Sample usage:               �����û����ã��û���ʹ��h�ļ��еĺ궨��
//-------------------------------------------------------------------------------------------------------------------
void send_nak(void)
{
    I2CMSST = 0x01;                             //����NAK�ź�
    I2CMSCR = 0x05;                             //����ACK����
    wait();
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      �ڲ�ʹ���û��������
//  @param      NULL            	
//  @return     void
//  Sample usage:               �����û����ã��û���ʹ��h�ļ��еĺ궨��
//-------------------------------------------------------------------------------------------------------------------
uint8 stop(void)
{
    uint8 ret;
    I2CMSCR = 0x06;                             //����stop����
    ret = wait();
    return ret;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Ӳ��IIC��ʼ��
//  @param      iic_n           ѡ��IICģ��
//  @param      wait_time       I2C�����ٶȣ��ȴ�ʱ����������: �ٶ�����Ϊ�ȴ�wait_time*2+1��ʱ��
//  @return     void
//  Sample usage:               iic_init(IIC_SCL_P15_SDA_P14,0);//Ӳ��IIC��ʼ��     
//-------------------------------------------------------------------------------------------------------------------
void iic_init(IICN_enum iic_n, IIC_PIN_enum scl_pin, IIC_PIN_enum sda_pin, uint32 wait_time)
{
	scl_pin = scl_pin;
	sda_pin = sda_pin;
    P_SW2 &= ~(0x03<<4);
    P_SW2 |= 1<<7;	//��EAXFR�Ĵ�����1����������ʹ�����⹦�ܼĴ���Ϊ��չSFR�������߼���ַλ�� XDATA ����
    switch(iic_n)
    {
    case IIC_1:
        P_SW2 |= (0x00<<4);	//SCL:P1.5	SDA:P1.4
        break;
    case IIC_2:
        P_SW2 |= (0x01<<4);	//SCL:P2.5	SDA:P2.4
        break;
    case IIC_3:
        P_SW2 |= (0x02<<4);	//SCL:P7.7	SDA:P7.6
        break;
    case IIC_4:
        P_SW2 |= (0x03<<4);	//SCL:P3.2	SDA:P3.3
        break;
    }

    I2CCFG |= 1<<6;		//����ģʽ
    I2CCFG |= 1<<7;		//ʹ��IIC
    I2CCFG |= wait_time;//�ٶ�����Ϊ�ȴ�wait_time*2+1��ʱ��
    I2CMSST = 0x00;		//����״̬�Ĵ���
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      д��һ���ֽ����ݵ�I2C�豸ָ���Ĵ�����ַ
//  @param      iic_n       IICģ��(IIC_1,IIC_2,IIC_3,IIC_0)
//  @param      slaveid     �ӻ���ַ(7λ��ַ)
//  @param      reg         �ӻ��Ĵ�����ַ
//  @param      dat         ��Ҫ���͵�����
//  @return                 ���ص�״ֵ̬ 0���ɹ�  1��ʧ��
//  @since      v2.0
//  Sample usage:       	iic_write_reg(IIC_2, 0x2D, 0x50,2);     //д������2��0x50��ַ���ӻ���ַΪ0x2D
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_write_reg(IICN_enum iic_n, uint8 dev_add, uint8 reg, uint8 dat)
{
    P_SW2 &= ~(0x03<<4);
    switch(iic_n)
    {
    case IIC_1:
        P_SW2 |= (0x00<<4);	//SCL:P1.5	SDA:P1.4
        break;
    case IIC_2:
        P_SW2 |= (0x01<<4);	//SCL:P2.5	SDA:P2.4
        break;
    case IIC_3:
        P_SW2 |= (0x02<<4);	//SCL:P7.7	SDA:P7.6
        break;
    case IIC_4:
        P_SW2 |= (0x03<<4);	//SCL:P3.2	SDA:P3.3
        break;
    }

    if(start() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(send_data((dev_add<<1) | 0x00) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(send_data(reg) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(send_data(dat) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(stop() != IIC_SEND_OK)
        return IIC_SEND_FAIL;


    return IIC_SEND_OK;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡI2C�豸ָ����ַ�Ĵ���������
//  @param      iic_n        I2Cͨ���ż�����
//  @param      dev_add     �ӻ���ַ(7λ��ַ)
//  @param      reg         �ӻ��Ĵ�����ַ
//  @param      dat         ���ݵ�ַ
//  @return                 ��ȡ�ļĴ���ֵ
//  @since      v1.0
//  Sample usage:       	uint8 value = i2c_read_reg(i2c0, 0x2D, 0x50);//��ȡ0x50��ַ�����ݣ��ӻ���ַΪ0x2D
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_read_reg(IICN_enum iic_n, uint8 dev_add, uint8 reg, uint8 *dat)
{
	P_SW2 &= ~(0x03<<4);
    switch(iic_n)
    {
    case IIC_1:
        P_SW2 |= (0x00<<4);	//SCL:P1.5	SDA:P1.4
        break;
    case IIC_2:
        P_SW2 |= (0x01<<4);	//SCL:P2.5	SDA:P2.4
        break;
    case IIC_3:
        P_SW2 |= (0x02<<4);	//SCL:P7.7	SDA:P7.6
        break;
    case IIC_4:
        P_SW2 |= (0x03<<4);	//SCL:P3.2	SDA:P3.3
        break;
    }

	if(start() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
    if(send_data((dev_add<<1) | 0x00) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
    if(send_data(reg) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
	
//   if(start() != IIC_SEND_OK)
//        return IIC_SEND_FAIL;
   
    if(send_data((dev_add<<1) | 0x01) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
	*dat = recv_data();
	
    if(send_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
    if(stop() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
    return IIC_SEND_OK;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡI2C�豸ָ����ַ�Ĵ���������
//  @param      iic_n       I2Cͨ���ż�����
//  @param      dev_add     �ӻ���ַ(7λ��ַ)
//  @param      reg         �ӻ��Ĵ�����ַ
//  @param      dat         ��ȡ�����ݴ洢�ĵ�ַ
//  @param      num         ��ȡ�ֽ���
//  @return     void
//  @since      v1.0
//  Sample usage:       	uint8 value = i2c_read_reg(i2c0, 0x2D, 0x50, 10, buf);//��ȡ0x50��ַ�����ݣ��ӻ���ַΪ0x2D��ʼ��10���ֽ�
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_read_reg_bytes(IICN_enum iic_n, uint8 dev_add, uint8 reg
						, uint8 *dat, uint8 num)
{
	P_SW2 &= ~(0x03<<4);
    switch(iic_n)
    {
    case IIC_1:
        P_SW2 |= (0x00<<4);	//SCL:P1.5	SDA:P1.4
        break;
    case IIC_2:
        P_SW2 |= (0x01<<4);	//SCL:P2.5	SDA:P2.4
        break;
    case IIC_3:
        P_SW2 |= (0x02<<4);	//SCL:P7.7	SDA:P7.6
        break;
    case IIC_4:
        P_SW2 |= (0x03<<4);	//SCL:P3.2	SDA:P3.3
        break;
    }

	if(start() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
    if(send_data((dev_add<<1) | 0x00) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
    if(send_data(reg) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;

	if(send_data((dev_add<<1) | 0x01) != IIC_SEND_OK)
		return IIC_SEND_FAIL;
	if(recv_ack() != IIC_SEND_OK)
		return IIC_SEND_FAIL;

    while(--num)
    {
        *dat = recv_data(); //��ȡ����
		if(send_ack() != IIC_SEND_OK)
		{
			return IIC_SEND_FAIL;
		}
        dat++;
    }
	
	*dat = recv_data();
	
	if(send_ack() != IIC_SEND_OK)
		return IIC_SEND_FAIL;
	
	if(stop() != IIC_SEND_OK)
		return IIC_SEND_FAIL;
	
	return IIC_SEND_OK;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      Ӳ��IIC�����л�����
//  @param      iic_n       	I2Cͨ���ż�����
//  @param      scl_pin         ѡ��SCL����
//  @param      sda_pin         ѡ��SDA����
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void iic_change_pin(IICN_enum iic_n,IIC_PIN_enum scl_pin,IIC_PIN_enum sda_pin)
{
	scl_pin = scl_pin;
	sda_pin = sda_pin;
    P_SW2 |= 1<<7;	//��EAXFR�Ĵ�����1����������ʹ�����⹦�ܼĴ���Ϊ��չSFR�������߼���ַλ�� XDATA ����
	
	P_SW2 &= ~(0x03<<4);	//��������л�λ
    switch(iic_n)	
    {
    case IIC_1:
        P_SW2 |= (0x00<<4);	//SCL:P1.5	SDA:P1.4
        break;
    case IIC_2:
        P_SW2 |= (0x01<<4);	//SCL:P2.5	SDA:P2.4
        break;
    case IIC_3:
        P_SW2 |= (0x02<<4); //û�и�������
        break;
    case IIC_4:
        P_SW2 |= (0x03<<4);	//SCL:P3.2	SDA:P3.3
        break;
    }
	
	P_SW2 &= ~(1<<7);

}
