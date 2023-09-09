#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Serial.h"
#include "stdio.h"
#include "Key.h"

uint8_t byte;

int main(void) {
    OLED_Init();
    Serial_Init();
    Key_Init();
//    Serial_SendString("Hello World!\r\n");
//    printf("Hello World!\r\n");
//    Serial_Printf("Hello World!\r\n");
//    Serial_Printf("Hello Num: %d\r\n", 123);

    OLED_ShowString(1, 1, "Tx:");
    OLED_ShowString(3, 1, "Rx:");
    Serial_TxPacket[0] = 0x01;
    Serial_TxPacket[1] = 0x02;
    Serial_TxPacket[2] = 0x03;
    Serial_TxPacket[3] = 0x04;

    while (1) {
//        Serial_ReceiveByte(&byte);
//        OLED_ShowHexNum(1, 1, byte, 2);
//        if (Serial_GetRxFlag() == 1) {
//            OLED_ShowHexNum(1, 1, Serial_GetRxData(), 2);
//        }

        if (Key_GetNum() == 1) {
            Serial_TxPacket[0]++;
            Serial_TxPacket[1]++;
            Serial_TxPacket[2]++;
            Serial_TxPacket[3]++;
            Serial_SendPacket();

            OLED_ShowHexNum(2, 1, Serial_TxPacket[0], 2);
            OLED_ShowHexNum(2, 4, Serial_TxPacket[1], 2);
            OLED_ShowHexNum(2, 7, Serial_TxPacket[2], 2);
            OLED_ShowHexNum(2, 10, Serial_TxPacket[3], 2);
        }

        if (Serial_GetRxFlag() == 1) {
            OLED_ShowHexNum(4, 1, Serial_RxPacket[0], 2);
            OLED_ShowHexNum(4, 4, Serial_RxPacket[1], 2);
            OLED_ShowHexNum(4, 7, Serial_RxPacket[2], 2);
            OLED_ShowHexNum(4, 10, Serial_RxPacket[3], 2);
        }
    }
}
