
#ifndef _SEEKFREE_MPU6050_h
#define _SEEKFREE_MPU6050_h

#include "common.h"

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define OLED_MODE 0

#define OLED_ADDRESS        (0x78>>1)  //OLED地址
#define OLED_ADDRESS_HARDWARE        0x78  //OLED地址
#define OLED_ADDRESS_LEN  1         //MPU6050地址长度
//OLED模式设置
//0:4线串行模式
//1:并行8080模式

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF
#define X_WIDTH 	128
#define Y_WIDTH 	64

void OLED_Init();
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_ShowCHinese(uint8 x,uint8 y,uint8 no);
void OLED_ShowString(uint8 x,uint8 y,uint8 *chr,uint8 Char_Size);
void OLED_ShowNum(uint8 x,uint8 y,uint32 num,uint8 len,uint8 size2);
uint32 oled_pow(uint8 m,uint8 n);
void OLED_P8x16Str(uint8 x,uint8 y,uint8 ch[]);
void OLED_ShowChar(uint8 x,uint8 y,uint8 chr,uint8 Char_Size);
void OLED_On(void);
void OLED_Clear(void);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void fill_picture(unsigned char fill_Data);
void Write_IIC_Data(unsigned char IIC_Data);

void OLED_P16x32Str(uint8 x, uint8 y, uint8 N);
void Draw_IMG48x32(uint8 x, uint8 y, uint8 N);
void fill_24x1(uint8 x, uint8 y);//清除24x1列
void fill_24x10(int8 x, int8 y);
void Draw_IMG24x24(int8 x, int8 y, uint8 N);
void Draw_IMG34x24(int8 x, int8 y, uint8 N);
void Draw_IMG42X32(int8 x, int8 y, uint8 N);

void show_IMG16x16(uint8 x, uint8 y, uint8 N);
void show_temp(uint8 x,uint16 temp);
void show_set_temp(uint8 x,uint8 y,uint16 temp);
void show_IMG56x8(uint8 x, uint8 y,uint8 percent);
void OLED_CH16Str(uint8 x,uint8 y,uint8 ch[]);
void OLED_Print(uint8 x, uint8 y, uint8 ch[]);
void Draw_IMG42X32_limit(int8 x, int8 y, uint8 N,uint8 mode);
void ROW_OLED_CH16Str(int8 x,int8 y,uint8 ch[]);//汉字滚动
void ROW_OLED_Print(int8 x, int8 y, uint8 ch[]);
void OLED_CH16_Str(uint8 x, uint8 y, uint8 N);
void OLED_CH16_Char(uint8 x, uint8 y,uint8 page_floor,uint8 page_one_numb,uint8 page_two_numb);


void OLED_WR_Byte(unsigned dat,unsigned cmd);
















#endif
