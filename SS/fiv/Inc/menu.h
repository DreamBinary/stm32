//
// Created by fivv on 2023/10/8.
//

#ifndef __TOUCH_LCD_MENU_H
#define ___TOUCH_LCD_MENU_H

#include "stm32f4xx_hal.h"
void menu_init(void);
void menu_select(uint16_t x, uint16_t y);
void showString(char *str);
#endif //___TOUCH_LCD_MENU_H
