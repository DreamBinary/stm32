//
// Created by FIV on 2023/7/11.
//

#include "stm32f10x.h"

void PWM_Init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
            .GPIO_Mode = GPIO_Mode_AF_PP,
            .GPIO_Pin = GPIO_Pin_0,
            .GPIO_Speed = GPIO_Speed_50MHz
    });

//    GPIO_InitTypeDef  GPIO_InitStructure;
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_InternalClockConfig(TIM2);

    TIM_TimeBaseInit(TIM2, &(TIM_TimeBaseInitTypeDef) {
            .TIM_ClockDivision = TIM_CKD_DIV1,
            .TIM_CounterMode = TIM_CounterMode_Up,
            .TIM_Period = 1000 - 1, // ARR
            .TIM_Prescaler = 7200 - 1, // PSC
            .TIM_RepetitionCounter = 0
    });
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseStructure.TIM_Period = 100 - 1; // ARR
//    TIM_TimeBaseStructure.TIM_Prescaler = 720 - 1; // PSC
//    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
//    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);


    TIM_OCInitTypeDef TIM_OCInitStructure;
    // ------------->
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);

    TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetCompare(uint16_t compare) {
    TIM_SetCompare1(TIM2, compare);
}
