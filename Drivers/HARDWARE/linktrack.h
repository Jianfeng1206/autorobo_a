#ifndef __LINKTRACK_H
#define __LINKTRACK_H
#include "main.h"

void LT_Application(void);                    //LinkTrack��λӦ�ú���

extern uint8_t u_rx_buf_1[256];               //usart1���ջ�������	
extern uint8_t LT_unpack_correct_flag;        //LinkTrackһ֡���ݽ����ȷ��־λ	
extern uint8_t LT_DMA_receive_flag;           //DMA����һ֡LinkTrackЭ�飨Node_Frame2��������ɱ�־λ
extern uint16_t LT_data_length;               //DMA����һ֡LinkTrackЭ�飨Node_Frame2�����ݳ���	
	
extern uint8_t LT_tag_id;                     //��ǩ��ID
extern uint32_t LT_local_time;                //LT��ǩ�ı���ʱ��
extern uint32_t LT_temp_local_time;           //LT��ǩ�ı���ʱ����ʱ������������ڼ���С��ƽ���ٶ�
extern float LT_pos_x;                      	//LinkTrack�����x����
extern float LT_pos_y;                      	//LinkTrack�����y����
extern float LT_pos_z;                      	//LinkTrack�����z����
extern float LT_expect_pos_x;               	//������x����
extern float LT_expect_pos_y;               	//������y����
extern float anchor_to_east_angle;       			//��վ����ϵ�붫����нǣ�С����ͷ����A0��A3���߷����ã�
extern float now_to_target_angle;           	//��ǰ����㵽Ŀ��������������x��н�
extern float forward_to_xaxis_angle;        	//��ǰС�����ߣ�ǰ��������x��н�
extern float forward_to_target_angle;       	//��ǰС�����ߣ�ǰ�������뵱ǰ���굽Ŀ���������ߵļн�	
extern uint8_t LT_start_flag;                 //�趨�����������𲽱�־λ
extern float yaw_expect;                    	//���������ֵ
extern float LT_dis_expect;                 	//��Ŀ�������֮����������ֵ
extern float LT_dis_measure;                	//��Ŀ�������֮�����Ĳ���ֵ�����������Ǻ������
extern float distance_target_range;         	//����Ŀ�귶Χ����λ����	
extern uint8_t LT_DT_data_length;             //LinkTrack��ǩ���յ����������ݳ���

extern float anchor_Vx;                       //�ػ�վ����ϵx�᷽���ٶȷ���
extern float anchor_Vy;                       //�ػ�վ����ϵy�᷽���ٶȷ���

#endif



