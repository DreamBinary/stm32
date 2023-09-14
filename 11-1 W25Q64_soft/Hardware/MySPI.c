//
// Created by 16477 on 2023/9/14.
//

#include "MySPI.h"
#include "stm32f10x.h"

void MySPI_W_SS(uint8_t val) {
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction) val);
}

void MySPI_W_SCK(uint8_t val) {
    GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction) val);
}

void MySPI_W_MOSI(uint8_t val) {
    GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction) val);
}

uint8_t MySPI_R_MISO() {
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

void MySPI_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    MySPI_W_SS(1);
    MySPI_W_SCK(0);
}

void MySPI_Start(void) {
    MySPI_W_SS(0);
}

void MySPI_Stop(void) {
    MySPI_W_SS(1);
}

uint8_t MySPI_SwapByte(uint8_t ByteSend) {
    uint8_t i, ByteReceive = 0x00;

    for (i = 0; i < 8; i++) {
        MySPI_W_MOSI(ByteSend & (0x80 >> i));
        MySPI_W_SCK(1);
        if (MySPI_R_MISO() == 1) { ByteReceive |= (0x80 >> i); }
        MySPI_W_SCK(0);
    }

    return ByteReceive;
}
