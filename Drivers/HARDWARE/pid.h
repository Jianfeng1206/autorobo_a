#ifndef __PID_H
#define __PID_H
#include "motor.h"

typedef struct
{
  float Kp;                       //����ϵ��Proportional
  float Ki;                       //����ϵ��Integral
  float Kd;                       //΢��ϵ��Derivative

  float Ek;                       //��ǰ���
  float Ek1;                      //ǰһ����� e(k-1)
  float Ek2;                      //��ǰһ����� e(k-2)
  float LocSum;                   //�ۼƻ���λ��
}PID_LocTypeDef;                  //λ��ʽPID�ṹ��

typedef struct
{
  float Kp;                       //����ϵ��Proportional
  float Ki;                       //����ϵ��Integral
  float Kd;                       //΢��ϵ��Derivative

  float Ek;                       //��ǰ���
  float Ek1;                      //ǰһ����� e(k-1)
  float Ek2;                      //��ǰһ����� e(k-2)
}PID_IncTypeDef;                  //����ʽPID�ṹ��

extern PID_LocTypeDef AOA_PID;                       //����Ƕ�PID�ṹ��
extern PID_LocTypeDef LT_ANGLE_PID;                  //����ǽǶ�PID�ṹ��
extern PID_LocTypeDef LT_DISTANCE_PID;               //LT����PID�ṹ��
extern PID_LocTypeDef LT_X_PID;                      //Ŀ���׷��ģʽ���������x��PID�ṹ��
extern PID_LocTypeDef LT_Y_PID;                      //Ŀ���׷��ģʽ���������y��PID�ṹ��

float PID_Loc(float SetValue, float ActualValue, PID_LocTypeDef *PID); //λ��ʽPID����
float PID_Inc(float SetValue, float ActualValue, PID_IncTypeDef *PID); //����ʽPID����

void PID_Init(void);              //PID��ʼ������

#endif


