#include "motor.h"

int v1,v2,v3,v4 = 0;                              //4�������ռ�ձ�
uint8_t motor_dead_width1=90;                     //1�ŵ������
uint8_t motor_dead_width2=90;                     //2�ŵ������
uint8_t motor_dead_width3=90;                     //3�ŵ������
uint8_t motor_dead_width4=90;                     //4�ŵ������

int x1_output=127;                                //����ƽ�����������Χ[0��255]
int x1_increase=0;                                //����ƽ�������������Χ[0��127]����������ƽ�Ƶ��ٶ�
int y1_output=127;                                //ǰ���������������Χ[0��255]
int y1_increase=0;                                //ǰ�����������������Χ[0��127]������ǰ�����˵��ٶ�
int z1_output=127;                                //��ת���������Χ[0��255]
int z1_increase=0;                                //��ת�����������Χ[0��127]��������ת���ٶ�

/************************************************
�������� �� Reinit_XYZ_Output
�������� �� ��λǰ�����ˡ�����ƽ�ơ���ת���������������ֹģʽ�л���С��ʧ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Reinit_XYZ_Output(void)
{
	x1_output=127;                                //��������ƽ�������
	x1_increase=0;                                //��������ƽ���������
	y1_output=127;                                //����ǰ�����������
	y1_increase=0;                                //����ǰ�������������
	z1_output=127;                                //������ת�����
	z1_increase=0;                                //������ת�������
}

/************************************************
�������� �� Moto1
�������� �� ����1��2�ŵ��ת��
��    �� �� L ------ 1�ŵ��ռ�ձ�
						R ------ 2�ŵ��ռ�ձ�
�� �� ֵ �� ��
*************************************************/
void Moto1(int L, int R)
{
	if (L > 0)
	{
		TIM4->CCR1 = LIMIT(L, 0, 999);
	}
	else
	{
		TIM4->CCR1 = LIMIT(-L, 0, 999);
	}

	if (R > 0)
	{
		TIM4->CCR2 = LIMIT(R, 0, 999);
	}
	else
	{
		TIM4->CCR2 = LIMIT(-R, 0, 999);
	}
}

/************************************************
�������� �� Moto2
�������� �� ����3��4�ŵ��ת��
��    �� �� L ------ 3�ŵ��ռ�ձ�
						R ------ 4�ŵ��ռ�ձ�
�� �� ֵ �� ��
*************************************************/
void Moto2(int L, int R)
{
	if (L > 0)
	{
		TIM4->CCR3 = LIMIT(L, 0, 999);
	}
	else
	{
		TIM4->CCR3 = LIMIT(-L, 0, 999);
	}

	if (R > 0)
	{
		TIM4->CCR4 = LIMIT(R, 0, 999);
	}
	else
	{
		TIM4->CCR4 = LIMIT(-R, 0, 999);
	}
}

/************************************************
�������� �� Move_Control
�������� �� �����˶��ϳɿ���
��    �� �� x ------ ƽ�������
            y ------ ǰ�����������
            z ------ ת�������
�� �� ֵ �� ��
*************************************************/
void Move_Control(uint16_t x, uint16_t y ,uint16_t z) //�˶�����
{
	if( (abs(x-128)>3) || abs(y-128)>3)             //����ң�ص�ҡ�������ٽ��п���
	{
		v1= abs(y+x -256)*3  - z+128;                 //�����˶��ϳɣ��õ��ĸ������ת��
		v2= abs(y-x )*3      + z-128;
		v3= abs(y+x -256)*3  + z-128;
		v4= abs(y-x )*3      - z+128;	
			
		v1=v1*1.25+motor_dead_width1;                 //�ʵ�����ռ�ձȣ������ϵ������
		v2=v2*1.25+motor_dead_width2;
		v3=v3*1.25+motor_dead_width3;
		v4=v4*1.25+motor_dead_width4;
		
		Moto1(v1,v2);                                 //���Ƶ��ת��
		Moto2(v3,v4);	                                //���Ƶ��ת��
			
	  if(256-y-x<0 )                                //ȷ�����ת��
    { 
			MOTOR1_F;		
      MOTOR3_B;
		} 
    if(256-y-x>0 )
    { 
	    MOTOR1_B;		
      MOTOR3_F;
    }
	  if(y - x>0)
    {
    	MOTOR2_B;		
			MOTOR4_F;
    }
    if(y - x<0)
    { 
    	MOTOR2_F;		
			MOTOR4_B;
    }	
	}
	else if( abs(z-128)>3)                          //����ң�ص�ҡ�������ٽ��п���
	{
		if(z<128)                                     //ת���˶�����
		{
			v1=v2=v3=v4=abs(z-128)*2.5;
			MOTOR1_B;
			MOTOR2_B;
			MOTOR3_B;
			MOTOR4_B;	
			v1=v1*1.25+motor_dead_width1;
			v2=v2*1.25+motor_dead_width2;
			v3=v3*1.25+motor_dead_width3;
			v4=v4*1.25+motor_dead_width4;
			Moto1(v1,v2);
			Moto2(v3,v4);			
		}
		else
		{
			v1=v2=v3=v4=abs(z-128)*2.5;
			MOTOR1_F;
			MOTOR2_F;
			MOTOR3_F;
			MOTOR4_F;
			v1=v1*1.25+motor_dead_width1;
			v2=v2*1.25+motor_dead_width2;
			v3=v3*1.25+motor_dead_width3;
			v4=v4*1.25+motor_dead_width4;
			Moto1(v1,v2);
			Moto2(v3,v4);
		}
	}
	else
	{
		Moto1(0,0);
		Moto2(0,0);
	}
}


