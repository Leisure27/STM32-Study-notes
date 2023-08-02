/*
 * 配置PA1和PA2输出PWM
 */

#include "stm32f10x.h" // Device header

void PWM_Init(void)
{
    // 1. 开启RCC内部时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // TIM2是APB1总线的外设

    // 2. 选择时基单元的时钟，选择内部时钟，因为定时器上电后默认就是使用内部时钟，所以这一步也可以省略
    TIM_InternalClockConfig(TIM2);

    // 3. 配置时基单元-1Khz
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;     // 不分频，这个参数与时基单元关系不大
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;                 // ARR自动重装寄存器的值
    TIM_TimeBaseInitStruct.TIM_Prescaler = 720 - 1;              //	PSC预分频器的值
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;            // 重复计数器的值(高级定时器才有的)
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    // 4. 启动定时器
    TIM_Cmd(TIM2, ENABLE);

    // 5. 配置输出比较电路
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct); // 给结构体赋初始值，后续使用到高级定时器初始化时，不会出错
    // 把结构体初始值更改为自己想要的值
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;             // 设置输出比较器的模式
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;     // 设置输出比较的极性
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; // 设置输出使能
    TIM_OCInitStruct.TIM_Pulse = 0;                            // 设置CCR的值(占空比初值)
    TIM_OC2Init(TIM2, &TIM_OCInitStruct);                      // TIM2的OC2通道上输出PWM波形，对应输出端口PA1
    TIM_OC3Init(TIM2, &TIM_OCInitStruct);                      // TIM2的OC3通道上输出PWM波形，对应输出端口PA2

    // 6. 配置GPIO(已验证)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启RCC时钟,Reset Clock Controller
    GPIO_InitTypeDef GPIO_InitStruct;                     // GPIO结构体
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;          // 使用复用推挽输出模式，引脚的控制权交给片上外设，PWM波形才能通过引脚输出
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;   // GPIO 0~15
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;        // 常用50MHz
    GPIO_Init(GPIOA, &GPIO_InitStruct);                   // 配置端口模式
}

// 设置PA1输出PWM的占空比
void PWM_SetCompare2(uint16_t pwm_duty)
{
    TIM_SetCompare2(TIM2, pwm_duty);
}

// 设置PA2输出PWM的占空比
void PWM_SetCompare3(uint16_t pwm_duty)
{
    TIM_SetCompare3(TIM2, pwm_duty);
}
