#ifndef USER_ADC_H
#define USER_ADC_H
#include "headfile.h"
extern float Iron_temp_now;
extern float SHOW_IRON_TEMP;


extern uint8 error_flag;//≈–∂œ¿”Ã˙ «∑Ò≤Â»Î
extern uint8 low_battery_flag;
extern uint8 adc_iron_flag;

#define IRON_PARM_0                  (float)page_two_data[5][0]
#define IRON_PARM_100                (float)page_two_data[5][1]
#define IRON_PARM_200                (float)page_two_data[5][2]
#define IRON_PARM_300                (float)page_two_data[5][3]
#define IRON_PARM_400                (float)page_two_data[5][4]
#define IRON_PARM_500                (float)page_two_data[5][5]
#define IRON_PARM_600                (float)page_two_data[5][6]

void user_adc_init(void);
float adc_vin_get();
float adc_sys_temp_get();
void adc_iron_temp(uint16 temp_data);
uint16 adc_get_filter(uint16 get_init_data);

#endif





