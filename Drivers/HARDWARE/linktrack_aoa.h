#ifndef __LINKTRACK_AOA_H
#define __LINKTRACK_AOA_H
#include "main.h"

extern uint8_t u_rx_buf_2[256];               //usart2���ջ�������
extern uint8_t AOA_unpack_correct_flag;       //AOAһ֡���ݽ����ȷ��־λ
extern uint8_t AOA_DMA_receive_flag;          //DMA����һ֡AOAЭ��������ɱ�־λ
extern uint16_t AOA_data_length;              //DMA����һ֡AOAЭ�����ݳ���
extern uint8_t AOA_valid_node_count;          //AOA���ýڵ����������жϱ�ǩͻȻ�ϵ����
extern float angle_target_range;            	//˫�����������Ŀ�껷��Χ���ǶȾ���ֵС��Ŀ�껷ʱ�����������ж�
extern float angle_dead_zone_range;         	//˫�������������������Χ���ǶȾ���ֵС��������ʱ���Ϊ0
extern uint8_t angle_dead_zone_range_flag;    //������������־λ

extern float angle_measure;                   //�ǶȲ���ֵ
extern float angle_expect;                    //��ƫֵ���Ƕȸ�������ֵ

extern float dis_measure;                     //�������ֵ
extern float dis_expect;                      //������������ʱ������PID����ֵΪ�������ģ���λ��m
extern float dis_range;                       //����������������С����λ��m

void AOA_Application(void);                   //AOA����Ӧ�ú���

#endif


