/**
  ******************************************************************************
  * File Name          : Control_usart.c
  * Description        : This file provides code for the control
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef UART_GLOBALS_VARIABLE_DEFINED
#define UART_GLOBALS_VARIABLE_DEFINED
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "Control_usart.h"
#include "stdio.h"
#include "string.h"


/* USER CODE BEGIN Preivate defines */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

#if (USE_HAL_UART4 == 1U)
  #define UART4_RxXferSize    ((uint16_t)1000)
  uint8_t  UART4_RxBuff[UART4_RxXferSize];
#endif

#if (USE_HAL_UART5 == 1U)
  #define UART5_RxXferSize    ((uint16_t)1000)
  uint8_t  UART5_RxBuff[UART5_RxXferSize];
#endif
/* USER CODE END Preivate defines */


/* USER CODE BEGIN 0 */
static const UART_HandleTypeDef* const UART_Array[] = {
        #if (USE_HAL_UART4 == 1U)
        &huart4，
        #endif

        #if (USE_HAL_UART5 == 1U)
        &huart5,
        #endif

        NULL
}
/* USER CODE END 0 */


/* USER CODE END 1 */
void MX_ALL_OF_UART_Init(void)
{
    const UART_HandleTypeDef* pUART_Array = UART_Array;

    for (; pUART_Array != NULL; pUART_Array++)
    {
        MMX_UART_Single_Config(pUART_Array);
    }  
}

void MX_SINGLE_OF_UART_Init(UART_HandleTypeDef* huart)
{
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    #if (USE_HAL_UART4 == 1U)
        if(UART4 == huart.Instance)
        {
            huart.pRxBuffPtr   = UART4_RxBuff;
            huart.RxXferSize   = UART4_RxXferSize;
        }
    #elif (USE_HAL_UART5 == 1U)
        if(UART5 == huart.Instance)
        {
            huart.pRxBuffPtr   = UART5_RxBuff;
            huart.RxXferSize   = UART5_RxXferSize;
        }
    #endif

    if(HAL_UART_Init(huart) != HAL_OK)
    {
        Error_Handler();
    }
    else
    {
        __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
        HAL_UART_Receive_IT(huart, huart.pRxBuffPtr, huart.RxXferSize);
    }
    
}

void UARTReceive_IDLE(UART_HandleTypeDef *huart)
{
    /*
    uint16_t Rx_len = 0x00;
    #if (USE_HAL_UART4 == 1U)
        Rx_len = UART4_RxXferSize - huart->RxXferCount;
    #elif (USE_HAL_UART5 == 1U)
        Rx_len = UART5_RxXferSize - huart->RxXferCount;
    #endif
    */
    __HAL_UART_CLEAR_IDLEFLAG(huart);
    HAL_UART_AbortReceive_IT(huart);
    HAL_UART_Receive_IT(huart, huart->pRxBuffPtr, huart->RxXferSize);
}

void GetRxData(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    #if (USE_HAL_UART4 == 1U)
        if(UART4 == huart.Instance)
        {
            memcpy(pData, UART4_RxBuff, Size);
        }
    #elif (USE_HAL_UART5 == 1U)
        if(UART5 == huart.Instance)
        {
            memcpy(pData, UART5_RxBuff, Size);
        }
    #endif
}
/* USER CODE END 1 */


/* USER CODE BEGIN 2 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#if (USE_HAL_UART4 == 1U)
    if (huart == &huart4)
    {
    //HAL_UART_Transmit(&huart4,i,10,10);
    //HAL_UART_Receive_IT(&huart4,i,10);
    }
#endif

#if (USE_HAL_UART5 == 1U)
    if (huart == &huart5)
    {
    //HAL_UART_Transmit(&huart5,str,10,10);
    //HAL_UART_Receive_IT(&huart5,str,10);
    }
#endif
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
#if (USE_HAL_UART4 == 1U)
  if (huart == &huart4)
  {
    memset(UART4_RxBuff, 0, 1000);
    HAL_UART_Receive_IT(&huart4, UART4_RxBuff，1000);
  }
#endif

#if (USE_HAL_UART5 == 1U)
  if (huart == &huart5)
  {
    memset(UART5_RxBuff, 0, 1000);
    HAL_UART_Receive_IT(&huart5, UART4_RxBuff，1000);
  }
#endif
}
/* USER CODE END 2 */

/* USER CODE BEGIN 3 */
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(P_printf, &ch, 1, 10);
  return ch;
}

int _write(int file, char *ptr, int len)
{
    int DataIdx;

    for (DataIdx = 0; DataIdx < len; DataIdx++)
    {
        #ifdef __GNUC__
            __io_putchar(*ptr++);
        #else
            fputc(*ptr++);
        #endif
        
    }
    
    return len;
}
/* USER CODE END 3 */

void UART4_IRQHandler(void)
{
    /* USER CODE BEGIN UART4_IRQn 0 */
    #if (USE_HAL_UART4 == 1U)
    /* USER CODE END UART4_IRQn 0 */
        HAL_UART_IRQHandler(&huart4);
    /* USER CODE BEGIN UART4_IRQn 1 */
        if(__HAL_UART_GET_IT(&huart4,UART_IT_IDLE) != RESET)
        {
            UARTReceive_IDLE(&huart4);
        }
    #endif
    /* USER CODE END UART4_IRQn 1 */
}
void UART5_IRQHandler(void)
{
    /* USER CODE BEGIN UART5_IRQn 0 */
    #if (USE_HAL_UART5 == 1U)
    /* USER CODE END UART5_IRQn 0 */
        HAL_UART_IRQHandler(&huart5);
    /* USER CODE BEGIN UART5_IRQn 1 */
        if(__HAL_UART_GET_IT(&huart5,UART_IT_IDLE) != RESET)
        {
            UARTReceive_IDLE(&huart5);
        }
    #endif
    /* USER CODE END UART5_IRQn 1 */
}

#ifdef __cplusplus
}
#endif
#endif /* UART_GLOBALS_VARIABLE_DEFINED */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
