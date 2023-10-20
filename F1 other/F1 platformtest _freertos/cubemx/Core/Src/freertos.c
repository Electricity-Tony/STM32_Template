/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId BOARD_LEDTaskHandle;
osThreadId USER_LEDTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartBOARD_LED(void const * argument);
void StartUSER_LED(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
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

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of BOARD_LEDTask */
  osThreadDef(BOARD_LEDTask, StartBOARD_LED, osPriorityIdle, 0, 128);
  BOARD_LEDTaskHandle = osThreadCreate(osThread(BOARD_LEDTask), NULL);

  /* definition and creation of USER_LEDTask */
  osThreadDef(USER_LEDTask, StartUSER_LED, osPriorityIdle, 0, 128);
  USER_LEDTaskHandle = osThreadCreate(osThread(USER_LEDTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for (;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartBOARD_LED */
/**
 * @brief Function implementing the BOARD_LEDTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartBOARD_LED */
void StartBOARD_LED(void const * argument)
{
  /* USER CODE BEGIN StartBOARD_LED */
  /* Infinite loop */
  for (;;)
  {
    HAL_GPIO_WritePin(Board_Led_GPIO_Port, Board_Led_Pin, RESET);
    osDelay(1000);
    HAL_GPIO_WritePin(Board_Led_GPIO_Port, Board_Led_Pin, SET);
    osDelay(1000);
    osDelay(1);
  }
  /* USER CODE END StartBOARD_LED */
}

/* USER CODE BEGIN Header_StartUSER_LED */
/**
 * @brief Function implementing the USER_LEDTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartUSER_LED */
void StartUSER_LED(void const * argument)
{
  /* USER CODE BEGIN StartUSER_LED */
  /* Infinite loop */
  for (;;)
  {
    HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, RESET);
    osDelay(500);
    HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, SET);
    osDelay(500);
    osDelay(1);
  }
  /* USER CODE END StartUSER_LED */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

