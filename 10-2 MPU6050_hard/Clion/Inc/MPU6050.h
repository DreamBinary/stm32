//
// Created by 16477 on 2023/9/11.
//


#ifndef STM32_MPU6050_H
#define STM32_MPU6050_H

#include "stm32f10x.h"

void MPU6050_Init();

void MPU6050_WriteReg(uint8_t RegAddr, uint8_t RegValue);

uint8_t MPU6050_GetID(void);

uint8_t MPU6050_ReadReg(uint8_t RegAddr);

void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ,
                     int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);

#endif //STM32_MPU6050_H
