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
#include "cmsis_os.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "max7219.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//matrix
QueueHandle_t queueSwitch;
uint8_t number_0[8] = {0x00,0x0E,0x0A,0x0A,0x0A,0x0E,0x00,0x00};
uint8_t number_1[8] = {0x00,0x02,0x02,0x02,0x02,0x02,0x00,0x00};
uint8_t number_2[8] = {0x00,0x0E,0x02,0x0E,0x08,0x0E,0x00,0x00};
uint8_t number_3[8] = {0x00,0x0E,0x02,0x0E,0x02,0x0E,0x00,0x00};
uint8_t number_4[8] = {0x00,0x0A,0x0A,0x0E,0x02,0x02,0x00,0x00};
uint8_t number_5[8] = {0x00,0x0E,0x08,0x0E,0x02,0x0E,0x00,0x00};
uint8_t number_6[8] = {0x00,0x08,0x08,0x0E,0x0A,0x0E,0x00,0x00};
uint8_t number_7[8] = {0x00,0x0E,0x0A,0x02,0x02,0x02,0x00,0x00};
uint8_t number_8[8] = {0x00,0x0E,0x0A,0x0E,0x0A,0x0E,0x00,0x00};
uint8_t number_9[8] = {0x00,0x0E,0x0A,0x0E,0x02,0x02,0x00,0x00};
uint8_t numbers[10][8] = {
			{0x00,0x0E,0x0A,0x0A,0x0A,0x0E,0x00,0x00},
			{0x00,0x02,0x02,0x02,0x02,0x02,0x00,0x00},
			{0x00,0x0E,0x02,0x0E,0x08,0x0E,0x00,0x00},
			{0x00,0x0E,0x02,0x0E,0x02,0x0E,0x00,0x00},
			{0x00,0x0A,0x0A,0x0E,0x02,0x02,0x00,0x00},
			{0x00,0x0E,0x08,0x0E,0x02,0x0E,0x00,0x00},
			{0x00,0x08,0x08,0x0E,0x0A,0x0E,0x00,0x00},
			{0x00,0x0E,0x0A,0x02,0x02,0x02,0x00,0x00},
			{0x00,0x0E,0x0A,0x0E,0x0A,0x0E,0x00,0x00},
			{0x00,0x0E,0x0A,0x0E,0x02,0x02,0x00,0x00}
};


uint8_t Max7219_data[4];
uint8_t Max7219_data1[4];
 
uint8_t screen1[4];
uint8_t screen2[4];
uint8_t screen3[4];
uint8_t screen4[4];

TaskHandle_t handleMatrix;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t counter = 0,sec=0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	 if(htim==&htim2){
		if(counter < 1000)
		{
		counter++;
		}else
		{
			sec++;
			counter=0;
		}
	 }
}

void taskMatrix(void *pvParm){
	uint8_t select = 0;
	uint8_t units =0,tens=0, hundreds =0;
	uint8_t unit =0,ten=0, hundred =0,thousand =0;

	while(1){
	xQueueReceiveFromISR(queueSwitch, &select, NULL);
	switch(select){
				case 1:{
						HAL_TIM_Base_Start_IT(&htim2); 
						//__HAL_TIM_SET_COUNTER(&htim2,0);
						//counter =__HAL_TIM_GET_COUNTER(&htim2);
					  //counter = (counter + 1) % 1000;
						units = counter %10 ;
						tens = (counter /10)%10;
						hundreds =(counter/100)%10;
						
						unit = sec %10 ;
						ten = (sec /10)%10;
						hundred =(sec/100)%10;
						thousand =(sec/1000)%10;
						for(int i = 0; i < 8; i++)//one step one line > so run 8 times
						{
							screen1[i] = numbers[hundred][i]| (numbers[thousand][i] << 4);
							screen2[i] = numbers[unit][i]| (numbers[ten][i] << 4);
							screen3[i] = numbers[units][i]| (numbers[tens][i] << 4);
							//screen4[i] = numbers[0][i]| (numbers[0][i] << 4);
							Max7219_data1[0] = screen1[i];
							Max7219_data1[1] = screen2[i];
							Max7219_data1[3] = screen3[i];
							Max7219_data1[2] = numbers[hundreds][i];
						
							Write_Matrix(i + 1,Max7219_data1);
						}
					
					break;
				}
				
			
				case 2:{
						HAL_TIM_Base_Stop_IT(&htim2);
						
					break;
				}
				
				case 3:{
					__HAL_TIM_SET_COUNTER(&htim2, 0);
					counter=0;
					sec=0;
					for(int i = 0; i < 8; i++)//one step one line > so run 8 times
					{
					Max7219_data[i] = numbers[0][i]| (numbers[0][i] << 4);
					Max7219_data1[0] = Max7219_data[i];
					Max7219_data1[1] = Max7219_data[i];
					Max7219_data1[3] = Max7219_data[i];
					Max7219_data1[2] = numbers[0][i];
						
					Write_Matrix(i + 1,Max7219_data1);

					}
					break;
				}				
				default:

					for(int i = 0; i < 8; i++)//one step one line > so run 8 times
					{
					Max7219_data[i] = numbers[0][i]| (numbers[0][i] << 4);
					Max7219_data1[0] = Max7219_data[i];
					Max7219_data1[1] = Max7219_data[i];
					Max7219_data1[3] = Max7219_data[i];
					Max7219_data1[2] = numbers[0][i];
						
					Write_Matrix(i + 1,Max7219_data1);

					}
					break;
			}
	}
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	uint8_t mode = 0;
	
	switch(GPIO_Pin){
		//sw1 PE3
		case GPIO_PIN_3:
		{
			if(HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin) == 1){
				mode = 1;
				//printf("display mode:default \r\n");
				//HAL_TIM_Base_Start_IT(&htim2);	
				xQueueSendFromISR(queueSwitch, &mode, NULL);
			}
			break;
		}
		
		//sw2 PE4
		case GPIO_PIN_4:
		{
			if(HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin) == 1){
				mode = 2;
				//printf("display mode:student id \r\n");
				xQueueSendFromISR(queueSwitch, &mode, NULL);
			}
			break;
		}
		case GPIO_PIN_5: //sw3 PE5
		{ 
			if(HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) ==0){
			mode = 3;
			//printf("display mode:system startup timer \r\n");
			xQueueSendFromISR(queueSwitch, &mode, NULL); }
			break; 
		}
	
		default:
			mode = 0;
			xQueueSendFromISR(queueSwitch, &mode, NULL);
			//printf("unknown irq happend \r\n");
			break;
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
  MX_SPI1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	Init_MAX7219_8x8(); 
	xTaskCreate(taskMatrix, "Matrix", 512, NULL, 1, &handleMatrix);
	queueSwitch = xQueueCreate(3, sizeof(uint8_t));
  vTaskStartScheduler();
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

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
