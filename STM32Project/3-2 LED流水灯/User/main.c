/*
* 使用库函数点灯
* 板载LED PC13，低电平点亮
*/
#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); // 开启RCC时钟,Reset Clock Controller
	
	GPIO_InitTypeDef GPIO_InitStruct; // GPIO结构体
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出模式(输出高低电平)
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All ;  // 配置GPIO的所有端口(0~15)
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  // 常用50MHz
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);// 配置端口模式
	
	while(1)
	{
		// 使用GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);进行设计，一次性给多个IO口赋值
		GPIO_Write(GPIOA, ~0x0001);	//0000 0000 0000 0001
		Delay_ms(100);
		GPIO_Write(GPIOA, ~0x0002);	//0000 0000 0000 0010
		Delay_ms(100);
		GPIO_Write(GPIOA, ~0x0004);	//0000 0000 0000 0100
		Delay_ms(100);
		GPIO_Write(GPIOA, ~0x0008);	//0000 0000 0000 1000
		Delay_ms(100);
		GPIO_Write(GPIOA, ~0x0010);	//0000 0000 0001 0000
		Delay_ms(100);
		GPIO_Write(GPIOA, ~0x0020);	//0000 0000 0010 0000
		Delay_ms(100);
		GPIO_Write(GPIOA, ~0x0040);	//0000 0000 0100 0000
		Delay_ms(100);
		GPIO_Write(GPIOA, ~0x0080);	//0000 0000 1000 0000
		Delay_ms(100);
	}
}
