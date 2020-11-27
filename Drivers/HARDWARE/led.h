#ifndef __LED_H
#define __LED_H
#include "stm32h7xx.h"

/** ����LED������ĺ꣬
	* LED�ߵ�ƽ��������ON=1��OFF=0
	* ��LED�͵�ƽ�����Ѻ����ó�ON=0 ��OFF=1 ����
	*/
#define OFF GPIO_PIN_SET
#define ON  GPIO_PIN_RESET

#define LED1(a)	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,a)
#define LED1_TOGGLE	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)

#define LED2(a)	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,a)
#define LED2_TOGGLE	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin)

#define LED3(a)	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,a)
#define LED3_TOGGLE	HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin)

#define LED4(a)	HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,a)
#define LED4_TOGGLE	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin)


#endif

