/*
 * LED正极连接到PA0
 * PWM驱动LED呼吸灯
 */
#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"

uint8_t i;

int main(void)
{
	OLED_Init(); // 屏幕初始化
	PWM_Init();
	while (1)
	{
		for (i = 0; i <= 100; i++)
		{
			PWM_SetDuty(i);
			Delay_ms(10);
		}
		for (i = 0; i <= 100; i++)
		{
			PWM_SetDuty(100 - i);
			Delay_ms(10);
		}
	}
}
