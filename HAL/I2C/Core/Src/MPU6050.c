//
// Created by 16477 on 2023/9/19.
//

#include "MPU6050.h"
#include "stm32f1xx_hal.h"
#include "main.h"
#include "MPU6050_Reg.h"

int16_t Sensor_I2C2_Serch(void) {
    for (uint8_t i = 1; i < 255; i++) {
        if (HAL_I2C_IsDeviceReady(&hi2c2, i, 1, 1000) == HAL_OK) {
            MPU6050_ADDR = i;
            return i;
        }
    }
    return 0xD1;
}

void MPU6050_Init(int16_t Addr) {
    uint8_t data = 0x01;
    MPU6050_WriteReg(Addr, MPU6050_PWR_MGMT_1, &data, 1);
    data = 0x00;
    MPU6050_WriteReg(Addr, MPU6050_PWR_MGMT_2, &data, 1);
    data = 0x09;
    MPU6050_WriteReg(Addr, MPU6050_SMPLRT_DIV, &data, 1);
    data = 0x06;
    MPU6050_WriteReg(Addr, MPU6050_CONFIG, &data, 1);
    data = 0x18;
    MPU6050_WriteReg(Addr, MPU6050_GYRO_CONFIG, &data, 1);
    MPU6050_WriteReg(Addr, MPU6050_ACCEL_CONFIG, &data, 1);
}

uint8_t MPU6050_ReadReg(uint16_t DevAddress, uint16_t MemAddr, uint8_t *pData, uint8_t Size) {
    // I2C_MEMADD_SIZE_8BIT  1字节
    return HAL_I2C_Mem_Read(&hi2c2, DevAddress, MemAddr, I2C_MEMADD_SIZE_8BIT, pData, Size, 100);

}

void MPU6050_WriteReg(uint16_t DevAddress, uint16_t MemAddr, uint8_t *pData, uint8_t Size) {
    HAL_I2C_Mem_Write(&hi2c2, DevAddress, MemAddr, I2C_MEMADD_SIZE_8BIT, pData, Size, 100);
}


uint8_t MPU6050_GetId() {
    return MPU6050_ReadReg(MPU6050_ADDR, MPU6050_WHO_AM_I, NULL, 1);
}