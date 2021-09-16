/*
PID Controller library.
-----------------------------------------------------------------
Use a PID_Controller_TypeDef to create one instance of controller
-----------------------------------------------------------------
Ivan Kondrashov
http://github.com/RavenAjven
vpiroman@gmail.com
2021
-----------------------------------------------------------------
*/

#ifndef PIDREG_H

#define PIDREG_H

#include <stdint.h>

/*Определение типа данных "PID Controller"*/
typedef struct PID_Controller_TypeDef {
	float TargetValue;			       /*Уставка*/
	float CurrentValue;			       /*Текущее измеренное значение в цепи обратной связи*/
	float (*PID_CurrentValueUpdateCallback)(void); /*Коллбэк для обновления измеренного значения, обратная связь*/
	/*-------------------------------------------------------------------*/
	/*Coefficients*/
	float Eror_Ratio;	/*Коэффициент усиления ошибки рассогласования*/
	float Prop_Ratio;	/*Пропорциональный коэффициент*/
	float Integral;		/*Накопление интеграла ошибки*/
	float Integral_Ratio;	/*Интегральный коэффициент*/
	float Derivative_Ratio; /*Дифференциальный коэффициент*/
	/*-------------------------------------------------------------------*/
	/*Components*/
	float ErrorT;		 /*Ошибка рассогласования*/
	float ErrorPreviusValue; /*Предыдущее значение ошибки рассогласования*/
	float Reg_Proportional;	 /*Пропорциональная составляющая*/
	float Reg_Integral;	 /*Интегральная составляющая*/
	float Reg_Derivative;	 /*Дифференциальная составляющая*/
	/*-------------------------------------------------------------------*/
	float PID_ControllerOut; /*Выход управляющего значения*/
	/*-------------------------------------------------------------------*/

	/*Свойства и флаги экземпляра контроллера
Использует отдельные биты в переменной "PID_Controller_Properties"
[0] - Enabled/Disabled
[1] - Reserved
[2] - Reserved
[3] - Reserved
[4] - Reserved
[5] - Reserved
[6] - Reserved
[7] - Reserved
*/

uint8_t PID_Controller_Properties;
#define PID_CONTROLLER_ENABLE 0x01 /*Битовая маска для 0 бита*/
	/*-------------------------------------------------------------------*/
} PID_Controller_TypeDef;

/*Перечисление коэффициентов, используется в функции PID_SetNewCoefficient*/
typedef enum {
	PID_ERROR_COEF,
	PID_PROPORTIONAL_COEF,
	PID_INTEGRAL_COEF,
	PID_DERIVATIVE_COEF
} PID_CoefficientList;

/*Стоп контроллера*/
void PID_Start(PID_Controller_TypeDef *pPID_Controller);

/*Старт контроллера*/
void PID_Stop(PID_Controller_TypeDef *pPID_Controller);

/*Инициализация контроллера*/
void PID_Init(PID_Controller_TypeDef *pPID_Controller, float TargetValue, float Error_Ratio, float Prop_Ratio, float Integral_Ratio, float Derivative_Ratio, float (*PID_CurrentValueUpdateCallback)(void));

/*Деинициализация контроллера*/
void PID_Deinit(PID_Controller_TypeDef *pPID_Controller);

/*Получить управляющее значение контроллера*/
float PID_GetControllerOut(PID_Controller_TypeDef *pPID_Controller);

/*Обработка ПИД. Вызвать в цикле программы или в задаче RTOS*/
void PID_Processing(PID_Controller_TypeDef *pPID_Controller);

/*Задать новую уставку*/
void PID_SetNewTargetValue(PID_Controller_TypeDef *pPID_Controller, float NewTarget);

/*Изменить коэффициент*/
void PID_SetNewCoefficient(PID_Controller_TypeDef *pPID_Controller, PID_CoefficientList PID_WhatChange, float NewtValue);

#endif