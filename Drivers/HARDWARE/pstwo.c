#include "pstwo.h"

uint8_t PS2_delay_count1=0;              //PS2��ȡ��ʱ��������1��10ms��
uint8_t PS2_delay_count2=0;              //PS2��ȡ��ʱ��������2��50ms��
uint8_t PS2_delay_flag1=0;               //PS2��ȡ��ʱ������������1��10ms��
uint8_t PS2_delay_flag2=0;               //PS2��ȡ��ʱ������������2��50ms��
uint8_t PS2_DataKey_flag=0;              //key1=PS2_DataKey()���ִ�б�־����
uint8_t key1=0;                          //PS2��ֵ����
int x_data,y_data,z_data=0;              //PS2����ҡ��ģ����������xyΪ��ҡ�����ҡ����·���zΪ��ҡ�����ҷ���

uint16_t handkey;                        //��ֵ�ݴ����
uint8_t comd[2]={0x01,0x42};	           //��ʼ�����������
uint8_t data_ps2[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //���ݴ洢����
uint16_t mask_ps2[]={
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
	};	                                   //����ֵ�밴����

/************************************************
�������� �� PS2_Application
�������� �� ͨ��PS2�ֱ�����С��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/	
void PS2_Application(void)
{
	if(PS2_DataKey_flag == 0)
	{
		key1=PS2_DataKey();
		PS2_DataKey_flag=1;
		if(PS2_delay_count1 == 0)
		{
			PS2_delay_count1 = 1;              //��ʼPS2��ȡ10ms��ʱ��ʱ
		}
	}		

	if((PS2_delay_flag1 == 1)||(PS2_delay_flag2 == 1))
	{
		PS2_DataKey_flag=0;
		PS2_delay_flag1=0;
		if(PS2_delay_count2 == 0)
		{
			if(PS2_delay_flag2 == 1)           //50ms��ʱ����
			{
				PS2_delay_flag2=0;
				LED1(ON);
				PS2_DataKey();	                 //�ֱ�����������
				x_data = PS2_AnologData(PSS_LX); //��ҡ�����ҷ���ҡ��ֵ��ȡ
				y_data = PS2_AnologData(PSS_LY); //��ҡ�����·���ҡ��ֵ��ȡ
				z_data = PS2_AnologData(PSS_RX); //��ҡ�����ҷ���ҡ��ֵ��ȡ
				if(mode_selection == 0)          //�������ң��ģʽ��
				{
					Move_Control(x_data, y_data, z_data);//����ҡ��ֵ�����˶�����
						
					if(key1 == 10)								 //�������10������		
					{
						Moto1(360, 360);
						Moto2(360, 360);
						MOTOR1_F;
						MOTOR2_F;
						MOTOR3_F;
						MOTOR4_F;
					}
					else if(key1 == 9)             //�������9������
					{
						Moto1(360, 360);
						Moto2(360, 360);
						MOTOR1_B;	
						MOTOR2_B;
						MOTOR3_B;
						MOTOR4_B;
					}
				}
					
			}														
			else if(!PS2_RedLight())           //������ں��ģʽ
			{
				if(PS2_delay_count2 == 0)
				{
					PS2_delay_count2 = 1;          //��ʼPS2��ȡ50ms��ʱ��ʱ
				}
				PS2_DataKey_flag=1;				 	 
			}
			else
			{		
				LED1(OFF);
				if(mode_selection == 0)          //�������ң��ģʽ
				{
					Moto1(0, 0);
					Moto2(0, 0);
				}
			}				
		}						
	}
}

/************************************************
�������� �� Delay_us
�������� �� us����ʱ�����������ʱ1000us
��    �� �� udelay ------ ��ʱʱ��
�� �� ֵ �� ��
*************************************************/
void Delay_us(uint32_t udelay)             
{
  uint32_t start_val,tickx,delayx,waits;
 
  start_val = SysTick->VAL;
  tickx = HAL_GetTick();
  //sysc = 480000;  //SystemCoreClock / (1000U / uwTickFreq);
  delayx =udelay * 480; //sysc / 1000 * udelay;
  if(delayx > start_val)
    {
      while(HAL_GetTick() == tickx)
        {
 
        }
      waits = 480000 + start_val - delayx;
      while(waits < SysTick->VAL)
        {
 
        }
    }
  else
    {
      waits = start_val - delayx;
      while(waits < SysTick->VAL && HAL_GetTick() == tickx)
        {
 
        }
    }
}	

/************************************************
�������� �� PS2_Cmd
�������� �� ���ֱ���������
��    �� �� CMD ------ ��Ҫ���͵�����
�� �� ֵ �� ��
*************************************************/
void PS2_Cmd(uint8_t CMD)
{
	volatile uint16_t ref=0x01;
	data_ps2[1] = 0;
	for(ref=0x01;ref<0x0100;ref<<=1)
	{
		if(ref&CMD)
		{
			DO_H;                              //���һλ����λ
		}
		else DO_L;

		CLK_H;                               //ʱ���ź�����
		Delay_us(10);
		CLK_L;
		Delay_us(10);
		CLK_H;
		if(DI)
			data_ps2[1] = ref|data_ps2[1];
	}
}

/************************************************
�������� �� PS2_RedLight
�������� �� �ж��Ƿ�Ϊ���ģʽ
��    �� �� ��
�� �� ֵ �� 0 ------ ���ģʽ
            ����ֵ - ����ģʽ
*************************************************/
uint8_t PS2_RedLight(void)
{
	CS_L;
	PS2_Cmd(comd[0]);                      //��ʼ����
	PS2_Cmd(comd[1]);                      //��������
	CS_H;
	if( data_ps2[1] == 0X73)
	{
		return 0 ;
	}
	else
	{
		return 1;
	}
		
}

/************************************************
�������� �� PS2_ReadData
�������� �� ��ȡ�ֱ�����
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void PS2_ReadData(void)
{
	volatile uint8_t byte=0;
	volatile uint16_t ref=0x01;

	CS_L;

	PS2_Cmd(comd[0]);                      //��ʼ����
	PS2_Cmd(comd[1]);                      //��������

	for(byte=2;byte<9;byte++)              //��ʼ��������
	{
		for(ref=0x01;ref<0x100;ref<<=1)
		{
			CLK_H;
			Delay_us(10);
			CLK_L;
			Delay_us(10);
			CLK_H;
		      if(DI)
		      data_ps2[byte] = ref|data_ps2[byte];
		}
        Delay_us(10);
	}
	CS_H;	
}

/************************************************
�������� �� PS2_DataKey
�������� �� �Զ�������PS2�����ݽ��д���ֻ�����˰������֣�Ĭ�������Ǻ��ģʽ��ֻ��һ����������ʱ
��    �� �� ��
�� �� ֵ �� 0 --------- ����δ����
            index+1 --- �������µļ�ֵ
*************************************************/
uint8_t PS2_DataKey()
{
	uint8_t index;

	PS2_ClearData();
	PS2_ReadData();

	handkey=(data_ps2[4]<<8)|data_ps2[3];          
	for(index=0;index<16;index++)
	{	    
		if((handkey&(1<<(mask_ps2[index]-1)))==0)
		return index+1;
	}
	return 0; 
}
//
/************************************************
�������� �� PS2_AnologData
�������� �� �õ�һ��ҡ�˵�ģ��������Χ0~256
��    �� �� button - ��Ҫ��ȡ��ҡ��ֵ
�� �� ֵ �� ҡ��ģ��ֵ
*************************************************/
uint8_t PS2_AnologData(uint8_t button)
{
	return data_ps2[button];
}

/************************************************
�������� �� PS2_ClearData
�������� �� ������ݻ�����
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void PS2_ClearData()
{
	uint8_t a;
	for(a=0;a<9;a++)
		data_ps2[a]=0x00;
}






