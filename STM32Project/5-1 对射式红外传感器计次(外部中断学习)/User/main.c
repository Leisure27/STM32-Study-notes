#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "CountSensor.h"

int main(void)
{
	OLED_Init();  // 屏幕初始化
	
	OLED_ShowString(1, 3, "Count:");

	CountSensorInit();	//	初始化外部中断
	while (1)
	{
		OLED_ShowNum(1,7,CountSensor_Get(),5);  // OLED显示触发的中断次数
	}
}
