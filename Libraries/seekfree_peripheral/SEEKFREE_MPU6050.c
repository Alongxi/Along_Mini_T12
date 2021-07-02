/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		MPU6050
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.28
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 * @note
					���߶��壺
					------------------------------------
						����IIC
                        SCL                 �鿴SEEKFREE_IIC�ļ��ڵ�SEEKFREE_SCL�궨��
						SDA                 �鿴SEEKFREE_IIC�ļ��ڵ�SEEKFREE_SDA�궨��
					------------------------------------
 ********************************************************************************************************************/
#include "headfile.h"

#include "SEEKFREE_IIC.h"
#include "SEEKFREE_MPU6050.h"
#include "zf_pca_delay.h"
#include "SEEKFREE_FONT.h"
#include "user_menu.h"


#define SOFTWARE_IIC
/*********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
	#ifdef SOFTWARE_IIC
    simiic_write_reg(OLED_ADDRESS,0x00, IIC_Command);
	#endif
	
	#ifdef HARDWARE_IIC
	user_iic_write_reg(OLED_ADDRESS_HARDWARE, 0x00,IIC_Command);
	#endif
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
	#ifdef SOFTWARE_IIC
    simiic_write_reg(OLED_ADDRESS,0x40, IIC_Data);
	#endif
	
	#ifdef HARDWARE_IIC
	user_iic_write_reg(OLED_ADDRESS_HARDWARE,0x40,IIC_Data);
	#endif
}
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
    if(cmd)
    {
        Write_IIC_Data(dat);
    }
    else
    {
        Write_IIC_Command(dat);
    }
}
/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
    unsigned char m,n;
    for(m=0; m<8; m++)
    {
        OLED_WR_Byte(0xb0+m,0);		//page0-page1
        OLED_WR_Byte(0x00,0);		//low column start address
        OLED_WR_Byte(0x10,0);		//high column start address
        for(n=0; n<128; n++)
        {
            OLED_WR_Byte(fill_Data,1);
        }
    }
}
//��������

void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f),OLED_CMD);
}
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!
void OLED_Clear(void)
{
    uint8 i,n;
    for(i=0; i<8; i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
        OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
        OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ
        for(n=0; n<128; n++)OLED_WR_Byte(0,OLED_DATA);
    } //������ʾ
}
void OLED_On(void)
{
    uint8 i,n;
    for(i=0; i<8; i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
        OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
        OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ
        for(n=0; n<128; n++)OLED_WR_Byte(1,OLED_DATA);
    } //������ʾ
}

void OLED_ShowChar(uint8 x,uint8 y,uint8 chr,uint8 Char_Size)
{
    unsigned char c=0,i=0;
    c=chr-' ';//�õ�ƫ�ƺ��ֵ
    if(x>Max_Column-1) {
        x=0;
        y=y+2;
    }

    if(select_flag == 0)
    {
        if(Char_Size ==16)
        {
            OLED_Set_Pos(x,y);
            for(i=0; i<8; i++)
                OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
            OLED_Set_Pos(x,y+1);
            for(i=0; i<8; i++)
                OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
        }
        else {
            OLED_Set_Pos(x,y);
            for(i=0; i<6; i++)
                OLED_WR_Byte(F6x8[c][i],OLED_DATA);

        }
    }
    else
    {
        if(Char_Size ==16)
        {
            OLED_Set_Pos(x,y);
            for(i=0; i<8; i++)
                OLED_WR_Byte(~F8X16[c*16+i],OLED_DATA);
            OLED_Set_Pos(x,y+1);
            for(i=0; i<8; i++)
                OLED_WR_Byte(~F8X16[c*16+i+8],OLED_DATA);
        }
        else {
            OLED_Set_Pos(x,y);
            for(i=0; i<6; i++)
                OLED_WR_Byte(~F6x8[c][i],OLED_DATA);

        }
    }
}
void OLED_P8x16Str(uint8 x,uint8 y,uint8 ch[])
{
    uint8 c=0,i=0,j=0;

    while (ch[j]!='\0')
    {
        c =ch[j]-32;
        if(x > 122) {
            x=0;
            y++;
        }
        OLED_Set_Pos(x,y);
        for(i=0; i<8; i++)
            OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
        OLED_Set_Pos(x,y+1);
        for(i=0; i<8; i++)
            OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
        x+=8;
        j++;
    }
}
//m^n����
uint32 oled_pow(uint8 m,uint8 n)
{
    uint32 result=1;
    while(n--)result*=m;
    return result;
}
//��ʾ2������
//x,y :�������
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);
void OLED_ShowNum(uint8 x,uint8 y,uint32 num,uint8 len,uint8 size2)
{
    uint8 t,temp;
    uint8 enshow=0;
    for(t=0; t<len; t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
                continue;
            } else enshow=1;

        }
        OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2);
    }
}
//��ʾһ���ַ��Ŵ�
void OLED_ShowString(uint8 x,uint8 y,uint8 *chr,uint8 Char_Size)
{
    unsigned char j=0;
    while (chr[j]!='\0')
    {   OLED_ShowChar(x,y,chr[j],Char_Size);
        if(Char_Size == 16)
        {
            x+=8;
        }
        else
        {
            x+=6;
        }
        if(x>120) {
            x=0;
            y+=2;
        }
        j++;
    }
}

/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{
    unsigned int j=0;
    unsigned char x,y;

    if(y1%8==0) y=y1/8;
    else y=y1/8+1;
    for(y=y0; y<y1; y++)
    {
        OLED_Set_Pos(x0,y);
        for(x=x0; x<x1; x++)
        {
            OLED_WR_Byte(BMP[j++],OLED_DATA);
        }
    }
}

//��ʼ��SSD1306
void OLED_Init(void)
{
    //pca_delay_ms(100);
    OLED_WR_Byte(0xAE,OLED_CMD);//�ر���ʾ

    OLED_WR_Byte(0x40,OLED_CMD);//---set low column address
    OLED_WR_Byte(0xB0,OLED_CMD);//---set high column address

    OLED_WR_Byte(0xC0,OLED_CMD);//-not offset

    OLED_WR_Byte(0x81,OLED_CMD);//���öԱȶ�
    OLED_WR_Byte(0xff,OLED_CMD);//���ȵ���

    OLED_WR_Byte(0xa0,OLED_CMD);//���ض�������  a1    a0
    OLED_WR_Byte(0xC0,OLED_CMD);//-not offset   c8    c0

    OLED_WR_Byte(0xa6,OLED_CMD);//

    OLED_WR_Byte(0xa8,OLED_CMD);//��������·��
    OLED_WR_Byte(0x1f,OLED_CMD);//����32��

    OLED_WR_Byte(0xd3,OLED_CMD);
    OLED_WR_Byte(0x00,OLED_CMD);

    OLED_WR_Byte(0xd5,OLED_CMD);
    OLED_WR_Byte(0xf0,OLED_CMD);

    OLED_WR_Byte(0xd9,OLED_CMD);
    OLED_WR_Byte(0x22,OLED_CMD);

    OLED_WR_Byte(0xda,OLED_CMD);
    OLED_WR_Byte(0x02,OLED_CMD);

    OLED_WR_Byte(0xdb,OLED_CMD);
    OLED_WR_Byte(0x49,OLED_CMD);

    OLED_WR_Byte(0x8d,OLED_CMD);
    OLED_WR_Byte(0x14,OLED_CMD);

    OLED_WR_Byte(0xaf,OLED_CMD);
    OLED_Clear();
}
/******************************************************************************
* ��  �� : ��ʾ20*40һ���׼ASCII�ַ���
* ��  �� : x:��0~127��y:ҳ��ַ0~7��
* ����ֵ : ��
******************************************************************************/
void OLED_P16x32Str(uint8 x, uint8 y, uint8 N)
{
    uint8 i=0;
    unsigned int adder=64*N;
    int yCount;
    OLED_Set_Pos(x, y);
    for (yCount = 0; yCount < 4; yCount++ )
    {
        OLED_Set_Pos(x, y);
        for ( i = 0; i < 16; i++ )
        {
            OLED_WR_Byte(F16x32[adder],OLED_DATA);
            adder += 1;
        }
        y++;
    }

}


