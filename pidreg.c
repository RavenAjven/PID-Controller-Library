/*
PID Controller library.
-----------------------------------------------------------------
Use a PID_Controller_TypeDef to create one instance of controller
Используйте PID_Controller_TypeDef для создания одного экземпляра контроллера
-----------------------------------------------------------------
Ivan Kondrashov
http://github.com/RavenAjven
vpiroman@gmail.com
2021
-----------------------------------------------------------------
*/

#include <stdint.h>
#include "pidreg.h"

void PID_Init (PID_Controller_TypeDef *pPID_Controller, float TargetValue, float Error_Ratio, float Prop_Ratio, float Integral_Ratio, float Derivative_Ratio, float (*PID_CurrentValueUpdateCallback)(void))
{
pPID_Controller->TargetValue = TargetValue;
pPID_Controller->Eror_Ratio = Error_Ratio;
pPID_Controller->Prop_Ratio = Prop_Ratio;
pPID_Controller->Integral_Ratio = Integral_Ratio;
pPID_Controller->Derivative_Ratio = Derivative_Ratio;
pPID_Controller->PID_CurrentValueUpdateCallback = PID_CurrentValueUpdateCallback;
}

void PID_Deinit(PID_Controller_TypeDef *pPID_Controller)
{
PID_Stop(pPID_Controller);
pPID_Controller->TargetValue = 0;
pPID_Controller->CurrentValue = 0;
pPID_Controller->PID_CurrentValueUpdateCallback = 0;
pPID_Controller->Eror_Ratio = 0;
pPID_Controller->Prop_Ratio = 0;
pPID_Controller->Integral = 0;
pPID_Controller->Integral_Ratio = 0;
pPID_Controller->Derivative_Ratio = 0;
pPID_Controller->ErrorT = 0;
pPID_Controller->ErrorPreviusValue = 0;
pPID_Controller->Reg_Proportional = 0;
pPID_Controller->Reg_Integral = 0;
pPID_Controller->Reg_Derivative = 0;
pPID_Controller->PID_ControllerOut = 0;
}

/*Start of the PID controller
(Cтарт ПИД-Контроллера*/
void PID_Start(PID_Controller_TypeDef *pPID_Controller)
{
	pPID_Controller->PID_Controller_Properties |= PID_CONTROLLER_ENABLE;
}

/*Stop of the PID controller
(Cтоп ПИД-Контроллера*/
void PID_Stop(PID_Controller_TypeDef *pPID_Controller)
{
	pPID_Controller->PID_Controller_Properties &= !PID_CONTROLLER_ENABLE;
}

void PID_Processing(PID_Controller_TypeDef *pPID_Controller)
{
  if (pPID_Controller->PID_Controller_Properties & PID_CONTROLLER_ENABLE)
  {
        pPID_Controller->CurrentValue = pPID_Controller->PID_CurrentValueUpdateCallback();
	pPID_Controller->ErrorPreviusValue = pPID_Controller->ErrorT;    
        pPID_Controller->ErrorT = pPID_Controller->TargetValue - pPID_Controller->CurrentValue;
	pPID_Controller->Reg_Proportional = pPID_Controller->Prop_Ratio * pPID_Controller->ErrorT;
        pPID_Controller->Integral = pPID_Controller->Integral + (pPID_Controller->ErrorT + pPID_Controller->ErrorPreviusValue)/2;
        pPID_Controller->Reg_Integral = pPID_Controller->Integral * (1 / pPID_Controller->Integral_Ratio);
        pPID_Controller->Reg_Derivative = pPID_Controller->Derivative_Ratio*(pPID_Controller->ErrorT - pPID_Controller->ErrorPreviusValue);
        pPID_Controller->PID_ControllerOut = pPID_Controller->Reg_Proportional +
                                            pPID_Controller->Reg_Integral +
                                            pPID_Controller->Reg_Derivative;
  }
}

/*Changing the target value 
(Изменение уставки)*/
void PID_SetNewTargetValue(PID_Controller_TypeDef *pPID_Controller, float NewTarget)
{
	pPID_Controller->TargetValue = NewTarget;
}

void PID_SetNewCoefficient(PID_Controller_TypeDef *pPID_Controller, PID_CoefficientList PID_WhatChange, float NewtValue)
{   
	switch (PID_WhatChange) { /*What change? (Что изменить?)*/
	case EC_ERROR_COEF: {
                /*Error Gain Coefficient (Коэффициент усиления ошибки)*/
		pPID_Controller->Eror_Ratio = NewtValue;
		break;
	}
	case PC_PROPORTIONAL_COEF: {
                /*Proportinal Coefficient (Пропорциональный коэффициент)*/
		pPID_Controller->Prop_Ratio = NewtValue;
		break;
	}
	case IC_INTEGRAL_COEF: {
                /*Integral Coefficient (Интегральный Коэффициент)*/
		pPID_Controller->Integral_Ratio = NewtValue;
		break;
	}
	case DC_DERIVATIVE_COEF: {
                /*Derivative Coefficient (Дифференциальный Коэффициент)*/
		pPID_Controller->Derivative_Ratio = NewtValue;
		break;
	}
	}
}

float PID_GetControllerOut (PID_Controller_TypeDef *pPID_Controller)
{
return pPID_Controller->PID_ControllerOut;
}