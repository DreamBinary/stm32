//
// Created by 16477 on 2023/9/11.
//

#include "stm32f10x.h"

#ifndef STM32_MYI2C_H
#define STM32_MYI2C_H

void MyI2C_Init();

void MyI2C_W_SCL(uint8_t BitValue);

void MyI2C_W_SDA(uint8_t BitValue);

uint8_t MyI2C_R_SDA();

void MyI2C_Start();

void MyI2C_Stop();

void MyI2C_SendByte(uint8_t Byte);

void MyI2C_SendACK(uint8_t ACK);

uint8_t MyI2C_ReceiveByte();

uint8_t MyI2C_ReceiveACK();


#endif //STM32_MYI2C_H
