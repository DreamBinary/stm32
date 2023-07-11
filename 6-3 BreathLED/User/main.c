#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "PWM.h"
#include "Delay.h"
int main(void) {
    OLED_Init();
    PWM_Init();

    while (1) {
        for (int i = 0; i < 1000; i++) {
            PWM_SetCompare(i);
            Delay_ms(10);
        }
        for (int i = 1000; i > 0; i--) {
            PWM_SetCompare(i);
            Delay_ms(10);
        }
    }
}
