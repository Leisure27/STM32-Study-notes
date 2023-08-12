#include "stm32f10x.h" // Device header

void AD_Init(void)
{
    // 1. 开启外设时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // 6分频使得ADC时钟为12MHz

    // 2. 配置GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // 模拟输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 3. 配置多路开关，选择通道进入规则组
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_1Cycles5);

    // 4. 使用结构体初始化ADC转换器
    ADC_InitTypeDef ADC_InitStructure;

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                  // 独立模式
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              // 数据右对齐
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 触发源不使用外部触发（使用软件触发）

    // 连续转换，非扫描方式(优点：不需要不断地触发，也不需要等待完成)
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; // 连续转换
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;      // 非扫描模式（因为是单通道）
    ADC_InitStructure.ADC_NbrOfChannel = 1;            // 只有1个通道（非扫描模式，参数不起作用）
    ADC_Init(ADC1, &ADC_InitStructure);

    // 5. 开启ADC的电源
    ADC_Cmd(ADC1, ENABLE);

    // 6. 进行ADC校准
    ADC_ResetCalibration(ADC1);                        // 复位校准
    while (ADC_GetResetCalibrationStatus(ADC1) == SET) // 等待复位校准完成
        ;
    ADC_StartCalibration(ADC1);                   // 开始校准
    while (ADC_GetCalibrationStatus(ADC1) == SET) // 等待校准完成
        ;

    ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 触发转换，连续转换模式，只需要触发一次即可
}

// 获取ADC转换结果
uint16_t AD_GetValue(void)
{
    return ADC_GetConversionValue(ADC1); // 硬件会自动清除EOC标志位
}
