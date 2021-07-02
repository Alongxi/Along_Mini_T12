/*
------------------------------------------------------------
�ٷ���ַ��www.alongxii.xyz
������ߣ�Along
QQ��1259306443
���䣺alongxii@outlook.com/1259306443@qq.com
Ӳ�����ߣ�LI JIAN
QQ��1557731308
���䣺jian19990317@qq.com
Դ��ײ������ɿƼ���Դ�⣬�ڴ˻����Ͻ��ж��ο���������ȫ����Դ��Github��
����ǰ����ϵ����Along���������ѯ��
------------------------------------------------------------
2021.7.2
Դ����������V1.3.1�汾
���ܰ�����
1.��������
2.��Ļ����
3.��������
4.����ʱ������
5.�¶���ֵ����
6.�躸У׼����
7.��ԴЭ���������
8.�˵�UI����
��������ʹ�÷�����www.alongxii.xyz������ϸ���ܡ�
������ַ���ܻ����Ϊwww.alongxii.com/www.alongxii.cn��
------------------------------------------------------------
Դ������ļ����ܣ�
*user_gpio.h:����ӳ���ͷ�ļ����ɸ����Լ���·�Ĳ����޸�����ӳ�䣬��ADC�ӿ������P1�����⣬
IIC��SPI�ӿھ�����ģ��ӿڣ������Ͽ�����ӳ�䡣
main.c:���ļ�����Ҫ�ṩ�����ʼ�����ã����˵��ȹ��ܳ�����á�
user_menu.c:���ļ����ڲ˵�UIʹ�á�
user_adc.c:���ļ�����ADC�źŲɼ�����ѹֵת�����¶�ת����
�����¶ȶ�ȡ���÷ֶ�һ�κ��������ζ�ÿ��100�ȷֶε�adcֵ��������õ���Ӧ�¶�ֵ��
��ѹ�ɼ�ʹ�õ����ѹ��
user_pid.c:���ļ�����λ��ʽPID���п��£����и��Ƚ����Ʒ��������ڴ��ļ����޸Ŀ��ƺ�����
user_button.c:���ļ��ṩ��ذ����жϺ���������߼����������ܵ��÷�ʽ��
------------------------------------------------------------
*/
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