void Draw_IMG24x24(uint8 x, uint8 y, uint8 N)
{
    uint8 i=0;
    unsigned int adder=72*N;
    int yCount;
    OLED_Set_Pos(x, y);
    for (yCount = 0; yCount < 3; yCount++ )
    {
        OLED_Set_Pos(x, y);
        for ( i = 0; i < 24; i++ )
        {
            OLED_WR_Byte(IMG24X24[adder],OLED_DATA);
            adder += 1;
        }
        y++;
    }

}
void Draw_IMG48x32(uint8 x, uint8 y, uint8 N)
{
    uint8 i=0;
    unsigned int adder=192*N;
    int yCount;
    OLED_Set_Pos(x, y);
    for (yCount = 0; yCount < 4; yCount++ )
    {
        OLED_Set_Pos(x, y);
        for ( i = 0; i < 48; i++ )
        {
            OLED_WR_Byte(IMG48X32[adder],OLED_DATA);
            adder += 1;
        }
        y++;
    }

}
void fill_24x1(uint8 x, uint8 y)//���24x1��
{
    int yCount;
    for (yCount = 0; yCount < 3; yCount++ )
    {
        OLED_Set_Pos(x, y);
        OLED_WR_Byte(0x00,OLED_DATA);

        y++;
    }
}

