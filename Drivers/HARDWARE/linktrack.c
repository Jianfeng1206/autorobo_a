#include "linktrack.h"

uint8_t u_rx_buf_1[256];                 //usart1���ջ�������
uint8_t LT_unpack_correct_flag=0;        //LinkTrackһ֡���ݽ����ȷ��־λ
uint8_t LT_DMA_receive_flag=0;           //DMA����һ֡LinkTrackЭ�飨Node_Frame2��������ɱ�־λ
uint16_t LT_data_length=0;               //DMA����һ֡LinkTrackЭ�飨Node_Frame2�����ݳ���
	
uint8_t LT_tag_id=0;                     //��ǩ��ID
uint32_t LT_local_time=0;                //LT��ǩ�ı���ʱ��
uint32_t LT_temp_local_time=0;           //LT��ǩ�ı���ʱ����ʱ������������ڼ���С��ƽ���ٶ�
float LT_pos_x=0.0;                      //LinkTrack�����x����
float LT_pos_y=0.0;                      //LinkTrack�����y����
float LT_pos_z=0.0;                      //LinkTrack�����z����
float LT_expect_pos_x=0.0;               //������x����
float LT_expect_pos_y=0.0;               //������y����
float anchor_to_east_angle=0.0;       //��վ����ϵ�붫����нǣ�С����ͷ����A0��A3���߷����ã�   ע���ı��վλ�ú������²����н�
float now_to_target_angle=0.0;           //��ǰ����㵽Ŀ��������������x��н�
float forward_to_xaxis_angle=0.0;        //��ǰС�����ߣ�ǰ��������x��н�
float forward_to_target_angle=0.0;       //��ǰС�����ߣ�ǰ�������뵱ǰ���굽Ŀ���������ߵļн�
uint8_t LT_start_flag=0;                 //�趨�����������𲽱�־λ
float yaw_expect=0.0;                    //���������ֵ
float LT_dis_expect=0.0;                 //��Ŀ�������֮����������ֵ
float LT_dis_measure=0.0;                //��Ŀ�������֮�����Ĳ���ֵ�����������Ǻ������
float distance_target_range=0.5;         //����Ŀ�귶Χ����λ����
uint8_t LT_DT_data_length=0;             //LinkTrack��ǩ���յ����������ݳ���

float anchor_Vx=0.0;                     //�ػ�վ����ϵx�᷽���ٶȷ���
float anchor_Vy=0.0;                     //�ػ�վ����ϵy�᷽���ٶȷ���

