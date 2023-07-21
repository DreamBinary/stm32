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
    TIM_InternalClockConfig(TIM2);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;		//ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 720 - 1;		//PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);


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


void PWM_SetPrescaler(uint16_t prescaler) {
    TIM_PrescalerConfig(TIM2, prescaler, TIM_PSCReloadMode_Immediate);
}

