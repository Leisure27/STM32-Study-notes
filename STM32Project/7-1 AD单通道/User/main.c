#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t ADValue;
float Voltage;
int main(void)
{
	OLED_Init(); // 屏幕初始化
	AD_Init();
	OLED_ShowString(1, 1, "ADValue:");
	OLED_ShowString(2, 1, "Voltage:0.00V"); // 小数点和V字符在后面就不需要进行刷新显示了
	while (1)
	{
		ADValue = AD_GetValue();
		Voltage = (float)AD_GetValue() / 4095 * 3.3;
		OLED_ShowNum(1, 9, ADValue, 5);
		OLED_ShowNum(2, 9, Voltage, 1); // 整数部分
		// OLED_ShowChar(2, 10, '.');
		OLED_ShowNum(2, 11, (uint16_t)(Voltage * 100) % 100, 2); // 浮点数不能进行取余，所以需要进行强制类型转换为整数
		Delay_ms(100);
	}
}
