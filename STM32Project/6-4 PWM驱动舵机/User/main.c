/*
 * LED正极连接到PA0
 * PWM驱动LED呼吸灯
 */
#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"

uint8_t i;

int main(void)
{
	OLED_Init(); // 屏幕初始化
	Servo_Init();
	Servo_SetAngle(0); // 转到90度
	while (1)
	{
		for (int i = 0; i < 181; i++)
		{
			Servo_SetAngle(i);
			Delay_ms(10);
		}
		for (int i = 0; i < 181; i++)
		{
			Servo_SetAngle(180 - i);
			Delay_ms(10);
		}
	}
}
