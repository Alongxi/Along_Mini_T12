#include "headfile.h"
#include "user_menu.h"

uint8 menu_flag = 0;//定义菜单的标志位，0：主界面 1：一级菜单 2：二级菜单
int8 page_flag = 0;//定义一个页面标志位， 0：第一个功能界面 1：第二个功能界面
uint8 select_flag = 0;//定义一个在二级菜单下是否确认的flag  0：未确认  1：已确认

int8 page_left = 0;
int8 page_center = 0;
int8 page_right = 0;
//-----------------------//
int8 last_left = 0;
int8 last_hide = 0;
int8 last_center = 0;
int8 last_right = 0;
//----------------------//
int8 page_2_up[page_max+1] = {0};
int8 page_2_center[page_max+1] = {0};
int8 page_2_down[page_max+1] = {0};
//----------------------//
uint8 icon_size_flag = 0;
uint8 row_derection = 1;//滚动方向
uint8 row_speed = 1;//滚动速率
//----------------------//
int8 row_flag = 0;//滚动标志位  -1为左移  1为右移
int8 BEEP_flag = 0;
int8 Strong_temp_flag = 0;//是否开启强温模式

uint8 TEMP_SET_INIT_FLAG = 1;

//0亮调节基础数据存储协,
//1议一二三四五六七阈值,
//2限零壹贰叁肆伍陆柒阶,
//3温滚动方向速率菜单冷
//4端补偿全局参数整定休
//5眠时间设置屏幕步度电
//6源管理焊咀校准图标大
//7小滚动上下分秒设比例
//8积分微反色显示翻转恢
//9复出厂进强初开始蜂鸣
//10音量开关于备欠压保护
//11机自动
uint8 code page_one_num[page_max+1][4] =
{
    {45,46,47,48},//  "参数整定",
    {55,56,53,54},//  "屏幕设置",
    {3, 4,53,54}, //  "基础设置",
    {49,50,53,54},//  "休眠设置",
    {30,58,18,19},//  "温度阈值",
    {63,64,65,66},//  "焊咀校准",
    {59,60,61,62},//  "电源管理",
    {37,38,53,54},//  "菜单设置",
    {103,104,53,105} //关于设备
};
uint8 code page_two_num[page_max+1][10][4] =
{
    {   //第一级页面中字条数
        {78,79,47,48},//"比例整定",
        {80,81,47,48},//"积分整定",
        {82,81,47,48},//"微分整定",
    },
    {   //第二级页面中字条数
        {83,84,85,86},//"反色显示",
        {73,74,87,88},//"上下翻转",
        {0,58, 1, 2},//"亮度调节",
    },
    {
        {5,6,7,8},//"数据存储",
        {89,90,91,92},//恢复出厂设置
        {98,99,102,103},//蜂鸣开关
        {100,101,69,70},//音量大小

    },
    {
        {75,5,53,48},//"分数设定",
        {76,5,53,48},//"秒数设定",
        {49,50,102,103},//休眠开关
        {103,110,51,52},//关机时间
        {111,112,103,110},//自动关机
    },
    {
        {30,58,74,20},//"温度下限",
        {30,58,73,20},//"温度上限",
        {95,19,53,48},//初值设定
        {30,58,57,93},//温度步进
        {94,30,53,54},//强温设置
        {49,50,30,58},//休眠温度

    },
    {
        //更换烙铁头（待添加）
        {21,29,65,66},//"零阶校准",
        {11,29,65,66},//"一阶校准",
        {12,29,65,66},//"二阶校准",
        {13,29,65,66},//"三阶校准",
        {14,29,65,66},//"四阶校准",
        {15,29,65,66},//"五阶校准",
        {16,29,65,66},//"六阶校准",
    },
    {
        {9,10,53,54},//"协议设置",
        {106,107,53,54},//欠压设置
        {106,107,108,109},//欠压保护
    },
    {
        {67,68,69,70},//"图标大小",
        {31,32,33,34},//"滚动方向",
    },

};
uint8 code page_two_num_max[page_max+1] =//定义所有二级页面中参数的数据最大量
{3,3,4,5,6,7,3,2};
//三个维度分别为 一级页面最大个数、二级页面最大个数、二级页面长度

//------------------//
//两个维度分别为 一级页面最大个数、二级页面最大参数个数
//用做中间变量，显示参数变量值
int16  code page_two_data_min[page_max+1][10] =
{
    {0,0,0},//p,i,d
    {0,0,0},
    {0,0,0,0},
    {0,0,0,1,0},
    {0,300,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0},
    {0,0},
};
int16  code page_two_data_max[page_max+1][10] =
{
    {255,255,255},//p,i,d
    {1,1,255},
    {1,1,1,99},
    {30,60,1,99,1},
    {300,600,500,50,600,300},
    {1023,1023,1023,1023,1023,1023,1023},
    {4,30,1},//协议设置
    {1,1},
};
uint8 data save_data_A[32] = {0};
uint8 data save_data_B[32] = {0};
int16 code page_two_init_data[page_max+1][10] =//出厂数据
{
    {13,2,17},//p,i,d
    {0,0,255},
    {0,0,1,50},
    {3,0,1,1,1},
    {200,500,320,10,400,200},
    {40,157,289,469,676,759,931},
    {4,15,0},
    {0,1},
};
int16 xdata page_two_data[page_max+1][10] =
{
    {0},//p,i,d
};
//第二页的翻页标志
int8  page_2_flag[page_max+1] = {0};

