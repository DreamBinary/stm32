#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "LightSensor.h"
#include "OLED.h"
#include "Timer.h"

uint16_t All_Count = 0;
uint16_t Time = 0;
int main(void) {
	
	// Delay_ms(5000);
	
	OLED_Init();
	LED_Init();
	LightSensor_Init();
	Timer_Init();

	OLED_ShowString(1, 1, "Count:");
	OLED_ShowString(2, 1, "Time:");
	OLED_ShowNum(1, 7, All_Count, 5);
	OLED_ShowNum(2, 6, Time, 5);
	
	
	//Delay_s(1);
	
	while(1) {
		
		LED_OFF();
		
		Delay_s(1);
		OLED_ShowNum(2, 6, Time, 5);
		

		LED_ON();
		Delay_ms(1); // void add delay
		All_Count += Get_Count();
		OLED_ShowNum(1, 7, All_Count, 5);
		
		Delay_s(1);
		OLED_ShowNum(2, 6, Time, 5);

	}
}


void TIM2_IRQHandler(void){
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Time ++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
