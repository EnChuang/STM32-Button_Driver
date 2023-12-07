/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
///* USER CODE BEGIN Includes */
#include	"bsp.h" //外部加入聲明集
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
uint8_t Read_KEY1_Level(void);
uint8_t Read_KEY2_Level(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BWK_Pin GPIO_PIN_0
#define BWK_GPIO_Port GPIOA
#define SW1_Pin GPIO_PIN_1
#define SW1_GPIO_Port GPIOA
#define RST_Pin GPIO_PIN_14
#define RST_GPIO_Port GPIOE
#define ACTIVE_Pin GPIO_PIN_15
#define ACTIVE_GPIO_Port GPIOE
#define Debuger_Tx_Pin GPIO_PIN_10
#define Debuger_Tx_GPIO_Port GPIOB
#define Debuger_Rx_Pin GPIO_PIN_11
#define Debuger_Rx_GPIO_Port GPIOB
#define BLE_EN_Pin GPIO_PIN_4
#define BLE_EN_GPIO_Port GPIOD
#define Data_Tx_Pin GPIO_PIN_5
#define Data_Tx_GPIO_Port GPIOD
#define Data_Rx_Pin GPIO_PIN_6
#define Data_Rx_GPIO_Port GPIOD
#define LED0_Pin GPIO_PIN_1
#define LED0_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

#define BLE_ON		HAL_GPIO_WritePin(BLE_EN_GPIO_Port,BLE_EN_Pin,GPIO_PIN_SET);
#define BLE_OFF		HAL_GPIO_WritePin(BLE_EN_GPIO_Port,BLE_EN_Pin,GPIO_PIN_RESET);

#define ACTIVE_ON		HAL_GPIO_WritePin(ACTIVE_GPIO_Port,	ACTIVE_Pin,	GPIO_PIN_SET);
#define ACTIVE_OFF		HAL_GPIO_WritePin(ACTIVE_GPIO_Port,	ACTIVE_Pin,	GPIO_PIN_RESET);
#define RST_ON		HAL_GPIO_WritePin(RST_GPIO_Port,	RST_Pin,	GPIO_PIN_SET);
#define RST_OFF		HAL_GPIO_WritePin(RST_GPIO_Port,	RST_Pin,	GPIO_PIN_RESET);

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