void BEEP_handle(void)
{
    if(BEEP_ON_FLAG == 1)
    {
        if(BEEP_flag == 1)
        {
            pwm_duty(BEEP, BEEP_VOLUME);
        }
        else
        {
            pwm_duty(BEEP, 0);
        }
    }
    else
    {
        BEEP_flag = 0;
    }
}
void OLED_OFF_handle(void)
{
    if(auto_oled_off_flag == 1)//熄屏
    {
        OLED_WR_Byte(0X8D, OLED_CMD);  //SET DCDC命令
        OLED_WR_Byte(0X10, OLED_CMD);  //DCDC OFF
        OLED_WR_Byte(0XAE, OLED_CMD);  //DISPLAY OFF
			  auto_oled_off_flag = 0;
    }
    if(oled_light_flag == 1)
    {
        OLED_WR_Byte(0X8D, OLED_CMD);  //SET DCDC命令
        OLED_WR_Byte(0X14, OLED_CMD);  //DCDC ON
        OLED_WR_Byte(0XAF, OLED_CMD);  //DISPLAY ON
        oled_light_flag = 0;
    }
}
void STRONG_TEMP_handle(void)//开启强温模式
{
    if(SLEEP_INIT_FLAG == 0)
        //if((TEMP_SET_INIT_FLAG == 1)&&(SLEEP_INIT_FLAG == 0))
    {
        if(Strong_temp_flag == 1)
        {
            show_IMG16x16(4,0,5);//强温模式
            Temp_Set = IRON_TEMP_SET_STRONG;
            TEMP_SET_INIT_FLAG = 1;

        }
        else
        {
            if(TEMP_SET_INIT_FLAG == 1)
            {
                show_IMG16x16(4,0,0);//正常模式
                Temp_Set = IRON_TEMP_SET_INIT;
                TEMP_SET_INIT_FLAG = 0;
            }
        }
    }
    else
    {

        show_IMG16x16(4,0,6);//休眠模式

    }
    if(sleep_flag == 0)
    {
        if((Strong_temp_flag == 0))
        {

            show_IMG16x16(4,0,0);//加热模式
            if(TEMP_SET_INIT_FLAG == 1)
            {
                Temp_Set = IRON_TEMP_SET_INIT;
                TEMP_SET_INIT_FLAG = 0;
            }
        }
    }

}
void data_init(void)//恢复出厂
{
    int i,j = 0;
    for(i = 0; i< page_max + 1; i++)
    {
        for(j = 0; j < 10; j++)
        {
            page_two_data[i][j] = page_two_init_data[i][j];
        }
    }
}