void fill_24x10(int8 x, int8 y)//���24x10��
{
    uint8 i=0;
    unsigned int adder=0;
    int yCount;
    if(x < 0)
    {

    }
    else if((x>0)&&(x<54))
    {
        OLED_Set_Pos(x, y);
        for (yCount = 0; yCount < 3; yCount++ )
        {
            OLED_Set_Pos(y, y);
            for ( i = 0; i < 10; i++ )
            {
                OLED_WR_Byte(0x00,OLED_DATA);
                adder += 1;
            }
            y++;
        }
    }
    else if(x > 54)
    {

    }
}
/*
void Draw_IMG24x24(int8 x, int8 y, uint8 N)
{
    uint8 i=0;
    unsigned int adder;
    int yCount;
    if((x >= 0)&&(x < 40))
    {
        adder=72*N;
        OLED_Set_Pos(x, y);
        for (yCount = 0; yCount < 3; yCount++ )
        {
            OLED_Set_Pos(x, y);
            for ( i = 0; i < 24; i++ )
            {
                OLED_WR_Byte(IMG24X24[adder],OLED_DATA);
                adder += 1;
            }
            y++;
        }
    }
    else if(x < 0)
    {
        adder=72*N -x;
        OLED_Set_Pos(0, y);
        for (yCount = 0; yCount < 3; yCount++ )
        {
            OLED_Set_Pos(0, y);

            for ( i = 0; i < 24+x; i++ )
            {
                OLED_WR_Byte(IMG24X24[adder],OLED_DATA);
                adder += 1;
            }
            adder += -x;
            y++;
        }
    }
    else if(x >=40)
    {
        adder=72*N;
        OLED_Set_Pos(x, y);
        for (yCount = 0; yCount < 3; yCount++ )
        {
            OLED_Set_Pos(x, y);
            for ( i = 0; i < 64-x; i++ )
            {
                OLED_WR_Byte(IMG24X24[adder],OLED_DATA);
                adder += 1;
            }
            adder += x-40;
            y++;
        }
    }


}
*/

