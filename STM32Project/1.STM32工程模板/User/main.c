/*
* 使用库函数点灯
* 板载LED PC13，低电平点亮
*/
#include "stm32f10x.h"                  // Device header

int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); // 开启时钟
	
	GPIO_InitTypeDef GPIO_InitStruct; // GPIO结构体
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 通用推挽输出模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&GPIO_InitStruct);// 配置端口模式
	
	// GPIO_SetBits(GPIOC,GPIO_Pin_13); // 将GPIO13设置为高电平
	GPIO_ResetBits(GPIOC,GPIO_Pin_13); // 将GPIO13设置为低电平
	
	while(1)
	{
	
	}
}
