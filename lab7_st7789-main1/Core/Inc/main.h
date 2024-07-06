/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SW1_Pin GPIO_PIN_3
#define SW1_GPIO_Port GPIOE
#define SW1_EXTI_IRQn EXTI3_IRQn
#define SW2_Pin GPIO_PIN_4
#define SW2_GPIO_Port GPIOE
#define SW2_EXTI_IRQn EXTI4_IRQn
#define SW3_Pin GPIO_PIN_5
#define SW3_GPIO_Port GPIOE
#define SW3_EXTI_IRQn EXTI9_5_IRQn
#define CS_Pin GPIO_PIN_4
#define CS_GPIO_Port GPIOA
#define RES_Pin GPIO_PIN_14
#define RES_GPIO_Port GPIOD
#define BLK_Pin GPIO_PIN_15
#define BLK_GPIO_Port GPIOD
#define SCL_Pin GPIO_PIN_3
#define SCL_GPIO_Port GPIOB
#define MOSI_Pin GPIO_PIN_4
#define MOSI_GPIO_Port GPIOB
#define DC_Pin GPIO_PIN_5
#define DC_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
