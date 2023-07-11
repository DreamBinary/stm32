#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Timer.h"

uint16_t Num;

int main(void) {
    OLED_Init();
    Timer_Init();

    OLED_ShowString(1, 1, "Num:");
    OLED_ShowString(2, 1, "CNT:");
    while (1) {
        OLED_ShowNum(1, 6, Num, 5);
        OLED_ShowNum(2, 6, Timer_GetCounter(), 5);
    }
}
