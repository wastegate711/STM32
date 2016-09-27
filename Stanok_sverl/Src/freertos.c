/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "stm32f0xx_hal.h"
#include "user.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;

/* USER CODE BEGIN Variables */
UserFlag Flag;

uint16_t delayTormozRunRight = 2000;
uint16_t delayTormozRunLeft = 2000;
uint16_t delayTormogenie = 2000;
uint16_t delayKachanie = 500;
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void MainThred(void const * argument);
void KompObmen(void const * argument);
void ReadButtonThred(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
void FunctionSOG(GPIO_PinState pinState);
void FunctionRunRight(GPIO_PinState pinState);
void FunctionRunLeft(GPIO_PinState pinState);
void FunctionTormogenie(GPIO_PinState pinState);
void InitUserStruct(void);
/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
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
  osThreadDef(defaultTask, MainThred, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, KompObmen, osPriorityIdle, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, ReadButtonThred, osPriorityIdle, 0, 128);
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
	InitUserStruct();//
  /* Infinite loop */
  while(1)
  {
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)//сож
	  {
		  osDelay(30);
		  FunctionSOG(GPIO_PIN_SET);
	  }
	  else
	  {
		  FunctionSOG(GPIO_PIN_RESET);
	  }
/////////////////////////////
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)//быстрый реверс
	  {
		  osDelay(30);
		  if(Flag.buttonRight == GPIO_PIN_SET)//правое вращение
		  {
			  if(Flag.runLeftMotor == GPIO_PIN_SET)
			  {
				  FunctionRunLeft(GPIO_PIN_RESET);
				  FunctionTormogenie(GPIO_PIN_SET);
				  osDelay(delayTormozRunRight);
				  FunctionTormogenie(GPIO_PIN_RESET);
				  osDelay(500);
				  FunctionRunRight(GPIO_PIN_SET);
			  }
			  else
			  {
				  FunctionRunRight(GPIO_PIN_SET);
			  }
		  }
		  ////////////////////////////////////
		  if(Flag.buttonLeft == GPIO_PIN_SET)//левое вращение
		  {
			  if(Flag.runRightMotor == GPIO_PIN_SET)
			  {
				  FunctionRunRight(GPIO_PIN_RESET);
				  FunctionTormogenie(GPIO_PIN_SET);
				  osDelay(delayTormozRunLeft);
				  FunctionTormogenie(GPIO_PIN_RESET);
				  osDelay(500);
				  FunctionRunLeft(GPIO_PIN_SET);
			  }
			  else
			  {
				  FunctionRunLeft(GPIO_PIN_SET);
			  }
		  }
	  }
	  else//быстрый реверс включен
	  {
		  if(Flag.buttonLeft == GPIO_PIN_SET)//реверс левого вращения
		  {
			  if(Flag.buttonLeft == GPIO_PIN_SET)
			  {
				  FunctionRunLeft(GPIO_PIN_RESET);
				  FunctionTormogenie(GPIO_PIN_SET);
				  osDelay(delayTormozRunLeft);
				  FunctionTormogenie(GPIO_PIN_RESET);
				  osDelay(500);
				  FunctionRunRight(GPIO_PIN_SET);
			  }
			  else
			  {
				  FunctionRunRight(GPIO_PIN_SET);
			  }
		  }
		  if(Flag.buttonRight == GPIO_PIN_SET)
		  {
			  if(Flag.buttonRight == GPIO_PIN_SET)
			  {
				  FunctionRunRight(GPIO_PIN_RESET);
				  FunctionTormogenie(GPIO_PIN_SET);
				  osDelay(delayTormozRunRight);
				  FunctionTormogenie(GPIO_PIN_RESET);
				  FunctionRunLeft(GPIO_PIN_SET);
			  }
			  else
			  {
				  FunctionRunLeft(GPIO_PIN_SET);
			  }
		  }
	  }
//////////////////////////////////////////
		if(Flag.buttonAvtoRevers == GPIO_PIN_SET)//автоматический реверс
		{
			if(Flag.runLeftMotor == GPIO_PIN_SET)
			{
				FunctionRunLeft(GPIO_PIN_RESET);
				osDelay(500);
				FunctionRunRight(GPIO_PIN_SET);
			}
			else if(Flag.runRightMotor == GPIO_PIN_SET)
			{
				FunctionRunRight(GPIO_PIN_RESET);
				osDelay(500);
				FunctionRunLeft(GPIO_PIN_SET);
			}
		}