void Draw_IMG34x24(int8 x, int8 y, uint8 N)
{
    uint8 i=0;
    unsigned int adder;
    int yCount;
    if((x >= 0)&&(x < 30))
    {
        adder=102*N;
        OLED_Set_Pos(x, y);
        for (yCount = 0; yCount < 3; yCount++ )
        {
            OLED_Set_Pos(x, y);
            for ( i = 0; i < 34; i++ )
            {
                OLED_WR_Byte(IMG34X24[adder],OLED_DATA);
                adder += 1;
            }
            y++;
        }
    }
    else if(x < 0)
    {
        adder=102*N -x;
        OLED_Set_Pos(0, y);
        for (yCount = 0; yCount < 3; yCount++ )
        {
            OLED_Set_Pos(0, y);

            for ( i = 0; i < 34+x; i++ )
            {
                OLED_WR_Byte(IMG34X24[adder],OLED_DATA);
                adder += 1;
            }
            adder += -x;
            y++;
        }
    }
    else if(x >=30)
    {
        adder=102*N;
        OLED_Set_Pos(x, y);
        for (yCount = 0; yCount < 3; yCount++ )
        {
            OLED_Set_Pos(x, y);
            for ( i = 0; i < 64-x; i++ )
            {
                OLED_WR_Byte(IMG34X24[adder],OLED_DATA);
                adder += 1;
            }
            adder += x-30;
            y++;
        }
    }


}
void Draw_IMG42X32(int8 x, int8 y, uint8 N)//�����Χ������x=0-64
{
    uint8 i=0;
    unsigned int adder;
    int yCount;
    if((x >= 0)&&(x < 22))
    {
        adder=168*N;
        OLED_Set_Pos(x, y);
        for (yCount = 0; yCount < 4; yCount++ )
        {
            OLED_Set_Pos(x, y);
            for ( i = 0; i < 42; i++ )
            {
                OLED_WR_Byte(IMG42X32[adder],OLED_DATA);
                adder += 1;
            }
            y++;
        }
    }
    else if(x < 0)
    {
        adder=168*N -x;
        OLED_Set_Pos(0, y);
        for (yCount = 0; yCount < 4; yCount++ )
        {
            OLED_Set_Pos(0, y);

            for ( i = 0; i < 42+x; i++ )
            {
                OLED_WR_Byte(IMG42X32[adder],OLED_DATA);
                adder += 1;
            }
            adder += -x;
            y++;
        }
    }
    else if(x >=22)
    {
        adder=168*N;
        OLED_Set_Pos(x, y);
        for (yCount = 0; yCount < 4; yCount++ )
        {
            OLED_Set_Pos(x, y);
            for ( i = 0; i < 64-x; i++ )
            {
                OLED_WR_Byte(IMG42X32[adder],OLED_DATA);
                adder += 1;
            }
            adder += x-22;
            y++;
        }
    }


}
void show_IMG16x16(uint8 x, uint8 y, uint8 N)
{
    uint8 i=0;
    int yCount;
    uint8 adder=0;
    OLED_Set_Pos(x, y);
    for (yCount = 0; yCount < 2; yCount++ )
    {
        OLED_Set_Pos(x, y);
        for ( i = 0; i < 16; i++ )
        {
            OLED_WR_Byte(IMG16X16[N][adder],OLED_DATA);
            adder += 1;
        }
        y++;
    }

}
void show_temp(uint8 x,uint16 temp)
{
    uint8 temp_data[3];
    temp_data[0] = temp/100%10;
    temp_data[1] = temp/10%10;
    temp_data[2] = temp%10;

if(auto_power_off_flag == 0)//���ϵͳû�����ػ�
{
    if(iron_ad < IRON_PARM_600)
    {

        //show_IMG16x16(x+48,0,4);//��
        if(((uint8)adc_vin_get() < LOW_BATTERY_VOLTAGE)&&(LOW_BATTERY_ON_FLAG == 1))
        {
            Draw_IMG48x32(x,0,1);//
            Draw_IMG24x24(x+48,0,1);//��
        }
        else
        {
            OLED_P16x32Str(x,0,temp_data[0]);//��ʾ��λ
            OLED_P16x32Str(x+16,0,temp_data[1]);//ʮλ
            OLED_P16x32Str(x+32,0,temp_data[2]);//��λ
            Draw_IMG24x24(x+48,0,0);
        }

    }
    else
    {
        Draw_IMG48x32(x,0,0);//
        if(((uint8)adc_vin_get() < LOW_BATTERY_VOLTAGE)&&(LOW_BATTERY_ON_FLAG == 1))
        {

            Draw_IMG24x24(x+48,0,2);//�͵�ѹ
        }
        else
        {
            
            Draw_IMG24x24(x+48,0,1);
        }

    }
	}
else//���ϵͳ�������ػ�
{
	Draw_IMG24x24(x+48,0,3);//���ػ�
	Draw_IMG48x32(x,0,2);//���ػ�����
}
	

}