//将修改好的数据传递给用来存储eeprom的数组
void data_transmit(void)
{
    save_data_A[0]  = page_two_data[0][0];//KP
    save_data_A[1]  = page_two_data[0][1];//KI
    save_data_A[2]  = page_two_data[0][2];//KD
    //----------------------------------------------------------//
    save_data_A[3]  = page_two_data[1][0];//
    save_data_A[4]  = page_two_data[1][1];
    save_data_A[5]  = page_two_data[1][2];//亮度
    //----------------------------------------------------------//
    //save_data[6] = page_two_data[2][0];//数据存贮
    //save_data[7] = page_two_data[2][1];//恢复出厂
    save_data_A[8] = page_two_data[2][2];//蜂鸣开关
    save_data_A[9] = page_two_data[2][3];//音量大小
    //----------------------------------------------------------//
    save_data_A[10]  = page_two_data[3][0];//休眠分钟
    save_data_A[11]  = page_two_data[3][1];//休眠秒钟
    save_data_A[12]  = page_two_data[3][2];//休眠开关
    save_data_A[13]  = page_two_data[3][3];//关机时间
    save_data_A[14]  = page_two_data[3][4];//自动关机
    //----------------------------------------------------------//
    save_data_A[15]  = (uint8)(page_two_data[4][0]/100);//
    save_data_A[16] = (page_two_data[4][0] - 100*save_data_A[15]);
    save_data_A[17] = (uint8)(page_two_data[4][1]/100);//
    save_data_A[18] = (page_two_data[4][1] - 100*save_data_A[17]);
    save_data_A[19] = (uint8)(page_two_data[4][2]/100);
    save_data_A[20] = (page_two_data[4][2] - 100*save_data_A[19]);
    save_data_A[21] = (uint8)(page_two_data[4][3]/100);
    save_data_A[22] = (page_two_data[4][3] - 100*save_data_A[21]);
    save_data_A[23] = (uint8)(page_two_data[4][4]/100);
    save_data_A[24] = (page_two_data[4][4] - 100*save_data_A[23]);
    save_data_A[25] = (uint8)(page_two_data[4][5]/100);
    save_data_A[26] = (page_two_data[4][5] - 100*save_data_A[25]);
    //----------------------------------------------------------//
    save_data_B[0] = (uint8)(page_two_data[5][0]/100);
    save_data_B[1] = (page_two_data[5][0] - 100*save_data_B[0]);

    save_data_B[2] = (uint8)(page_two_data[5][1]/100);
    save_data_B[3] = (page_two_data[5][1] - 100*save_data_B[2]);

    save_data_B[4] = (uint8)(page_two_data[5][2]/100);
    save_data_B[5] = (page_two_data[5][2] - 100*save_data_B[4]);

    save_data_B[6] = (uint8)(page_two_data[5][3]/100);
    save_data_B[7] = (page_two_data[5][3] - 100*save_data_B[6]);

    save_data_B[8] = (uint8)(page_two_data[5][4]/100);
    save_data_B[9] = (page_two_data[5][4] - 100*save_data_B[8]);

    save_data_B[10] = (uint8)(page_two_data[5][5]/100);
    save_data_B[11] = (page_two_data[5][5] - 100*save_data_B[10]);

    save_data_B[12] = (uint8)(page_two_data[5][6]/100);
    save_data_B[13] = (page_two_data[5][6] - 100*save_data_B[12]);
    //----------------------------------------------------------//
    save_data_B[14] = page_two_data[6][0];//协议设置
    save_data_B[15] = page_two_data[6][1];//欠压设置
    save_data_B[16] = page_two_data[6][2];//欠压保护
    //
    save_data_B[17] = page_two_data[7][0];//图标大小
    save_data_B[18] = page_two_data[7][1];//图标方向
    //save_data_B[17] = page_two_data[7][2];//图标速度

}
//数据还原
void data_restore(void)
{
    page_two_data[0][0] = save_data_A[0];//KP
    page_two_data[0][1] = save_data_A[1];//KI
    page_two_data[0][2] = save_data_A[2];//KD
//
    page_two_data[1][0] = save_data_A[3];//
    page_two_data[1][1] = save_data_A[4];
    page_two_data[1][2] = save_data_A[5];//亮度
//
    // page_two_data[2][0];//数据存贮

    page_two_data[2][2] = save_data_A[8];//蜂鸣开关
    page_two_data[2][3] = save_data_A[9];//音量大小
//
    page_two_data[3][0] = save_data_A[10];//休眠分钟
    page_two_data[3][1] = save_data_A[11];//休眠秒钟
    page_two_data[3][2] = save_data_A[12];//休眠开关
    page_two_data[3][3] = save_data_A[13];//关机时间
    page_two_data[3][4] = save_data_A[14];//自动关机
//
    page_two_data[4][0] = 100*save_data_A[15] + save_data_A[16];//温度下线
    page_two_data[4][1] = 100*save_data_A[17] + save_data_A[18];//温度上限
    page_two_data[4][2] = 100*save_data_A[19] + save_data_A[20];//初值
    page_two_data[4][3] = 100*save_data_A[21] + save_data_A[22];//步进
    page_two_data[4][4] = 100*save_data_A[23] + save_data_A[24];//强温
    page_two_data[4][5] = 100*save_data_A[25] + save_data_A[26];//休眠温度
//
    page_two_data[5][0] = 100*save_data_B[0] + save_data_B[1];
    page_two_data[5][1] = 100*save_data_B[2] + save_data_B[3];
    page_two_data[5][2] = 100*save_data_B[4] + save_data_B[5];
    page_two_data[5][3] = 100*save_data_B[6] + save_data_B[7];
    page_two_data[5][4] = 100*save_data_B[8] + save_data_B[9];
    page_two_data[5][5] = 100*save_data_B[10] + save_data_B[11];
    page_two_data[5][6] = 100*save_data_B[12] + save_data_B[13];
//
    page_two_data[6][0] = save_data_B[14];//协议设置
    page_two_data[6][1] = save_data_B[15];//欠压设置
    page_two_data[6][2] = save_data_B[16];//欠压保护
//
    page_two_data[7][0] = save_data_B[17];//图标大小
    page_two_data[7][1] = save_data_B[18];//图标方向
    //page_two_data[7][2] = save_data_B[17];//图标速度

}
void Function_init(void)//实现功能
{

    SHOW_IRON_TEMP = 0;
    Temp_Set = IRON_TEMP_SET_INIT;
    if(page_two_data[1][0] == 1)//反色显示部分
    {
        OLED_WR_Byte(0xa7,OLED_CMD);
    }
    else
    {
        OLED_WR_Byte(0xa6,OLED_CMD);
    }
    if(page_two_data[1][1] == 1)//反转
    {
        OLED_WR_Byte(0xa1,OLED_CMD);//段重定向设置  a1    a0
        OLED_WR_Byte(0xC8,OLED_CMD);//-not offset   c8    c0
    }
    else
    {
        OLED_WR_Byte(0xa0,OLED_CMD);//段重定向设置  a1    a0
        OLED_WR_Byte(0xC0,OLED_CMD);//-not offset   c8    c0
    }
    if(page_two_data[1][2] > 0)
    {
        OLED_WR_Byte(0x81,OLED_CMD);//设置对比度
        OLED_WR_Byte(page_two_data[1][2],OLED_CMD);
    }
    else
    {
        OLED_WR_Byte(0x81,OLED_CMD);//设置对比度
        OLED_WR_Byte(0xff,OLED_CMD);//亮度调满
    }
    if(page_two_data[2][0] == 1)//数据存储
    {
        //
        data_transmit();
        eeprom_erase(0x40);
        eeprom_write(0x00,save_data_A,32);
        eeprom_write(0x20,save_data_B,32);
        page_two_data[2][0] = 0;
    }
    if(page_two_data[2][1] == 1)//恢复出厂
    {
        //
        data_init();
        data_transmit();
        eeprom_erase(0x40);
        eeprom_write(0x00,save_data_A,32);
        eeprom_write(0x20,save_data_B,32);
        page_two_data[2][1] = 0;
    }

    switch(page_two_data[6][0])
    {
    case 0://默认5V
        CFG1 = 1;
        CFG2 = 0;
        CFG3 = 0;
        break;
    case 1://9V
        CFG1 = 0;
        CFG2 = 0;
        CFG3 = 0;
        break;
    case 2://12V
        CFG1 = 0;
        CFG2 = 0;
        CFG3 = 1;
        break;
    case 3://15V
        CFG1 = 0;
        CFG2 = 1;
        CFG3 = 1;
        break;
    case 4://20V
        CFG1 = 0;
        CFG2 = 1;
        CFG3 = 0;
        break;
    }

    icon_size_flag = page_two_data[7][0];
    row_derection = page_two_data[7][1];//滚动方向
    if(icon_size_flag == 0)
    {
        if(row_derection == 1)
        {
            row_speed = 1;
        }
        else
        {
            row_speed = 6;
        }
    }
    else
    {
        row_speed = 1;
    }



}

