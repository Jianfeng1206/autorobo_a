#ifndef __WT901C_H
#define __WT901C_H
#include "main.h"

void WTIMU_Application(void);                 //����9��IMUӦ�ú���

extern uint8_t u_rx_buf_4[50];                //usart4���ջ�������	
extern uint8_t WTIMU_unpack_correct_flag;     //����9��IMUһ֡���ݽ����ȷ��־λ	
extern uint8_t WTIMU_DMA_receive_flag;        //DMA����һ֡����9��IMUЭ��������ɱ�־λ
extern uint16_t WTIMU_data_length;            //DMA����һ֡����9��IMUЭ�����ݳ���
extern uint8_t loop_count;                    //ѭ����������
extern uint16_t loop_sum;                     //forѭ���е���ͱ���
extern float WT_IMU_pitch;                  	//����9��IMU����ĸ�����x
extern float WT_IMU_roll;                   	//����9��IMU����ĺ����y
extern float WT_IMU_yaw;                    	//����9��IMU����ĺ����z
extern float yaw_target_range;              	//Ŀ�껷��Χ���ǶȾ���ֵС��Ŀ�껷ʱ�����������ж�
extern float yaw_dead_zone_range;           	//��������Χ���ǶȾ���ֵС��������ʱ���Ϊ0
extern uint8_t yaw_dead_zone_range_flag;      //������������־λ


#endif