void show_set_temp(uint8 x,uint8 y,uint16 temp)
{
    OLED_ShowNum(x,y,temp,3,16);//��ʾ3λ���� 16
}
/******************************************************************************
* ��  �� : ��ʾ104*8������
* ��  �� : x:��0~127��y:ҳ��ַ0~7��
* ����ֵ : ��
******************************************************************************/
void show_IMG56x8(uint8 x, uint8 y,uint8 percent)
{
    uint8 j;
    uint8 nember_data[3];
    nember_data[0] = percent/100%10;
    nember_data[1] = percent/10%10;
    nember_data[2] = percent%10;
    OLED_Set_Pos(x, y);
    for(j = 0; j < 56; j++)
    {
        if((j>=3)&&(j<=53))
        {
            if(percent/2 >j-3)
            {
                OLED_WR_Byte(0xBD,OLED_DATA);
            }
            else
            {
                OLED_WR_Byte(0x81,OLED_DATA);
            }
        }
        else
        {
            OLED_WR_Byte(IMG_56x8[j],OLED_DATA);
        }
    }
    OLED_ShowNum(x+32,y-1,nember_data[0],1,12);
    OLED_ShowNum(x+38,y-1,nember_data[1],1,12);
    OLED_ShowNum(x+44,y-1,nember_data[2],1,12);
    OLED_ShowString(x+50,y-1,"%",8);

}

