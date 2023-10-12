//
// Created by 16477 on 2023/9/21.
//

#include "Beep.h"

void HAL_Delay_us(uint32_t us) {
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000000);
    HAL_Delay(us - 1);
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
}

void Sound(uint16_t frq) {
    uint32_t time;
    if (frq) {
        time = 100000 / ((uint32_t) frq);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);//打开蜂鸣器
        Delay_us(time);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);//关闭蜂鸣器
        Delay_us(time);
    } else {
        Delay_us(1000);
    }
}

void Play_Music(void) {
    uint16_t tone[] = {247, 262, 294, 330, 349, 392, 440, 494, 523, 587,
                       659, 698, 784, 0};
    uint32_t music[] = {
            3, 5, 8, 6, 5, 13, 3, 5, 6, 8,
            5, 13, 8, 10, 9, 8, 9, 8, 6,
            8, 5, 13, 3, 5, 6, 5, 6, 8,
            9, 5, 6, 13, 3, 2, 1, 2, 13,
            2, 2, 3, 5, 5, 8, 2, 3, 5,
            13
    };
    uint32_t time[] = {
            2, 2, 2, 2, 6, 4, 2, 2, 2, 2,
            6, 4, 6, 2, 4, 4, 2, 2, 2,
            2, 6, 4, 6, 2, 4, 2, 2, 4,
            2, 2, 6, 4, 2, 2, 4, 6, 4,
            4, 2, 2, 4, 4, 4, 2, 2, 6,
            4
    };
    uint32_t scale = 2;
    uint16_t i, e;
    for (i = 0; i < sizeof(music) / sizeof(music[0]); i++) {
        for (e = 0; e < time[i] * tone[music[i]] / scale; e++) {
            Sound((uint32_t) tone[music[i]]);
        }
    }
}