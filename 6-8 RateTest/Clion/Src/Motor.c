//
// Created by FIV on 2023/7/11.
//


#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Motor_Init(void) {
    GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
            .GPIO_Mode = GPIO_Mode_AF_PP,
            .GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5,
            .GPIO_Speed = GPIO_Speed_50MHz
    });
    PWM_Init();
}

void Motor_SetSpeed(int8_t Speed) {

    if (Speed >= 0) {
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
        PWM_SetCompare(Speed);
    } else {
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
        PWM_SetCompare(-Speed);
    }
}