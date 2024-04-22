/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include <stdbool.h>
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rtwtypes.h"
#include "BrakeSimProto.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//GPIO_InitTypeDef GPIO_SensInitStruct;
//GPIO_SensInitStruct.Pin = GPIO_PIN_x;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

//Velocity Sensing variables
volatile float wheel_speed = 0;
volatile float vehicle_speed = 0;

float t1 = 0;
float t2 = 0;
float delta_t1 = 1;
float delta_t2 = 1;

float t1_ = 0;
float t2_ = 0;
float delta_t1_ = 1;
float delta_t2_ = 1;

float rad = 0.2618; //(Guess) This will, of course, need to get set later once measured

float IIR_alpha = 0.5; //Get rid of the reentrant IIR if you need more tuning

//Controller variables
float slp_rto = 0.2; //Shouldn't be used just yet, but will for differential braking
int controller_out = 0; //collection variable for the simulink model output

float tol = 2500.0;
float counter_check = 0;
bool brake_pressed = 0;
uint8_t mode = 0;
uint8_t count=0;
uint8_t count2 =0;
uint8_t count3 = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
//float IIR(float input, float old); //First-order IIR filter

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//First-Order IIR Filter (for velocity filtering)
float IIR(float input, float old) {
	return (1-IIR_alpha)*old + IIR_alpha*input;
}

//Timing Function
void delta(float* delta_t, float* t) {
//	HAL_Delay(1);
	float temp_t = HAL_GetTick();
	*delta_t = temp_t - *t;
	*t = temp_t;
}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	if (GPIO_Pin == GPIO_PIN_13){
		mode = mode + 1;
		count++ ;
	}
	if (mode > 3)
		mode = 0;


	if (GPIO_Pin == GPIO_PIN_4){
//		delta(&delta_t1,&t1);
//		wheel_speed = IIR(rad/delta_t1,wheel_speed);
//		wheel_speed = 30/delta_t1;

		float tmp = HAL_GetTick();
		delta_t1 = tmp - t1;
		t1 = tmp;
		wheel_speed = 30/delta_t1;
		count2++;
	}


	if (GPIO_Pin == GPIO_PIN_3){
//		delta(&delta_t2,&t2);
//		vehicle_speed = IIR(rad/delta_t2,vehicle_speed);
//		vehicle_speed = 30/delta_t2;
		float tmp1 = HAL_GetTick();
		delta_t2 = tmp1 - t2;
		t2 = tmp1;
		vehicle_speed = 30/delta_t2;
		count3++ ;
	}
//	HAL_Delay(10);
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

//This function should get called when delta_t becomes very large (give it a tolerance)
//something like 2-3 secs, also GetTick is updated every 1ms, so it should be in units of ms.
void ForceBrakesOn() {
	//make this function set the brake variable to high
	//so that the brakes will just be hard turned on
	controller_out = 1;
}

//int _write(int file, char *ptr, int len)
//{
//  /* Implement your write code here, this is used by puts and printf for example */
//  int i=0;
//  for(i=0 ; i<len ; i++)
//    ITM_SendChar((*ptr++));
//  return len;
//}



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

	//Put initializations here
	//Like turning on I/O, resetting any counters, etc

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  BrakeSimProto_initialize();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//	  brake_pressed = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3);
//	  rtU._w = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
//	  vehicle_speed = IIR(rad/delta_t2,vehicle_speed);
//	  rtU._w = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
//	  vehicle_speed = IIR(rad/delta_t2,vehicle_speed);
//	  rtU._w = wheel_speed;
//	  rtU._v = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
//	  rtU._v = vehicle_speed;
//	  rtU._v = 10;
//	  rtU._w = 10;





	  rtU._v = vehicle_speed;
	  rtU._w = wheel_speed;
	  rtU.DesiredRelativeSlip = 0.2;
	  BrakeSimProto_step();
//	  HAL_Delay(1000);
	  controller_out = rtY.MotorInput;

	  //Forcing the brakes on if no detection within 2.5 seconds (they should be hard on)
	  counter_check = HAL_GetTick();
//	  if ((counter_check - t1) >= tol || (counter_check - t2) >= tol)
//		  ForceBrakesOn();

	  //Still need to measure the magnets to get a good rad measurement

//	  rtU._w = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3);
//	  rtU._v = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2);

	  if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == GPIO_PIN_SET){
	  	  		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	  }
	  else{
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	  }


//	  if (mode == 0)
//	  		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
//	  	  else if (mode == 1)
//	  		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//	  	  else if (mode == 2)
//	  	  {
//	  		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//	  		  HAL_Delay(50);
//	  		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
//	  		  HAL_Delay(50);
//	  	  }
//	  	  else if (mode == 3)
//	  	  	  {
//	  	  		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
//	  	  		  HAL_Delay(200);
//	  	  		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
//	  	  		  HAL_Delay(200);
//	  	  	  }


	  if (controller_out == 1){
	  		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	  }
	  else{
	  		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
//	  		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	  }


//	  count++;
//	  printf("hello world count is %d \n", count);
//	  HAL_Delay(250);
	  //later, make the signals send into the generated matlab code
	  //(figure out the best way to implement the interfacing between here and MATLAB stuff)

	  //Make sure the output of the controller gets sent to the PWM generator

	  //PWM generator

	  //You also need to find some way to deal with the data acquisition you planned on.
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PC0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC1 PC2 PC3 PC4 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
int _write(int file, char *ptr, int len)
{
  /* Implement your write code here, this is used by puts and printf for example */
  int i=0;
  for(i=0 ; i<len ; i++)
    ITM_SendChar((*ptr++));
  return len;
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