/*
* ����16X16��
*/
void OLED_CH16Str(uint8 x,uint8 y,uint8 ch[])
{
    uint8 str_offset = 0,ii = 0;//
    uint32 adder = 1; //�������Ӧ�����

    while(ch[ii] != '\0')//�����ַ�������Ƿ��β
    {
        str_offset = 0;	//�����ַ�ƫ����
        adder = 1;		//��ʼ��
        /*
        * 	���㺺���������
        */
        while(CHINESE_Idx[str_offset] > 127)//�ж��Ƿ�Ϊ���ֵ�ASCII��ֵ
        {
            if(CHINESE_Idx[str_offset] == ch[ii])
            {
                if(CHINESE_Idx[str_offset + 1] == ch[ii + 1])
                {
                    adder = str_offset * 16;//adder ��ȡ
                    break;//
                }
            }
            str_offset += 2;//	ƫ������
        }
        if(x>122) {
            x=0;
            y+=2;
        }
        OLED_Set_Pos(x, y);
        if(adder != 1)// ��ʾ����
        {
            OLED_Set_Pos(x, y); //��ǰ����ʾ
            for(str_offset = 0; str_offset < 16; str_offset++)
            {
                OLED_WR_Byte(CH_16[adder],OLED_DATA);//
                adder += 1;
            }
            OLED_Set_Pos(x,y + 1); //������ʾ
            for(str_offset = 0; str_offset < 16; str_offset++)
            {
                OLED_WR_Byte(CH_16[adder],OLED_DATA);
                adder += 1;
            }
        }
        else			  //��ʾ�հ��ַ�
        {
            ii += 1;
            OLED_Set_Pos(x,y);
            for(str_offset = 0; str_offset < 16; str_offset++)
            {
                OLED_WR_Byte(0,OLED_DATA);
            }
            OLED_Set_Pos(x,y + 1);
            for(str_offset = 0; str_offset < 16; str_offset++)
            {
                OLED_WR_Byte(0,OLED_DATA);
            }
        }
        x += 16;//��ʾX����ƫ��
        ii += 2;//����ռ2���ֽ�
    }
}
//��������ַ���
void OLED_Print(uint8 x, uint8 y, uint8 ch[])
{
    uint8 buff[3];
    uint32 ii=0;

    while(ch[ii] != '\0')//�ж���ʾ�ַ��Ƿ��β
    {
        if(ch[ii] > 127)//�ж�->����ASCII����
        {
            buff[0] = ch[ii];
            buff[1] = ch[ii + 1];
            buff[2] = '\0';			//����Ϊ�����ֽ�
            OLED_CH16Str(x, y, buff);	//��ʾ����
            x += 16;//��ʾƫ������
            ii += 2;//����ƫ��
        }
        else//�ж�->��ĸASCII
        {
            buff[0] = ch[ii];
            buff[1] = '\0';			//��ĸռһ���ֽ�
            OLED_P8x16Str(x, y, buff);	//��ʾ��ĸ
            x += 8;//��ʾƫ������
            ii+= 1;//����ƫ��
        }
    }
}
void Draw_IMG42X32_limit(int8 x, int8 y, uint8 N,uint8 mode)//�����Χ������x=0-64   y������0-3
{
    uint8 i=0;
    unsigned int adder;
    uint8 y_now = 0;
    int yCount;
    if(mode == 0)
    {
        if((x >= 0)&&(x < 22))
        {
            adder=168*N;
            OLED_Set_Pos(x, y);
            for (yCount = 0; yCount < 4; yCount++ )
            {
                OLED_Set_Pos(x, y);
                for ( i = 0; i < 42; i++ )
                {
                    OLED_WR_Byte(IMG42X32[adder],OLED_DATA);
                    adder += 1;
                }
                y++;
            }
        }
        else if(x < 0)
        {
            adder=168*N -x;
            OLED_Set_Pos(0, y);
            for (yCount = 0; yCount < 4; yCount++ )
            {
                OLED_Set_Pos(0, y);

                for ( i = 0; i < 42+x; i++ )
                {
                    OLED_WR_Byte(IMG42X32[adder],OLED_DATA);
                    adder += 1;
                }
                adder += -x;
                y++;
            }
        }
        else if(x >=22)
        {
            adder=168*N;
            OLED_Set_Pos(x, y);
            for (yCount = 0; yCount < 4; yCount++ )
            {
                OLED_Set_Pos(x, y);
                for ( i = 0; i < 64-x; i++ )
                {
                    OLED_WR_Byte(IMG42X32[adder],OLED_DATA);
                    adder += 1;
                }
                adder += x-22;
                y++;
            }
        }
    }
    else if(mode == 1)
    {
        adder=168*N;
        if(y < 0)
        {
            OLED_Set_Pos(x, 0);
            adder = adder +42*(-y);
            for (yCount = 0; yCount < 4+y; yCount++ )
            {
                OLED_Set_Pos(x, y_now);

                for ( i = 0; i < 42; i++ )
                {
                    OLED_WR_Byte(IMG42X32[adder],OLED_DATA);
                    adder += 1;
                }
                y_now++;
            }
        }
        else if(y == 0)
        {
            OLED_Set_Pos(x, y);
            for (yCount = 0; yCount < 4; yCount++ )
            {
                OLED_Set_Pos(x, y);
                for ( i = 0; i < 42; i++ )
                {
                    OLED_WR_Byte(IMG42X32[adder],OLED_DATA);
                    adder += 1;
                }
                y++;
            }
        }
        else if(y > 0)
        {
            OLED_Set_Pos(x, y);
            y_now = y;
            for (yCount = 0; yCount < 4-y; yCount++ )
            {
                OLED_Set_Pos(x, y_now);
                for ( i = 0; i < 42; i++ )
                {
                    OLED_WR_Byte(IMG42X32[adder],OLED_DATA);
                    adder += 1;
                }
                y_now++;
            }
        }
    }

}
/*
* ����16X16��
*/
void ROW_OLED_CH16Str(int8 x,int8 y,uint8 ch[])//���ֹ���
{
    int yCount;
    uint8 str_offset = 0,ii = 0;//
    uint32 adder = 1; //�������Ӧ�����
    //uint8 y_now = 0;
    uint8 i = 0;
    while(ch[ii] != '\0')//�����ַ�������Ƿ��β
    {
        str_offset = 0;	//�����ַ�ƫ����
        adder = 1;		//��ʼ��
        /*
        * 	���㺺���������
        */
        while(CHINESE_Idx[str_offset] > 127)//�ж��Ƿ�Ϊ���ֵ�ASCII��ֵ
        {
            if(CHINESE_Idx[str_offset] == ch[ii])
            {
                if(CHINESE_Idx[str_offset + 1] == ch[ii + 1])
                {
                    adder = str_offset * 16;//adder ��ȡ
                    break;//
                }
            }
            str_offset += 2;//	ƫ������
        }
        if(x>122) {
            x=0;
            y++;
        }


        if(y == -1)
        {
            OLED_Set_Pos(x, 0);

            if(adder != 1)
            {
                adder = adder +16;

                OLED_Set_Pos(x, 0);
                for ( i = 0; i < 16; i++ )
                {
                    OLED_WR_Byte(CH_16[adder],OLED_DATA);
                    adder += 1;
                }

            }
            else			  //��ʾ�հ��ַ�
            {
                ii += 1;

                OLED_Set_Pos(x, 0);
                for ( i = 0; i < 16; i++ )
                {
                    OLED_WR_Byte(0,OLED_DATA);
                    adder += 1;
                }

            }
        }
        else if(y == -2)
        {

        }
        else if(y == 0)
        {
            OLED_Set_Pos(x, y);
            if(adder != 1)// ��ʾ����
            {
                OLED_Set_Pos(x, y); //��ǰ����ʾ
                for(str_offset = 0; str_offset < 16; str_offset++)
                {
                    OLED_WR_Byte(CH_16[adder],OLED_DATA);//
                    adder += 1;
                }
                OLED_Set_Pos(x,y + 1); //������ʾ
                for(str_offset = 0; str_offset < 16; str_offset++)
                {
                    OLED_WR_Byte(~CH_16[adder],OLED_DATA);
                    adder += 1;
                }
            }
            else			  //��ʾ�հ��ַ�
            {
                ii += 1;
                OLED_Set_Pos(x,y);
                for(str_offset = 0; str_offset < 16; str_offset++)
                {
                    OLED_WR_Byte(0,OLED_DATA);
                }
                OLED_Set_Pos(x,y + 1);
                for(str_offset = 0; str_offset < 16; str_offset++)
                {
                    OLED_WR_Byte(0xff,OLED_DATA);
                }
            }
        }
        else if(y == 1)
        {
            OLED_Set_Pos(x, y);
            if(adder != 1)// ��ʾ����
            {
                for (yCount = 0; yCount < 2; yCount++ )
                {
                    OLED_Set_Pos(x, y);
                    for ( i = 0; i < 16; i++ )
                    {
                        OLED_WR_Byte(~CH_16[adder],OLED_DATA);
                        adder += 1;
                    }
                    y++;
                }

            }
            else			  //��ʾ�հ��ַ�
            {
                ii += 1;
                for (yCount = 0; yCount < 2; yCount++ )
                {
                    OLED_Set_Pos(x, y);
                    for ( i = 0; i < 16; i++ )
                    {
                        OLED_WR_Byte(0xff,OLED_DATA);
                        adder += 1;
                    }
                    y++;
                }
            }
        }
        else if(y == 2)
        {
            OLED_Set_Pos(x, y);
            if(adder != 1)// ��ʾ����
            {
                OLED_Set_Pos(x, y); //��ǰ����ʾ
                for(str_offset = 0; str_offset < 16; str_offset++)
                {
                    OLED_WR_Byte(~CH_16[adder],OLED_DATA);//
                    adder += 1;
                }
                OLED_Set_Pos(x,y + 1); //������ʾ
                for(str_offset = 0; str_offset < 16; str_offset++)
                {
                    OLED_WR_Byte(CH_16[adder],OLED_DATA);
                    adder += 1;
                }
            }
            else			  //��ʾ�հ��ַ�
            {
                ii += 1;
                OLED_Set_Pos(x,y);
                for(str_offset = 0; str_offset < 16; str_offset++)
                {
                    OLED_WR_Byte(0xff,OLED_DATA);
                }
                OLED_Set_Pos(x,y + 1);
                for(str_offset = 0; str_offset < 16; str_offset++)
                {
                    OLED_WR_Byte(0,OLED_DATA);
                }
            }
        }
        else
        {
            OLED_Set_Pos(x, y);
            if(adder != 1)// ��ʾ����
            {
                for (yCount = 0; yCount < 2; yCount++ )
                {
                    OLED_Set_Pos(x, y);
                    for ( i = 0; i < 16; i++ )
                    {
                        OLED_WR_Byte(CH_16[adder],OLED_DATA);
                        adder += 1;
                    }
                    y++;
                }

            }
            else			  //��ʾ�հ��ַ�
            {
                ii += 1;
                for (yCount = 0; yCount < 2; yCount++ )
                {
                    OLED_Set_Pos(x, y);
                    for ( i = 0; i < 16; i++ )
                    {
                        OLED_WR_Byte(0,OLED_DATA);
                        adder += 1;
                    }
                    y++;
                }
            }

        }
        x += 16;//��ʾX����ƫ��
        ii += 2;//����ռ2���ֽ�
    }
}

