#ifndef _TOUCH_H_
#define _TOUCH_H_

#include "stm32f4xx.h"

/* ADS7843/7846/UH7843/7846/XPT2046/TSC2046 ָ� */
#define CMD_RDY 0X90  //0B10010000���ò�ַ�ʽ��Y����
#define CMD_RDX	0XD0  //0B11010000���ò�ַ�ʽ��X���� 

/* ����״̬	*/ 
#define Key_Down 0x01
#define Key_Up   0x00 

/* �ʸ˽ṹ�� */
typedef struct 
{
	uint16_t X0;//ԭʼ����
	uint16_t Y0;
	uint16_t X; //����/�ݴ�����
	uint16_t Y;						   	    
	uint8_t  Key_Sta;//�ʵ�״̬			  
	//������У׼����
	float xfac;
	float yfac;
	short xoff;
	short yoff;
}Pen_Holder;

void Touch_Init(void);
uint8_t Read_ADS(uint16_t *x,uint16_t *y);
void Touch_IRQ(void);
uint8_t Convert_Pos(void);
void Refreshes_Screen(void);
void Draw_Big_Point(uint16_t x,uint16_t y);

#endif

