//
// Created by 16477 on 2023/9/12.
//

#include "stm32f1xx_hal.h" // HAL库的头文件

DMA_HandleTypeDef hdma;
uint16_t MyDMA_Size;

void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size) {
    //  AddrA: 源地址  --- 外设
    //  AddrB: 目的地址  --- 存储器
    MyDMA_Size = Size;
    // 初始化HAL库
    HAL_Init();

    // 使能DMA时钟
    __HAL_RCC_DMA1_CLK_ENABLE();

    // 配置DMA传输参数
    hdma.Instance = DMA1_Channel1;
    hdma.Init.Direction = DMA_PERIPH_TO_MEMORY; // 外设到存储器
    hdma.Init.PeriphInc = DMA_PINC_ENABLE;      // 外设地址自增
    hdma.Init.MemInc = DMA_MINC_ENABLE;         // 存储器地址自增
    hdma.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma.Init.Mode = DMA_NORMAL;
    hdma.Init.Priority = DMA_PRIORITY_MEDIUM;
//    hdma.Init.PeriphBurst = DMA_PBURST_SINGLE;
//    hdma.Init.MemBurst = DMA_MBURST_SINGLE;
//    hdma.Init.PeriphBaseAddr = AddrA;
//    hdma.Init.MemBaseAddr = AddrB;
//    hdma.Init.BufferSize = Size;

    // 初始化DMA
    HAL_DMA_Init(&hdma);
}

void MyDMA_Transfer(uint32_t AddrA, uint32_t AddrB, uint16_t Size) {
    // 启动DMA传输
    HAL_DMA_Start(&hdma, AddrA, AddrB, MyDMA_Size);
    // 等待传输完成
    HAL_DMA_PollForTransfer(&hdma, HAL_DMA_FULL_TRANSFER, HAL_MAX_DELAY);
}
