//
// Created by 16477 on 2023/9/14.
//

#ifndef STM32_MYSPI_H
#define STM32_MYSPI_H
#include "stm32f10x.h"
void MySPI_Init(void);

void MySPI_Start(void);

void MySPI_Stop(void);

uint8_t MySPI_SwapByte(uint8_t ByteSend);

#endif //STM32_MYSPI_H
