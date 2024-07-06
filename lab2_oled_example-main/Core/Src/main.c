/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "oled.h"
#include "u8g2.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "img_qrcode.h"
#include "bongo_cat_1.h"
#include "bongo_cat_2.h"
#include "capoo1.h"



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
TaskHandle_t handleOled;
QueueHandle_t queueSwitch;

u8g2_t u8g2;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void taskOLED(void *pvParm){
	u8g2Init(&u8g2);
	u8g2_ClearBuffer(&u8g2);
	u8g2_ClearDisplay(&u8g2);
	u8g2_SetFont(&u8g2, u8g2_font_samim_16_t_all);
	uint8_t displayMode = 9;
	uint8_t stuID[9] = "B10913154";
	char str[10];
	int progress ;
 
	
	while(1){
		
		xQueueReceive(queueSwitch, &displayMode, NULL);
		
		switch(displayMode){
			case 0:{
				u8g2_ClearBuffer(&u8g2);
				u8g2_DrawCircle(&u8g2, 8, 24, 6, U8G2_DRAW_ALL);				
					for(int i= 0;i<10;i++)
					{
						snprintf(str, i, "%s", stuID);
						//int numchars = snprintf(str, 10, "%c", stuID[i]);
						//if (numchars > 0) {
           // u8g2_DrawStr(&u8g2, 10, 24, str);
						//}
						//printf("%d",stuID[i]);					
						//vTaskDelay(200);	
					}
				u8g2_DrawStr(&u8g2, 18, 30, str);
				u8g2_DrawLine(&u8g2, 18, 35, 103, 35);
				u8g2_DrawCircle(&u8g2, 110, 24, 6, U8G2_DRAW_ALL);				
				//u8g2_DrawBox(&u8g2, 110, 18, 12, 12);
				u8g2_SendBuffer(&u8g2);
				
				break;
			}

			case 1:{
				
				u8g2_ClearBuffer(&u8g2);
				u8g2_DrawXBMP(&u8g2, 0, 0, 64, 64, gImage_capoo1);
				u8g2_SendBuffer(&u8g2);
		
				break;
			}
			
			case 2:{
				
				u8g2_ClearBuffer(&u8g2);
				u8g2_DrawStr(&u8g2, 70, 10, "scan");
				u8g2_DrawStr(&u8g2, 70, 30, "qrcode");
				u8g2_DrawXBMP(&u8g2, 0, 0, 64, 64, gImage_img_qrcode);
				u8g2_SendBuffer(&u8g2);
				
											
				break;
			}
				
			default:{
				u8g2_ClearBuffer(&u8g2);
				u8g2_DrawStr(&u8g2, 40, 28, "finish");
				u8g2_DrawBox(&u8g2,0, 30 ,128, 15);
				if(progress < 128){
				progress = progress +4;
				u8g2_DrawStr(&u8g2, 30, 20, "loadig...");	
				u8g2_DrawBox(&u8g2,0, 30 ,progress, 15);
				}					
				else{
				u8g2_DrawStr(&u8g2, 40, 28, "finish");
				u8g2_DrawBox(&u8g2,0, 30 ,128, 15);
				}
				u8g2_SendBuffer(&u8g2);
				break;
			}
		}
		
		vTaskDelay(200);
	}
}

/****
sw1, 2 -> rising edge
sw3, 4 -> falling edge
****/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	uint8_t mode = 0;
	
	switch(GPIO_Pin){
		//sw1 PE3
		case GPIO_PIN_3:
		{
			if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == 1){
				mode = 0;
				printf("display mode:student id, line, circle\r\n");
				xQueueSendFromISR(queueSwitch, &mode, NULL);
			}
			break;
		}
		
		//sw2 PE4
		case GPIO_PIN_4:
		{
			if(HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) == 1){
				mode = 1;
				printf("display mode:show QRcode, timer \r\n");
				xQueueSendFromISR(queueSwitch, &mode, NULL);
			}
			break;
		}
		
				
		
		default:
		{
			mode = 0;
			xQueueSendFromISR(queueSwitch, &mode, NULL);
			printf("unknown irq happend \r\n");
			break;
		}
	}
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	queueSwitch = xQueueCreate(3, sizeof(uint8_t));
	xTaskCreate(taskOLED, "OLED", 512, NULL, 1, &handleOled);
	
	vTaskStartScheduler();
  /* USER CODE END 2 */

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
