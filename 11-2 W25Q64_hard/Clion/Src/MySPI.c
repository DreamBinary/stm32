//
// Created by 16477 on 2023/9/14.
//

#include "MySPI.h"
#include "stm32f10x.h"

void MySPI_W_SS(uint8_t val) {
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction) val);
}

void MySPI_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);


    GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
            .GPIO_Pin = GPIO_Pin_4,
            .GPIO_Mode = GPIO_Mode_Out_PP,
            .GPIO_Speed = GPIO_Speed_50MHz
    });

    GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
            .GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7,
            .GPIO_Mode = GPIO_Mode_AF_PP,
            .GPIO_Speed = GPIO_Speed_50MHz
    });

    GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
            .GPIO_Pin = GPIO_Pin_6,
            .GPIO_Mode = GPIO_Mode_IPU,
            .GPIO_Speed = GPIO_Speed_50MHz
    });

    SPI_Init(SPI2, &(SPI_InitTypeDef) {
            .SPI_Direction = SPI_Direction_2Lines_FullDuplex,
            .SPI_Mode = SPI_Mode_Master,
            .SPI_DataSize = SPI_DataSize_8b,
            .SPI_CPOL = SPI_CPOL_Low,
            .SPI_CPHA = SPI_CPHA_1Edge,
            .SPI_NSS = SPI_NSS_Soft,
            .SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128,
            .SPI_FirstBit = SPI_FirstBit_MSB,
            .SPI_CRCPolynomial = 7
    });

    SPI_Cmd(SPI1, ENABLE);

    MySPI_W_SS(1);
}

void MySPI_Start(void) {
    MySPI_W_SS(0);
}

void MySPI_Stop(void) {
    MySPI_W_SS(1);
}

uint8_t MySPI_SwapByte(uint8_t ByteSend) {

    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) {}
    SPI_I2S_SendData(SPI1, ByteSend);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) {}
    return SPI_I2S_ReceiveData(SPI1);
}
