/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * Copyright (c) 2016 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define EEP_CS_Pin GPIO_PIN_4
#define EEP_CS_GPIO_Port GPIOA
#define EEP_SCK_Pin GPIO_PIN_5
#define EEP_SCK_GPIO_Port GPIOA
#define EEP_MISO_Pin GPIO_PIN_6
#define EEP_MISO_GPIO_Port GPIOA
#define EEP_MOSI_Pin GPIO_PIN_7
#define EEP_MOSI_GPIO_Port GPIOA
#define Valve_cool_water_Pin GPIO_PIN_7
#define Valve_cool_water_GPIO_Port GPIOE
#define Valve_hot_water_Pin GPIO_PIN_8
#define Valve_hot_water_GPIO_Port GPIOE
#define Valve_pena_Pin GPIO_PIN_9
#define Valve_pena_GPIO_Port GPIOE
#define Valve_air_Pin GPIO_PIN_10
#define Valve_air_GPIO_Port GPIOE
#define Valve_nasekom_Pin GPIO_PIN_11
#define Valve_nasekom_GPIO_Port GPIOE
#define Valve_osmos_Pin GPIO_PIN_12
#define Valve_osmos_GPIO_Port GPIOE
#define Valve_sbros_Pin GPIO_PIN_13
#define Valve_sbros_GPIO_Port GPIOE
#define Dozator_vosk_Pin GPIO_PIN_14
#define Dozator_vosk_GPIO_Port GPIOE
#define Dozator_pena_Pin GPIO_PIN_15
#define Dozator_pena_GPIO_Port GPIOE
#define Sensor_potok_Pin GPIO_PIN_10
#define Sensor_potok_GPIO_Port GPIOB
#define Motor_run_left_Pin GPIO_PIN_10
#define Motor_run_left_GPIO_Port GPIOD
#define Motor_run_right_Pin GPIO_PIN_11
#define Motor_run_right_GPIO_Port GPIOD
#define M_PWM_Pin GPIO_PIN_12
#define M_PWM_GPIO_Port GPIOD
#define SDIO_CD_Pin GPIO_PIN_7
#define SDIO_CD_GPIO_Port GPIOC
#define RS485_1_TX_Pin GPIO_PIN_9
#define RS485_1_TX_GPIO_Port GPIOA
#define RS485_1_RX_Pin GPIO_PIN_10
#define RS485_1_RX_GPIO_Port GPIOA
#define CS_rs485_1_Pin GPIO_PIN_11
#define CS_rs485_1_GPIO_Port GPIOA
#define RS485_2_TX_Pin GPIO_PIN_5
#define RS485_2_TX_GPIO_Port GPIOD
#define RS485_2_RX_Pin GPIO_PIN_6
#define RS485_2_RX_GPIO_Port GPIOD
#define CS_rs485_2_Pin GPIO_PIN_7
#define CS_rs485_2_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
