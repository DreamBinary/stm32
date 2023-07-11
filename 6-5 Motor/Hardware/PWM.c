//
// Created by FIV on 2023/7/11.
//

#include "stm32f10x.h"

void PWM_Init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
            .GPIO_Mode = GPIO_Mode_AF_PP,
            .GPIO_Pin = GPIO_Pin_2,
            .GPIO_Speed = GPIO_Speed_50MHz
    });
    TIM_InternalClockConfig(TIM2);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    // ------------->
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);

    TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetCompare(uint16_t compare) {
    TIM_SetCompare3(TIM2, compare);
}
