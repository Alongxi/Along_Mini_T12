
#include "headfile.h"
#include "user_gpio.h"
void main()
{
    DisableGlobalIRQ();	//�ر����ж�
    board_init();
    user_adc_init();//ADC��ʼ��
    button_init();//������ʼ��
    ALL_PWM_init();//PWM��ʼ��
		#ifdef HARDWARE_IIC
		//iic_change_pin(IIC_1,IIC1_SCL_P15,IIC1_SDA_P14);
	  //iic_init(IIC_1,IIC1_SCL_P15,IIC1_SDA_P14,0);
	  user_iic_init();
		#endif
    OLED_Init();//OLED��ʼ��
    pit_timer_ms(TIM_1, 10);//10ms�ж�
    pit_timer_ms(TIM_4, 10);//10ms�ж�
    pit_timer_ms(TIM_3, 10);//10ms�ж�

    CFG1 = 1;
    CFG2 = 0;
    CFG3 = 0;
    EnableGlobalIRQ();	//�������ж�
    eeprom_read(0x00,save_data_A,32);
    eeprom_read(0x20,save_data_B,32);
    data_restore();
    //data_init();
    Function_init();

    while(1)
    {
        top_menu(Temp_Set,SHOW_IRON_TEMP, (uint8)adc_sys_temp_get(), (uint8)adc_vin_get(), (int)((pwm_duty_out)*100/PWM_DUTY_MAX));
        show_menu();
        key_press();
        key_press_handler();
        OLED_sleep_handle();
        adc_iron_get_handle();
        adc_iron_temp(adc_get_filter(iron_ad));//��ȡADֵ

//        printf("sleep_cont:%d\r\n",sleep_cont);
//        printf("sleep_second:%d\r\n",sleep_second);
//        printf("Temp_init_flag:%bd\r\n",TEMP_SET_INIT_FLAG);
        printf("%d,%d\n",adc_get_filter(iron_ad),(uint16)Iron_temp_now);
//        printf("Vin:%f v\r\n",adc_vin_get());
//        printf("Res_temp:%f oC\r\n",adc_sys_temp_get());

    }
}











