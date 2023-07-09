#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"
#include "LightSensor.h"

uint8_t keyNum;
int main(void) {
	
	LED_Init();
	LightSensor_Init();


	while(1) {
		Delay_ms(1000);
		LED_ON();
		Delay_ms(1000);
		LED_OFF();
		
		/* if (LightSensor_Get() == 1 ) {
			Buzzer_ON();
			
		} else {
			
			Buzzer_OFF();
		} */
	}
}
