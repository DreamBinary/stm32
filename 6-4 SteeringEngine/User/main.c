#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Servo.h"
#include "Delay.h"
#include "Key.h"

int main(void) {
    uint8_t KeyNum = 0;
    float Angle = 0;
    OLED_Init();
	Key_Init();
	Servo_Init();

    OLED_ShowString(1, 1, "Angle");

    while (1) {
        KeyNum = Key_GetNum();
        if (KeyNum == 1) {
            Angle += 30;
            if (Angle > 180) {
                Angle = 0;
            }
        }
        Servo_SetAngle(Angle);
        OLED_ShowNum(1, 7, Angle, 3);
    }
}
