/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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
#define Spray_Time_Pin GPIO_PIN_0
#define Spray_Time_GPIO_Port GPIOC
#define AC1_Over_Heat_LED_Pin GPIO_PIN_1
#define AC1_Over_Heat_LED_GPIO_Port GPIOC
#define Temp_Sensor1_Pin GPIO_PIN_2
#define Temp_Sensor1_GPIO_Port GPIOC
#define Temp_Sensor2_Pin GPIO_PIN_3
#define Temp_Sensor2_GPIO_Port GPIOC
#define Sig_Oiler_Pin GPIO_PIN_0
#define Sig_Oiler_GPIO_Port GPIOA
#define Sig_Solenoid2_Pin GPIO_PIN_1
#define Sig_Solenoid2_GPIO_Port GPIOA
#define Sig_Solenoid1_Pin GPIO_PIN_2
#define Sig_Solenoid1_GPIO_Port GPIOA
#define Sig_Clamp_Pin GPIO_PIN_3
#define Sig_Clamp_GPIO_Port GPIOA
#define Machine_LED_Pin GPIO_PIN_4
#define Machine_LED_GPIO_Port GPIOA
#define Mag_Mosfet_Pin GPIO_PIN_5
#define Mag_Mosfet_GPIO_Port GPIOA
#define Demag_Mosfet_Pin GPIO_PIN_6
#define Demag_Mosfet_GPIO_Port GPIOA
#define Mag_In_Pin GPIO_PIN_4
#define Mag_In_GPIO_Port GPIOC
#define Demag_In_Pin GPIO_PIN_5
#define Demag_In_GPIO_Port GPIOC
#define GREEN_LED_Pin GPIO_PIN_6
#define GREEN_LED_GPIO_Port GPIOB
#define RED_LED_Pin GPIO_PIN_7
#define RED_LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
