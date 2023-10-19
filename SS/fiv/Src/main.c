/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2023 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
extern uint8_t gImage_fg[];

__IO uint16_t
adcx[4]={0};
float temp0, temp1, temp2, temp3;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
void MX_FREERTOS_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void lcd_init(void);

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void HAL_Delay_us(uint32_t us) {
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000000);
    HAL_Delay(us - 1);
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
}

void LED(void const *arg) {
    while (1) {
        HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10);
        osDelay(500);
    }
}

void BEEP(void const *arg) {
    while (1) {
        HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
				osDelay(500);

        /*HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);
        osDelay(50);
        HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);
        osDelay(50);*/
    }
}

void Port(void const *arg) {
    while (1) {
        // HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);

        //osDelay(500);

        printf("fsdafasd\n");
        osDelay(1000);
    }
}

void MyADC(void const *arg) {
    while (1) {
        // HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);

        //osDelay(500);
        temp0 = (float) adcx[0] * (3.3 / 4096);
        temp1 = (float) adcx[1] * (3.3 / 4096);
        temp2 = (float) adcx[2] * (3.3 / 4096);
        temp3 = (float) adcx[3] * (3.3 / 4096);
        printf("\r\n 酒精传感器 =%f\n 光敏传感器 =%f\n 火焰传感器 =%f\n 气体传感器 =%f\n\r", temp0, temp1, temp2,
               temp3);
        osDelay(1000);
    }
}

void Steer(void const *arg) {
    uint16_t i;

    while (1) {
        for (i = 600; i < 2400; i++) {
            __HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, i);
            HAL_Delay(1);
        }
        for (i = 2400; i > 600; i--) {
            __HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, i);
						HAL_Delay(1);
        }
    }
}

void MyLCD(void const *arg) {
    char s[50] = "";

    while (1) {
       //sprintf(s, "\r\n 酒精传感器 =%f\n 光敏传感器 =%f\n 火焰传感器 =%f\n 气体传感器 =%f\n\r", temp0, temp1, temp2,
               //temp3);
        //showString(s);
			lcd_clear(Blue);
			 LCD_ShowString(60, 18, "fsdafasd\nfasfsdaasfd", Black, White);
        osDelay(1000);
    }

}


/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_FSMC_Init();
  MX_USART1_UART_Init();
  MX_ADC3_Init();
  MX_TIM12_Init();
  MX_I2C1_Init();
	lcd_init();
  /* USER CODE BEGIN 2 */
	
	
		lcd_clear(Blue);
		HAL_Delay(500);
		LCD_ShowString(60, 18, "**** 液晶驱动 ****", Blue, White);
	
		HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
		HAL_ADC_Start_DMA(&hadc3, (uint32_t *) adcx, 4);//开启ADC转换
   


    osThreadDef(led, LED, osPriorityAboveNormal, 0, 128);
		osThreadCreate(osThread(led), NULL);

    osThreadDef(beep, BEEP, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(beep), NULL);

    osThreadDef(port, Port, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(port), NULL);

    osThreadDef(myadc, MyADC, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(myadc), NULL);

		//osThreadDef(steer, Steer, osPriorityNormal, 0, 128);
		//osThreadCreate(osThread(steer), NULL);

    osThreadDef(mylcd, MyLCD, osPriorityNormal, 0, 128);
    osThreadCreate(osThread(mylcd), NULL);

  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
			//lcd_clear(Blue);
			//LCD_ShowString(60, 18, "adsfsdfsad", Blue, White); 
      //HAL_Delay(1000);
        // printf("%d\n", Pen_Point.Key_Sta);
        /********MENU HANDLER********/

        /****************************/
    }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/* USER CODE BEGIN 4 */
/*int fputc(int ch, FILE *f) {
    while ((USART1->SR & 0X40) == 0);
    USART1->DR = (uint8_t) ch;
    return ch;
}*/
int fputc(int ch, FILE *f){ 
  uint8_t tmp[1]={0};
	tmp[0] = (uint8_t)ch;
	HAL_UART_Transmit(&huart1,tmp,1,10);	
	return ch;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
    /* User can add his own implementation to report the HAL error return state */
    while (1) {
    }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
