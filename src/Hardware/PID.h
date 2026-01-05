#ifndef __PID_H
#define __PID_H

#include "sys.h" 

int Upstanding(float Med, float Angle, float Gyro_X);
int Velocity(int Target, int Encoder_Left, int Encoder_Right);
int Turn_PID(int32_t Angle, int32_t Target);
u8 turn_off(float angle);

void EXTI9_5_IRQHandler(void);

#endif // __PID_H__
