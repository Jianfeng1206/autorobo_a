#include "ws2812b.h"

uint8_t r_buffer[PIXEL_MAX]={0};                                 //��ɫRGBֵ
uint8_t g_buffer[PIXEL_MAX]={0};                                 //��ɫRGBֵ
uint8_t b_buffer[PIXEL_MAX]={0};                                 //��ɫRGBֵ

uint16_t RGB_delay=0;                                            //RGB������ʱ����ʱʱ��
uint16_t RGB_delay_count=0;                                      //RGB������ʱ����ʱʱ�������������ʾ�����˶��ٸ���ʱ����

/************************************************
�������� �� RGB_Show
�������� �� RGB��������ģʽ��ʾ��ͬ��Ч��
��    �� �� mode ------ ģʽ
�� �� ֵ �� ��
*************************************************/
void RGB_Show(uint8_t mode)
{
	switch(mode)                                                   //����ģʽ���ò�ͬ��RGB�ƹ�Ч��
	{
		case 0:				
			ColorWipe(Color(0, 255, 0), 200);
			break;
		case 1:
			Rainbow(200);
			break;
		case 2:
			Rainbow(25);
			break;
		case 3:
			RainbowCycle(25);
			break;
	}	
}

/************************************************
�������� �� Send_8_Bits
�������� �� ����8λ����
��    �� �� data ------ ��Ҫ���͵�����
�� �� ֵ �� ��
*************************************************/
void Send_8_Bits(uint8_t data)                                   //��RGB�ź��߷���8λ����
{
  uint8_t j=0;
  static uint8_t CodeOne=0x7c;                                   //����SPI����һ���ֽ���ģ�����1��ʱ�� 7c��3e
  static uint8_t CodeZero=0x70;                                  //����SPI����һ���ֽ���ģ�����0��ʱ�� 70��38
  
  for (j=0;j<8;j++)
  {
    if((data & 0x80)==0x80)
    {
      HAL_SPI_Transmit(&hspi1, &CodeOne, 1, 10);
    }
    else
    {
      HAL_SPI_Transmit(&hspi1, &CodeZero, 1, 10); 
    }
    data=data<<1;
  }
}

/************************************************
�������� �� Send_24_Bits
�������� �� ����24λ���ݿ���һ�����ص㣨����G--R--B��˳���ͣ�
��    �� �� RData ------ ��ɫ
            GData ------ ��ɫ
            BData ------ ��ɫ
�� �� ֵ �� ��
*************************************************/
void Send_24_Bits(uint8_t RData,uint8_t GData,uint8_t BData)     //��������3��8λ���ݣ�����һ�����ص�RGB��ʾ
{   
  Send_8_Bits(GData);  
  Send_8_Bits(RData); 
  Send_8_Bits(BData);
} 

/************************************************
�������� �� Pixel_Update
�������� �� ��λ����
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Pixel_Update(void)                                          //��λ������Ӧ�� >24us
{
  uint8_t a[24]={0};
  HAL_SPI_Transmit(&hspi1, a, 24, 10);
}

/************************************************
�������� �� Ws2812b_Init
�������� �� ��ʼ������
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Ws2812b_Init(void)                                          //��ʼ��������Ӧ�� >50us
{
  uint8_t Res_Code[50]={0};
  HAL_SPI_Transmit(&hspi1, Res_Code, 50, 10);
  SetAllPixelColor(0, 0, 0);
  HAL_Delay (1);
  SetAllPixelColor(0, 0, 0);
  HAL_Delay (1);
}

/************************************************
�������� �� SetAllPixelColor
�������� �� ���������ص�����Ϊͬһ����ɫ
��    �� �� R ------ ��ɫ
            G ------ ��ɫ
            B ------ ��ɫ
�� �� ֵ �� ��
*************************************************/
void SetAllPixelColor(uint8_t R, uint8_t G, uint8_t B)           //���������ص�����Ϊͬһ����ɫ
{ 
  uint8_t i=0;
  for(i=0;i<PIXEL_MAX;i++)
  {
    r_buffer[i]=0;
    g_buffer[i]=0;
    b_buffer[i]=0;
  }
  for(i=0;i<PIXEL_MAX;i++)
  {
    r_buffer[i]=R;
    g_buffer[i]=G;
    b_buffer[i]=B;
  }

  for(i=0;i<PIXEL_MAX;i++)
  {							  
    Send_24_Bits(r_buffer[i],g_buffer[i],b_buffer[i]);
  }
	Pixel_Update();
}

/************************************************
�������� �� setPixelColor
�������� �� �������õ�X+1�����ص����ɫ,�������ص�ȫ��Ϩ��
��    �� �� X ------ ��X+1�����ص�
            R ------ ��ɫ
            G ------ ��ɫ
            B ------ ��ɫ
�� �� ֵ �� ��
*************************************************/
void setPixelColor(uint16_t X, uint8_t R, uint8_t G, uint8_t B)  //�������õ�X+1�����ص����ɫ,�������ص�ȫ��Ϩ��
{	 
  uint8_t i=0;

  for(i=0;i<PIXEL_MAX;i++)
  {
    r_buffer[i]=0;
    g_buffer[i]=0;
    b_buffer[i]=0;
  }
  r_buffer[X]=R;
  g_buffer[X]=G;
  b_buffer[X]=B;
  for(i=0;i<PIXEL_MAX;i++)
  {							  
    Send_24_Bits(r_buffer[i],g_buffer[i],b_buffer[i]);
  }
  Pixel_Update();
}

