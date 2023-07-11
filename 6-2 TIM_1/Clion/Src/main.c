#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Timer.h"

uint16_t Num;

int main(void) {
    OLED_Init();
    Timer_Init();

    OLED