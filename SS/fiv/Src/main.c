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
#include "spi.h"
#include "tim.h"
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
uint8_t Dowm_flag = 0;  //1 ï¿½ï¿½Ê¾ï¿½Ñ¾ï¿½ï¿½ï¿½ï¿½ï¿½   
uint16_t line_x = 0;        //ï¿½æ´¢ï¿½ï¿½Ç°ï¿½ï¿½ï¿½ï¿½
uint16_t line_y = 0;
uint16_t Date = 0;
uint8_t j = 0;

__IO uint16_t adcx[4]={0};
float temp0,temp1,temp2,temp3;
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

void HAL_Delay_us(uint32_t us) {
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000000);
    HAL_Delay(us - 1);
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
}

void LED(void const *arg) {
	while(1) {
			HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10);
			osDelay(500);
	}
}

void BEEP(void const *arg) {
	while(1) {
			// HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
			
			//osDelay(500);
		
		/*HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);
		osDelay(50);
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);
		osDelay(50);*/
	}
}

void Chuang(void const *arg) {
	while(1) {
			// HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
			
			//osDelay(500);
		
		printf("fsdafasd");
		osDelay(1000);
	}
}

void MyADC(void const *arg) {
	while(1) {
			// HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
			
			//osDelay(500);
			temp0 = (float)adcx[0]*(3.3/4096);
			temp1 = (float)adcx[1]*(3.3/4096); 
			temp2 = (float)adcx[2]*(3.3/4096); 
			temp3 = (float)adcx[3]*(3.3/4096); 	
			printf("\r\n ¾Æ¾«´«¸ÐÆ÷ =%f\n ¹âÃô´«¸ÐÆ÷ =%f\n »ðÑæ´«¸ÐÆ÷ =%f\n ÆøÌå´«¸ÐÆ÷ =%f\n\r",temp0,temp1,temp2,temp3);
			HAL_Delay(1000);
	}
}

void Steer(void const *arg) { 
	uint16_t i;
	
	while(1){
		for(i = 600;i < 2400;i++)
	 {
		__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,i);
		HAL_Delay(1);
	 }
	  for(i = 2400;i > 600;i--)
	 {
		__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,i);
		HAL_Delay(1);
	 }
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
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  MX_ADC3_Init();
  MX_TIM12_Init();

  /* USER CODE BEGIN 2 */

	HAL_ADC_Start_DMA(&hadc3,(uint32_t*)adcx,4);//¿ªÆôADC×ª»»
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
	
	
		//osThreadDef(led, LED, osPriorityAboveNormal, 0, 128);
		//osThreadCreate(osThread(led), NULL);
		
		//osThreadDef(beep, BEEP, osPriorityNormal, 0, 128);
		//osThreadCreate(osThread(beep), NULL);
		
		//osThreadDef(chuang, Chuang, osPriorityNormal, 0, 128);
		//osThreadCreate(osThread(chuang), NULL);
		
		//osThreadDef(myadc, MyADC, osPriorityNormal, 0, 128);
		//osThreadCreate(osThread(myadc), NULL);
		
		osThreadDef(steer, Steer, osPriorityNormal, 0, 128);
		osThreadCreate(osThread(steer), NULL);

    /*printf("=====init======\n");
    lcd_init();
    menu_init();
    printf("init ok!!!!!!\n");*/

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
			/*
        if (Pen_Point.Key_Sta == Key_Down)     //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
        {
            HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);                 //ï¿½Ø±ï¿½ï¿½Ð¶ï¿½
            HAL_Delay(20);
            if (!HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_7)) {
                HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);    //ï¿½Ø±ï¿½ï¿½Ð¶ï¿½
                printf("++++++intter+++++\r\n");

                if (Convert_Pos())             //ï¿½ï¿½Åµï¿½ï¿½ï¿½ï¿½X,Yï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Öµ	ï¿½É¹ï¿½×ªï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½1 Ê§ï¿½Ü·ï¿½ï¿½ï¿½0
                {
                    line_x = Pen_Point.X0;
                    line_y = Pen_Point.Y0;
                    HAL_Delay(200);
                    //						while(!HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_7));		//ï¿½Ð¶ï¿½P_7ï¿½Ç·ï¿½ï¿½Ú°ï¿½ï¿½Â£ï¿½Ö±ï¿½ï¿½Ì§ï¿½ï¿½ï¿½ï¿½Ö¹  ï¿½ï¿½ï¿½ï¿½Îª0ï¿½ï¿½Ì§ï¿½ï¿½Îª1
                    printf("x = %d,y = %d\r\n", line_x, line_y);
                    menu_select(line_x, line_y); //TODO
                    Pen_Point.X0 = 0;
                    Pen_Point.Y0 = 0;
                    Pen_Point.Key_Sta = Key_Up;            //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ýºï¿½, ï¿½Ø¸ï¿½ï¿½ï¿½Ã»ï¿½Ð°ï¿½ï¿½Âµï¿½×´Ì¬
                }

                Pen_Point.Key_Sta = Key_Up;            //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ýºï¿½, ï¿½Ø¸ï¿½ï¿½ï¿½Ã»ï¿½Ð°ï¿½ï¿½Âµï¿½×´Ì¬
                // printf("%%%%%%%%%%%%%%\r\n");
                HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);                     //ï¿½ï¿½ï¿½ï¿½ï¿½Ð¶ï¿½
            } else {
                HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
                Pen_Point.Key_Sta = Key_Up;
                continue;
            }
        }*/
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

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 96;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/* USER CODE BEGIN 4 */
int fputc(int ch, FILE *f) {
    while ((USART1->SR & 0X40) == 0);//Ñ­ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½,Ö±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?
    USART1->DR = (uint8_t) ch;
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