void page_one_menu(uint8 x,uint8 y,uint8 flag)
{
    OLED_CH16_Char( x,y,1,flag,0);
}
//写一个滚动函数
void row_page(int8 flag,uint8 speed)//页码标志，速度
{
    int i;
    page_left   = flag - 1;
    page_center = flag;
    page_right  = flag + 1;
    if(page_left < 0)
    {
        page_left = page_max + 0;
    }
    if(page_right >= page_max + 1)
    {
        page_right = 0;
    }
    if(row_flag == -1)
    {
        for(i = 0; i<34; i+=speed) //向右平移34个单位
        {
            last_hide = last_left - 1;
            if(last_hide < 0)
            {
                last_hide = page_max + 0;
            }
            Draw_IMG34x24(-46+i,1, last_hide);
            Draw_IMG34x24(-14+i,1, last_left);
            Draw_IMG34x24(20+i,1, last_center);
            Draw_IMG34x24(54+i,1, last_right);

        }
        row_flag = 0;
    }
    else if(row_flag == 1)//向左滚动
    {
        for(i = 0; i>=-33; i-=speed)
        {
            last_hide = last_right + 1;
            if(last_hide >= page_max + 1)
            {
                last_hide = 0;
            }
            Draw_IMG34x24(-14+i,1, last_left);
            Draw_IMG34x24(20+i,1, last_center);
            Draw_IMG34x24(54+i,1, last_right);
            Draw_IMG34x24(86+i,1, last_hide);
        }
        row_flag = 0;
    }
    Draw_IMG34x24(-14,1, page_left);
    Draw_IMG34x24(20,1, page_center);
    Draw_IMG34x24(54,1, page_right);
    last_left = page_left;
    last_center = page_center;
    last_right = page_right;

}
//重构一个平移的函数
void new_row_page(int8 flag,uint8 speed,uint8 mode)
{
    int i;
    page_left   = flag - 1;
    page_center = flag;
    page_right  = flag + 1;
    if(page_left < 0)
    {
        page_left = page_max + 0;
    }
    if(page_right >= page_max + 1)
    {
        page_right = 0;
    }
    if(mode == 0)//左右横移模式
    {

        if(row_flag == -1)
        {
            for(i = 0; i<42; i+=speed) //向右平移34个单位
            {
                last_hide = last_left - 1;
                if(last_hide < 0)
                {
                    last_hide = page_max + 0;
                }
                Draw_IMG42X32_limit(-68+i,0, last_hide,mode);
                Draw_IMG42X32_limit(-26+i,0, last_left,mode);
                Draw_IMG42X32_limit(16+i,0, last_center,mode);
                Draw_IMG42X32_limit(58+i,0, last_right,mode);

            }
            row_flag = 0;
        }
        else if(row_flag == 1)//向左滚动
        {
            for(i = 0; i>=-41; i-=speed)
            {
                last_hide = last_right + 1;
                if(last_hide >= page_max + 1)
                {
                    last_hide = 0;
                }

                Draw_IMG42X32_limit(-26+i,0, last_left,mode);
                Draw_IMG42X32_limit(16+i,0, last_center,mode);
                Draw_IMG42X32_limit(58+i,0, last_right,mode);
                Draw_IMG42X32_limit(100+i,0, last_hide,mode);
            }
            row_flag = 0;
        }
        Draw_IMG42X32_limit(-26,0, page_left,mode);
        Draw_IMG42X32_limit(16,0, page_center,mode);
        Draw_IMG42X32_limit(58,0, page_right,mode);
        last_left = page_left;
        last_center = page_center;
        last_right = page_right;
    }
    else if(mode == 1)//上下横移模式
    {
        if(row_flag == -1)
        {
            for(i = 0; i<4; i+=speed) //向下平移4个单位
            {

                Draw_IMG42X32_limit(16,i-4, last_left,mode);
                Draw_IMG42X32_limit(16,i, last_center,mode);
                //Draw_IMG42X32(16,i+1, last_right);
                pca_delay_ms(30);
            }
            row_flag = 0;
        }
        else if(row_flag == 1)//
        {
            for(i = 0; i>=-3; i-=speed)
            {

                //Draw_IMG42X32(16,0, last_left);
                Draw_IMG42X32_limit(16,i, last_center,mode);
                Draw_IMG42X32_limit(16,i+4, last_right,mode);
                pca_delay_ms(30);
            }
            row_flag = 0;
        }
        Draw_IMG42X32_limit(16,0, page_center,mode);
        last_left = page_left;
        last_center = page_center;
        last_right = page_right;
    }
}
//用来上下翻转第二页菜单参数名的函数
void row_page_two(int8 what_page)//确保此时移动的是第几页的参数
{
    uint8  up_ch[12] = {0};
    uint8  center_ch[12] = {0};
    uint8  down_ch[12] = {0};
    int8 i = 0;
    //定义一个参数表示当前的页码
    int8 page_1_num = what_page;
    page_2_up[what_page] = page_2_flag[what_page] - 1;
    page_2_center[what_page] = page_2_flag[what_page];
    page_2_down[what_page] = page_2_flag[what_page] + 1;
    if(page_2_up[what_page] < 0)
    {
        page_2_up[what_page] = page_two_num_max[what_page] - 1;
    }

    if(page_2_down[what_page] >page_two_num_max[what_page] - 1)
    {
        page_2_down[what_page] = 0;
    }
    //OLED_CH16_Char(0,-1,2,what_page,page_2_up[what_page]);
    OLED_CH16_Char(0,1,2,what_page,page_2_center[what_page]);
    //OLED_CH16_Char(0,3,2,what_page,page_2_down[what_page]);
    //要修改数值显示内容就得改这个，//

    switch(what_page)//一级菜单编号
    {
    case 0:
        OLED_ShowNum(80,1,page_two_data[what_page][page_2_center[what_page]],4,16);
        break;
    case 1://第一个页面：屏幕设置
        switch(page_2_center[what_page])//二级菜单编号
        {
        case 0:
            switch(page_two_data[what_page][page_2_center[what_page]])//二级菜单对应数据数值
            {
            case 0:
                OLED_ShowString(80,1,"Blac",16);
                break;
            case 1:
                OLED_ShowString(80,1,"Whit",16);
                break;
            }
            break;
        case 1:
            switch(page_two_data[what_page][page_2_center[what_page]])//二级菜单对应数据数值
            {
            case 0:
                OLED_ShowString(80,1,"  UP",16);
                break;
            case 1:
                OLED_ShowString(80,1,"DOWN",16);
                break;
            }
            break;
        case 2:
            OLED_ShowNum(80,1,page_two_data[what_page][page_2_center[what_page]],4,16);
            break;
        }
        break;
    case 2:
        switch(page_2_center[what_page])//二级菜单编号
        {
        case 0:
            switch(page_two_data[what_page][page_2_center[what_page]])//二级菜单对应数据数值
            {
            case 0:
                OLED_ShowString(80,1,"  No",16);
                break;
            case 1:
                OLED_ShowString(80,1," Yes",16);
                break;
            }
            break;
        case 1:
            switch(page_two_data[what_page][page_2_center[what_page]])//二级菜单对应数据数值
            {
            case 0:
                OLED_ShowString(80,1,"  No",16);
                break;
            case 1:
                OLED_ShowString(80,1," Yes",16);
                break;
            }
            break;
        case 2:
            switch(page_two_data[what_page][page_2_center[what_page]])//二级菜单对应数据数值
            {
            case 0:
                OLED_ShowString(80,1," OFF",16);
                break;
            case 1:
                OLED_ShowString(80,1,"  ON",16);
                break;
            }
            break;
        case 3:
            OLED_ShowNum(80,1,page_two_data[what_page][page_2_center[what_page]],4,16);
            break;
        }
        break;
    case 3:
        switch(page_2_center[what_page])//二级菜单编号
        {
        case 0:
            OLED_ShowNum(80,1,page_two_data[what_page][page_2_center[what_page]],4,16);
            break;
        case 1:
            OLED_ShowNum(80,1,page_two_data[what_page][page_2_center[what_page]],4,16);
            break;
        case 2:
            switch(page_two_data[what_page][page_2_center[what_page]])//二级菜单对应数据数值
            {
            case 0:
                OLED_ShowString(80,1," OFF",16);
                break;
            case 1:
                OLED_ShowString(80,1,"  ON",16);
                break;
            }
            break;
        case 3:
            OLED_ShowNum(80,1,page_two_data[what_page][page_2_center[what_page]],3,16);
            OLED_ShowString(104,1,"M",16);
            break;
        case 4:
            switch(page_two_data[what_page][page_2_center[what_page]])//二级菜单对应数据数值
            {
            case 0:
                OLED_ShowString(80,1," OFF",16);
                break;
            case 1:
                OLED_ShowString(80,1,"  ON",16);
                break;
            }
            break;

        }
        break;
    case 4:
        OLED_ShowNum(80,1,page_two_data[what_page][page_2_center[what_page]],4,16);
        break;
    case 5:
        OLED_ShowNum(80,1,page_two_data[what_page][page_2_center[what_page]],4,16);
        break;
    case 6:
        switch(page_2_center[what_page])//二级菜单编号
        {
        case 0:
            switch(page_two_data[what_page][page_2_center[what_page]])//二级菜单对应数据数值
            {
            case 0:
                OLED_ShowString(80,1," +5V",16);
                break;
            case 1:
                OLED_ShowString(80,1," +9V",16);
                break;
            case 2:
                OLED_ShowString(80,1,"+12V",16);
                break;
            case 3:
                OLED_ShowString(80,1,"+15V",16);
                break;
            case 4:
                OLED_ShowString(80,1,"+20V",16);
                break;
            }
            break;
        case 1:
            OLED_ShowString(80,1,"+",16);
            OLED_ShowNum(88,1,page_two_data[what_page][page_2_center[what_page]],2,16);
            OLED_ShowString(104,1,"V",16);
            break;
        case 2:
            switch(page_two_data[what_page][page_2_center[what_page]])//二级菜单对应数据数值
            {
            case 0:
                OLED_ShowString(80,1," OFF",16);
                break;
            case 1:
                OLED_ShowString(80,1,"  ON",16);
                break;
            }
            break;
        }
        break;
    case 7:
        switch(page_2_center[what_page])//二级菜单编号
        {
        case 0:
            switch(page_two_data[what_page][page_2_center[what_page]])//二级菜单对应数据数值
            {
            case 0:
                OLED_ShowString(80,1,"Larg",16);
                break;
            case 1:
                OLED_ShowString(80,1,"Smal",16);
                break;

            }
            break;
        case 1:
            switch(page_two_data[what_page][page_2_center[what_page]])//二级菜单对应数据数值
            {
            case 0:
                OLED_ShowString(80,1," L&R",16);
                break;
            case 1:
                OLED_ShowString(80,1," U&D",16);
                break;

            }
            break;
        }
        break;


    }
    //
}



