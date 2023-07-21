//
// Created by FIV on 2023/7/21.
//

#include "stm32f10x.h"                  // Device header
#include "Encoder.h"


void Encoder_Init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
            .GPIO_Mode = GPIO_Mode_IPU,
            .GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7,
            .GPIO_Speed = GPIO_Speed_50MHz
    });

    TIM_TimeBaseInit(TIM3, &(TIM_TimeBaseInitTypeDef) {
            .TIM_ClockDivision = TIM_CKD_DIV1,
            .TIM_CounterMode = TIM_CounterMode_Up,
            .TIM_Period = 65536 - 1,
            .TIM_Prescaler = 0,
            .TIM_RepetitionCounter = 0
    });

    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xf;
//    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    TIM_Cmd(TIM3, ENABLE);
}

int16_t Encoder_GetCount(void) {
    return TIM_GetCounter(TIM3);
}
