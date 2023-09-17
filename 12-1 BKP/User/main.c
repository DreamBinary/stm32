#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Key.h"
#include "Delay.h"

uint8_t KeyNum;

uint16_t ArrayWrite[] = {0x1234, 0x5678};
uint16_t ArrayRead[2];


int main(void) {
    OLED_Init();
    Key_Init();

    OLED_ShowString(1, 1, "W:");
    OLED_ShowString(2, 1, "R:");

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    PWR_BackupAccessCmd(ENABLE);

    while (1) {
        KeyNum = Key_GetNum();

        if (KeyNum) {
            BKP_WriteBackupRegister(BKP_DR1, ArrayWrite[0]);
            BKP_WriteBackupRegister(BKP_DR2, ArrayWrite[1]);

            OLED_ShowHexNum(1, 3, ArrayWrite[0], 4);
            OLED_ShowHexNum(1, 8, ArrayWrite[1], 4);

            ArrayWrite[0]++;
            ArrayWrite[1]++;
        }

        ArrayRead[0] = BKP_ReadBackupRegister(BKP_DR1);
        ArrayRead[1] = BKP_ReadBackupRegister(BKP_DR2);

        OLED_ShowHexNum(2, 3, ArrayRead[0], 4);
        OLED_ShowHexNum(2, 8, ArrayRead[1], 4);
    }
}
