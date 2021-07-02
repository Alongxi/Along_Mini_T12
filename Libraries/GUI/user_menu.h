#ifndef USER_MENU_H
#define USER_MENU_H
#include "headfile.h"
#define page_min 0
#define page_max 8




extern uint8 menu_flag;
extern int8 page_flag;
extern uint8 enter_flag;
extern uint8 TEMP_SET_INIT_FLAG;

void show_menu(void);
void top_menu(uint16 set_temp,uint16 iron_temp, uint8 sys_temp, uint8 vin, uint8 pwm_duty);
void key_press(void);
void Function_init(void);
void data_restore(void);//数据还原

void data_init(void);


extern uint8 data save_data_A[32];
extern uint8 data save_data_B[32];
extern uint8 code page_one_num[page_max+1][4];
extern uint8 code page_two_num[page_max+1][10][4];
extern int16 xdata page_two_data[page_max+1][10];

extern int8 Strong_temp_flag;
extern int8 BEEP_flag;
#define TEMP_STEEP                page_two_data[4][3]//温度步进
#define IRON_TEMP_SET_MIN         page_two_data[4][0] //烙铁调温最大值
#define IRON_TEMP_SET_INIT        page_two_data[4][2]
#define IRON_TEMP_SET_MAX         page_two_data[4][1] //烙铁调温最小值 
#define IRON_TEMP_SET_STRONG      page_two_data[4][4]
#define IRON_TEMP_SET_SLEEP       page_two_data[4][5]
#define BEEP_VOLUME               page_two_data[2][3]*100

#define ICON_SIZE_FLAG            page_two_data[7][0]
#define ICON_ROW_FLAG             page_two_data[7][1]

#define BEEP_ON_FLAG              page_two_data[2][2]
#define SLEEP_ON_FLAG             page_two_data[3][2]
#define SET_SLEEP_MINUTE          page_two_data[3][0]
#define SET_SLEEP_SECOND          page_two_data[3][1]
#define LOW_BATTERY_ON_FLAG       page_two_data[6][2]
#define LOW_BATTERY_VOLTAGE       page_two_data[6][1]
#define AUTO_SHUTDOWN_MINUTE      page_two_data[3][3]
#define AUTO_SHUTDOWN_ON_FLAG     page_two_data[3][4]
//----------------------版本信息-----------------------//
#define INFO_VERSION              " Version:1.3.1.Alpha "
#define INFO_HARDWARE             "  Hardware:LI JIAN   "
#define INFO_SOFTWARE             "  Software: ALONG    "
#define INFO_WEBSITE              "  Web:ALONGXII.XYZ   "
//-----------------------------------------------------//

#endif


