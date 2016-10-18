/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "workfunction.h"
#include "crc.h"
#include "kompobmen.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;

/* USER CODE BEGIN Variables */
extern uint8_t addrMaster;
extern uint8_t addrSlave;

volatile uint8_t rxDataCount1 = 0;
volatile uint8_t rxDataCount2 = 0;
uint8_t rxDataUsart2[255];
uint8_t txDataUsart2[255];
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void MainThred(void const * argument);
void KompObmenThred(void const * argument);
void WorkFuncThred(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
void ClearArray(UART_HandleTypeDef *huart, uint8_t *data, uint8_t len);
uint8_t CompareDate(uint8_t *Buf);//функция сравнения CRC
/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void)
{
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, MainThred, osPriorityNormal, 0, 1280);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, KompObmenThred, osPriorityIdle, 0, 1280);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, WorkFuncThred, osPriorityIdle, 0, 1280);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* MainThred function */
void MainThred(void const * argument)
{

  /* USER CODE BEGIN MainThred */
  /* Infinite loop */
  while(1)
  {
    osDelay(1);
  }
  /* USER CODE END MainThred */
}

/* KompObmenThred function */
void KompObmenThred(void const * argument)
{
  /* USER CODE BEGIN KompObmenThred */
    HAL_UART_Receive_IT(&huart2, rxDataUsart2, 100);
  /* Infinite loop */
  while(1)
  {
      if((rxDataUsart2[1] != 0) && 
      (rxDataUsart2[0] == addrSlave) && 
      (rxDataCount2 == rxDataUsart2[3]))
      {
          if(CompareDate(rxDataUsart2) == 1)
          {
              switch(rxDataUsart2[2])
              {
                  case TEST:    //тестовый запрос проверки связи
                        ValveAir(GPIO_PIN_SET);
                        CmdTest();
                        ValveAir(GPIO_PIN_RESET);
                      break;
                  case GET_ID_DEVICE: //запрос UID устройства
                        CmdGetUidDevice();
                      break;
                  case GET_VERSION_SOFT: //запрос версии ПО
                      CmdGetVersionSoft();
                      break;
                  case TEST_MEHANIZM: //включение исполнительных механизмов
                      TestMehanizm();
                      break;
              }
              ClearArray(&huart2, rxDataUsart2, 10);
          }
      }
    osDelay(1);
  }
  /* USER CODE END KompObmenThred */
}

/* WorkFuncThred function */
void WorkFuncThred(void const * argument)
{
  /* USER CODE BEGIN WorkFuncThred */
  /* Infinite loop */
  while(1)
  {
    osDelay(1);
  }
  /* USER CODE END WorkFuncThred */
}

/* USER CODE BEGIN Application */
/*########################################*/
/*########################################*/
/*########################################*/
/*########################################*/
/*########################################*/
/*########################################*/
/*########################################*/
void ClearArray(UART_HandleTypeDef *huart, uint8_t *data, uint8_t len)
{
    uint16_t i;
    
    for(i = 0;i < len;i++)
    {
        data[i] = 0x00;
    }
    
    rxDataCount2 = 0;
    huart->RxXferCount = 0xff;
    huart->RxXferSize = 0xff;
    huart->pRxBuffPtr = data;
}
/*########################################*/
uint8_t CompareDate(uint8_t *Buf)//функция сравнения CRC
{
	uint32_t Compare7 = 0;
	uint8_t i = 0;
	uint8_t a[2];
	uint8_t b[2];
	uint8_t Dostup = 0;
	if (Buf[3] > 4)
	{
		Compare7 = crc16(Buf, Buf[3] - 2);
        //Compare7 = GetCRC16(rxDataUsart2, rxDataUsart2[3]);
        //Compare7 = crc_16_rec(rxDataUsart2, rxDataUsart2[3]);

		a[0] = Compare7 >> 8;
		a[1] = Compare7;

		i = Buf[3];
		i = i - 1;
		b[1] = Buf[i];
		i = i - 1;
		b[0] = Buf[i];

		if ((a[0] == b[0]) && (a[1] == b[1]))//сравниваем CRC16 преобразованный и полученые результаты
		{
			Dostup = 1;  //если все сошлось рарешаем доступ на обработку полученых данных
		}
	}
	return Dostup;
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
