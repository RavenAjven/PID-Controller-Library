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

#include <stdint.h>
#include "pidreg.h"

/*Start of the PID controller
(C���� ���-�����������*/
void PID_Start(PID_Controller_TypeDef *pPID_Controller)
{
	pPID_Controller->PID_Controller_Properties |= PID_CONTROLLER_ENABLE;
}

/*Stop of the PID controller
(C��� ���-�����������*/
void PID_Stop(PID_Controller_TypeDef *pPID_Controller)
{
	pPID_Controller->PID_Controller_Properties &= !PID_CONTROLLER_ENABLE;
}

void PID_Processing(PID_Controller_TypeDef *pPID_Controller)
{
  if (pPID_Controller->PID_Controller_Properties & PID_CONTROLLER_ENABLE)
  {
	pPID_Controller->ErrorPreviusValue = pPID_Controller->ErrorT;    
	pPID_Controller->Reg_Proportional = pPID_Controller->Prop_Ratio * pPID_Controller->ErrorT;
        pPID_Controller->Integral = pPID_Controller->Integral + (pPID_Controller->ErrorT + pPID_Controller->ErrorPreviusValue)/2;
        pPID_Controller->Reg_Integral = pPID_Controller->Integral * (1 / pPID_Controller->Integral_Ratio);
        pPID_Controller->Reg_Derivative = pPID_Controller->Derivative_Ratio*(pPID_Controller->ErrorT - pPID_Controller->ErrorPreviusValue);
        pPID_Controller->PID_RegulatorOut = pPID_Controller->Reg_Proportional +
                                            pPID_Controller->Reg_Integral +
                                            pPID_Controller->Reg_Derivative;
  }
}

/*Changing the target value 
(��������� �������)*/
void PID_ChangeTargetValue(PID_Controller_TypeDef *pPID_Controller, float NewTarget)
{
	pPID_Controller->TargetValue = NewTarget;
}

void PID_ChangeCoefficient(PID_Controller_TypeDef *pPID_Controller, PID_CoefficientList PID_WhatChange, float NewtValue)
{   
	switch (PID_WhatChange) { /*What change? (��� ��������?)*/
	case EC_ERROR_COEF: {
                /*Error Gain Coefficient (����������� �������� ������)*/
		pPID_Controller->Eror_Ratio = NewtValue;
		break;
	}
	case PC_PROPORTIONAL_COEF: {
                /*Proportinal Coefficient (���������������� �����������)*/
		pPID_Controller->Prop_Ratio = NewtValue;
		break;
	}
	case IC_INTEGRAL_COEF: {
                /*Integral Coefficient (������������ �����������)*/
		pPID_Controller->Integral_Ratio = NewtValue;
		break;
	}
	case DC_DERIVATIVE_COEF: {
                /*Derivative Coefficient (���������������� �����������)*/
		pPID_Controller->Derivative_Ratio = NewtValue;
		break;
	}
	}
}