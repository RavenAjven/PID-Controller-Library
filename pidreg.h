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

#ifndef  PIDREG_H
#define  PIDREG_H

/*Definition of the "PID Controller" type
Определение типа "ПИД-Контроллер"*/
typedef struct PID_Controller_TypeDef 
{
float TargetValue; /*Target Value (Целевое значение для регулятора)*/
float CurrentValue; /*CurrentValue (Текущее, измеренное значение)*/
float (*PID_CurrentValueUpdateCallback) (void);
/*-------------------------------------------------------------------*/
/*Coefficients (Коэффициенты)*/
float Eror_Ratio; /*Error Gain Coefficient (Коэффициент усиления ошибки)*/
float Prop_Ratio; /*Proportinal Coefficient (Пропорциональный коэффициент)*/
float Integral; /*Integral Of Error (Интеграл ошибки)*/
float Integral_Ratio; /*Integral Coefficient (Интегральный Коэффициент)*/
float Derivative_Ratio; /*Derivative Coefficient (Дифференциальный Коэффициент)*/
/*-------------------------------------------------------------------*/
/*Components (Составляющие)*/
float ErrorT; /*Error (Ошибка рассогласования)*/
float ErrorPreviusValue; /*Previus Error (Предыдущее значение ошибки)*/
float Reg_Proportional; /*Proportinal Component (Пропорциональная составляющая регулятора)*/
float Reg_Integral; /*Integral Component (Интегральная составляющая регулятора)*/
float Reg_Derivative; /*Derivative Component (Дифференциальная составляющая регулятора)*/
/*-------------------------------------------------------------------*/
float PID_RegulatorOut; /*Выход регулятора*/

/*Properties and flags of the controller instance
This uses the individual bits in the variable "PID_Controller_Properties"
Свойства и флаги экземляра ПИД-контроллера
Используются отдельные биты в uint8_t переменной "PID_Controller_Properties"

[0] - Enabled/Disabled (Контроллер: Активен/Не активен)
[1] - Reserved (Зарезервирован)
[2] - Reserved (Зарезервирован)
[3] - Reserved (Зарезервирован)
[4] - Reserved (Зарезервирован)
[5] - Reserved (Зарезервирован)
[6] - Reserved (Зарезервирован)
[7] - Reserved (Зарезервирован)
*/
uint8_t PID_Controller_Properties;
#define PID_CONTROLLER_ENABLE 0x01
/*-------------------------------------------------------------------*/
} PID_Controller_TypeDef;

/*List of coefficients
Список коэффициентов*/
typedef enum 
{
EC_ERROR_COEF,
PC_PROPORTIONAL_COEF,
IC_INTEGRAL_COEF,
DC_DERIVATIVE_COEF
} PID_CoefficientList;

/*Start of the PID controller
(Cтарт ПИД-Контроллера)*/
void PID_Start (PID_Controller_TypeDef *pPID_Controller);

/*Stop of the PID controller
(Стоп ПИД-Контроллера)*/
void PID_Stop(PID_Controller_TypeDef *pPID_Controller);

void PID_Init (void);

void PID_Deinit(void);

/*Call it in a program loop
(Вызывать в цикле программы)*/
void PID_Processing (PID_Controller_TypeDef *pPID_Controller);

/*Changing the target value 
(Изменение уставки)*/
void PID_ChangeTargetValue (PID_Controller_TypeDef *pPID_Controller, float NewTarget);

/*Changing the coefficient value
(Изменение коэффициента)
*/
void PID_ChangeCoefficient(PID_Controller_TypeDef *pPID_Controller, PID_CoefficientList PID_WhatChange, float NewtValue);

#endif