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
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "Touch.h"
#include "stdio.h"
#include "menu.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
extern uint8_t CMD_X[3];
extern uint8_t CMD_Y[3];
////uint8_t CMD_X[6] ={0xD0,0x00,0x00,0x00,0x00,0x00};
////uint8_t CMD_Y[6] ={0x90,0x00,0x00,0x00,0x00,0x00};
//uint8_t  pseudo_data[2]={0x00,0x00};
extern uint8_t SPI_RE[3];

extern uint8_t Cmd_Buf[15];
extern uint8_t Cmdcont;
extern unsigned char gImage_menu[];
extern unsigned char gImage_fg[];
uint8_t aaa[16] = {0};
uint8_t recv_end_flag = 0;
uint8_t rx_len = 0;
uint8_t Dowm_flag = 0;  //1 ��ʾ�Ѿ�����   
uint16_t line_x = 0;        //�洢��ǰ����
uint16_t line_y = 0;
uint16_t Date = 0;
uint8_t j = 0;
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
Pen_Holder Pen_Point;

/* USER CODE END 0 */

int main(void) {

    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration----------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_FSMC_Init();
    MX_SPI2_Init();
    MX_USART1_UART_Init();

    /* USER CODE BEGIN 2 */

    printf("=====init======\n");
    lcd_init();
    menu_init();
    printf("init ok!!!!!!\n");

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
        // printf("%d\n", Pen_Point.Key_Sta);
        if (Pen_Point.Key_Sta == Key_Down)     //������������
        {
            HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);                 //�ر��ж�
            HAL_Delay(20);
            if (!HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_7)) {
                HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);    //�ر��ж�
                printf("++++++intter+++++\r\n");

                if (Convert_Pos())             //��ŵ����X,Y������ֵ	�ɹ�ת�� ����1 ʧ�ܷ���0
                {
                    line_x = Pen_Point.X0;
                    line_y = Pen_Point.Y0;
                    HAL_Delay(200);
                    //						while(!HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_7));		//�ж�P_7�Ƿ��ڰ��£�ֱ��̧����ֹ  ����Ϊ0��̧��Ϊ1
                    printf("x = %d,y = %d\r\n", line_x, line_y);
                    menu_select(line_x, line_y); //TODO
                    Pen_Point.X0 = 0;
                    Pen_Point.Y0 = 0;
                    Pen_Point.Key_Sta = Key_Up;            //�������ݺ�, �ظ���û�а��µ�״̬
                }

                Pen_Point.Key_Sta = Key_Up;            //�������ݺ�, �ظ���û�а��µ�״̬
                // printf("%%%%%%%%%%%%%%\r\n");
                HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);                     //�����ж�
            } else {
                HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
                Pen_Point.Key_Sta = Key_Up;
                continue;
            }
        }
        /********MENU HANDLER********/

        /****************************/
    }
    /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void) {

    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 16;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 96;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
        Error_Handler();
    }

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/* USER CODE BEGIN 4 */
int fputc(int ch, FILE *f) {
    while ((USART1->SR & 0X40) == 0);//ѭ������,ֱ���������
    USART1->DR = (uint8_t) ch;
    return ch;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void) {
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
