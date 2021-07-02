#ifndef USER_H
#define USER_H
#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"
#include "app_uart.h"
//Log需要引用的头文件
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif
#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif
#include "nrf_drv_twi.h"
#include "nrf_drv_saadc.h"
#include "nrf_temp.h"
#include "oled.h"
#include "oledfont.h"
#include "user_menu.h"
#include "user_gpio.h"

#define page_min 0
#define page_max 7



//按键初始化函数
void button_init(void);
extern uint8_t select_flag;
extern uint8_t  up_flag;
extern uint8_t  mode_flag;
extern uint8_t  down_flag;
extern uint8_t  enter_flag;
extern uint8_t  quit_flag;//退出标志位

extern uint8_t  up_short_flag;
extern uint8_t  up_long_flag;
extern uint8_t  down_short_flag;
extern uint8_t  down_long_flag;


#endif




