#include "stm32f10x.h"
#include "sys.h"


extern int length;

#define SPEED_Y 10   //俯仰(前后)最大设定速度
#define SPEED_Z 100//偏航(左右)最大设定速度 


int Upstanding(float Med, float Angle, float Gyro_X) {
		int PWM_Out;
		PWM_Out = Balance_Kp*(Angle-Med)+Balance_Kd*(Gyro_X-0);
		return PWM_Out;
}
u8 mpu6050_data_ready;

int Velocity(int Target, int Encoder_Left, int Encoder_Right){
	static int Encoder_S, EnC_Err_Lowout_Buffer, EnC_Err_Lowout, Encoder_Err, PWM_out;
	float a = 0.7;
	
	Encoder_Err = Target_Speed-(Encoder_Left+Encoder_Right);
	EnC_Err_Lowout = (1-a)*Encoder_Err+a*EnC_Err_Lowout_Buffer;
	EnC_Err_Lowout_Buffer = EnC_Err_Lowout;
	Encoder_S += EnC_Err_Lowout;
	Encoder_S = Encoder_S>5000?5000:(Encoder_S<(-5000)?(-5000):Encoder_S);
	
	if(stop==1) Encoder_S = 0, stop = 0;
	
	PWM_out = Velocity_Kp*EnC_Err_Lowout+Velocity_Ki*Encoder_S;
	return PWM_out;
	
}

int Turn(int32_t Gyro_Z, int32_t RC) {
    int PWM_Out;
		PWM_Out = Turn_Kp*Gyro_Z + Turn_Kd*RC;
		return PWM_Out;
    
}

u8 turn_off(float angle) {
	u8 temp;
	if (angle<-40||angle>40) {
		temp = 1;
		AIN1=0;                                            
		AIN2=0;
		BIN1=0;
		BIN2=0;
	}
	else {
		temp = 0;
	}
	return temp;
}
		

void EXTI9_5_IRQHandler(void)
{
		int PWM_out;
    if (EXTI_GetITStatus(EXTI_Line5)!=0)
    {
			if(PBin(5) == 0){
        EXTI_ClearITPendingBit(EXTI_Line5);
            // 读取编码器、传感器、计算 PID
				Encoder_Left=-Read_Speed(2);//电机是相对安装，刚好相差180度，为了编码器输出极性一致，就需要对其中一个取反。
				Encoder_Right=Read_Speed(4);

            // 只用上一帧的 Pitch、gyro、accel 来做 PID
						mpu_dmp_get_data(&Roll,&Pitch,&Yaw);	
						MPU_Get_Gyroscope(&gyroy,&gyrox,&gyroz);	//陀螺仪
						MPU_Get_Accelerometer(&aacx,&aacy,&aacz);
						
						
						if((Left==0)&&(Right==0))Turn_Kd=-0.7;//若无左右转向指令，则开启转向约束
				
				
						Target_Speed=Target_Speed>SPEED_Y?SPEED_Y:(Target_Speed<-SPEED_Y?(-SPEED_Y):Target_Speed);
						Turn_Speed=Turn_Speed>SPEED_Z?SPEED_Z:(Turn_Speed<-SPEED_Z?(-SPEED_Z):Turn_Speed);
            Velocity_out = Velocity(Target_Speed, Encoder_Left,Encoder_Right);
            Vertical_out = Upstanding(Velocity_out+Med_Angle, Pitch, gyroy);
            Turn_out = Turn(gyroz, Turn_Speed);
						
						PWM_out=Vertical_out;
						MOTO1=PWM_out-Turn_out;//左电机
						MOTO2=PWM_out+Turn_out;//右电机
						Limit(&MOTO1,&MOTO2);	 //PWM限幅			
					
						Load(MOTO1,MOTO2);		 //加载到电机上。
						
			
						Stop(&Med_Angle,&Pitch);//安全检测
			}
			
    }
}

