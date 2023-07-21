//
// Created by FIV on 2023/7/11.
//

#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Servo_Init(void) {
    PWM_Init();

}

void Servo_SetAngle(float Angle) {
    PWM_SetCompare(Angle / 180 * 2000 + 500);
}