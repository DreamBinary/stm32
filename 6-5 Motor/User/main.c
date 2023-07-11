#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Motor.h"
#include "Delay.h"
#include "Key.h"

int main(void) {
    uint8_t KeyNum = 0;
    int8_t Speed = 0;
    OLED_Init();
	Key_Init();
	Motor_Init();

    OLED_ShowString(1, 1, "Speed");

    while (1) {
        KeyNum = Key_GetNum();
        if (KeyNum == 1) {
            Speed += 20;
            if (Speed > 100) {
                Speed = -100;
            }
        }
        Motor_SetSpeed(Speed);
        OLED_ShowNum(1, 7, Speed, 3);
    }
}
