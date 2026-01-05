#include "stm32f10x.h"

void PWM_SetCompare1(uint16_t Compare) {
	TIM_SetCompare1(TIM1,Compare);
}


