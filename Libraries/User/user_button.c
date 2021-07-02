#include "headfile.h"
#include "user_button.h"

uint8 BEEP_CONT = 0;
uint8 PWM_CONT = 0;
int iron_ad = 0;

int16 key_hold_ms = 0;
int16 sleep_cont = 0;
int16 sleep_second = 0;//自动休眠时间
int16 olde_off_cont = 0;
int16 oled_off_second = 0;//自动关机时间
int16 shutdown_cont = 0;
int16 shutdown_second = 0;//自动关机时间

uint8  mode_flag = 0;//模式标志位
uint8  enter_flag = 0;
uint8  quit_flag = 0;//退出标志位

uint8  up_flag = 0;//上键
uint8  up_short_flag = 0;//上键单击
uint8  up_long_flag = 0;//上键长按

uint8  down_flag = 0;//下键
uint8  down_short_flag = 0;//下键单击
uint8  down_long_flag = 0;//下键长按

uint8  sleep_flag = 0;
uint8  sleep_short_flag = 0;
uint8  sleep_long_flah = 0;

uint8 auto_power_off_flag = 0;
uint8 oled_off_on_flag = 0;//oled熄屏计时开启
uint8 auto_oled_off_flag = 0;
uint8 oled_handle_flag = 0;
uint8 oled_light_flag = 0;


int8 SLEEP_INIT_FLAG = 0;
int8 ADC_GET_FLAG = 0;

//GPIOTE事件处理函回调函数，事件回调函数里面可以获取pin编号和引脚状态变化

void button_init(void)
{

    gpio_pull_set(key_up_pin,PULLUP);
    gpio_pull_set(key_mode_pin,PULLUP);
    gpio_pull_set(key_down_pin,PULLUP);
    gpio_pull_set(key_sleep_pin,PULLUP);
}


void key_press_handler(void)
{
    if(key_up == 0)
    {

        up_flag = 1;
    }
    else
    {
        up_flag = 0;
    }
    if(key_mode == 0)
    {

        mode_flag = 1;
    }

    if(key_down == 0)
    {

        down_flag = 1;
    }
    else
    {
        down_flag = 0;
    }
    if(key_sleep == 0)
    {

        sleep_flag = 1;
    }
    else
    {
        sleep_flag = 0;
    }

}
//10ms定时器


