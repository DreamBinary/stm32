//
// Created by 16477 on 2023/9/8.
//
#include "stm32f10x.h"
#ifndef STM32_SERIAL_H
#define STM32_SERIAL_H

extern uint8_t Serial_TxPacket[4];
extern uint8_t Serial_RxPacket[4];

void Serial_Init();
void Serial_SendByte(uint8_t byte);
void Serial_SendString(char *string);
void Serial_ReceiveByte(uint8_t *byte);
void Serial_Printf(char *format, ...);
uint8_t Serial_GetRxFlag();
uint8_t Serial_GetRxData();

void Serial_SendPacket();
#endif //STM32_SERIAL_H
