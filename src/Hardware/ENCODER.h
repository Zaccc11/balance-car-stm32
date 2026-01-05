#ifndef __ENCODER_H
#define __ENCODER_H
void Encoder_Init_TIM2(void);
void Encoder_Init_TIM4(void);
int Read_Speed(int TIMx);
void TIM2_IRQHandler(void);
void TIM4_IRQHandler(void);
#endif
