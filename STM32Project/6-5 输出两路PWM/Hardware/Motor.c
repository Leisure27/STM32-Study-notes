#include "stm32f10x.h" // Device header
#include "PWM.h"

void Motor_Init(void)
{
    PWM_Init();
}

// 输出两路PWM
void Motor_SetSpeed(int8_t Speed)
{
    PWM_SetCompare2(Speed); // PA1输出PWM
    PWM_SetCompare3(0);     // PA2输出
}
