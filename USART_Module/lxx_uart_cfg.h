#ifndef LXX_UART_CFG_H
#define LXX_UART_CFG_H

/************************************************************************************/
/*                              include file                                        */
/************************************************************************************/
/*  system file */

/*  internal file */
#include "lxx_uart.h"
/*  external file */

/************************************************************************************/
/*                              global macro define                                 */
/************************************************************************************/
#ifdef UART_GLOBALS_VARIABLE_DEFINITION
    #define EXTERN
#else
    #define EXTERN  extern
#endif

/************************************************************************************/
/*                              global variable                                     */
/************************************************************************************/
EXTERN LXX_UART_InitTypeDef usart1 = {
                                        .BaudRate       = BR_115200,              
                                        .WordLength     = WORDLENGTH_8BIT,
                                        .Parity         = PARITY_NONE,
                                        .Mode           = MODE_TRANSMITTER_RECEIVER,
                                        .StopBits       = STOP_1_BIT,
                                        .HWEnable       = UART_HARDWARE_DISABLE
                                        .Cmd            = UART_DISABLE,
                                        .GroupPriority  = (uint8_t)0x00,
                                        .SubPriority    = (uint8_t)0x00

                                    };

EXTERN LXX_UART_InitTypeDef usart2 = {
                                        .BaudRate       = BR_115200,              
                                        .WordLength     = WORDLENGTH_8BIT,
                                        .Parity         = PARITY_NONE,
                                        .Mode           = MODE_TRANSMITTER_RECEIVER,
                                        .StopBits       = STOP_1_BIT,
                                        .HWEnable       = UART_HARDWARE_DISABLE,
                                        .Cmd            = UART_DISABLE,
                                        .GroupPriority  = (uint8_t)0x00,
                                        .SubPriority    = (uint8_t)0x00
                                    };

EXTERN LXX_UART_InitTypeDef usart3 = {
                                        .UARTx          = USART3,
                                        .BaudRate       = BR_115200,              
                                        .WordLength     = WORDLENGTH_8BIT,
                                        .Parity         = PARITY_NONE,
                                        .Mode           = MODE_TRANSMITTER_RECEIVER,
                                        .StopBits       = STOP_1_BIT,
                                        .HWEnable       = UART_HARDWARE_DISABLE,
                                        .Cmd            = UART_DISABLE,
                                        .GroupPriority  = (uint8_t)0x00,
                                        .SubPriority    = (uint8_t)0x00
                                    };

EXTERN LXX_UART_InitTypeDef uart4 = {
                                        .BaudRate       = BR_115200,              
                                        .WordLength     = WORDLENGTH_8BIT,
                                        .Parity         = PARITY_NONE,
                                        .Mode           = MODE_TRANSMITTER_RECEIVER,
                                        .StopBits       = STOP_1_BIT,
                                        .HWEnable       = UART_HARDWARE_DISABLE,
                                        .Cmd            = UART_DISABLE,
                                        .GroupPriority  = (uint8_t)0x00,
                                        .SubPriority    = (uint8_t)0x00
                                    };

EXTERN LXX_UART_InitTypeDef uart5 = {
                                        .BaudRate       = BR_115200,              
                                        .WordLength     = WORDLENGTH_8BIT,
                                        .Parity         = PARITY_NONE,
                                        .Mode           = MODE_TRANSMITTER_RECEIVER,
                                        .StopBits       = STOP_1_BIT,
                                        .HWEnable       = UART_HARDWARE_DISABLE,
                                        .Cmd            = UART_DISABLE,
                                        .GroupPriority  = (uint8_t)0x00,
                                        .SubPriority    = (uint8_t)0x00
                                    };

/************************************************************************************/
/*                              global function                                     */
/************************************************************************************/
void MMX_UART_Init(void);
void MMX_UART_Single_Config(LXX_UART_InitTypeDef * huart);

#endif /* LXX_UART_CFG_H */
