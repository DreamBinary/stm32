#ifndef __LCD_H__
#define __LCD_H__	

#include "stm32f4xx_hal.h"


#define   HDP	479

#define   HT	531
#define   HPS	43
#define   LPS	8
#define   HPW	10

#define   VDP	271
#define   VT	288
#define   VPS	12
#define   FPS	4
#define    VPW	10


/***********************************************************************************
������ɫ�궨��
***********************************************************************************/
#define   Black        0x0000                    // ��ɫ�� 0, 0, 0              
#define   Navy         0x000F                    // ����ɫ�� 0, 0, 128          
#define   Dgreen       0x03E0                    // ����ɫ�� 0, 128, 0          
#define   Dcyan        0x03EF                    // ����ɫ�� 0, 128, 128        
#define   Marooon       0x7800                    // ���ɫ��128, 0, 0           
#define   Purple       0x780F                    // ��ɫ�� 128, 0, 128          
#define   Olive        0x7BE0                    // ����̣�128, 128, 0         
#define   Lgray        0xC618                    // �Ұ�ɫ��192, 192, 192        
#define   Dgray        0x7BEF                    // ���ɫ��128, 128, 128        
#define   Blue         0x001F                    // ��ɫ�� 0, 0, 255            
#define   Green        0x07E0                 	 // ��ɫ�� 0, 255, 0             
#define   Cyan         0x07FF                    // ��ɫ�� 0, 255, 255           
#define   Red          0xF800                    // ��ɫ�� 255, 0, 0             
#define   Magenta      0xF81F                    // Ʒ�죺 255, 0, 255          
#define   Yellow       0xFFE0                    // ��ɫ�� 255, 255, 0           
#define   White        0xFFFF                    // ��ɫ�� 255, 255, 255   

/********************************************************************************/
/*********************�궨��*****************************************************/
/* Private typedef -----------------------------------------------------------*/
//typedef struct
//{
//  vuint16_t LCD_REG;
//  vuint16_t LCD_RAM;
//} LCD_TypeDef;

/* LCD is connected to the FSMC_Bank1_NOR/SRAM4 and NE4 is used as ship select signal */
//#define LCD_BASE    ((u32)(0x60000000 | 0x0C000000))
//#define LCD         ((LCD_TypeDef *) LCD_BASE)

//#define LCD_REG (*(volatile unsigned int*)(0x6c000000))
//#define LCD_RAM (*(volatile unsigned int*)(0x6c000002))
//д����
//#define LCD_WriteCom(LCD_Reg) LCD->LCD_REG=(LCD_Reg)
//
////д����
//#define LCD_WriteRAM(RGB_Code) LCD->LCD_RAM=(RGB_Code)
//


//��������
void lcd_clear(uint16_t Color);
void lcd_init(void);
void write_data_Prepare(void);
void LCD_ShowString(uint16_t x0, uint16_t y0, uint8_t *pcStr, uint16_t PenColor, uint16_t BackColor);
void LCD_Fill(uint8_t xsta, uint16_t ysta, uint8_t xend, uint16_t yend, uint16_t colour);
void LCD_DrawLine(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color);
void LCD_DrawPicture(uint16_t StartX,uint16_t StartY,uint16_t Xend,uint16_t Yend,uint8_t *pic);
void Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);
void LCD_DrawRectangle(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color);
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint8_t size, uint16_t PenColor, uint16_t BackColor);
#endif
