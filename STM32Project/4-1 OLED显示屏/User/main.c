#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

int main(void)
{
	OLED_Init();  // 屏幕初始化
	
	OLED_ShowChar(1, 1, 'A');
	OLED_ShowString(1, 3, "HelloWorld!");
	OLED_ShowNum(2, 1, 12345, 5);   // 显示无符号十进制数，最后一个参数为长度
	OLED_ShowSignedNum(2, 7, -66, 2);	// 显示有符号十进制数
	OLED_ShowHexNum(3, 1, 0xAA55, 4);	// 显示十六进制
	OLED_ShowBinNum(4, 1, 0xAA55, 16);	// 显示二进制
	
	while (1)
	{
		
	}
}
