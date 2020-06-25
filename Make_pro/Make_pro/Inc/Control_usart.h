/**
  ******************************************************************************
  * File Name          : Control_usart.h
  * Description        : This file provides code for the control
  *                      of the UART instances.
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
#ifndef __Constrol_usart_H
#define __Constrol_usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */


/* USER CODE BEGIN Global defines */
#ifdef UART_GLOBALS_VARIABLE_DEFINED
    #define EXTERN
#else
    #define EXTERN  extern
#endif

#define USE_HAL_UART4         0U
#define USE_HAL_UART5         0U  
#define USE_HAL_UART1         1U  
#define USE_HAL_UART2         0U  
#define USE_HAL_UART3         0U  

/* USER CODE END Global defines */


/* USER CODE BEGIN Prototypes */
#if (USE_HAL_UART4 == 1U)
  EXTERN UART_HandleTypeDef huart4
  #ifdef UART_GLOBALS_VARIABLE_DEFINED
                                    = {
                                        .Instance = UART4,
                                        .Init = {
                                          .BaudRate   = 115200,
                                          .WordLength = UART_WORDLENGTH_8B,             /* @ref UART_Word_Length */
                                          .StopBits   = UART_STOPBITS_1,                /* @ref UART_Stop_Bits */
                                          .Parity     = UART_PARITY_NONE,               /* @ref UART_Parity */
                                          .Mode       = UART_MODE_TX_RX                 /* @ref UART_Mode */
                                        }
                                    }
  #endif
                                      ;
#endif

#if (USE_HAL_UART5 == 1U)
  EXTERN UART_HandleTypeDef huart5
  #ifdef UART_GLOBALS_VARIABLE_DEFINED
                                    = {
                                        .Instance = UART5,
                                        .Init = {
                                          .BaudRate   = 115200,
                                          .WordLength = UART_WORDLENGTH_8B,             /* @ref UART_Word_Length */
                                          .StopBits   = UART_STOPBITS_1,                /* @ref UART_Stop_Bits */
                                          .Parity     = UART_PARITY_NONE,               /* @ref UART_Parity */
                                          .Mode       = UART_MODE_TX_RX                 /* @ref UART_Mode */
                                        }
                                    }
  #endif
                                      ;
#endif

#if (USE_HAL_UART1 == 1U)
  EXTERN UART_HandleTypeDef huart1
  #ifdef UART_GLOBALS_VARIABLE_DEFINED
                                    = {
                                        .Instance = USART1,
                                        .Init = {
                                          .BaudRate   = 115200,
                                          .WordLength = UART_WORDLENGTH_8B,             /* @ref UART_Word_Length */
                                          .StopBits   = UART_STOPBITS_1,                /* @ref UART_Stop_Bits */
                                          .Parity     = UART_PARITY_NONE,               /* @ref UART_Parity */
                                          .Mode       = UART_MODE_TX_RX                 /* @ref UART_Mode */
                                        }
                                    }
  #endif
                                      ;
#endif

#if (USE_HAL_UART2 == 1U)
  EXTERN UART_HandleTypeDef huart2
  #ifdef UART_GLOBALS_VARIABLE_DEFINED
                                    = {
                                        .Instance = USART2,
                                        .Init = {
                                          .BaudRate   = 115200,
                                          .WordLength = UART_WORDLENGTH_8B,             /* @ref UART_Word_Length */
                                          .StopBits   = UART_STOPBITS_1,                /* @ref UART_Stop_Bits */
                                          .Parity     = UART_PARITY_NONE,               /* @ref UART_Parity */
                                          .Mode       = UART_MODE_TX_RX                 /* @ref UART_Mode */
                                        }
                                    }
  #endif
                                      ;
#endif

#if (USE_HAL_UART3 == 1U)
  EXTERN UART_HandleTypeDef huart3
  #ifdef UART_GLOBALS_VARIABLE_DEFINED
                                    = {
                                        .Instance = USART3,
                                        .Init = {
                                          .BaudRate   = 115200,
                                          .WordLength = UART_WORDLENGTH_8B,             /* @ref UART_Word_Length */
                                          .StopBits   = UART_STOPBITS_1,                /* @ref UART_Stop_Bits */
                                          .Parity     = UART_PARITY_NONE,               /* @ref UART_Parity */
                                          .Mode       = UART_MODE_TX_RX                 /* @ref UART_Mode */
                                        }
                                    }
  #endif
                                      ;
#endif

EXTERN UART_HandleTypeDef *P_printf 
#ifdef UART_GLOBALS_VARIABLE_DEFINED
                                    = &huart1
#endif
                                    ;
                   
void MX_ALL_OF_UART_Init(void);
void MX_SINGLE_OF_UART_Init(UART_HandleTypeDef* huart);
void UARTReceive_IDLE(UART_HandleTypeDef *huart);
void GetRxData(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /* __Constrol_usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
