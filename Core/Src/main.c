/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

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
#define MAX_Receive_Num 10
uint8_t RxBuffer[MAX_Receive_Num];
uint8_t *expp1 = "������������������·���\r\n";
uint8_t *expp2 = "���յ�������Ϊ��";
uint8_t aRxBuffer;
uint8_t UART1_RX_Cnt;
uint8_t Uart1_Rx_Cnt;
uint8_t UART1_RX_Sta;
uint8_t pwm_compare = 5;

//�ض���
int fgetc(FILE *f)
{
    uint8_t ch = 0;
    HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
    return ch;
}
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
    return ch;
}

//�ⲿ�жϻص�����

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == KEY2_Pin)
    {
        if(pwm_compare == 25)
            pwm_compare = 5;
        else
            pwm_compare += 5;
    }
    else
    {
        if(pwm_compare == 0)
            pwm_compare = 25;
        else
            pwm_compare -= 5;
    }
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, pwm_compare);
    printf("��ǰռ�ձ�Ϊ��%d\r\n", pwm_compare);

}
//����1�ص�����
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	UNUSED(huart);
//	if(huart==(&huart1))
//	{
//////		if(UART1_RX_Sta==0)//����δ���
////		{
//			if(UART1_RX_Cnt>=MAX_Receive_Num-1)//�������
//			{
//				UART1_RX_Cnt=0;
//				memset(RxBuffer,0x00,sizeof(RxBuffer));
//				HAL_UART_Transmit(&huart1,(uint8_t *)expp1,strlen(expp1),0xffff);
//				while(HAL_UART_GetState(&huart1)==HAL_UART_STATE_BUSY_TX);
//			}
//			else//��������
//			{
//				RxBuffer[UART1_RX_Cnt++]=aRxBuffer;
//				if((RxBuffer[UART1_RX_Cnt-1]==0x0a)&&(RxBuffer[UART1_RX_Cnt-2]==0x0d))//���յ�0x0a��0x0d
//				{
////					UART1_RX_Sta=1;
//					HAL_UART_Transmit(&huart1,(uint8_t *)expp2,strlen(expp2),0xffff);
//					while(HAL_UART_GetState(&huart1)==HAL_UART_STATE_BUSY_TX);
//					HAL_UART_Transmit(&huart1,(uint8_t *)RxBuffer,UART1_RX_Cnt,0xffff);
//					while(HAL_UART_GetState(&huart1)==HAL_UART_STATE_BUSY_TX);
//					UART1_RX_Cnt=0;
////					UART1_RX_Sta=0;
//					memset(RxBuffer,0x00,sizeof(RxBuffer));	//�������
//				}
//			}
////		}
////		else//�������
////		{
////			HAL_UART_Transmit(&huart1,(uint8_t *)RxBuffer,UART1_RX_Cnt,0xffff);
////			while(HAL_UART_GetState(&huart1)==HAL_UART_STATE_BUSY_TX);
////			UART1_RX_Cnt=0;
////			UART1_RX_Sta=0;
////			memset(RxBuffer,0x00,sizeof(RxBuffer));	//�������
////		}
//	}
//	HAL_UART_Receive_IT(&huart1,(uint8_t *)&aRxBuffer,1);
//}



