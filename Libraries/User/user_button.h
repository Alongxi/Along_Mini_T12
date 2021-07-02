#ifndef USER_BUTTON_H
#define USER_BUTTON_H
#include "headfile.h"

extern uint8  select_flag;
extern uint8  mode_flag;//模式标志位
extern uint8  enter_flag;
extern uint8  quit_flag;//退出标志位
extern uint8  up_flag;//上键
extern uint8  up_short_flag;//上键单击
extern uint8  up_long_flag;//上键长按
extern uint8  down_flag;//下键
extern uint8  down_short_flag;//下键单击
extern uint8  down_long_flag;//下键长按
extern uint8  sleep_flag;//下键
extern uint8  sleep_short_flag;//下键单击
extern uint8  sleep_long_flag;//下键长按



extern uint8 auto_power_off_flag;
extern uint8 oled_handle_flag;
extern uint8 auto_oled_off_flag;
extern uint8 oled_light_flag;

extern int8 SLEEP_INIT_FLAG;

extern int16 sleep_cont;
extern int16 sleep_second;

extern int iron_ad;

void button_init(void);
void key_press_handler(void);
void adc_iron_get_handle(void);
void OLED_sleep_handle(void);
#endif


