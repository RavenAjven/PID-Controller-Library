/*
PID Controller library.
-----------------------------------------------------------------
Use a PID_Controller_TypeDef to create one instance of controller
����������� PID_Controller_TypeDef ��� �������� ������ ���������� �����������
-----------------------------------------------------------------
Ivan Kondrashov
http://github.com/RavenAjven
vpiroman@gmail.com
2021
-----------------------------------------------------------------
*/

#ifndef  PIDREG_H
#define  PIDREG_H

/*Definition of the "PID Controller" type
����������� ���� "���-����������"*/
typedef struct PID_Controller_TypeDef 
{
float TargetValue; /*Target Value (������� �������� ��� ����������)*/
float CurrentValue; /*CurrentValue (�������, ���������� ��������)*/
float (*PID_CurrentValueUpdateCallback) (void);
/*-------------------------------------------------------------------*/
/*Coefficients (������������)*/
float Eror_Ratio; /*Error Gain Coefficient (����������� �������� ������)*/
float Prop_Ratio; /*Proportinal Coefficient (���������������� �����������)*/
float Integral; /*Integral Of Error (�������� ������)*/
float Integral_Ratio; /*Integral Coefficient (������������ �����������)*/
float Derivative_Ratio; /*Derivative Coefficient (���������������� �����������)*/
/*-------------------------------------------------------------------*/
/*Components (������������)*/
float ErrorT; /*Error (������ ���������������)*/
float ErrorPreviusValue; /*Previus Error (���������� �������� ������)*/
float Reg_Proportional; /*Proportinal Component (���������������� ������������ ����������)*/
float Reg_Integral; /*Integral Component (������������ ������������ ����������)*/
float Reg_Derivative; /*Derivative Component (���������������� ������������ ����������)*/
/*-------------------------------------------------------------------*/
float PID_RegulatorOut; /*����� ����������*/

/*Properties and flags of the controller instance
This uses the individual bits in the variable "PID_Controller_Properties"
�������� � ����� ��������� ���-�����������
������������ ��������� ���� � uint8_t ���������� "PID_Controller_Properties"

[0] - Enabled/Disabled (����������: �������/�� �������)
[1] - Reserved (��������������)
[2] - Reserved (��������������)
[3] - Reserved (��������������)
[4] - Reserved (��������������)
[5] - Reserved (��������������)
[6] - Reserved (��������������)
[7] - Reserved (��������������)
*/
uint8_t PID_Controller_Properties;
#define PID_CONTROLLER_ENABLE 0x01
/*-------------------------------------------------------------------*/
} PID_Controller_TypeDef;

/*List of coefficients
������ �������������*/
typedef enum 
{
EC_ERROR_COEF,
PC_PROPORTIONAL_COEF,
IC_INTEGRAL_COEF,
DC_DERIVATIVE_COEF
} PID_CoefficientList;

/*Start of the PID controller
(C���� ���-�����������)*/
void PID_Start (PID_Controller_TypeDef *pPID_Controller);

/*Stop of the PID controller
(���� ���-�����������)*/
void PID_Stop(PID_Controller_TypeDef *pPID_Controller);

void PID_Init (void);

void PID_Deinit(void);

/*Call it in a program loop
(�������� � ����� ���������)*/
void PID_Processing (PID_Controller_TypeDef *pPID_Controller);

/*Changing the target value 
(��������� �������)*/
void PID_ChangeTargetValue (PID_Controller_TypeDef *pPID_Controller, float NewTarget);

/*Changing the coefficient value
(��������� ������������)
*/
void PID_ChangeCoefficient(PID_Controller_TypeDef *pPID_Controller, PID_CoefficientList PID_WhatChange, float NewtValue);

#endif