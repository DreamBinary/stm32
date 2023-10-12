////
//// Created by fivv on 2023/10/12.
////
//
//
///**
//  ******************************************************************************
//  * File Name          : main.c
//  * Description        : Main program body
//  ******************************************************************************
//  *
//  * COPYRIGHT(c) 2023 STMicroelectronics
//  *
//  * Redistribution and use in source and binary forms, with or without modification,
//  * are permitted provided that the following conditions are met:
//  *   1. Redistributions of source code must retain the above copyright notice,
//  *      this list of conditions and the following disclaimer.
//  *   2. Redistributions in binary form must reproduce the above copyright notice,
//  *      this list of conditions and the following disclaimer in the documentation
//  *      and/or other materials provided with the distribution.
//  *   3. Neither the name of STMicroelectronics nor the names of its contributors
//  *      may be used to endorse or promote products derived from this software
//  *      without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  *
//  ******************************************************************************
//  */
///* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx_hal.h"
//
///* USER CODE BEGIN Includes */
//
///* USER CODE END Includes */
//
///* Private variables ---------------------------------------------------------*/
//ADC_HandleTypeDef hadc3;
//DMA_HandleTypeDef hdma_adc3;
//
//UART_HandleTypeDef huart1;
//
///* USER CODE BEGIN PV */
///* Private variables ---------------------------------------------------------*/
//__IO uint16_t
//adcx[1] = {
//0};
//float temp;
///* USER CODE END PV */
//
///* Private function prototypes -----------------------------------------------*/
//void SystemClock_Config(void);
//
//void Error_Handler(void);
//
//static void MX_GPIO_Init(void);
//
//static void MX_DMA_Init(void);
//
//static void MX_ADC3_Init(void);
//
//static void MX_USART1_UART_Init(void);
//
///* USER CODE BEGIN PFP */
///* Private function prototypes -----------------------------------------------*/
//
///* USER CODE END PFP */
//
///* USER CODE BEGIN 0 */
//
///* USER CODE END 0 */
//
//int main(void) {
//
//    /* USER CODE BEGIN 1 */
//
//    /* USER CODE END 1 */
//
//    /* MCU Configuration----------------------------------------------------------*/
//
//    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
//    HAL_Init();
//
//    /* Configure the system clock */
//    SystemClock_Config();
//
//    /* Initialize all configured peripherals */
//    MX_GPIO_Init();
//    MX_DMA_Init();
//    MX_ADC3_Init();
//    MX_USART1_UART_Init();
//
//    /* USER CODE BEGIN 2 */
//    HAL_ADC_Start_DMA(&hadc3, (uint32_t *) adcx, 1);//����ADCת��
//    /* USER CODE END 2 */
//
//    /* Infinite loop */
//    /* USER CODE BEGIN WHILE */
//    while (1) {
//        /* USER CODE END WHILE */
//
//        /* USER CODE BEGIN 3 */
//        temp = (float) adcx[0] * (3.3 / 4096);
//        printf("\r\n �ƾ������� =%f\n ", temp);
//        HAL_Delay(1000);
//    }
//    /* USER CODE END 3 */
//
//}
//
///** System Clock Configuration
//*/
//void SystemClock_Config(void) {
//
//    RCC_OscInitTypeDef RCC_OscInitStruct;
//    RCC_ClkInitTypeDef RCC_ClkInitStruct;
//
//    __HAL_RCC_PWR_CLK_ENABLE();
//
//    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
//
//    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
//    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
//    RCC_OscInitStruct.HSICalibrationValue = 16;
//    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
//    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
//        Error_Handler();
//    }
//
//    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
//                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
//    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
//    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
//    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
//    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
//        Error_Handler();
//    }
//
//    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
//
//    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
//
//    /* SysTick_IRQn interrupt configuration */
//    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
//}
//
///* ADC3 init function */
//static void MX_ADC3_Init(void) {
//
//    ADC_ChannelConfTypeDef sConfig;
//
//    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
//    */
//    hadc3.Instance = ADC3;
//    hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
//    hadc3.Init.Resolution = ADC_RESOLUTION_12B;
//    hadc3.Init.ScanConvMode = ENABLE;
//    hadc3.Init.ContinuousConvMode = ENABLE;
//    hadc3.Init.DiscontinuousConvMode = DISABLE;
//    hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
//    hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
//    hadc3.Init.NbrOfConversion = 1;
//    hadc3.Init.DMAContinuousRequests = ENABLE;
//    hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
//    if (HAL_ADC_Init(&hadc3) != HAL_OK) {
//        Error_Handler();
//    }
//
//    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
//    */
//    sConfig.Channel = ADC_CHANNEL_4;
//    sConfig.Rank = 1;
//    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
//    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK) {
//        Error_Handler();
//    }
//
//}
//
///* USART1 init function */
//static void MX_USART1_UART_Init(void) {
//
//    huart1.Instance = USART1;
//    huart1.Init.BaudRate = 115200;
//    huart1.Init.WordLength = UART_WORDLENGTH_8B;
//    huart1.Init.StopBits = UART_STOPBITS_1;
//    huart1.Init.Parity = UART_PARITY_NONE;
//    huart1.Init.Mode = UART_MODE_TX_RX;
//    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
//    if (HAL_UART_Init(&huart1) != HAL_OK) {
//        Error_Handler();
//    }
//
//}
//
///**
//  * Enable DMA controller clock
//  */
//static void MX_DMA_Init(void) {
//    /* DMA controller clock enable */
//    __HAL_RCC_DMA2_CLK_ENABLE();
//
//    /* DMA interrupt init */
//    /* DMA2_Stream0_IRQn interrupt configuration */
//    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
//
//}
//
///** Pinout Configuration
//*/
//static void MX_GPIO_Init(void) {
//
//    /* GPIO Ports Clock Enable */
//    __HAL_RCC_GPIOF_CLK_ENABLE();
//    __HAL_RCC_GPIOA_CLK_ENABLE();
//
//}
//
///* USER CODE BEGIN 4 */
//int fputc(int ch, FILE *f) {
//    while ((USART1->SR & 0X40) == 0);//ѭ������,ֱ���������
//    USART1->DR = (uint8_t) ch;
//    return ch;
//}
///* USER CODE END 4 */
//
///**
//  * @brief  This function is executed in case of error occurrence.
//  * @param  None
//  * @retval None
//  */
//void Error_Handler(void) {
//    /* USER CODE BEGIN Error_Handler */
//    /* User can add his own implementation to report the HAL error return state */
//    while (1) {
//    }
//    /* USER CODE END Error_Handler */
//}
//
//#ifdef USE_FULL_ASSERT
//
///**
//   * @brief Reports the name of the source file and the source line number
//   * where the assert_param error has occurred.
//   * @param file: pointer to the source file name
//   * @param line: assert_param error line source number
//   * @retval None
//   */
//void assert_failed(uint8_t* file, uint32_t line)
//{
//  /* USER CODE BEGIN 6 */
//  /* User can add his own implementation to report the file name and line number,
//    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
//  /* USER CODE END 6 */
//
//}
//
//#endif
//
///**
//  * @}
//  */
//
///**
//  * @}
//*/
//
///************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
