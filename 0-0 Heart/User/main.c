#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"

int x = 0;
int flag = 1;
int time = 1;
int main(void) {

	LED_Init();
	
	uint8_t LED_Type[] = {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint16_t LED_Num[] = {0x0100, 0x0080, 0x0040, 0x0020, 0x0010, 0x0008, 0x8000, 0x1000, 
	0x0080, 0x0040, 0x0020, 0x0010, 0x0008, 0x0004, 0x0002, 0x0001};
	// Delay_s(5);
	while(1) {
		LED_ON(LED_Type[x], LED_Num[x]);
		Delay_ms(500);
		x++;
		if (x >= 16) {
			x -= 16;
		}
		// hearting
		/* if (x < 16) {
			LED_ON(LED_Type[x], LED_Num[x]);
			Delay_ms(500);
			x++;
			
		} 
		 else {
			while(1) {
				for(int  i = 0;i < 5; i++) {
					LED_All_ON();
					Delay_us(time);
					LED_All_OFF();
					Delay_us(1201-time);
				}
				time++;	
				if (time == 800) {
					time = 1;
					break;
				}
			}
			
			while(1) {
				LED_All_ON();
				time++;	
				if (time == 10) {
					time = 1;
					break;
				}
			}
			
			while(1) {
				for(int  i = 0;i < 10; i++) {
					LED_All_ON();
					Delay_us(200);
					LED_All_OFF();
					Delay_us(1000);
				}
				time++;	
				if (time == 100) {
					time = 1;
					break;
				}
			}
			
			while(1) {
				LED_All_ON();
				time++;	
				if (time == 10) {
					time = 1;
					break;
				}
			}
			
			while(1) {
				for(int  i = 0;i < 10; i++) {
					LED_All_ON();
					Delay_us(200);
					LED_All_OFF();
					Delay_us(1000);
				}
				time++;	
				if (time == 30) {
					time = 1;
					break;
				}
			}
			
			time = 400;
			while(1) {
				for(int  i = 0;i < 10; i++) {
					LED_All_ON();
					Delay_us(time);
					LED_All_OFF();
					Delay_us(1001-time);
				}
				time--;	
				if (time == 1) {
					break;
				}
			}
		} */
	}
}
