//
// Created by 16477 on 2023/9/12.
//

#ifndef STM_MYDMA_H
#define STM_MYDMA_H

#include "stm32f1xx_hal.h"

void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size);

void MyDMA_Transfer(uint32_t AddrA, uint32_t AddrB, uint16_t Size);

#endif //STM_MYDMA_H
