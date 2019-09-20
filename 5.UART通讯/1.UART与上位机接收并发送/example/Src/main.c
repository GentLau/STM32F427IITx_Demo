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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void tim_delay_us(uint16_t us);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t aRxBuffer;			

uint8_t Uart1_RxBuff[256]="asdfjasljga";		

uint8_t Uart1_Rx_Cnt = 0;	

uint8_t	cAlmStr[] = "(256)\r\n";
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
  MX_TIM7_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim7);
	HAL_UART_Receive_IT(&huart4, (uint8_t *)&aRxBuffer, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_RESET);
					HAL_Delay(50);
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET);
					HAL_Delay(50);
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_3, GPIO_PIN_RESET);
					HAL_Delay(50);
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_4, GPIO_PIN_RESET);
					HAL_Delay(50);
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_5, GPIO_PIN_RESET);
					HAL_Delay(50);
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);
					HAL_Delay(50);
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_7, GPIO_PIN_RESET);
					HAL_Delay(50);
					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8, GPIO_PIN_RESET);
					HAL_Delay(50);
					HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_1);
					HAL_Delay(50);
					HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_2);
					HAL_Delay(50);
					HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_3);
					HAL_Delay(50);
					HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_4);
					HAL_Delay(50);
					HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_5);
					HAL_Delay(50);
					HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
					HAL_Delay(50);
					HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_7);
					HAL_Delay(50);
					HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_8);
					HAL_Delay(50);
		
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

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void tim_delay_us(uint16_t us)
{
//	HAL_TIM_Base_Start_IT(&htim7);
	__HAL_TIM_SetCounter(&htim7,5); 
	while(__HAL_TIM_GetCounter(&htim7) < 40*us+5);
//	HAL_TIM_Base_Stop_IT(&htim7);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{  
		if(Uart1_Rx_Cnt >= 255)  
		{		
			Uart1_Rx_Cnt = 0;		
			int i=0;for(;i<256;i++)Uart1_RxBuff[i]=0;		
			HAL_UART_Transmit(&huart4, (uint8_t *)&cAlmStr, sizeof(cAlmStr),0xFFFF);		
		}
		else	
		{		
			Uart1_RxBuff[Uart1_Rx_Cnt++] = aRxBuffer;   
			if(Uart1_RxBuff[Uart1_Rx_Cnt-1] == '!')
			{			
				#if 1
				HAL_UART_Transmit(&huart4, (uint8_t *)&Uart1_RxBuff, Uart1_Rx_Cnt,0xffffffff);	
				int i=0;for(;i<256;i++){Uart1_RxBuff[i]=0;}	
				#else
				HAL_UART_Transmit_IT(&huart4, (uint8_t *)&Uart1_RxBuff, Uart1_Rx_Cnt);			
				#endif				
				Uart1_Rx_Cnt = 0;			
			}	
		}		
		HAL_UART_Receive_IT(&huart4, (uint8_t *)&aRxBuffer, 1);   
}
 
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
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
