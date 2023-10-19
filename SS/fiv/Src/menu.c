//
// Created by fivv on 2023/10/8.
//

#include "menu.h"
#include "lcd.h"
#include "cmsis_os.h"
#include "fsmc.h"
//#include "tim.h"

uint16_t edge_x[] = {60, 210, 270, 420};
uint16_t edge_y[] = {24, 124, 148, 248};
uint16_t center_x[] = {115, 325};
uint16_t center_y[] = {64, 188};
//uint8_t start_steer = 0;
uint16_t cnt = 0;
char *menu[] = {"LED", "CNT", "BEEP", "BG"};
// colors
unsigned short colors[] = {White, Navy, Dgreen, Dcyan, Marooon, Purple, Olive, Lgray, Dgray, Blue, Green, Cyan,
                           Red, Magenta, Yellow};
uint8_t color_index = 0;


void menu_init(void) {
    unsigned short color = colors[color_index];
    lcd_clear(color);
    for (uint8_t i = 0; i < 3; i += 2) {
        for (uint8_t j = 0; j < 3; j += 2) {
            LCD_DrawRectangle(edge_x[i], edge_y[j], edge_x[i + 1], edge_y[j + 1], Black);
        }
    }
    for (uint8_t i = 0; i < 2; i++) {
        for (uint8_t j = 0; j < 2; j++) {
            // string
            LCD_ShowString(center_x[i], center_y[j], menu[i * 2 + j], Black, color);
        }
    }
}

void showString(char *str) {
    LCD_ShowString(0, 0, str, Black, White);
}

uint8_t menu_area(uint16_t x, uint16_t y) {
    uint8_t area = 0;
    if (x > edge_x[0] && x < edge_x[1] && y > edge_y[0] && y < edge_y[1]) {
        area = 1;
    } else if (x > edge_x[2] && x < edge_x[3] && y > edge_y[0] && y < edge_y[1]) {
        area = 2;
    } else if (x > edge_x[0] && x < edge_x[1] && y > edge_y[2] && y < edge_y[3]) {
        area = 3;
    } else if (x > edge_x[2] && x < edge_x[3] && y > edge_y[2] && y < edge_y[3]) {
        area = 4;
    }
    return area;
}

void menu_select(uint16_t x, uint16_t y) {
    uint8_t c = menu_area(x, y);
    switch (c) {
        case 1:// led
            //osThreadDef(led, LED, osPriorityNormal, 0, 128);
            //osThreadCreate(osThread(led), NULL);
            HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10);
            break;
        case 2:// beep
            HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
            break;
        case 3:// steer
            cnt++;
            printf("%d\n", cnt);
//            start_steer = (start_steer + 1) % 2;
            // uint16_t i;
//            while (start_steer == 1) {
            /*for (i = 600; i < 2400; i++) {
                __HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, i);
                HAL_Delay(1);
            }
            for (i = 2400; i > 600; i--) {
                __HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, i);
                HAL_Delay(1);
            }*/
//            }
            break;
        case 4:// bg
            color_index = (color_index + 1) % 15;
            menu_init();
            break;
        default:
            break;
    }
}
