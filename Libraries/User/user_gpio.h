#ifndef USER_GPIO_H
#define USER_GPIO_H

#define Product_V2

#ifdef  Demo
#define key_up       P36
#define key_mode     P35
#define key_down     P51

#define key_up_pin           P0_2//P36
#define key_mode_pin         P0_4//P35
#define key_down_pin         P0_5//P51

#define PWM_control  PWM0_P06
#define SLEEP        P53
#define BEEP         PWM5_P50

#define ADC_VIN            ADC_P12
#define ADC_IRON_TEMP      ADC_P10
#define ADC_SYS_TEMP       ADC_P17
#endif

#ifdef  Product
#define CFG1           P22//P36
#define CFG2           P20//P35
#define CFG3           P21//P51

#define key_up           P02//P36
#define key_mode         P04//P35
#define key_down         P05//P51
#define key_sleep        P37

#define key_up_pin           P0_2//P36
#define key_mode_pin         P0_4//P35
#define key_down_pin         P0_5//P51
#define key_sleep_pin        P3_7//P51

#define PWM_control      PWM1_P17

#define BEEP             PWM0_P00

#define ADC_VIN            ADC_P12
#define ADC_IRON_TEMP      ADC_P11
#define ADC_SYS_TEMP       ADC_P10
#endif

#ifdef  Product_V2
#define CFG1           P22//P36
#define CFG2           P20//P35
#define CFG3           P21//P51

#define key_up           P02//P36
#define key_mode         P04//P35
#define key_down         P05//P51
#define key_sleep        P37

#define key_up_pin           P0_2//P36
#define key_mode_pin         P0_4//P35
#define key_down_pin         P0_5//P51
#define key_sleep_pin        P3_7//P51

#define PWM_control      PWM1_P17

#define BEEP             PWM0_P00

#define ADC_VIN            ADC_P12
#define ADC_IRON_TEMP      ADC_P11
#define ADC_SYS_TEMP       ADC_P10
#endif
#endif