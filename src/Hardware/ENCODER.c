#include "stm32f10x.h"


void Encoder_Init_TIM2(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; // PA0 and PA1 for TIM2 CH1 and CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // No prescaler
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // Count up
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF; // Max period
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // No clock division
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update); // Clear the update flag
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    TIM_SetCounter(TIM2, 0);

    TIM_Cmd(TIM2, ENABLE); // Enable TIM2

}

void Encoder_Init_TIM4(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // PA0 and PA1 for TIM2 CH1 and CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Prescaler = 0; // No prescaler
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // Count up
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF; // Max period
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; // No clock division
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
    TIM_ClearFlag(TIM4, TIM_FLAG_Update); // Clear the update flag
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

    TIM_SetCounter(TIM4, 0);

    TIM_Cmd(TIM4, ENABLE); // Enable TIM4
}

	int Read_Speed(int TIMx)
{
	int value_1;
	switch(TIMx)
	{
		case 2:value_1=(short)TIM_GetCounter(TIM2);TIM_SetCounter(TIM2,0);break;//IF是定时器2，1.采集编码器的计数值并保存。2.将定时器的计数值清零。
		case 4:value_1=(short)TIM_GetCounter(TIM4);TIM_SetCounter(TIM4,0);break;
		default:value_1=0;
	}
	return value_1;
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=0)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
	
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=0)
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}