
#include "headfile.h"
#include "user_adc.h"
/*float temp_res[30] =//����������0-29��ʱ�ĵ���ֵ(��λ��k��)
{
	27.65, 26.47, 25.34, 24.27, 23.25, 22.27, 21.35, 20.47, 19.63, 18.83,
	18.06, 17.34, 16.64, 15,98, 15.35, 14.74, 14.17, 13.62, 13.09, 12.59,
  12.11, 11.65, 11.21, 10.79, 10.39, 10.00, 9.569, 9.158, 8.768, 8.396,
};*/
uint8 error_flag = 1;
uint8 low_battery_flag = 0;
uint8 adc_iron_flag = 0;
float SHOW_IRON_TEMP;
float Iron_temp_now;
float Iron_temp_last;
float iron_k[4];//���������¶ȱ仯����Ϊһ��һ�κ�����y = kx + b
float iron_b[4];

void user_adc_init(void)
{
    adc_init(ADC_VIN, ADC_SYSclk_DIV_8);	//��ʼ��24V��ѹ��ȡ
    adc_init(ADC_IRON_TEMP, ADC_SYSclk_DIV_8);	//��ʼ��������ѹ
    adc_init(ADC_SYS_TEMP, ADC_SYSclk_DIV_8);	//��ʼ�����¼��
}

float adc_vin_get()//��ȡϵͳ��ѹ
{
    float vin_ad,temp = 0;
    float ad_array[51];
    int vin_data,i,j = 0;
    vin_data = adc_once(ADC_VIN, ADC_10BIT);
#ifdef Demo
    vin_ad = ((float)vin_data/1024.0)*(32.2/2.2)*3.3;//����һ����ʼ��ѹֵ
#endif
#ifdef Product
    vin_ad = ((float)vin_data/1024.0)*(28.7/4.7)*3.3;
#endif
#ifdef Product_V2
    vin_ad = ((float)vin_data/1024.0)*(51.7/4.7)*3.3;
#endif
    for(i = 0; i<51; i++)
    {
        ad_array[i] = vin_ad;//������50�ε�ѹ����adֵ��ֵ��������
    }
    for (j=0; j<50; j++) //����ð������
    {
        for (i=0; i<50-j; i++)
        {
            if ( ad_array[i]>ad_array[i+1] )
            {
                temp = ad_array[i];//��ֵ�������ʱ����
                ad_array[i] = ad_array[i+1];
                ad_array[i+1] = temp;
            }
        }
    }
    return ad_array[25];
}

float adc_sys_temp_get()//��ȡ����ϵͳ���¶�
{
    float temp,resister = 0;
    int temp_data_sys = adc_once(ADC_SYS_TEMP, ADC_10BIT);
    resister = 75.0f/((1024/(float)temp_data_sys) - 1);
    temp = -1.42f*resister + 39.16f;//�˺���ֻ��0-30��֮�����׼ȷ
    return temp;
}
#define FILTER_A
#define FILTER_N 12
uint16 filter_buf[FILTER_N + 1];

//�½�һ���˲��㷨
uint16 adc_get_filter(uint16 get_init_data)
{
//����ƽ���˲���
#ifdef FILTER_A
    //uint8 filter_i = 0;
    uint8 filter_count = 0;
    int filter_sum = 0;
    filter_buf[FILTER_N] = get_init_data;
    for(filter_count = 0; filter_count < FILTER_N; filter_count++)
    {
       // filter_sum += filter_buf[filter_count];
			    filter_buf[filter_count] = filter_buf[filter_count + 1]; // �����������ƣ���λ�Ե�
          filter_sum += filter_buf[filter_count];
    }
    return (uint16)(filter_sum / FILTER_N);

#endif
//
#ifdef FILTER_B
		
#endif

}

















//��ȡ������ADֵ������ת��Ϊ�¶�
void adc_iron_temp(uint16 temp_data)
{
    float temp = 0;

    if(temp_data < IRON_PARM_600)
    {
			  adc_iron_flag = 1;
        if(temp_data <= IRON_PARM_0)//��0-200��ʱ
        {

            temp = 0;
        }
        else if((IRON_PARM_0 <= temp_data)&&(temp_data <= IRON_PARM_200))//��0-200��ʱ
        {
            iron_k[0] = (200 - 0)/(IRON_PARM_200 - IRON_PARM_0);
            iron_b[0] = 200 - iron_k[0]*IRON_PARM_200;
            temp = iron_k[0]*(float)temp_data +  iron_b[0];
        }
        else if((IRON_PARM_200 < temp_data)&&(temp_data <= IRON_PARM_400))//��200-400��ʱ
        {
            iron_k[1] = (400 - 200)/(IRON_PARM_400 - IRON_PARM_200);
            iron_b[1] = 400 - iron_k[1]*IRON_PARM_400;
            temp = iron_k[1]*(float)temp_data +  iron_b[1];
        }
        else if((IRON_PARM_400 < temp_data)&&(temp_data <= IRON_PARM_500))//��400-500��ʱ
        {
            iron_k[2] = (500 - 400)/(IRON_PARM_500 - IRON_PARM_400);
            iron_b[2] = 500 - iron_k[2]*IRON_PARM_500;
            temp = iron_k[2]*(float)temp_data +  iron_b[2];
        }
        else if((IRON_PARM_500 < temp_data)&&(temp_data <= IRON_PARM_600))//��500-600��ʱ
        {
            iron_k[3] = (600 - 500)/(IRON_PARM_600 - IRON_PARM_500);
            iron_b[3] = 600 - iron_k[3]*IRON_PARM_600;
            temp = iron_k[3]*(float)temp_data +  iron_b[3];
        }
        Iron_temp_now  = temp + adc_sys_temp_get();//��ȡ��ǰ�����¶�
        //if((Iron_temp_last - Iron_temp_now> 150)||((Iron_temp_last - Iron_temp_now < -150)))//
        //{
        //Iron_temp_now = Iron_temp_last;
        //}

        if((SHOW_IRON_TEMP > Temp_Set - 10)&&(SHOW_IRON_TEMP < Temp_Set + 10))
        {
            SHOW_IRON_TEMP = Temp_Set;
        }
        else
        {
            SHOW_IRON_TEMP = Iron_temp_now;
        }
        Iron_temp_last = Iron_temp_now;
    }
		else
		{
			adc_iron_flag = 0;
            pwm_flag = 0;//��������
		}
}