/************************************************
�������� �� SetPixelColor
�������� �� �������õ�X+1�����ص����ɫ,�������ص㱣�ֲ���
��    �� �� X ------ ��X+1�����ص�
            D ------ RGB��ɫ
�� �� ֵ �� ��
*************************************************/
void SetPixelColor(uint16_t X, uint32_t D)                       //�������õ�X+1�����ص����ɫ,�������ص㱣�ֲ���
{	 
  uint8_t i=0;
	  
  r_buffer[X]=(uint8_t)(D>>16);
  g_buffer[X]=(uint8_t)(D>>8);
  b_buffer[X]=(uint8_t)D;

  for(i=0;i<PIXEL_MAX;i++)
  {							  
    Send_24_Bits(r_buffer[i],g_buffer[i],b_buffer[i]);
  }
	Pixel_Update();
}

/************************************************
�������� �� Color
�������� �� ��RGB 3����ɫ�ϲ���һ������
��    �� �� R ------ ��ɫ
            G ------ ��ɫ
            B ------ ��ɫ
�� �� ֵ �� �ϲ���uint32_t����
*************************************************/
uint32_t Color(uint8_t R, uint8_t G, uint8_t B)                  //��RGB 3����ɫ�ϲ���һ������
{
  return ((uint32_t)R << 16) | ((uint32_t)G <<  8) | B;
}

/************************************************
�������� �� Wheel
�������� �� �Ա������д���
��    �� �� Wheel_Pos ------ ��Ҫ����ı���
�� �� ֵ �� ������uint32_t����
*************************************************/
uint32_t Wheel(uint8_t Wheel_Pos)
{
  Wheel_Pos = 255 - Wheel_Pos;
  if(Wheel_Pos < 85) 
  {
    return Color(255 - Wheel_Pos * 3, 0, Wheel_Pos * 3);
  }
  if(Wheel_Pos < 170) 
	{
    Wheel_Pos -= 85;
    return Color(0, Wheel_Pos * 3, 255 - Wheel_Pos * 3);
  }
  Wheel_Pos -= 170;
  return Color(Wheel_Pos * 3, 255 - Wheel_Pos * 3, 0);
}

/************************************************
�������� �� Rainbow
�������� �� �ʺ�ģʽ
��    �� �� time ------ ÿ�θı����صļ��ʱ�䣬��λms
�� �� ֵ �� ��
*************************************************/
void Rainbow(uint16_t time)                                       //�ʺ�ģʽ
{
  uint16_t i;
  
	if(RGB_delay == 0)
	{
		for(i=0; i<PIXEL_MAX; i++)
    {
      SetPixelColor(i, Wheel((i+RGB_delay_count) & 255));
    }
//    Pixel_update();
		RGB_delay=time;
		RGB_delay_count++;
		if(RGB_delay_count == 256)
		{
			RGB_delay_count=0;
		}
		
	}
	
}

/************************************************
�������� �� RainbowCycle
�������� �� �ʺ�ѭ��ģʽ
��    �� �� time ------ ÿ�θı����صļ��ʱ�䣬��λms
�� �� ֵ �� ��
*************************************************/
void RainbowCycle(uint16_t time)                                  //�ʺ�ѭ��ģʽ
{
  uint16_t i;
  
	if(RGB_delay == 0)
	{
		for(i=0; i< PIXEL_MAX; i++) 
    {
      SetPixelColor(i, Wheel(((i * 256 / PIXEL_MAX) + RGB_delay_count) & 255));
    }
//    Pixel_update();
		RGB_delay=time;
		RGB_delay_count++;
		if(RGB_delay_count == 256*5)
		{
			RGB_delay_count=0;
		}

	}

}

/************************************************
�������� �� ColorWipe
�������� �� ���ε���ģʽ
��    �� �� D --------- RGB��ɫ
						time ------ ÿ�θı����صļ��ʱ�䣬��λms
�� �� ֵ �� ��
*************************************************/
void ColorWipe(uint32_t D, uint16_t time)                         //���ε���ģʽ
{	
	if(RGB_delay == 0)
	{
		if(RGB_delay_count == PIXEL_MAX)
		{
			SetAllPixelColor( 0, 0, 0);
		}
		else
		{
			SetPixelColor(RGB_delay_count, D);			
		}
//		Pixel_update();
		RGB_delay=time;
		RGB_delay_count++;
		if(RGB_delay_count == PIXEL_MAX+1)
		{
			RGB_delay_count=0;
		}
	}
	
}

/************************************************
�������� �� Ws2812b_Test
�������� �� RGB�������Գ���
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Ws2812b_Test(void)
{
  SetAllPixelColor(255, 0, 0);
  HAL_Delay (500);
  SetAllPixelColor(0, 255, 0);
  HAL_Delay (500);
  SetAllPixelColor(0, 0, 255);
  HAL_Delay (500);
  
  SetAllPixelColor(0, 0, 0);
  HAL_Delay (500);
  
  setPixelColor(0, 0, 255, 0);
  HAL_Delay (500);
  setPixelColor(2, 0, 0, 255);
  HAL_Delay (500); 
  setPixelColor(4, 255, 0, 0);
  HAL_Delay (500);
  setPixelColor(6, 125, 125, 125);
  HAL_Delay (500);    
  setPixelColor(5, 0, 255, 0);
  HAL_Delay (500);
  setPixelColor(3, 0, 0, 255);
  HAL_Delay (500); 
  setPixelColor(1, 255, 0, 0);
  HAL_Delay (500);
  SetAllPixelColor(0, 0, 0);
  HAL_Delay (50);
}






