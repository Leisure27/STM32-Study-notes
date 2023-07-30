/* 功能：旋转编码器计次
* 知识点：使用两个外部中断
*/
#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "CountSensor.h"

int16_t Num;

int main(void)
{
	OLED_Init();  // 屏幕初始化
	
	OLED_ShowString(1, 3, "Count:");

	CountSensorInit();	//	初始化外部中断
	while (1)
	{
		Num += CountSensor_Get(); // 存储旋转编码器的当前值
		OLED_ShowNum(1,7,Num,5);  // OLED显示触发的中断次数
	}
}
