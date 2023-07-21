#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "AD.h"

uint16_t AD0, AD1, AD2, AD3;

int main(void) {
    OLED_Init();
    AD_Init();

    OLED_ShowString(1, 1, "AD0:");
    OLED_ShowString(2, 1, "AD1:");
    OLED_ShowString(3, 1, "AD2:");
    OLED_ShowString(4, 1, "AD3:");
    while (1) {
        AD0 = AD_GetValue(ADC_Channel_0);
        AD1 = AD_GetValue(ADC_Channel_1);
        AD2 = AD_GetValue(ADC_Channel_2);
        AD3 = AD_GetValue(ADC_Channel_3);

        OLED_ShowNum(1, 9, AD0, 4);
        OLED_ShowNum(2, 9, AD1, 4);

        OLED_ShowNum(3, 9, AD2, 4);
        OLED_ShowNum(4, 9, AD3, 4);
    }
}
