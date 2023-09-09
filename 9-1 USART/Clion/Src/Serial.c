//
// Created by 16477 on 2023/9/8.
//

#include "Serial.h"
#include "stm32f10x.h"
#include "stdio.h"
#include "stdarg.h"

uint8_t Serial_RxData;
uint8_t Serial_RxFlag = 0;

uint8_t Serial_TxPacket[4];
uint8_t Serial_RxPacket[4];

void Serial_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
            .GPIO_Mode = GPIO_Mode_AF_PP,
            .GPIO_Pin = GPIO_Pin_9,
            .GPIO_Speed = GPIO_Speed_50MHz
    });

    GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
            .GPIO_Mode = GPIO_Mode_IPU,
            .GPIO_Pin = GPIO_Pin_10,
            .GPIO_Speed = GPIO_Speed_50MHz
    });

    USART_Init(USART1, &(USART_InitTypeDef) {
            .USART_BaudRate = 9600,
            .USART_HardwareFlowControl = USART_HardwareFlowControl_None,
            .USART_Mode = USART_Mode_Tx | USART_Mode_Rx,
            .USART_Parity = USART_Parity_No,
            .USART_StopBits = USART_StopBits_1,
            .USART_WordLength = USART_WordLength_8b
    });

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_Init(&(NVIC_InitTypeDef) {
            .NVIC_IRQChannel = USART1_IRQn,
            .NVIC_IRQChannelCmd = ENABLE,
            .NVIC_IRQChannelPreemptionPriority = 0,
            .NVIC_IRQChannelSubPriority = 0
    });

    USART_Cmd(USART1, ENABLE);
}

void Serial_SendByte(uint8_t byte) {
    USART_SendData(USART1, byte);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendString(char *string) {
    while (*string) {
        Serial_SendByte(*string++);
    }
}

void Serial_ReceiveByte(uint8_t *byte) {
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    *byte = USART_ReceiveData(USART1);
}


int fputc(int ch, FILE *f) {
    Serial_SendByte(ch);
    return ch;
}


void Serial_Printf(char *format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    Serial_SendString(buffer);
}

uint8_t Serial_GetRxFlag() {
    if (Serial_RxFlag) {
        Serial_RxFlag = 0;
        return 1;
    }
    return 0;
}

uint8_t Serial_GetRxData() {
    return Serial_RxData;
}

void USART1_IRQHandler() {
    uint8_t state = 0;
    uint8_t rxCnt = 0;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
//        Serial_RxData = USART_ReceiveData(USART1);
//        Serial_RxFlag = 1;
        uint8_t data = USART_ReceiveData(USART1);
        if (state == 0) {
            if (data == 0xFF) {
                state = 1;
                rxCnt = 0;
            }
        } else if (state == 1) {
            Serial_RxPacket[rxCnt++] = data;
            if (rxCnt == 4) {
                state = 2;
            }
        } else if (state == 2) {
            if (data == 0xFE) {
                state = 0;
                Serial_RxFlag = 1;
            }
        }

        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

void Serial_SendArray(uint8_t *array, uint8_t length) {
    for (int i = 0; i < length; ++i) {
        Serial_SendByte(array[i]);
    }
}

void Serial_SendPacket() {
    Serial_SendByte(0xFF);
    Serial_SendArray(Serial_TxPacket, 4);
    Serial_SendByte(0xFE);
}

