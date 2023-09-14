#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "MyI2C.h"
#include "MPU6050.h"

int16_t AX, AY, AZ, GX, GY, GZ;

int main(void) {
    OLED_Init();

//    MyI2C_Init();
//    MyI2C_Start();
////    MyI2C_SendByte(0xD0);  // 0xD0 1101 0000 -> MPU6050的从机地址
//    MyI2C_SendByte(0xD2); // 1101 0010  AD0 <- +++
//    uint8_t ACK = MyI2C_ReceiveACK();
//    MyI2C_Stop();
//    OLED_ShowNum(1, 1, ACK, 3);

//    MPU6050_Init();
//    MPU6050_WriteReg(0x6B, 0x00); // 解除休眠状态
//    MPU6050_WriteReg(0x19, 0xAA); // 采样率 1kHz
//    uint8_t id = MPU6050_ReadReg(0x19);
//    OLED_ShowHexNum(1, 1, id, 2 );
    while (1) {
        MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
        OLED_ShowSignedNum(2, 1, AX, 5);
        OLED_ShowSignedNum(3, 1, AY, 5);
        OLED_ShowSignedNum(4, 1, AZ, 5);
        OLED_ShowSignedNum(2, 8, GX, 5);
        OLED_ShowSignedNum(3, 8, GY, 5);
        OLED_ShowSignedNum(4, 8, GZ, 5);
    }
}
