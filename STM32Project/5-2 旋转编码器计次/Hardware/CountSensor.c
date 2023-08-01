#include "stm32f10x.h"

int16_t Encoder_Count = 0;

void CountSensorInit(void)
{
	// 1.打开外设时钟，EXTI、NVIC外设的时钟一直处于打开状态，不需要再进行配置 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  // 开启GPIO外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	// 开启AFIO外设时钟
	
	// 2.配置GPIO工作模式
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_0;  // 使用PB0和PB1作为中断检测引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	// 3.配置AFIO，选择哪一个GPIO_Pin
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0); // 配置AFIO数据选择器,选择PB0端口
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1); // 配置AFIO数据选择器,选择PB1端口
	
	// 4.配置EXTI，选择外部中断触发方式，响应方式
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line0 | EXTI_Line1; // 中断线
	EXTI_InitStruct.EXTI_LineCmd = ENABLE; // 使能中断线
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt; // 外部中断模式，也可以设置为事件模式
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; // PB0和PB1均为下降沿触发(高电平转为低电平)
	EXTI_Init(&EXTI_InitStruct);
	
	// 5.配置NVIC（库函数在misc.h文件中），设置中断优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 首先设置中断的优先级分组，每个工程只能出现一次
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;	
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	// 通道使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	// 设置抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;	// 设置响应优先级
	NVIC_Init(&NVIC_InitStruct); // 初始化NVIC
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;	
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	// 通道使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	// 设置抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;	// 设置响应优先级
	NVIC_Init(&NVIC_InitStruct); // 初始化NVIC
}

/* PB0中断函数
* 在STM32中，中断函数的名字都是固定的，每个中断通道都对应一个中断函数。
* 中断函数的名字可以参考启动文件中的“stratup_stm32f10x_md文件
*/
void  EXTI0_IRQHandler(void)
{
	// 中断标志位判断
	if(EXTI_GetFlagStatus(EXTI_Line0)==SET){
		// 中断执行函数
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0){
			Encoder_Count--;
		}
		
		EXTI_ClearFlag(EXTI_Line0);	// 清除中断标志位
	}
}

// PB1下降沿触发中断函数
void  EXTI1_IRQHandler(void){
	// 中断标志位判断
	if(EXTI_GetFlagStatus(EXTI_Line1)==SET){
		// 中断执行函数
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0){
			Encoder_Count++;
		}
		
		EXTI_ClearFlag(EXTI_Line1);	// 清除中断标志位
	}
}

/* 
* 输出中断触发的次数
*/
uint16_t CountSensor_Get(void){
	int16_t Temp;
	Temp = Encoder_Count;
	Encoder_Count = 0; // 每次旋转编码器的值需要重新设为0
	return Temp;
}
