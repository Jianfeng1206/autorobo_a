#ifndef __MOTOR_H
#define __MOTOR_H
#include "main.h"

#define MOTOR1_F HAL_GPIO_WritePin(Motor1__Direction_GPIO_Port,Motor1__Direction_Pin,GPIO_PIN_RESET)      // PD7  1�ŵ����ת
#define MOTOR1_B HAL_GPIO_WritePin(Motor1__Direction_GPIO_Port,Motor1__Direction_Pin,GPIO_PIN_SET)    		// PD7  1�ŵ����ת
#define MOTOR2_F HAL_GPIO_WritePin(Motor2__Direction_GPIO_Port,Motor2__Direction_Pin,GPIO_PIN_RESET)      // PB3  2�ŵ����ת
#define MOTOR2_B HAL_GPIO_WritePin(Motor2__Direction_GPIO_Port,Motor2__Direction_Pin,GPIO_PIN_SET)    		// PB3  2�ŵ����ת
#define MOTOR3_F HAL_GPIO_WritePin(Motor3__Direction_GPIO_Port,Motor3__Direction_Pin,GPIO_PIN_RESET)      // PB4  3�ŵ����ת
#define MOTOR3_B HAL_GPIO_WritePin(Motor3__Direction_GPIO_Port,Motor3__Direction_Pin,GPIO_PIN_SET)    		// PB4  3�ŵ����ת
#define MOTOR4_F HAL_GPIO_WritePin(Motor4__Direction_GPIO_Port,Motor4__Direction_Pin,GPIO_PIN_RESET)      // PB5  4�ŵ����ת
#define MOTOR4_B HAL_GPIO_WritePin(Motor4__Direction_GPIO_Port,Motor4__Direction_Pin,GPIO_PIN_SET)   			// PB5  4�ŵ����ת

#define LIMIT(x, min, max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) )                       //ռ�ձ��޷�

extern int x1_output;                                //����ƽ�����������Χ[0��255]
extern int x1_increase;                              //����ƽ�������������Χ[0��127]����������ƽ�Ƶ��ٶ�
extern int y1_output;                                //ǰ���������������Χ[0��255]
extern int y1_increase;                              //ǰ�����������������Χ[0��127]������ǰ�����˵��ٶ�
extern int z1_output;                                //��ת���������Χ[0��255]
extern int z1_increase;                              //��ת�����������Χ[0��127]��������ת���ٶ�

void Moto1(int L, int R);
void Moto2(int L, int R);
void Move_Control(uint16_t x, uint16_t y , uint16_t z);
void Reinit_XYZ_Output(void);

#endif

