/**
  ******************************************************************************
  * File Name          : mxconstants.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MXCONSTANT_H
#define __MXCONSTANT_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define button_right_run_motor_Pin GPIO_PIN_0
#define button_right_run_motor_GPIO_Port GPIOC
#define button_left_run_motor_Pin GPIO_PIN_1
#define button_left_run_motor_GPIO_Port GPIOC
#define button_stop_Pin GPIO_PIN_2
#define button_stop_GPIO_Port GPIOC
#define button_SOG_Pin GPIO_PIN_0
#define button_SOG_GPIO_Port GPIOA
#define button_avto_revers_Pin GPIO_PIN_1
#define button_avto_revers_GPIO_Port GPIOA
#define button_fast_revers_Pin GPIO_PIN_2
#define button_fast_revers_GPIO_Port GPIOA
#define CS_SPI1_Pin GPIO_PIN_4
#define CS_SPI1_GPIO_Port GPIOA
#define button_kachanie_Pin GPIO_PIN_4
#define button_kachanie_GPIO_Port GPIOC
#define puskatel_1_Pin GPIO_PIN_5
#define puskatel_1_GPIO_Port GPIOC
#define puskatel_3_Pin GPIO_PIN_6
#define puskatel_3_GPIO_Port GPIOC
#define puskatel_4_Pin GPIO_PIN_7
#define puskatel_4_GPIO_Port GPIOC
#define puskatel_5_Pin GPIO_PIN_8
#define puskatel_5_GPIO_Port GPIOC
#define puskatel_2_Pin GPIO_PIN_9
#define puskatel_2_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MXCONSTANT_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
