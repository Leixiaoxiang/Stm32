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

#if (USE_HAL_UART1 == 1U)
  #define UART1_RxXferSize    ((uint16_t)1000)
  uint8_t  UART1_RxBuff[UART1_RxXferSize];
#endif

#if (USE_HAL_UART2 == 1U)
  #define UART2_RxXferSize    ((uint16_t)1000)
  uint8_t  UART2_RxBuff[UART2_RxXferSize];
#endif

#if (USE_HAL_UART3 == 1U)
  #define UART3_RxXferSize    ((uint16_t)1000)
  uint8_t  UART3_RxBuff[UART3_RxXferSize];
#endif
/* USER CODE END Preivate defines */


/* USER CODE BEGIN 0 */
static UART_HandleTypeDef* UART_Array[] = {
        #if (USE_HAL_UART4 == 1U)
            &huart4,
        #endif

        #if (USE_HAL_UART5 == 1U)
            &huart5,
        #endif

        #if (USE_HAL_UART1 == 1U)
            &huart1,
        #endif

        #if (USE_HAL_UART2 == 1U)
            &huart2,
        #endif

        #if (USE_HAL_UART3 == 1U)
            &huart3,
        #endif

        NULL
};
/* USER CODE END 0 */


/* USER CODE END 1 */
void MX_ALL_OF_UART_Init(void)
{
    UART_HandleTypeDef** pUART_Array = UART_Array;

    for (; pUART_Array != NULL; pUART_Array++)
    {
        MX_SINGLE_OF_UART_Init(*pUART_Array);
    }  
}

void MX_SINGLE_OF_UART_Init(UART_HandleTypeDef* huart)
{
    huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart->Init.OverSampling = UART_OVERSAMPLING_16;
    #if (USE_HAL_UART4 == 1U)
        if(UART4 == huart->Instance)
        {
            huart->pRxBuffPtr   = UART4_RxBuff;
            huart->RxXferSize   = UART4_RxXferSize;
        }
    #elif (USE_HAL_UART5 == 1U)
        if(UART5 == huart->Instance)
        {
            huart->pRxBuffPtr   = UART5_RxBuff;
            huart->RxXferSize   = UART5_RxXferSize;
        }
    #elif (USE_HAL_UART1 == 1U)
        if(UART1 == huart->Instance)
        {
            huart->pRxBuffPtr   = UART1_RxBuff;
            huart->RxXferSize   = UART1_RxXferSize;
        }
    #elif (USE_HAL_UART2 == 1U)
        if(UART2 == huart->Instance)
        {
            huart->pRxBuffPtr   = UART2_RxBuff;
            huart->RxXferSize   = UART2_RxXferSize;
        }
    #elif (USE_HAL_UART3 == 1U)
        if(UART3 == huart->Instance)
        {
            huart->pRxBuffPtr   = UART3_RxBuff;
            huart->RxXferSize   = UART3_RxXferSize;
        }
    #endif

    if(HAL_UART_Init(huart) != HAL_OK)
    {
        Error_Handler();
    }
    else
    {
        __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
        HAL_UART_Receive_IT(huart, huart->pRxBuffPtr, huart->RxXferSize);
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
        if(UART4 == huart->Instance)
        {
            memcpy(pData, UART4_RxBuff, Size);
        }
    #elif (USE_HAL_UART5 == 1U)
        if(UART5 == huart->Instance)
        {
            memcpy(pData, UART5_RxBuff, Size);
        }
    #elif (USE_HAL_UART1 == 1U)
        if(UART1 == huart->Instance)
        {
            memcpy(pData, UART1_RxBuff, Size);
        }
    #elif (USE_HAL_UART2 == 1U)
        if(UART2 == huart->Instance)
        {
            memcpy(pData, UART2_RxBuff, Size);
        }
    #elif (USE_HAL_UART3 == 1U)
        if(UART3 == huart->Instance)
        {
            memcpy(pData, UART3_RxBuff, Size);
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
        /* */
        }
    #endif

    #if (USE_HAL_UART5 == 1U)
        if (huart == &huart5)
        {
        /* */
        }
    #endif

    #if (USE_HAL_UART1 == 1U)
        if (huart == &huart1)
        {
        /* */
        }
    #endif

    #if (USE_HAL_UART2 == 1U)
        if (huart == &huart2)
        {
        /* */
        }
    #endif

    #if (USE_HAL_UART3 == 1U)
        if (huart == &huart3)
        {
        /* */
        }
    #endif
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    #if (USE_HAL_UART4 == 1U)
        if (huart == &huart4)
        {
            memset(UART4_RxBuff, 0, 1000);
            HAL_UART_Receive_IT(&huart4, UART4_RxBuff, 1000);
        }
    #endif

    #if (USE_HAL_UART5 == 1U)
        if (huart == &huart5)
        {
            memset(UART5_RxBuff, 0, 1000);
            HAL_UART_Receive_IT(&huart5, UART5_RxBuff, 1000);
        }
    #endif

    #if (USE_HAL_UART1 == 1U)
        if (huart == &huart1)
        {
            memset(UART1_RxBuff, 0, 1000);
            HAL_UART_Receive_IT(&huart1, UART1_RxBuff, 1000);
        }
    #endif

    #if (USE_HAL_UART2 == 1U)
        if (huart == &huart2)
        {
            memset(UART2_RxBuff, 0, 1000);
            HAL_UART_Receive_IT(&huart2, UART2_RxBuff, 1000);
        }
    #endif

    #if (USE_HAL_UART3 == 1U)
        if (huart == &huart3)
        {
            memset(UART3_RxBuff, 0, 1000);
            HAL_UART_Receive_IT(&huart3, UART3_RxBuff, 1000);
        }
    #endif
}
/* USER CODE END 2 */


/* USER CODE BEGIN 3 */
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(P_printf, (uint8_t *)&ch, 1, 10);

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
