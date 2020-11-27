#ifndef __PSTWO_H
#define __PSTWO_H
#include "main.h"

#define DI   HAL_GPIO_ReadPin(PS2_DAT_GPIO_Port,PS2_DAT_Pin)                       //PB14 ����

#define DO_H HAL_GPIO_WritePin(PS2_COM_GPIO_Port,PS2_COM_Pin,GPIO_PIN_SET)         //PB15 ����λ��
#define DO_L HAL_GPIO_WritePin(PS2_COM_GPIO_Port,PS2_COM_Pin,GPIO_PIN_RESET)       //PB15 ����λ��

#define CS_H HAL_GPIO_WritePin(PS2_ATT_GPIO_Port,PS2_ATT_Pin,GPIO_PIN_SET)         //PB12 CS����
#define CS_L HAL_GPIO_WritePin(PS2_ATT_GPIO_Port,PS2_ATT_Pin,GPIO_PIN_RESET)       //PB12 CS����

#define CLK_H HAL_GPIO_WritePin(PS2_CLK_GPIO_Port,PS2_CLK_Pin,GPIO_PIN_SET)        //PB13 ʱ������
#define CLK_L HAL_GPIO_WritePin(PS2_CLK_GPIO_Port,PS2_CLK_Pin,GPIO_PIN_RESET)      //PB13 ʱ������

//��ֵ�궨��
#define PSB_SELECT      1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2          9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16
#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      26

#define PSS_RX 5                
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8

extern uint8_t data_ps2[9];                   //���ݴ洢����
extern uint16_t mask_ps2[16];                 //����ֵ�밴����
extern uint16_t handkey;                      //��ֵ�ݴ����

extern uint8_t PS2_delay_count1;              //PS2��ȡ��ʱ��������1��10ms��
extern uint8_t PS2_delay_count2;              //PS2��ȡ��ʱ��������2��50ms��
extern uint8_t PS2_delay_flag1;               //PS2��ȡ��ʱ������������1��10ms��
extern uint8_t PS2_delay_flag2;               //PS2��ȡ��ʱ������������2��50ms��
extern uint8_t PS2_DataKey_flag;              //key1=PS2_DataKey()���ִ�б�־����
extern uint8_t key1;                          //PS2��ֵ����
extern int x_data,y_data,z_data;              //PS2����ҡ��ģ����������xyΪ��ҡ�����ҡ����·���zΪ��ҡ�����ҷ���

uint8_t PS2_RedLight(void);                   //�ж��Ƿ�Ϊ���ģʽ
void PS2_ReadData(void);                      //��ȡ�ֱ�����
void PS2_Cmd(uint8_t CMD);		                //���ֱ���������
uint8_t PS2_DataKey(void);		                //��ֵ��ȡ
uint8_t PS2_AnologData(uint8_t button);       //�õ�һ��ҡ�˵�ģ����
void PS2_ClearData(void);	                    //������ݻ�����
void PS2_Application(void);                   //PS2Ӧ�ú���


#endif





