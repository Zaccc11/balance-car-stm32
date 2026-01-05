#include "stm32f10x.h"
#include "sys.h"
#include "MOTOR.h"



void Motor_Init(void) {
    //Configure the Motor Driver GPIO pins
    //PB12, PB13, PB14, PB15 are used for motor control
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Set GPIO mode to Output Push Pull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Set GPIO speed to 50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//PWM Output initialize, TIM1 CH1 and CH4 are used.
void Motor_PWN_Init(uint16_t arr, uint16_t psc) {
    Motor_Init();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); // Enable TIM1 clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11; // TIM_CH1 and TIM_CH4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_ClockDivision= 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // Set PWM mode 1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // Enable output state
    TIM_OCInitStructure.TIM_Pulse = 0; // Set initial pulse value to 0
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure); // Initialize TIM1 Channel 1
    TIM_OC4Init(TIM1, &TIM_OCInitStructure); // Initialize TIM1 Channel 4

    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); // Enable preload for TIM1 Channel 1
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable); // Enable
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
}



void Load(int moto1,int moto2)//moto1=-200：反转200个脉冲
{
	//1.研究正负号，对应正反转
	if(moto1>0)	AIN1=1,			AIN2=0; //前进
	else 				AIN1=0,			AIN2=1; //后退
	//2.研究PWM值
	TIM_SetCompare1(TIM1,myabs(moto1));
	
	if(moto2>0)	BIN1=1,			BIN2=0;	//前进
	else 				BIN1=0,			BIN2=1; //后退
	TIM_SetCompare4(TIM1,myabs(moto2));
}
	
void Limit (int *moto1, int *moto2) {
	if (*moto1 > 7200) *moto1 = 7200;
	if (*moto1 < (-7200)) *moto1 = -7200;
	
	if (*moto2 > 7200) *moto2 = 7200;
	if (*moto2 < (-7200)) *moto2 = -7200;
}


void Stop(float *Stop_Med, float *Stop_Angle){
	
	if (myabs(*Stop_Med - *Stop_Angle) > 60)
	{
		Load(0,0);
		stop=1;
	}
}

int myabs(int a)
{ 		   
	int temp;
	if(a<0)  temp=-a;  
	else temp=a;
	return temp;
}
