#ifndef __ADC_VOLTAGE_H
#define __ADC_VOLTAGE_H
#include "main.h"

#define LOW_VOLTAGE 7.4

extern __IO uint16_t ADC_converted_value;               //ADCת���ĵ�ص�ѹ16λ��ֵ
extern float battery_voltage;                           //��ص�ѹ
extern uint16_t ADC_converted_count;                    //ADת����ʱ����
extern uint8_t battery_low_voltage_count;               //��ص͵�ѹ��������
extern uint8_t battery_low_voltage_flag;                //��ص͵�ѹ��־λ

void Battery_Low_Voltage_Warning(void);                 //��ص͵�ѹ���Ʒ�����������ֹ���ź���

#endif

