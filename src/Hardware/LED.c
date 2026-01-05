#include "stm32f10x.h"
#define LED_PIN GPIO_Pin_13


void LED_initialize(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = LED_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_SetBits(GPIOC, LED_PIN); 
}


void LED_On(void){
    GPIO_ResetBits(GPIOC, LED_PIN); // Set GPIO low to turn on the LED
}


void LED_Off(void){
    GPIO_SetBits(GPIOC, LED_PIN); // Set GPIO high to turn off the LED
}

