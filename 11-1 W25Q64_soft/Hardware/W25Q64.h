//
// Created by 16477 on 2023/9/14.
//

#ifndef STM32_W25Q64_H
#define STM32_W25Q64_H

#include "stm32f10x.h"

void W25Q64_Init(void);

void W25Q64_ReadID(uint8_t *MID, uint16_t *DID);

void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count);

void W25Q64_SectorErase(uint32_t Address);

void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count);

#endif //STM32_W25Q64_H
