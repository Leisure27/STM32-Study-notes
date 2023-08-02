#include "stm32f10x.h"                  // Device header

extern uint16_t Num;

void Timer_Init(void)
{
	// 1. 开启RCC内部时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); // TIM2是APB1总线的外设
	
	// 2. 选择时基单元的时钟，选择内部时钟，因为定时器上电后默认就是使用内部时钟，所以这一步也可以省略
	TIM_InternalClockConfig(TIM2);
	
	// 3. 配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // 不分频，这个参数与时基单元关系不大
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	// 向上计数
	
	// 定时频率 = 72M/(PSC+1)/(ARR+1), 定时1s，也就是定时频率1Hz，可设置位下面的值
	// PSC和ARR的取值范围：0~65536
	// 预分频小，自动重装大，代表以一个比较高的频率计比较多的数。
	// ARR = 10000, PSC = 7200，表示在10K的频率下计10000个数，也就是定时1s
	TIM_TimeBaseInitStruct.TIM_Period = 10000-1;	// ARR自动重装寄存器的值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;	//	PSC预分频器的值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;	// 重复计数器的值(高级定时器才有的)
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	// 4. 使能更新中断
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);// 在初始化的时候，先手动清除一下中断标志位，可以避免刚初始化就进入中断的问题
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 开启更新中断到NVIC通路
	
	// 5. 配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // NVIC优先级分组
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	// 6. 启动定时器
	TIM_Cmd(TIM2,ENABLE);
}

// 定时器中断函数
void TIM2_IRQHandler(void)
{
	// 检查TIM2的更新中断标志位
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){
		
		// 定时中断执行函数
		Num++;  // 1s加一次
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	// 清零中断标志位
	}
	
}
