/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
<<<<<<< HEAD
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "DHT11.h"
#include "OLED.h"
#include "LED.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
=======
#include "DHT11.h"
#include "OLED.h"
#include "LED.h"
#include "stdio.h"
#include "usart.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

>>>>>>> 1843ad9ec5044a61c52c5d0eedf03f57c55b3d7a
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern uint8_t rec_data[4]; 
extern uint8_t dht11_error_flag;
void SystemClock_Config(void);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
<<<<<<< HEAD
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
typedef struct
{
  uint8_t humi_h;
  uint8_t humi_l;
  uint8_t temp_h;
  uint8_t temp_l;
  uint8_t valid;
} dht11_data_t;

static osMessageQueueId_t g_dht11_queue = NULL;

static const osThreadAttr_t dht11OledTask_attributes = {
  .name = "DHT11_OLED",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

static const osThreadAttr_t hc05TxTask_attributes = {
  .name = "HC05_TX",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
=======

/* USER CODE BEGIN PV */
>>>>>>> 1843ad9ec5044a61c52c5d0eedf03f57c55b3d7a

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
<<<<<<< HEAD
void StartDefaultTask(void *argument);

/* USER CODE BEGIN PFP */
static void Dht11OledTask(void *argument);
static void Hc05TxTask(void *argument);
=======
/* USER CODE BEGIN PFP */

>>>>>>> 1843ad9ec5044a61c52c5d0eedf03f57c55b3d7a
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART1_UART_Init(); // 初始化串口，用于HC-05通信
  /* USER CODE BEGIN 2 */
// --- 硬件初始化 ---
    OLED_Init();        // OLED 初始化
    OLED_Clear();       // 先清空屏幕，防止有杂点
    // --- 界面 UI 初始化 (画一次就行，不用一直刷) ---
    // 在第0行显示 "Temp:"
    OLED_ShowString(2, 2, "Temp:"); 
    // 在第2行显示 "Humi:"
    OLED_ShowString(4, 2, "Humi:"); 
    // LED 用于指示程序是否在循环中运行
    LED_Init();
  /* USER CODE END 2 */

<<<<<<< HEAD
  /* Init scheduler */
  osKernelInitialize();

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
  g_dht11_queue = osMessageQueueNew(1, sizeof(dht11_data_t), NULL);
  if (g_dht11_queue == NULL)
  {
    OLED_ShowString(2, 70, "RTOS Err!   ");
    OLED_ShowString(4, 70, "Queue Fail ");
    while (1) { }
  }
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  if (osThreadNew(Dht11OledTask, NULL, &dht11OledTask_attributes) == NULL)
  {
    OLED_ShowString(2, 70, "RTOS Err!   ");
    OLED_ShowString(4, 70, "Task1 Fail ");
    while (1) { }
  }

  if (osThreadNew(Hc05TxTask, NULL, &hc05TxTask_attributes) == NULL)
  {
    OLED_ShowString(2, 70, "RTOS Err!   ");
    OLED_ShowString(4, 70, "Task2 Fail ");
    while (1) { }
  }
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

=======
>>>>>>> 1843ad9ec5044a61c52c5d0eedf03f57c55b3d7a
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
<<<<<<< HEAD

=======
    // LED 翻转：确认主循环在跑（如果 LED 不闪，说明程序卡住了）
    LED1_Turn();

    DHT11_RECdata(); // 获取 DHT11 数据
    if(dht11_error_flag == 0)
    {
      // 获取数据失败，显示错误提示
      OLED_ShowString(2, 70, "DHT11 Error!   ");
    }
    else
    {
      // 获取数据成功，显示温湿度
      char temp_str[16], humi_str[16];
      sprintf(temp_str, "%d.%d C", rec_data[2], rec_data[3]);
      sprintf(humi_str, "%d.%d %%", rec_data[0], rec_data[1]);
      OLED_ShowString(2, 70, temp_str); // 显示温度
      OLED_ShowString(4, 70, humi_str); // 显示湿度
      
      // 通过串口发送到HC-05
      char buf[50];
      sprintf(buf, "T:%d.%d H:%d.%d\r\n", rec_data[2], rec_data[3], rec_data[0], rec_data[1]);
      send_string(buf);
    }
    HAL_Delay(3000); // 延时3秒，避免读取过于频繁，提高 DHT11 稳定性
>>>>>>> 1843ad9ec5044a61c52c5d0eedf03f57c55b3d7a
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
<<<<<<< HEAD
static void Dht11OledTask(void *argument)
{
  (void)argument;

  if (g_dht11_queue == NULL)
  {
    OLED_ShowString(2, 70, "RTOS Err!   ");
    OLED_ShowString(4, 70, "Queue Null ");
    osThreadExit();
  }

  uint8_t beat = 0;
  for (;;)
  {
    // 任务心跳指示，确认任务确实在运行（显示在第一行最后一格）
    OLED_ShowChar(1, 16, (beat++ & 1) ? '|' : '-');

    // LED 翻转：确认任务在跑
    LED1_Turn();

    // DHT11 对时序很敏感，读取期间避免任务切换，但不要关闭中断
    vTaskSuspendAll();
    DHT11_RECdata(); // 获取 DHT11 数据
    xTaskResumeAll();

    dht11_data_t data;
    data.humi_h = rec_data[0];
    data.humi_l = rec_data[1];
    data.temp_h = rec_data[2];
    data.temp_l = rec_data[3];
    data.valid = dht11_error_flag;

    if (data.valid == 0)
    {
      // 获取数据失败，显示错误提示并清理湿度残留显示
      OLED_ShowString(2, 8, "DHT11Err");
      OLED_ShowString(4, 8, "DHT11Err");
    }
    else
    {
      // 获取数据成功，显示温湿度（固定宽度，覆盖旧内容）
      char temp_str[16], humi_str[16];
      snprintf(temp_str, sizeof(temp_str), "%2d.%1d C ", data.temp_h, data.temp_l);
      snprintf(humi_str, sizeof(humi_str), "%2d.%1d %% ", data.humi_h, data.humi_l);
      OLED_ShowString(2, 8, temp_str); // 显示温度
      OLED_ShowString(4, 8, humi_str); // 显示湿度
    }

    // 将最新数据写入队列（队列满则丢弃旧数据）
    if (g_dht11_queue != NULL)
    {
      osStatus_t st = osMessageQueuePut(g_dht11_queue, &data, 0, 0);
      if (st == osErrorResource)
      {
        dht11_data_t drop;
        (void)osMessageQueueGet(g_dht11_queue, &drop, NULL, 0);
        (void)osMessageQueuePut(g_dht11_queue, &data, 0, 0);
      }
    }

    osDelay(2000); // 2 秒刷新一次
  }
}

static void Hc05TxTask(void *argument)
{
  (void)argument;

  dht11_data_t data;
  send_string("HC05 Task Start\r\n");
  for (;;)
  {
    if (g_dht11_queue == NULL)
    {
      osDelay(100);
      continue;
    }

    if (osMessageQueueGet(g_dht11_queue, &data, NULL, 2000) == osOK)
    {
      if (data.valid == 0)
      {
        send_string("DHT11 Error\r\n");
      }
      else
      {
        char buf[50];
        sprintf(buf, "T:%d.%d H:%d.%d\r\n", data.temp_h, data.temp_l, data.humi_h, data.humi_l);
        send_string(buf);
      }
    }
    else
    {
      send_string("NO DATA\r\n");
    }
  }
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  // 默认任务仅用于确认 RTOS 运行，之后退出，避免抢占用户任务
  osThreadExit();
  /* USER CODE END 5 */
}

=======

/* USER CODE END 4 */

>>>>>>> 1843ad9ec5044a61c52c5d0eedf03f57c55b3d7a
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  // 调试输出：汇编死循环，便于硬件调试器断点
  printf("[ERROR] Error_Handler called!\r\n");
  __disable_irq();
  while (1)
  {
    // 如果有LED，可以在这里闪烁LED表示出错
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