void Function_execute(void)//实现功能
{
    switch(page_flag)
    {
    case 0://参数整定部分
        break;
    case 1://
        if(page_two_data[1][0] == 1)//反色显示部分
        {
            OLED_WR_Byte(0xa7,OLED_CMD);
        }
        else
        {
            OLED_WR_Byte(0xa6,OLED_CMD);
        }
        if(page_two_data[1][1] == 1)//反转
        {
            OLED_WR_Byte(0xa1,OLED_CMD);//段重定向设置  a1    a0
            OLED_WR_Byte(0xC8,OLED_CMD);//-not offset   c8    c0
        }
        else
        {
            OLED_WR_Byte(0xa0,OLED_CMD);//段重定向设置  a1    a0
            OLED_WR_Byte(0xC0,OLED_CMD);//-not offset   c8    c0
        }
        if(page_two_data[1][2] > 0)
        {
            OLED_WR_Byte(0x81,OLED_CMD);//设置对比度
            OLED_WR_Byte(page_two_data[1][2],OLED_CMD);
        }
        else
        {
            OLED_WR_Byte(0x81,OLED_CMD);//设置对比度
            OLED_WR_Byte(0xff,OLED_CMD);//亮度调满
        }
        break;
    case 2://基础设置部分
        if(page_two_data[2][0] == 1)//数据存储
        {
            //
            data_transmit();
            eeprom_erase(0x40);
            eeprom_write(0x00,save_data_A,32);
            eeprom_write(0x20,save_data_B,32);
            page_two_data[2][0] = 0;
        }
        if(page_two_data[2][1] == 1)//恢复出厂
        {
            //
            data_init();
            data_transmit();
            eeprom_erase(0x40);
            eeprom_write(0x00,save_data_A,32);
            eeprom_write(0x20,save_data_B,32);
            page_two_data[2][1] = 0;
        }

        break;
    case 3://休眠时间设定
        break;
    case 4:
        break;
    case 5:
        break;
    case 6://协议设置
        switch(page_two_data[6][0])
        {
        case 0://默认5V
            CFG1 = 1;
            CFG2 = 0;
            CFG3 = 0;
            break;
        case 1://9V
            CFG1 = 0;
            CFG2 = 0;
            CFG3 = 0;
            break;
        case 2://12V
            CFG1 = 0;
            CFG2 = 0;
            CFG3 = 1;
            break;
        case 3://15V
            CFG1 = 0;
            CFG2 = 1;
            CFG3 = 1;
            break;
        case 4://20V
            CFG1 = 0;
            CFG2 = 1;
            CFG3 = 0;
            break;
        }
        break;
    case 7://UI修改
        icon_size_flag = page_two_data[7][0];
        row_derection = page_two_data[7][1];//滚动方向
        if(icon_size_flag == 0)
        {
            if(row_derection == 1)
            {
                row_speed = 1;
            }
            else
            {
                row_speed = 4;
            }
        }
        else
        {
            row_speed = 1;
        }

        break;

    }
}
/**/
void key_press(void)
{
    //------------------------------------------------------------//
    if(enter_flag == 1)
    {

        if(menu_flag == 0)//在主界面时按下mode键
        {
            menu_flag = 1;
        }
        else if(menu_flag == 1)//在一级菜单下按下mode键
        {
            //功能
            menu_flag = 2;
        }
        else if(menu_flag == 2)//在二级菜单下按下mode键
        {
            if(select_flag == 0)
            {
                select_flag = 1;//进入编辑界面
            }
            else
            {

                Function_execute();
                select_flag = 0;
            }



        }
        OLED_Clear();
        enter_flag = 0;

    }
    //------------------------------------------------------------//
    if(quit_flag == 1)
    {

        if(menu_flag == 0)
        {
            Strong_temp_flag = !Strong_temp_flag;//开启一键加强模式
        }
        else if(menu_flag == 1)
        {
            menu_flag = 0;
        }
        else if(menu_flag == 2)
        {
            if(select_flag == 0)
            {
                menu_flag = 1;
            }
        }

        OLED_Clear();
        quit_flag = 0;

    }
    //------------------------------------------------------------//

    if(up_short_flag == 1)
    {

        //function
        if(menu_flag == 0)//在主界面时按下up键
        {
            Temp_Set -=TEMP_STEEP;//五度步进
            if(Temp_Set >= IRON_TEMP_SET_MAX)
            {
                Temp_Set = IRON_TEMP_SET_MAX;

            }
            else if(Temp_Set <= IRON_TEMP_SET_MIN)
            {
                Temp_Set = IRON_TEMP_SET_MIN;
            }
        }
        else if(menu_flag == 1)//在一级菜单时按下up键
        {
            page_flag -= 1;
            row_flag = -1;
        }
        else if(menu_flag == 2)
        {

            if(select_flag == 1)
            {
                page_two_data[page_flag][page_2_flag[page_flag]]--;
                if(page_two_data[page_flag][page_2_flag[page_flag]] < page_two_data_min[page_flag][page_2_flag[page_flag]])
                {
                    page_two_data[page_flag][page_2_flag[page_flag]] = page_two_data_max[page_flag][page_2_flag[page_flag]];
                }
                else if(page_two_data[page_flag][page_2_flag[page_flag]] > page_two_data_max[page_flag][page_2_flag[page_flag]])
                {
                    page_two_data[page_flag][page_2_flag[page_flag]] = page_two_data_min[page_flag][page_2_flag[page_flag]];
                }
            }
            else
            {
                page_2_flag[page_flag] -= 1;
                if(page_2_flag[page_flag] < 0)
                {
                    page_2_flag[page_flag] = page_two_num_max[page_flag] - 1;
                }
            }
        }
        //
        up_short_flag = 0;

    }
    if(up_long_flag == 1)
    {
        //BEEP_flag = 1;
        //function
        if(menu_flag == 0)//在主界面时按下up键
        {
            Temp_Set -=TEMP_STEEP;//五度步进
            if(Temp_Set >= IRON_TEMP_SET_MAX)
            {
                Temp_Set = IRON_TEMP_SET_MAX;

            }
            else if(Temp_Set <= IRON_TEMP_SET_MIN)
            {
                Temp_Set = IRON_TEMP_SET_MIN;
            }
        }
        else if(menu_flag == 1)//在一级菜单时按下up键
        {
            page_flag -= 1;
            row_flag = -1;
        }
        else if(menu_flag == 2)
        {

            if(select_flag == 1)
            {
                page_two_data[page_flag][page_2_flag[page_flag]]--;
                if(page_two_data[page_flag][page_2_flag[page_flag]] < page_two_data_min[page_flag][page_2_flag[page_flag]])
                {
                    page_two_data[page_flag][page_2_flag[page_flag]] = page_two_data_max[page_flag][page_2_flag[page_flag]];
                }
                else if(page_two_data[page_flag][page_2_flag[page_flag]] > page_two_data_max[page_flag][page_2_flag[page_flag]])
                {
                    page_two_data[page_flag][page_2_flag[page_flag]] = page_two_data_min[page_flag][page_2_flag[page_flag]];
                }
            }
            else
            {
                page_2_flag[page_flag] -= 1;
                if(page_2_flag[page_flag] < 0)
                {
                    page_2_flag[page_flag] = page_two_num_max[page_flag] - 1;
                }
            }
        }
        //
        //up_long_flag = 0;
    }

    //------------------------------------------------------------//
    if(down_short_flag == 1)
    {

        //function
        if(menu_flag == 0)//在主界面时按下up键
        {
            Temp_Set +=TEMP_STEEP;//五度步进
            if(Temp_Set >= IRON_TEMP_SET_MAX)
            {
                Temp_Set = IRON_TEMP_SET_MAX;

            }
            else if(Temp_Set <= IRON_TEMP_SET_MIN)
            {
                Temp_Set = IRON_TEMP_SET_MIN;
            }
        }
        else if(menu_flag == 1)//在一级菜单时按下down键
        {
            page_flag += 1;
            row_flag = 1;
        }
        else if(menu_flag == 2)
        {


            if(select_flag == 1)
            {
                page_two_data[page_flag][page_2_flag[page_flag]]++;
                if(page_two_data[page_flag][page_2_flag[page_flag]] < page_two_data_min[page_flag][page_2_flag[page_flag]])
                {
                    page_two_data[page_flag][page_2_flag[page_flag]] = page_two_data_max[page_flag][page_2_flag[page_flag]];
                }
                else if(page_two_data[page_flag][page_2_flag[page_flag]] > page_two_data_max[page_flag][page_2_flag[page_flag]])
                {
                    page_two_data[page_flag][page_2_flag[page_flag]] = page_two_data_min[page_flag][page_2_flag[page_flag]];
                }
            }
            else
            {
                page_2_flag[page_flag] += 1;
                if(page_2_flag[page_flag] >page_two_num_max[page_flag] - 1)
                {
                    page_2_flag[page_flag] = 0;
                }
            }
        }
        //
        down_short_flag = 0;

    }
    if(down_long_flag == 1)
    {
        //function
        if(menu_flag == 0)//在主界面时按下up键
        {
            Temp_Set +=TEMP_STEEP;//五度步进
            if(Temp_Set >= IRON_TEMP_SET_MAX)
            {
                Temp_Set = IRON_TEMP_SET_MAX;

            }
            else if(Temp_Set <= IRON_TEMP_SET_MIN)
            {
                Temp_Set = IRON_TEMP_SET_MIN;
            }
        }
        else if(menu_flag == 1)//在一级菜单时按下down键
        {
            page_flag += 1;
            row_flag = 1;
        }
        else if(menu_flag == 2)
        {


            if(select_flag == 1)
            {
                page_two_data[page_flag][page_2_flag[page_flag]]++;
                if(page_two_data[page_flag][page_2_flag[page_flag]] < page_two_data_min[page_flag][page_2_flag[page_flag]])
                {
                    page_two_data[page_flag][page_2_flag[page_flag]] = page_two_data_max[page_flag][page_2_flag[page_flag]];
                }
                else if(page_two_data[page_flag][page_2_flag[page_flag]] > page_two_data_max[page_flag][page_2_flag[page_flag]])
                {
                    page_two_data[page_flag][page_2_flag[page_flag]] = page_two_data_min[page_flag][page_2_flag[page_flag]];
                }
            }
            else
            {
                page_2_flag[page_flag] += 1;
                if(page_2_flag[page_flag] >page_two_num_max[page_flag] - 1)
                {
                    page_2_flag[page_flag] = 0;
                }
            }
        }
        //
        //down_long_flag = 0;
    }
    //------------------------------------------------------------//

    //------------------------------------------------------------//
    if(page_flag < page_min)
    {
        page_flag = page_max;
    }
    else if(page_flag > page_max)
    {
        page_flag = page_min;
    }

}
/*定义一个主菜单函数*/
void top_menu(uint16 set_temp,uint16 iron_temp, uint8 sys_temp, uint8 vin, uint8 pwm_duty)
{
    pwm_out_get();//获取pwm输出值
    BEEP_handle();
    OLED_OFF_handle();
    if(menu_flag == 0)
    {
        //显示输入电压
        OLED_ShowString(100,0,"V:",8);
        OLED_ShowNum(110,0,vin,2,12);
        OLED_ShowString(122,0,"v",8);
        //显示系统温度
        //
        if((vin < LOW_BATTERY_VOLTAGE)&&(LOW_BATTERY_ON_FLAG == 1))//触发低电量保护
        {
            low_battery_flag = 1;
            pwm_flag = 0;
        }
        else
        {
            low_battery_flag = 0;
        }
        OLED_ShowString(100,1,"T:",8);
        OLED_ShowNum(110,1,sys_temp,2,12);
        OLED_ShowString(122,1,"^",8);
        //显示设置温度
        show_set_temp(0,2,set_temp);
        //显示烙铁温度
        show_temp(24,iron_temp);
        //显示PWM占空比
        show_IMG56x8(72, 3,pwm_duty);
        if((SLEEP_INIT_FLAG == 0)&&(Strong_temp_flag == 0))
        {
            show_IMG16x16(4,0,0);//加热模式
        }
        //
    }
    else
    {
        //
        pwm_flag = 0;
    }
}

void show_menu(void)
{
    if(menu_flag == 0)
    {

        STRONG_TEMP_handle();//强温模式判断
    }
    else if(menu_flag == 1)
    {
        //显示一级菜单
        //先执行一个全局赋值函数，再执行后面的函数
        if(icon_size_flag == 1)
        {
            row_page(page_flag,row_speed*10);
        }
        else
        {
            new_row_page(page_flag,row_speed,row_derection);
        }
        page_one_menu(64,1,page_flag);
    }
    else if(menu_flag == 2)//
    {
        if(page_flag == 8)
        {
            OLED_ShowString(0,0,INFO_VERSION,12);
            OLED_ShowString(0,1,INFO_HARDWARE,12);
            OLED_ShowString(0,2,INFO_SOFTWARE,12);
            OLED_ShowString(0,3,INFO_WEBSITE,12);
        }
        else
        {
            //显示二级菜单
            OLED_P8x16Str(64,1,">");
            OLED_P8x16Str(120,1,"<");
            row_page_two(page_flag);
        }

    }

}




