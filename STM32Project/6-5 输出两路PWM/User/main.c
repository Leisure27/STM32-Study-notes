/*
 * LED正极连接到PA0
 * PWM驱动LED呼吸灯
 */
#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"

int main(void)
{
	OLED_Init(); // 屏幕初始化
	Motor_Init();
	while (1)
	{
	}
}
