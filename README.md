# PID-Controller-Library
Cross-platform, minimalistic PID controller library.
Allows you to create multiple instances of controllers as long as there is enough memory.

Use a *PID_Controller_TypeDef* to create one instance of controller:

```C
PID_Controller_TypeDef Example1_PID, Example2_PID;
```

You should create a callback function that returns *float*, from which the measured value will be updated:
```C
float ExampleUpdateValueCallback_1 (void)
{
uint16_t adc_data;
adc_data = ADC1->DR;
return (float)adc_data;
}

float ExampleUpdateValueCallback_2 (void)
{
uint16_t adc_data;
adc_data = ADC1->DR;
return (float)adc_data;
}
```
Then you should pass references to these functions when initializing the controller:
```C
PID_Init(&Example1_PID, 1, 1.5, 50.0, 1.2, 1.0, ExampleUpdateValueCallback_1);
PID_Init(&Example2_PID, 1, 2, 70.0, 5.2, 2.0, ExampleUpdateValueCallback_2);
PID_Start(&Example1_PID);
PID_Start(&Example2_PID);

while(1)
{
PID_Processing(&Example1_PID);
PID_Processing(&Example2_PID));
}
```
