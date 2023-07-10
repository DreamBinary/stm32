#include "stm32f10x.h"                  // Device header
#include "OLED.h"


int main(void) {
	OLED_Init();
	OLED_ShowString(1, 1, "Hello World");
	while(1) {}
}