/************************************************
�������� �� LT_Application
�������� �� LinkTrack��λӦ�ú���
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void LT_Application(void)
{
	if((u_rx_buf_1[0] == 0x55)&&(u_rx_buf_1[1] == 0x04))                        //������յ�����Node_Frame2�Ķ�λ֡
	{
		LT_unpack_correct_flag=g_nlt_nodeframe2.UnpackData(u_rx_buf_1,LT_data_length); //���ú���ָ�����н��뺯�������ؽ�����ȷ/ʧ��ֵ
		if(LT_unpack_correct_flag == 1)                                           //���������ȷ
		{
			LT_tag_id=g_nlt_nodeframe2.result.id;                                   //ȡ��ǰ���ӵı�ǩID
			LT_local_time=g_nlt_nodeframe2.result.local_time;                       //ȡ��ǰ���ӵı�ǩ�ı���ʱ��
			LT_pos_x=g_nlt_nodeframe2.result.pos_3d[0];                             //ȡLinkTrack�����x����
			LT_pos_y=g_nlt_nodeframe2.result.pos_3d[1];                             //ȡLinkTrack�����y����
		}
	}
	else if((u_rx_buf_1[0] == 0x55)&&(u_rx_buf_1[1] == 0x02))                   //������յ�����Node_Frame0������֡
	{
		LT_unpack_correct_flag=g_nlt_nodeframe0.UnpackData(u_rx_buf_1,LT_data_length); //���ú���ָ�����н��뺯�������ؽ�����ȷ/ʧ��ֵ
		if((LT_unpack_correct_flag == 1)&&(g_nlt_nodeframe0.result.valid_node_count>0))//���������ȷ���������ýڵ����0
		{
			LT_DT_data_length=g_nlt_nodeframe0.result.nodes[0]->data_length;        //ȡLinkTrack��ǩ���յ����������ݳ���
			if((g_nlt_nodeframe0.result.nodes[0]->data[2] == '.')&&
					(g_nlt_nodeframe0.result.nodes[0]->data[4] == ' ')&&
					 (g_nlt_nodeframe0.result.nodes[0]->data[7] == '.'))                  //�жϽ��յ��������Ƿ���ϸ�ʽ
			{
				LT_expect_pos_x=(float)(((uint8_t)(g_nlt_nodeframe0.result.nodes[0]->data[0])-48)*100+
																((uint8_t)(g_nlt_nodeframe0.result.nodes[0]->data[1])-48)*10+
																((uint8_t)(g_nlt_nodeframe0.result.nodes[0]->data[3])-48))/10;  //��������x����
				LT_expect_pos_y=(float)(((uint8_t)(g_nlt_nodeframe0.result.nodes[0]->data[5])-48)*100+
																((uint8_t)(g_nlt_nodeframe0.result.nodes[0]->data[6])-48)*10+
																((uint8_t)(g_nlt_nodeframe0.result.nodes[0]->data[8])-48))/10;  //��������y����
				LT_start_flag=1;                                                      //������յ����������꣬�𲽱�־λ��1
			}

		}				
	}
			
	if(mode_selection == 3)                                                     //������ڶ�λĿ����ƶ�ģʽ
	{
		if((LT_start_flag == 1)||(LT_start_flag == 2))                            //����𲽱�־λΪ1��2���׶�1��ֻת��  �׶�2����ת���ǰ����
		{
			forward_to_xaxis_angle=WT_IMU_yaw;                                      //��ǰС�����ߣ�ǰ��������x��н�
			now_to_target_angle=(float)(atan2(((double)(LT_expect_pos_y-LT_pos_y)),((double)(LT_expect_pos_x-LT_pos_x)))*180/3.14); //�����Ǻ������㵱ǰ����㵽Ŀ��������������x��н�
			forward_to_target_angle=now_to_target_angle-forward_to_xaxis_angle;     //�����ʱС�����ߣ�ǰ�������뵱ǰ���굽Ŀ���������ߵļн�
			yaw_expect=now_to_target_angle;                                         //�������������
															
			if(((yaw_expect-WT_IMU_yaw)>180)||((yaw_expect-WT_IMU_yaw)<-180))         //��������ֵС��180�ȵķ������ת��
			{
				z1_increase = (int)PID_Loc(yaw_expect, WT_IMU_yaw, &LT_ANGLE_PID);      //PID��������
			}
			else
			{
				z1_increase = -(int)PID_Loc(yaw_expect, WT_IMU_yaw, &LT_ANGLE_PID);     //PID��������
			}
			if(fabsf(yaw_expect-WT_IMU_yaw)<yaw_target_range)                         //�жϺ���ǲ���ֵ�Ƿ�ﵽ��Ŀ�껷��
			{
				yaw_dead_zone_range_flag=1;                                             //����ﵽĿ�껷�������������жϲ���λ��־λ
				LT_start_flag=2;                                                        //�𲽱�־λ��2���ڽǶ�PID���Ƶ�ͬʱ���о���PID����
			}
			if(yaw_dead_zone_range_flag == 1)                                         //�����������־λΪ1
			{
				if(fabsf(yaw_expect-WT_IMU_yaw)<yaw_dead_zone_range)                    //����ǶȲ�����ΧС����������Χ
				{
					z1_increase=0;                                                        //�����Ϊ0
				}
				else
				{
					yaw_dead_zone_range_flag=0;                                           //����ǶȲ�����Χ������������Χ����־λ����
				}
			}
			if(z1_increase>0)                                                         //���ֵ�Ӵ�һ�㣬��ֹС�Ƕ�ʱ�����Ħ���������ص���С��ת����
			{
				z1_increase+=20;
			}
			else if(z1_increase<0)
			{
				z1_increase-=20;
			}
			if(z1_increase>127)                                                       //����޷�
			{
				z1_increase=127;
			}
			else if(z1_increase<-127)
			{
				z1_increase=-127;
			}
			z1_output = z1_increase+127;                                              //�����������Χ
													
			LT_dis_measure=(float)sqrt(pow((double)(LT_expect_pos_x-LT_pos_x),2)+pow((double)(LT_expect_pos_y-LT_pos_y),2)); //�����ʱ�����������֮�����
			y1_increase = (int)PID_Loc( LT_dis_expect, LT_dis_measure, &LT_DISTANCE_PID); //PID��������
			if(y1_increase>0)                                                       //���ֵ�Ӵ�һ�㣬��ֹ�����Сʱ�����Ħ���������ص���С���߲���
			{
				y1_increase+=20;
			}
			else if(y1_increase<0)
			{
				y1_increase-=20;
			}
			if(y1_increase>127)                                                     //����޷�
			{
				y1_increase=127;
			}
			else if(y1_increase<-127)
			{
				y1_increase=-127;
			}
			y1_output = y1_increase+127;                                            //�����������Χ
			if(fabsf(LT_dis_expect-LT_dis_measure)<distance_target_range)           //�жϾ������ֵ�Ƿ�ﵽ��Ŀ�귶Χ�ڣ�������ֹͣ����
			{
				Move_Control( 127, 127, 127);                                         //ֹͣ
				LT_start_flag=3;                                                      //�𲽱�־λ��3��������һ��
			}
			else
			{
				if(LT_start_flag == 1)
				{
					Move_Control( 127, 127, z1_output);                                 //����PID���ֵ���нǶ��˶�����
				}
				else if(LT_start_flag == 2)
				{
					Move_Control( 127, y1_output, z1_output);                           //����PID���ֵ����ǰ���ͽǶ��˶�����
				}

			}

		}
		else if(LT_start_flag == 3)                                               //����𲽱�־λΪ3��������һ�����׶�3��������������ƽ��ֱ���������������ӽ�Ŀ��㣩
		{					
			anchor_Vx = PID_Loc( LT_expect_pos_x, LT_pos_x, &LT_X_PID);             //PID��������
			anchor_Vy = PID_Loc( LT_expect_pos_y, LT_pos_y, &LT_Y_PID);             //PID��������
			x1_increase=(int)(anchor_Vx*sin((double)WT_IMU_yaw*3.14/180)-anchor_Vy*cos((double)WT_IMU_yaw*3.14/180)); //������������ϵ��x���ٶ����������������ƽ�����������
			y1_increase=-(int)(anchor_Vx*cos((double)WT_IMU_yaw*3.14/180)+anchor_Vy*sin((double)WT_IMU_yaw*3.14/180)); //������������ϵ��y���ٶ������������ǰ���������������

			if(x1_increase>0)                                                       //���ֵ�Ӵ�һ�㣬��ֹ�����Сʱ�����Ħ���������ص���С���߲���
			{
				x1_increase+=20;
			}
			else if(x1_increase<0)
			{
				x1_increase-=20;
			}
			if(x1_increase>127)                                                     //����޷�
			{
				x1_increase=127;
			}
			else if(x1_increase<-127)
			{
				x1_increase=-127;
			}					
			if(y1_increase>0)                                                       //���ֵ�Ӵ�һ�㣬��ֹ�����Сʱ�����Ħ���������ص���С���߲���
			{
				y1_increase+=20;
			}
			else if(y1_increase<0)
			{
				y1_increase-=20;
			}
			if(y1_increase>127)                                                     //����޷�
			{
				y1_increase=127;
			}
			else if(y1_increase<-127)
			{
				y1_increase=-127;
			}
			x1_output = x1_increase+127;                                            //�����������Χ
			y1_output = y1_increase+127;                                            //�����������Χ
					
			if((fabsf(LT_expect_pos_x-LT_pos_x)<0.03)&&(fabsf(LT_expect_pos_y-LT_pos_y)<0.03)) //�жϾ������ֵ�Ƿ�ﵽ��Ŀ�귶Χ�ڣ�������ֹͣ����
			{
				Move_Control( 127, 127, 127);                                         //ֹͣ
				LT_start_flag=4;                                                      //�𲽱�־λ��4��������һ��
			}
			else
			{
				Move_Control( x1_output, y1_output, 127);                             //����PID���ֵ����ǰ���˶�����
			}
					
		}
		else
		{
			Move_Control( 127, 127, 127);                                           //����𲽱�־λΪ����ֵ��С��ֹͣ����ֹģʽ�л���ʧ��
		}
		
	}
	
}


