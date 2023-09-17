//
// Created by 16477 on 2023/9/17.
//

#ifndef STM32_MYRTC_H
#define STM32_MYRTC_H
extern uint16_t MyRTC_Time[];

void MyRTC_Init(void);
void MyRTC_SetTime(void);
void MyRTC_ReadTime(void);
#endif //STM32_MYRTC_H