//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	UNUSED(huart);
//	if(huart==(&huart1))//�ж����ĸ�����
//	{
//		if(UART1_RX_Sta==0)//����δ���
//		{
//			if(UART1_RX_Cnt>=MAX_Receive_Num-1)//�������
//			{
//				UART1_RX_Cnt=0;
//				memset(RxBuffer,0x00,sizeof(RxBuffer));
//				HAL_UART_Transmit(&huart1,(uint8_t *)expp1,strlen((char *)expp1),0xffff);
//				while(HAL_UART_GetState(&huart1)==HAL_UART_STATE_BUSY_TX);
//			}
//			else//��������
//			{
//				RxBuffer[UART1_RX_Cnt++]=aRxBuffer;
//				if((RxBuffer[UART1_RX_Cnt-1]==0x0a)&&(RxBuffer[UART1_RX_Cnt-2]==0x0d))//���յ�0x0a��0x0d
//				{
//					UART1_RX_Sta=1;
//				}
//			}
//		}
////		else//�������
////		{
////			HAL_UART_Transmit(&huart1,(uint8_t *)expp2,strlen((char *)expp2),0xffff);
////			while(HAL_UART_GetState(&huart1)==HAL_UART_STATE_BUSY_TX);
////			HAL_UART_Transmit(&huart1,(uint8_t *)RxBuffer,UART1_RX_Cnt,0xffff);
////			while(HAL_UART_GetState(&huart1)==HAL_UART_STATE_BUSY_TX);
////			UART1_RX_Cnt=0;
////			UART1_RX_Sta=0;
////			memset(RxBuffer,0x00,sizeof(RxBuffer));	//�������
////		}
//	HAL_UART_Receive_IT(&huart1,(uint8_t *)&aRxBuffer,1);//���������ж�
//	}
//}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    UNUSED(huart);
    if(huart == (&huart1)) //�ж����ĸ�����
    {
        if(UART1_RX_Sta == 0) //����δ���
        {
            if(UART1_RX_Cnt >= MAX_Receive_Num - 1) //�������
            {
                UART1_RX_Cnt = 0;
                memset(RxBuffer, 0x00, sizeof(RxBuffer));
                HAL_UART_Transmit(&huart1, (uint8_t *)expp1, strlen((char *)expp1), 0xffff);
                while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX); //�ȴ��������
            }
            else//��������
            {
                RxBuffer[UART1_RX_Cnt++] = aRxBuffer; //��Ž����ַ�
                if((RxBuffer[UART1_RX_Cnt - 1] == 0x0a) && (RxBuffer[UART1_RX_Cnt - 2] == 0x0d)) //���յ�0x0a��0x0d
                {
                    UART1_RX_Sta = 1;
                }
            }
        }
        HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1); //���������ж�
    }
}


//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(huart);
//  /* NOTE: This function Should not be modified, when the callback is needed,
//           the HAL_UART_TxCpltCallback could be implemented in the user file
//   */
//	if(huart==(&huart1))
//	{
//
//	if(Uart1_Rx_Cnt >= 10)  //����ж�
//	{
//		Uart1_Rx_Cnt = 0;
//		memset(RxBuffer,0x00,sizeof(RxBuffer));
//		HAL_UART_Transmit(&huart1, (uint8_t *)"�������\r\n", 10,0xFFFF);
//		while(HAL_UART_GetState(&huart1)==HAL_UART_STATE_BUSY_TX);
//
//	}
//	else
//	{
//		RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;   //��������ת��
//
//		if((RxBuffer[Uart1_Rx_Cnt-1] == 0x0A)&&(RxBuffer[Uart1_Rx_Cnt-2] == 0x0D)) //�жϽ���λ
//		{
//			HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer, Uart1_Rx_Cnt,0xFFFF); //���յ�����Ϣ���ͳ�ȥ
//            while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//���UART���ͽ���
//			Uart1_Rx_Cnt = 0;
//			memset(RxBuffer,0x00,sizeof(RxBuffer)); //�������
//		}
//	}
//
//	HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);   //�ٿ��������ж�
//	}
//}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
/***********************************************************
*@fuction	:main
*@brief		:
*@param		:--
*@return	:void
*@author	:--
*@date		:2022-10-10
***********************************************************/

int main(void)
{
    /* USER CODE BEGIN 1 */
    uint16_t i;
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
    MX_ADC1_Init();
    MX_TIM2_Init();
    MX_USART1_UART_Init();
    /* USER CODE BEGIN 2 */
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
    printf("system is started\r\n");
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while(1)
    {
        HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
        HAL_Delay(500);
        if(UART1_RX_Sta == 1) //�������
        {
            HAL_UART_Transmit(&huart1, (uint8_t *)expp2, strlen((char *)expp2), 0xffff);
            while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);
            HAL_UART_Transmit(&huart1, (uint8_t *)RxBuffer, UART1_RX_Cnt, 0xffff);
            while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);
            UART1_RX_Cnt = 0;
            UART1_RX_Sta = 0;
            memset(RxBuffer, 0x00, sizeof(RxBuffer));	//�������
        }

        //	if(UART1_RX_Sta)
        //	{
        //		i=(uint16_t)atoi((char *)RxBuffer);
        //		memset(RxBuffer,0,strlen((char *)RxBuffer));
        //		__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,i);
        //		UART1_RX_Cnt=0;
        //		UART1_RX_Sta=0;
        //		printf("��ǰռ�ձ�Ϊ��%d\r\n",i);
        //	}
        //	printf("system is ongoing\r\n");
        HAL_Delay(500);

        /* USER CODE END WHILE */

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

    /** Configure the main internal regulator output voltage
    */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 168;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }
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