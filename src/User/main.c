#include "stm32f10x.h"                  // Device header
#include "sys.h"

/*2025/6/30: Tested Motor 2 to ensure its avaibility, should test out Motor 1 the same, then goes for PID control.
  
	Two Motor, Motor 1 and 2
	To control Motor 1, Configure PB12 and PB13
	To control Motor 2, Configure PB14 and PB15
	Use Motor_PWN_Init(arr,psc) to set arr and psc
	Use Motor_SetSpeed(arr) to set the frequency of the motor
*/

// 全局变量定义区
float Pitch, Roll, Yaw; // 角度
int16_t gyrox, gyroy, gyroz; // 陀螺仪--角速度
int16_t aacx, aacy, aacz; // 加速度
int Encoder_Left, Encoder_Right; // 编码器数据（速度）
int MOTO1, MOTO2;
int PWM_MAX = 7200, PWM_MIN = -7200;

char stop = 0;
u8 Fore = 0, Back = 0, Left = 0, Right = 0;

//PID.c variable
float Med_Angle=-3;		//机械中值。---在这里修改你的机械中值即可。
float Target_Speed=0;	//期望速度（俯仰）。---二次开发接口，用于控制小车前进后退及其速度。
float Turn_Speed=0;		//期望速度（偏航）

float 
		Balance_Kp=220,
		Balance_Kd=0.7;
		
float
		Velocity_Kp=0.3,
		Velocity_Ki=0.0015;
float
		Turn_Kp=-0.6,
		Turn_Kd=0;

int Vertical_out,Velocity_out,Turn_out;//直立环&速度环&转向环 的输出变量
uint8_t ID;								//定义用于存放ID号的变量




int main(void)
{
	NVIC_Config();
	//uart1_init(115200);	

	//uart3_init(9600);//先9600  
	OLED_Init();
  MPU6050_Init();
	mpu_dmp_init();
	MPU6050_EXTI_Init();
	Encoder_Init_TIM2();
	Encoder_Init_TIM4();
	Motor_PWN_Init(7199,0);
	TIM3_Int_Init();
OLED_ShowString(1, 1, "Pitch:");
			OLED_ShowString(2, 1, "Roll:");
	OLED_ShowString(3, 1, "Yaw:");
	
	while (1){

		OLED_ShowSignedNum(1, 7, (int)Pitch,  5);

    OLED_ShowSignedNum(2, 7, (int)Roll,   5);
    
		OLED_ShowSignedNum( 3, 7, (int)Yaw,    5);
		OLED_ShowSignedNum(4,5,(int)((Encoder_Left+Encoder_Right)*2.38),5);	
                
	}
	

                



}

void TIM3_Int_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//		NVIC_InitTypeDef NVIC_InitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			
		
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;//设置为推挽输出
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStruct);

		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
	
		//定时器3初始化
		TIM_TimeBaseStructure.TIM_Period = 999; //ARR
		TIM_TimeBaseStructure.TIM_Prescaler =7199; //PSC
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		
//		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );//使能制定TIM3中断，允许更新中断
//		//中断设置
//		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//		NVIC_Init(&NVIC_InitStructure);

		TIM_Cmd(TIM3, DISABLE);

/*void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        dmp_data_ready = 1;

        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}
*/
}