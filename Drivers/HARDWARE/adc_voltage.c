#include "adc_voltage.h"

__IO uint16_t ADC_converted_value=0;               //ADCת���ĵ�ص�ѹ16λ��ֵ
float battery_voltage=0.0;                         //��ص�ѹ
uint16_t ADC_converted_count=0;                    //ADת����ʱ����
uint8_t battery_low_voltage_count=0;               //��ص͵�ѹ��������
uint8_t battery_low_voltage_flag=0;                //��ص͵�ѹ��־λ


/************************************************
�������� �� Battery_Low_Voltage_Warning
�������� �� ��ص͵�ѹ���Ʒ�����������ֹ����
��    �� �� ��
�� �� ֵ �� ��
*************************************************/	
void Battery_Low_Voltage_Warning(void)
{
	if(battery_low_voltage_flag == 1)                //�����ص͵�ѹ��־λΪ1
	{
		BEE(BEE_ON);                                   //����������
	}
}




