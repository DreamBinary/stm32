//
// Created by FIV on 2023/7/19.
//

#include "IC.h"
#include "stm32f10x.h"

void IC_Init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
            .GPIO_Mode = GPIO_Mode_IPU,
            .GPIO_Pin = GPIO_Pin_6,
            .GPIO_Speed = GPIO_Speed_50MHz
    });

    TIM_InternalClockConfig(TIM3);

    TIM_TimeBaseInit(TIM3, &(TIM_TimeBaseInitTypeDef) {
            .TIM_ClockDivision = TIM_CKD_DIV1,
            .TIM_CounterMode = TIM_CounterMode_Up,
            .TIM_Period = 65536 - 1,
            .TIM_Prescaler = 72 - 1,
            .TIM_RepetitionCounter = 0
    });

    TIM_ICInit(TIM3, &(TIM_ICInitTypeDef) {
            .TIM_Channel = TIM_Channel_1,
            .TIM_ICFilter = 0xf,
            .TIM_ICPolarity = TIM_ICPolarity_Rising,
            .TIM_ICPrescaler = TIM_ICPSC_DIV1,
            .TIM_ICSelection = TIM_ICSelection_DirectTI
    });

    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);

    TIM_Cmd(TIM3, ENABLE);
}

uint32_t IC_GetFreq(void) {
    return 1000000 / TIM_GetCapture1(TIM3);
}