void TM1_Isr() interrupt 3
{

    //key_press_handler();
    //--------------------------------------------------------//
    if(mode_flag == 1)
    {
        if(key_mode == 0)//任然保持按下状态
        {
            key_hold_ms ++;//假如一直保持按下状态
            if(key_hold_ms == 100)//长按 到达1s中
            {
                quit_flag = 1;//确定退出，但是此刻仍然在计数
                //mode_flag = 0;
            }
        }
        else//只有松开按键之后，停止计数
        {
            if((key_hold_ms <= 100 )&&(key_hold_ms >= 10))//假如判断按下时间不足1s，则为短按
            {
                key_hold_ms = 0;
                enter_flag = 1;
                mode_flag = 0;
            }
            else if(key_hold_ms > 100)
            {
                key_hold_ms = 0;
                mode_flag = 0;
            }

            else
            {
                key_hold_ms = 0;
            }
            if((key_hold_ms <= 100 )&&(key_hold_ms >= 0)&&(enter_flag == 1))
            {
                BEEP_flag = 1;
            }

        }

    }
    //--------------------------------------------------------//

    if(up_flag == 1)
    {
        if(key_up == 0)
        {

            if(key_hold_ms <= 100)
            {
                key_hold_ms ++;//假如一直保持按下状态
            }
            else if(key_hold_ms > 100)//长按
            {
                key_hold_ms = 0;
                up_long_flag = 1;
                up_flag = 0;
            }
        }
        else
        {
            if((key_hold_ms <= 100 ))//短按
            {
                key_hold_ms = 0;
                up_short_flag = 1;
                BEEP_flag = 1;
                up_flag = 0;
            }

        }

    }
    else//down_flag = 0
    {
        if(key_up !=0)
        {
            up_long_flag = 0;
        }
    }

    //--------------------------------------------------------//
    if(down_flag == 1)
    {

        if(key_down == 0)
        {

            if(key_hold_ms <= 100)
            {
                key_hold_ms ++;//假如一直保持按下状态
            }
            else if(key_hold_ms > 100)//长按
            {
                key_hold_ms = 0;
                down_long_flag = 1;
                down_flag = 0;
            }
        }
        else
        {

            if((key_hold_ms <= 100 ))//短按
            {
                key_hold_ms = 0;
                down_short_flag = 1;
                BEEP_flag = 1;
                down_flag = 0;
            }

        }

    }
    else//down_flag = 0
    {
        if(key_down !=0)
        {
            down_long_flag = 0;
        }
    }
    //--------------------------------------------------------//
    if(sleep_flag == 1)
    {
        if(SLEEP_ON_FLAG == 1)
        {

            sleep_cont ++ ;
            if(sleep_cont == 100)
            {
                sleep_second ++;
                sleep_cont = 0;
            }
            if(sleep_second == SET_SLEEP_MINUTE*60 + SET_SLEEP_SECOND)
            {
                if((menu_flag == 0)&&(auto_power_off_flag == 0))//在主菜单并且自动关机标志位为0
                {
                    SLEEP_INIT_FLAG = 1;
                    Temp_Set = IRON_TEMP_SET_SLEEP;//休眠设定温度
                    sleep_second = 0;
                    BEEP_flag = 1;
                    TEMP_SET_INIT_FLAG = 1;
                    //系统开始休眠
                }


            }
        }
				//下部分是自动关机的函数
				if(AUTO_SHUTDOWN_ON_FLAG == 1)//如果自动关机设置打开的话
				{
					shutdown_cont ++;
					 if(shutdown_cont == 100)//一秒钟加一秒
            {
                shutdown_second ++;
                shutdown_cont = 0;
            }
						if(shutdown_second == AUTO_SHUTDOWN_MINUTE*60)//到达关机时间时
            {
							//系统软关机
							auto_power_off_flag = 1;
							shutdown_second = 0;
							pwm_flag = 0;
							oled_off_on_flag = 1;//开始准备熄屏计时
						}
						
				}
				if(oled_off_on_flag == 1)
				{
						olde_off_cont ++;
					 if(olde_off_cont == 100)//一秒钟
            {
                oled_off_second ++;
                olde_off_cont = 0;
            }
						if(oled_off_second == 60)//达到一分钟确认熄屏
						{
							auto_oled_off_flag = 1;//此标志位置为1，准备熄屏
							oled_handle_flag = 1;
							oled_off_second = 0;
						}
				}

    }
    else
    {
        sleep_cont = 0;
        sleep_second = 0;
        SLEEP_INIT_FLAG = 0;
				shutdown_cont = 0;
				shutdown_second = 0;
			  auto_power_off_flag = 0;
			  auto_oled_off_flag = 0;
			  oled_off_on_flag = 0;
			if(oled_handle_flag == 1)
			{
				//加入一个标志位用于亮屏
				oled_light_flag = 1;
				//
				oled_handle_flag = 0;
			}

    }
    if(menu_flag != 0)
    {
        SLEEP_INIT_FLAG = 0;
		   	auto_power_off_flag = 0;
    }
}

void TM4_Isr() interrupt 20
{

    PWM_CONT++;
    if(PWM_CONT == 8)//0.05s
    {
        if((error_flag == 1)&&(menu_flag == 0)&&(adc_iron_flag == 1)&&(low_battery_flag == 0)&&(auto_power_off_flag == 0))//只有烙铁插入,并且不为低电压状态，在主菜单才开启pwm
        {
            pwm_flag = !pwm_flag;

        }
        PWM_CONT = 0;
    }
    if((PWM_CONT == 7)&&(pwm_flag == 0))
    {
        ADC_GET_FLAG = 1;
        //iron_ad = adc_once(ADC_IRON_TEMP, ADC_10BIT);
    }                               //测试端口
    AUXINTIF &= ~0x04;                          //清中断标志
}
void TM3_Isr() interrupt 19
{
    if(BEEP_flag == 1)
    {
        BEEP_CONT ++;
        if(BEEP_CONT == 5)
        {
            BEEP_flag = 0;
            BEEP_CONT = 0;

        }
    }                              //测试端口
    AUXINTIF &= ~0x02;                          //清中断标志
}

void adc_iron_get_handle(void)
{
    if(ADC_GET_FLAG == 1)
    {
        iron_ad = adc_once(ADC_IRON_TEMP, ADC_10BIT);
        ADC_GET_FLAG = 0;
    }
}

void OLED_sleep_handle(void)
{
    if(SLEEP_INIT_FLAG == 1)
    {
        OLED_WR_Byte(0x81,OLED_CMD);//设置对比度
        OLED_WR_Byte(0x00,OLED_CMD);
    }
    else
    {
        OLED_WR_Byte(0x81,OLED_CMD);//设置对比度
        OLED_WR_Byte(page_two_data[1][2],OLED_CMD);
    }
}