#include "stm32f10x.h"

uint16_t CountSensor_Count = 0;//中断触发次数

void CountSensorInit()
{
	// 1.打开外设时钟，EXTI、NVIC外设的时钟一直处于打开状态，不需要再进行配置 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  // 开启GPIO外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	// 开启AFIO外设时钟
	
	// 2.配置GPIO工作模式
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;  // PB14
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	// 3.配置AFIO，选择哪一个GPIO_Pin
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14); // 配置AFIO数据选择器,选择GPIOB14端口
	
	// 4.配置EXTI，选择外部中断触发方式，响应方式
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line14; // 中断线，GPIOB的14号端口
	EXTI_InitStruct.EXTI_LineCmd = ENABLE; // 使能中断线
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt; // 外部中断模式，也可以设置为事件模式
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发(高电平转为低电平)
	EXTI_Init(&EXTI_InitStruct);
	
	// 5.配置NVIC（库函数在misc.h文件中），设置中断优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 首先设置中断的优先级分组，每个工程只能出现一次
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;	// 通道15~10，我们选择的为14号通道，因此应该选择这个参数
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	// 通道使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	// 设置抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;	// 设置响应优先级
	NVIC_Init(&NVIC_InitStruct); // 初始化NVIC
}

/* 中断函数
* 在STM32中，中断函数的名字都是固定的，每个中断通道都对应一个中断函数。
* 中断函数的名字可以参考启动文件中的“stratup_stm32f10x_md文件
*/
void  EXTI15_10_IRQHandler(void)
{
	// 中断标志位判断
	if(EXTI_GetFlagStatus(EXTI_Line14)==SET){
		// 中断执行函数
		CountSensor_Count++;
		
		EXTI_ClearFlag(EXTI_Line14);	// 清除中断标志位
	}
}


/* 
* 输出中断触发的次数
*/
uint16_t CountSensor_Get(void){
	return CountSensor_Count;
}
