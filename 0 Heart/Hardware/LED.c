#include "stm32f10x.h"                  // Device header


void LED_Init(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	
	GPIO_InitTypeDef GPIO_InitStructureA;
	GPIO_InitStructureA.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructureA.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructureA.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructureA);
	
	GPIO_InitTypeDef GPIO_InitStructureB;
	GPIO_InitStructureB.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructureB.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructureB.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructureB);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_All);
	GPIO_SetBits(GPIOB, GPIO_Pin_All);
}

void LED_ON(uint8_t type,uint16_t num) {
	if (type == 0) {
		GPIO_Write(GPIOB, 0xFFFF);
		GPIO_Write(GPIOA, ~num);
	} else {
		GPIO_Write(GPIOA, 0xFFFF   );
		GPIO_Write(GPIOB, ~num);
	}
}

void LED_All_ON(void) {
	GPIO_ResetBits(GPIOA, GPIO_Pin_All);
	GPIO_ResetBits(GPIOB, GPIO_Pin_All);
}
void LED_All_OFF(void) {
	GPIO_SetBits(GPIOA, GPIO_Pin_All);
	GPIO_SetBits(GPIOB, GPIO_Pin_All);
}


