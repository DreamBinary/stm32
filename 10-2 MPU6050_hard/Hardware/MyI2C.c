//
// Created by 16477 on 2023/9/11.
//

#include "MyI2C.h"
#include "stm32f10x.h"
#include "Delay.h"

void MyI2C_Init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_Init(GPIOB, &(GPIO_InitTypeDef) {
            .GPIO_Mode = GPIO_Mode_Out_OD,
            .GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11,
            .GPIO_Speed = GPIO_Speed_50MHz
    });

    GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);
}

void MyI2C_W_SCL(uint8_t BitValue) {
    GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction) BitValue);
    Delay_us(100);
}

void MyI2C_W_SDA(uint8_t BitValue) {
    GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction) BitValue);
    Delay_us(100);
}

uint8_t MyI2C_R_SDA() {
    uint8_t BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    Delay_us(100);
    return BitValue;
}

void MyI2C_Start() {
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(0);
    MyI2C_W_SCL(0);
}

void MyI2C_Stop() {
    MyI2C_W_SDA(0);
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte) {
    uint8_t i;
    for (i = 0; i < 8; i++) {
        MyI2C_W_SCL(0); // SDA 数据无效
        MyI2C_W_SDA(Byte & (0x80 >> i));
        MyI2C_W_SCL(1); // SDA 数据有效
    }
    MyI2C_W_SCL(0);
}

void MyI2C_SendACK(uint8_t ACK) {
    MyI2C_W_SCL(0);
    MyI2C_W_SDA(ACK);
    MyI2C_W_SCL(1);
    MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveByte() {
    uint8_t i, Byte = 0x00;
    MyI2C_W_SDA(1); // 数据发送端会释放 SDA 的控制权，由数据接收端控制 SDA
    for (i = 0; i < 8; ++i) {
        MyI2C_W_SCL(1);
        if (MyI2C_R_SDA()) {
            Byte |= (0x80 >> i);
        }
        MyI2C_W_SCL(0);
    }
    return Byte;
}

uint8_t MyI2C_ReceiveACK() {
    uint8_t ACK;
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(1);
    ACK = MyI2C_R_SDA();
    MyI2C_W_SCL(0);
    return ACK;
}


