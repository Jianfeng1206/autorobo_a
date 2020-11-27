#ifndef __BEE_H
#define __BEE_H
#include "stm32h7xx.h"

/** ���Ʒ�������ĺ꣬
	* �������ߵ�ƽ�죬����ON=1��OFF=0
	* ���������͵�ƽ�죬�Ѻ����ó�ON=0 ��OFF=1 ����
	*/
#define BEE_ON   GPIO_PIN_SET
#define BEE_OFF  GPIO_PIN_RESET

#define BEE(a)	HAL_GPIO_WritePin(BEE_GPIO_Port,BEE_Pin,a)
#define BEE_TOGGLE	HAL_GPIO_TogglePin(BEE_GPIO_Port, BEE_Pin)




#endif