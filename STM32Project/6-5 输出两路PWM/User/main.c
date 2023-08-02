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
		
	}
}
