#ifndef __KEY_H
#define __KEY_H
#include "stm32h7xx.h"

#define READ_KEY1	HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)

extern uint8_t key_delay_count;               //�������������ʱ��������
extern uint8_t mode_selection;                //ģʽ�л����� 0��ң��ģʽ  1���Ƕȸ���ģʽ  2���ǶȾ���ȫ����ģʽ  3����λĿ����ƶ�ģʽ


#endif

