/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
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
TIM_HandleTypeDef htim3;
DMA_HandleTypeDef hdma_tim3_ch1_trig;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

volatile uint32_t rgb     = 0xaaaaaa;

uint8_t red_color[] ={
			9, 9, 9, 9, 9, 9,  9, 9,
			9, 9, 9, 9, 9, 9, 17, 9,
			9, 9, 9, 9, 9, 9,  9, 9
};
uint8_t blue_color[] ={
			9, 9, 9, 9, 9, 9, 17, 9,
			9, 9, 9, 9, 9, 9,  9, 9,
			9, 9, 9, 9, 9, 9,  9, 9
};
#define DMA_LED_LEN 288
volatile uint8_t pwm_buffer[DMA_LED_LEN +2] = {
					9, 9, 9, 9,    9, 9, 17, 9,
					9, 9, 9, 9,    9, 9, 9, 9,
	 				9, 9, 9, 9,    9, 9, 9, 9,

					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 17, 9,

					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,


					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 17,

//					9, 9, 9, 9,    9, 9, 9, 9,
	 				9, 9, 9, 9,    9, 9, 9, 9,

					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,

					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,



					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,

					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,


					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,

					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,

					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,

					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,

				    };

volatile uint8_t pwm_buffer2[DMA_LED_LEN +2] = {
					9, 9, 9, 9,    17, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,
	 				9, 9, 9, 9,    9, 9, 9, 9,

					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    17, 9, 9, 9,

					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,


					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 17, 9, 9,

//					9, 9, 9, 9,    9, 9, 9, 9,
	 				9, 9, 9, 9,    9, 9, 9, 9,

					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,

					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,
					9, 9, 9, 9,    9, 9, 9, 9,



					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,

					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,


					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,

					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,

					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,

					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0, 0, 0, 0,

				    };

volatile uint8_t bit_id   = 0;
volatile uint16_t next_led = 0;
volatile uint32_t duty_cycle = 0;
volatile uint8_t led_pattern = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3) {

		if (((rgb >> bit_id) & 0x1)==0X01) {
			duty_cycle = 19;//86;
		}else{
			duty_cycle = 10;//33;
		}


		if (bit_id > 7) {
			duty_cycle = 0;
		//	GPIOC->ODR |= GPIO_PIN_8;
		}else {
			bit_id++;
		}


		//htim->Instance->CCR1 = duty_cycle;
		__HAL_TIM_CLEAR_FLAG(htim,TIM_FLAG_UPDATE);
	}
}


volatile uint8_t transfer_finished_ifg = 0;
volatile uint8_t buffer_change_ifg = 0;
//#if 1
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim){
#if 0
		if (htim->Instance == TIM3) {

//			HAL_DMA_Abort(htim->hdma[TIM_DMA_ID_CC1]);

/*fix posible bug with */

//__disable_irq();
/* might not be necessary */

 htim->hdma[TIM_DMA_ID_CC1]->XferCpltCallback = NULL;
 HAL_TIM_PWM_Stop_DMA( htim,TIM_CHANNEL_1)L
// __enable_irq();

		//	__HAL_DMA_DISABLE(htim->hdma[TIM_DMA_ID_CC1]);
			transfer_finished_ifg = 1;

		}
		// if ( pwm_buffer[0] == 8)
		// pwm_buffer[0] = 14;
	// else
		// pwm_buffer[0] = 8;
#endif
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
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	GPIOA->ODR &=~GPIO_PIN_6;
	GPIOC->ODR |= GPIO_PIN_8;
	HAL_Delay(1000);
	volatile uint32_t blink_counter = 0;
  HAL_TIM_Base_Start(&htim3);
//  HAL_DMA_RegisterCallback ( &htim3.dma[TIM_DMA_ID_CC1],HAL_DMA_XFER_CPLT_CB_ID, half_transfer_callback_dma);
  HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *)(&pwm_buffer[0]), DMA_LED_LEN);

volatile uint8_t color_swap = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	if (HAL_GetTick() > blink_counter) {
		blink_counter = HAL_GetTick()+ 500;
		GPIOC->ODR ^= GPIO_PIN_8;


		transfer_finished_ifg = 0;
		if (pwm_buffer[46] == 9){
			pwm_buffer[46] = 17;
			buffer_change_ifg = 0;
		}
		else{
			pwm_buffer[46] = 9;
		}

 		if (transfer_finished_ifg) {


			// HAL_DMA_Start(htim3.hdma[TIM_DMA_ID_CC1],
				// (uint32_t *)(&pwm_buffer[0]),
				// (uint32_t *)(&(htim3.Instance->CCR1)),DMA_LED_LEN);

		}
	}
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

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 30;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */
  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel4_5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LD4_Pin|LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

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
void assert_failed(char *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
