//
// Created by FIV on 2023/7/21.
//

#include "stm32f10x.h"
#include "AD.h"

void AD_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    GPIO_Init(GPIOA, &(GPIO_InitTypeDef){
            .GPIO_Pin = GPIO_Pin_0,
            .GPIO_Mode = GPIO_Mode_AIN,
            .GPIO_Speed = GPIO_Speed_50MHz,
    });



    ADC_Init(ADC1, &(ADC_InitTypeDef){
            .ADC_Mode = ADC_Mode_Independent,
            .ADC_ScanConvMode = DISABLE,
            .ADC_ContinuousConvMode = DISABLE,
            .ADC_ExternalTrigConv = ADC_ExternalTrigConv_None,
            .ADC_DataAlign = ADC_DataAlign_Right,
            .ADC_NbrOfChannel = 1,
    });

    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));

}

uint16_t AD_GetValue(uint8_t ADC_Channel) {
    ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_239Cycles5);

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    return ADC_GetConversionValue(ADC1);
}
