#include "stm32f10x.h" // Device header
#include "PWM.h"

void Servo_Init(void)
{
    PWM_Init();
}

/*
 * 0° -- 500
 * 180° -- 250
 */
void Servo_SetAngle(float Angle)
{
    PWM_SetDuty(Angle / 180 * 2000 + 500); // 进行角度映射
}
