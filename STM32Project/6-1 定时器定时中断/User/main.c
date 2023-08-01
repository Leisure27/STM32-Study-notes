#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t Num = 0;

int main(void)
{
	OLED_Init();  // 屏幕初始化
	Timer_Init(); // 初始化定时器
	
	OLED_ShowString(1, 1, "Num: ");

	while (1)
	{
		OLED_ShowNum(1, 5, Num, 5);
	}
}
