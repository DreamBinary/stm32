//
// Created by 16477 on 2023/9/19.
//

#ifndef STM_MPU6050_H
#define STM_MPU6050_H

#include "stm32f1xx_hal.h"
static uint16_t MPU6050_ADDR = 0x68;

int16_t Sensor_I2C2_Serch(void);

void MPU6050_Init(int16_t Addr);

uint8_t MPU6050_ReadReg(uint16_t DevAddress, uint16_t MemAddr, uint8_t *pData, uint8_t Size);

void MPU6050_WriteReg(uint16_t DevAddress, uint16_t MemAddr, uint8_t *pData, uint8_t Size);


uint8_t MPU6050_GetId();

#endif //STM_MPU6050_H
