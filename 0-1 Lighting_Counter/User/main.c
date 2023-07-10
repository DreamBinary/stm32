#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "LightSensor.h"
#include "OLED.h"

uint16_t All_Count = 0;
int main(void) {
	
	OLED_Init();
	LED_Init();
	LightSensor_Init();
	// Delay_ms(5000);
	OLED_ShowString(1, 1, "Count:");
	OLED_ShowNum(1, 7, All_Count, 5);
	Delay_ms(1000);
	while(1) {
		LED_ON();
		Delay_ms(10); // void add delay
		All_Count += Get_Count();
		OLED_ShowNum(1, 7, All_Count, 5);
		Delay_ms(1000);
		LED_OFF();
		Delay_ms(1000);
	}
}
