#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Serial.h"
#include "stdio.h"

uint8_t byte;

int main(void) {
    OLED_Init();
    Serial_Init();
//    Serial_SendString("Hello World!\r\n");
//    printf("Hello World!\r\n");
    Serial_Printf("Hello World!\r\n");
//    Serial_Printf("Hello Num: %d\r\n", 123);
    while (1) {
//        Serial_ReceiveByte(&byte);
//        OLED_ShowHexNum(1, 1, byte, 2);
        if (Serial_GetRxFlag() == 1) {
            OLED_ShowHexNum(1, 1, Serial_GetRxData(), 2);
        }
    }
}
