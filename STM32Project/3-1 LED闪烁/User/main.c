/*
* 使用库函数点灯
* 板载LED PC13，低电平点亮
*/
#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); // 开启RCC时钟,Reset Clock Controller
	
	GPIO_InitTypeDef GPIO_InitStruct; // GPIO结构体
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出模式(输出高低电平)
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 ;  // GPIO 0~15
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  // 常用50MHz
	
	GPIO_Init(GPIOC,&GPIO_InitStruct);// 配置端口模式
	
	while(1)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);  // PC13输出低电平
		Delay_ms(100);
		GPIO_SetBits(GPIOC,GPIO_Pin_13); // PC13输出高电平
		Delay_ms(100);
	}
}