////////////////////////////////
		if(Flag.buttonKachanie == GPIO_PIN_SET)//кнопка качание
		{
			Flag.kachanie = GPIO_PIN_SET;
			while(Flag.kachanie == GPIO_PIN_SET)
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
				osDelay(delayKachanie);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
				osDelay(200);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
				osDelay(delayKachanie);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
				osDelay(200);

				if(Flag.buttonLeft == GPIO_PIN_SET)//если нажата одна из кнопок выходим из цикла
				{
					Flag.buttonKachanie = GPIO_PIN_RESET;
				}
				if(Flag.buttonRight == GPIO_PIN_SET)
				{
					Flag.buttonKachanie = GPIO_PIN_RESET;
				}
			}
		}
////////////////////////////////
		if(Flag.buttonStop == GPIO_PIN_SET)//кнопка стоп
		{
			if(Flag.runLeftMotor == GPIO_PIN_SET)
			{
				FunctionRunLeft(GPIO_PIN_RESET);
			}
			else if(Flag.runRightMotor == GPIO_PIN_SET)
			{
				FunctionRunRight(GPIO_PIN_RESET);
			}
			else if(Flag.kachanie == GPIO_PIN_SET)
			{
				Flag.kachanie = GPIO_PIN_RESET;
			}
			FunctionTormogenie(GPIO_PIN_SET);
			osDelay(delayTormogenie);
			FunctionTormogenie(GPIO_PIN_RESET);
		}
    osDelay(1);
  }
  /* USER CODE END MainThred */
}

/* KompObmen function */
void KompObmen(void const * argument)
{
  /* USER CODE BEGIN KompObmen */
  /* Infinite loop */
  while(1)
  {
    osDelay(1);
  }
  /* USER CODE END KompObmen */
}

/* ReadButtonThred function */
void ReadButtonThred(void const * argument)
{
  /* USER CODE BEGIN ReadButtonThred */
  /* Infinite loop */
  while(1)
  {
	  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_RESET)//кнопка правое вращение
	  {
		  osDelay(50);
		  Flag.buttonRight = GPIO_PIN_SET;
	  }
	  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_RESET)//левое вращение
	  {
		  osDelay(50);
		  Flag.buttonLeft = GPIO_PIN_SET;
	  }
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_RESET)//кнопка автореверс
	  {
		  osDelay(50);
		  Flag.buttonAvtoRevers = GPIO_PIN_SET;
	  }
	  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4) == GPIO_PIN_RESET)//кнопка качание
	  {
		  osDelay(50);
		  Flag.buttonKachanie = GPIO_PIN_SET;
	  }
	  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == GPIO_PIN_RESET)//кнопка стоп
	  {
		  osDelay(50);
		  Flag.buttonStop = GPIO_PIN_SET;
	  }
    osDelay(1);
  }
  /* USER CODE END ReadButtonThred */
}

/* USER CODE BEGIN Application */
void FunctionSOG(GPIO_PinState pinstate)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, pinstate);
}
/////////////////////////////////////////
void FunctionRunRight(GPIO_PinState pinState)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, pinState);
	Flag.runRightMotor = pinState;
}
/////////////////////////////////////////
void FunctionRunLeft(GPIO_PinState pinState)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, pinState);
	Flag.runLeftMotor = pinState;
}
/////////////////////////////////////////
void FunctionTormogenie(GPIO_PinState pinState)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, pinState);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, pinState);
}
/////////////////////////////////////////
void InitUserStruct(void)
{
	Flag.runLeftMotor = 0;
	Flag.runRightMotor = 0;
	Flag.kachanie = 0;
	Flag.buttonSog = 0;
	Flag.buttonLeft = 0;
	Flag.buttonRight = 0;
	Flag.buttonStop = 0;
	Flag.buttonAvtoRevers = 0;
	Flag.buttonFastRevers = 0;
	Flag.buttonKachanie = 0;
}
/////////////////////////////////////////
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
