#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "PWN.h"
#include "Delay.h"
int main(void) {
    OLED_Init();
    PWN_Init();

    while (1) {
        for (int i = 0; i < 100; i++) {
            PWN_SetCompare(i);
            Delay_ms(10);
        }
        for (int i = 100; i > 0; i--) {
            PWN_SetCompare(i);
            Delay_ms(10);
        }
    }
}