//�ɹ����ĺ����ַ���
void ROW_OLED_Print(int8 x, int8 y, uint8 ch[])
{
    uint8 buff[3];
    uint32 ii=0;

    while(ch[ii] != '\0')//�ж���ʾ�ַ��Ƿ��β
    {
        if(ch[ii] > 127)//�ж�->����ASCII����
        {
            buff[0] = ch[ii];
            buff[1] = ch[ii + 1];
            buff[2] = '\0';			//����Ϊ�����ֽ�
            ROW_OLED_CH16Str(x, y, buff);	//��ʾ����
            x += 16;//��ʾƫ������
            ii += 2;//����ƫ��
        }
        else//�ж�->��ĸASCII
        {
            buff[0] = ch[ii];
            buff[1] = '\0';			//��ĸռһ���ֽ�
            ROW_OLED_CH16Str(x, y, buff);	//��ʾ��ĸ
            x += 8;//��ʾƫ������
            ii+= 1;//����ƫ��
        }
    }

}
void OLED_CH16_Str(uint8 x, uint8 y, uint8 N)
{
    uint8 i=0;
    unsigned int adder=32*N;
    int yCount;
    OLED_Set_Pos(x, y);
    for (yCount = 0; yCount < 2; yCount++ )
    {
        OLED_Set_Pos(x, y);
        for ( i = 0; i < 16; i++ )
        {
            OLED_WR_Byte(CH_16[adder],OLED_DATA);
            adder += 1;
        }
        y++;
    }

}
//
//���ܣ���ʾ�����ַ�chuan
//���壺page_floor���ڶ��ټ��˵�  page_num���ڼ����˵�
//
void OLED_CH16_Char(uint8 x, uint8 y,uint8 page_floor,uint8 page_one_numb,uint8 page_two_numb)//��ʾ�ַ���
{
    uint8 page_center_data[4] = {0};
    int i = 0;
    for(i = 0; i < 4; i++)
    {
        if(page_floor == 1)
        {
            page_center_data[i] = page_one_num[page_one_numb][i];
            OLED_CH16_Str(x,y,page_center_data[i]);
            x += 16;
        }
        else if(page_floor == 2)
        {
            page_center_data[i] = page_two_num[page_one_numb][page_two_numb][i];
            OLED_CH16_Str(x,y,page_center_data[i]);
            x += 16;
        }
    }

}


