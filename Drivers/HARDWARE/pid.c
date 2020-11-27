#include "pid.h"

PID_LocTypeDef AOA_PID;                           //����Ƕ�PID�ṹ��
PID_LocTypeDef LT_ANGLE_PID;                      //����ǽǶ�PID�ṹ��
PID_LocTypeDef LT_DISTANCE_PID;                   //LT����PID�ṹ��
PID_LocTypeDef LT_X_PID;                          //Ŀ���׷��ģʽ���������x��PID�ṹ��
PID_LocTypeDef LT_Y_PID;                          //Ŀ���׷��ģʽ���������y��PID�ṹ��

/************************************************
�������� �� PID_Init
�������� �� PID������ʼ��
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void PID_Init(void)
{
	AOA_PID.Kp=2.5;                                 //2.0��3.0
	AOA_PID.Ki=0.0;                                 
	AOA_PID.Kd=-16.5;                               //-16    
	
	LT_ANGLE_PID.Kp=2.5;                                 
	LT_ANGLE_PID.Ki=0.0;                                 
	LT_ANGLE_PID.Kd=-16.5;   

	LT_DISTANCE_PID.Kp=20;                          //20       
	LT_DISTANCE_PID.Ki=0.0;                                 
	LT_DISTANCE_PID.Kd=0.0;   
	
	LT_X_PID.Kp=25;                                 //20       
	LT_X_PID.Ki=0.0;                                 
	LT_X_PID.Kd=0.0;  
	
	LT_Y_PID.Kp=25;                                 //20       
	LT_Y_PID.Ki=0.0;                                 
	LT_Y_PID.Kd=0.0;  
}


/************************************************
�������� �� PID_Loc
�������� �� PIDλ��(Location)����
��    �� �� SetValue ------ ����ֵ(����ֵ)
            ActualValue --- ʵ��ֵ(����ֵ)
            PID ----------- PID���ݽṹ
�� �� ֵ �� PIDLoc -------- PIDλ��
*************************************************/
float PID_Loc(float SetValue, float ActualValue, PID_LocTypeDef *PID)
{
  float PIDLoc;                                   //λ��

  PID->Ek = SetValue - ActualValue;               // ���㵱ǰ���
  PID->LocSum += PID->Ek;                         //�ۼ����

  PIDLoc = PID->Kp * PID->Ek + (PID->Ki * PID->LocSum) + PID->Kd * (PID->Ek1 - PID->Ek);

  PID->Ek1 = PID->Ek;                             // �����ϴ����  
	
	return PIDLoc;
}


/************************************************
�������� �� PID_Inc
�������� �� PID����(Increment)����
��    �� �� SetValue ------ ����ֵ(����ֵ)
            ActualValue --- ʵ��ֵ(����ֵ)
            PID ----------- PID���ݽṹ
�� �� ֵ �� PIDInc -------- ����PID����(+/-)
*************************************************/
float PID_Inc(float SetValue, float ActualValue, PID_IncTypeDef *PID)
{
  float PIDInc;                                   //�������

  PID->Ek = SetValue - ActualValue;               // ���㵱ǰ���
  PIDInc = (PID->Kp * PID->Ek) - (PID->Ki * PID->Ek1) + (PID->Kd * PID->Ek2);

  PID->Ek2 = PID->Ek1;                            // �������ϴ����
  PID->Ek1 = PID->Ek;                             // �����ϴ����
	
	return PIDInc;
}




