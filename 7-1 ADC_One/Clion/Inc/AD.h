//
// Created by FIV on 2023/7/21.
//

#ifndef STM32_AD_H
#define STM32_AD_H

void AD_Init(void);
uint16_t AD_GetValue(uint8_t ADC_Channel);

#endif //STM32_AD_H
