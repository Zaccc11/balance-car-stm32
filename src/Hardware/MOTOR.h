#ifndef __MOTOR_H
#define __MOTOR_H

#include "sys.h"

#define BIN2   PBout(13)
#define BIN1   PBout(12)
#define AIN2   PBout(14)
#define AIN1   PBout(15)

#define AIN1_ON GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define AIN1_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define AIN2_ON GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define AIN2_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define BIN1_ON GPIO_SetBits(GPIOB,GPIO_Pin_14)
#define BIN1_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_14)
#define BIN2_ON GPIO_SetBits(GPIOB,GPIO_Pin_15)
#define BIN2_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_15)

void Motor_Init(void);
void Motor_PWN_Init(uint16_t arr, uint16_t psc);
//void Load(int moto1, int moto2);
void Limit (int *moto1, int *moto2);
void Stop(float *Stop_Med, float *Stop_Angle);
int myabs(int a);
void Load(int moto1,int moto2);


#endif
