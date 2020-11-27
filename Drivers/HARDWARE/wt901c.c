#include "wt901c.h"

uint8_t u_rx_buf_4[50];                  //usart4���ջ�������	
uint8_t WTIMU_unpack_correct_flag=0;     //����9��IMUһ֡���ݽ����ȷ��־λ	
uint8_t WTIMU_DMA_receive_flag=0;        //DMA����һ֡����9��IMUЭ��������ɱ�־λ
uint16_t WTIMU_data_length=0;            //DMA����һ֡����9��IMUЭ�����ݳ���
uint8_t loop_count=0;                    //ѭ����������
uint16_t loop_sum=0;                     //forѭ���е���ͱ���
float WT_IMU_pitch=0.0;                  //����9��IMU����ĸ�����x
float WT_IMU_roll=0.0;                   //����9��IMU����ĺ����y
float WT_IMU_yaw=0.0;                    //����9��IMU����ĺ����z
float yaw_target_range=2.0;              //Ŀ�껷��Χ���ǶȾ���ֵС��Ŀ�껷ʱ�����������ж�
float yaw_dead_zone_range=9.0;           //��������Χ���ǶȾ���ֵС��������ʱ���Ϊ0
uint8_t yaw_dead_zone_range_flag=0;      //������������־λ

/************************************************
�������� �� WTIMU_Application
�������� �� ���պͽ�������9��IMU������
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void WTIMU_Application(void)
{
	for(loop_count=22;loop_count<32;loop_count++)
	{
		loop_sum+=u_rx_buf_4[loop_count];                                         //����9��IMU����Ƕȵ�У���
	}
	if((uint8_t)loop_sum == u_rx_buf_4[32])                                     //��������У��͵ĵ��ֽڵ���Э���е�У��ͣ�˵��������ȷ
	{
		WT_IMU_yaw=(float)(((uint16_t)u_rx_buf_4[29]<<8)|(uint16_t)u_rx_buf_4[28])/32768*180; //ȡ9��IMU����ĺ����
	}
	loop_sum=0;                                                                 //������ͱ���
	if((WT_IMU_yaw>=0)&&(WT_IMU_yaw<90))                                        //����ϵ�н�ת����ת����Ϊ0�ȣ���Ϊ90�ȣ���Ϊ180��-180�ȣ�
	{
		WT_IMU_yaw+=90;
	}
	else
	{
		WT_IMU_yaw-=270;
	}
	if(anchor_to_east_angle>0)
	{
		if((WT_IMU_yaw<=anchor_to_east_angle-180)&&(WT_IMU_yaw>-180))             //����ϵ�н�ת����ת����A0��A3����Ϊ0��
		{
			WT_IMU_yaw+=360-anchor_to_east_angle;
		}
		else
		{
			WT_IMU_yaw-=anchor_to_east_angle;
		}
	}
	else if(anchor_to_east_angle<0)
	{
		if((WT_IMU_yaw>=180+anchor_to_east_angle)&&(WT_IMU_yaw<180))              //����ϵ�н�ת����ת����A0��A3����Ϊ0��
		{
			WT_IMU_yaw-=360+anchor_to_east_angle;
		}
		else
		{
			WT_IMU_yaw-=anchor_to_east_angle;
		}
	}
	
}
	