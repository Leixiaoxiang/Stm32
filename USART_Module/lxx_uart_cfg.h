#ifndef LXX_UART_CFG_H
#define LXX_UART_CFG_H

/*************************************************************************************************************/
/*                              include file                                                                 */
/*************************************************************************************************************/
/*  internal file */

/*  external file */
#include "lxx_gpio.h"
/*  system file */
#include "main.h"

/*************************************************************************************************************/
/*                              global typedef                                                               */
/*************************************************************************************************************/

/*********************************************************************************/
typedef struct
{
    uint16_t                CTS_Pin;
    uint16_t                RTS_Pin;
    LXX_GPIO_InitTypeDef    TX_Pin;
    LXX_GPIO_InitTypeDef    RX_Pin;
    uint16_t                CK_Pin;
}USART_Pin_Config;

/*********************************************************************************/
typedef struct 
{
    USART_TypeDef * USARTx;
    USART_Pin_Config USARTxPin;
    uint32_t BaudRate;              
    uint32_t WordLength;
    uint32_t Parity;
    uint32_t Mode;
    uint32_t StopBits;
    uint32_t HWEnable;
    FunctionalState Cmd;
    uint8_t GroupPriority;
    uint8_t SubPriority;
}LXX_UART_InitTypeDef;

/*********************************************************************************/
typedef enum
{
    UART_EIE    = ((uint32_t)(0x1 << 0u)),
    UART_IDLEIE = ((uint32_t)(0x1 << 4u)),
    UART_RXNEIE = ((uint32_t)(0x1 << 5u)),
    UART_TCIE   = ((uint32_t)(0x1 << 6u)),
    //UART_LBDIE  = ((uint32_t)(0x1 << 6u)),
    UART_TXEIE  = ((uint32_t)(0x1 << 7u)),
    UART_PEIE   = ((uint32_t)(0x1 << 8u)),
    UART_CTSIE  = ((uint32_t)(0x1 << 10u))
}LXX_UART_IT_TypeDef;

/*********************************************************************************/
typedef enum
{
    IT_FLAG_CTS  = ((uint32_t)(0x1 << 9u)),
    IT_FLAG_TXE  = ((uint32_t)(0x1 << 7u)),
    IT_FLAG_TC   = ((uint32_t)(0x1 << 6u)),
    IT_FLAG_RXNE = ((uint32_t)(0x1 << 5u)),
    IT_FLAG_IDLE = ((uint32_t)(0x1 << 4u)),
    IT_FLAG_PE   = ((uint32_t)(0x1 << 0u))
}LXX_UART_ITFlag_TypeDef;

/*************************************************************************************************************/
/*                              global macro define                                                          */
/*************************************************************************************************************/
#ifdef UART_GLOBALS_VARIABLE_DEFINITION
    #define EXTERN
#else
    #define EXTERN  extern
#endif
/*********************************************************************************/

#define BR_9600                         ((uint32_t)9600)
#ifdef BR_9600

    #define DIV_MANTISSA_BR_9600        ((uint32_t)0x9 << 4u)          /* 9.6 / 1 = 9 */
    #define DIV_FRACTION_BR_9600        ((uint32_t)0xA)                /* (9.6 % 1) * 16 = 9.6*/
    #define BAUDRATE_9600               ((uint32_t)(DIV_MANTISSA_BR_9600 | DIV_FRACTION_BR_9600))
#endif

#define BR_115200                       ((uint32_t)115200)
#ifdef BR_115200
    #define DIV_MANTISSA_BR_115200      ((uint32_t)0x27 << 4u)       /* 39.0625 / 1 = 39 */
    #define DIV_FRACTION_BR_115200      ((uint32_t)0x1)              /* (39.0625  % 1) * 16 = 1 */
    #define BAUDRATE_115200             ((uint32_t)(DIV_MANTISSA_BR_115200 + DIV_FRACTION_BR_115200))
#endif
#define CHECK_BAUDRATE(X)               (((X) == BR_9600) || ((X) == BR_115200))

/*********************************************************************************/
#define WORDLENGTH_8BIT                 ((uint32_t)0x0 << 12u)
#define WORDLENGTH_9BIT                 ((uint32_t)0x1 << 12u)
#define CHECK_UART_WORDLENGTH(X)        (((X) == WORDLENGTH_8BIT) || ((X) == WORDLENGTH_9BIT))

/*********************************************************************************/
#define PARITY_NONE                     ((uint32_t)(0x0 << 10u))
#define PARITY_EVEN                     ((uint32_t)((0x0 << 8u) | (0x1 << 10u)))
#define PARITY_ODD                      ((uint32_t)((0x1 << 8u) | (0x1 << 10u)))
#define CHECK_UART_PARITY(X)            (((X) == PARITY_NONE)   ||  \
                                         ((X) == PARITY_EVEN)   ||  \
                                         ((X) == PARITY_ODD))

/*********************************************************************************/
#define MODE_TRANSMITTER                ((uint32_t)(0x1 << 3u))
#define MODE_RECEIVER                   ((uint32_t)(0x1 << 2u))
#define MODE_TRANSMITTER_RECEIVER       ((uint32_t)(MODE_TRANSMITTER | MODE_RECEIVER))
#define CHECK_UART_MODE(X)              (((X) == MODE_TRANSMITTER)            ||  \
                                         ((X) == MODE_RECEIVER)               ||  \
                                         ((X) == MODE_TRANSMITTER_RECEIVER)   ||  \
                                         ((X) == PARITY_ODD))

/*********************************************************************************/
#define STOP_1_BIT                      ((uint32_t)(0x0 << 12u))
#define STOP_0_5_BIT                    ((uint32_t)(0x1 << 12u))
#define STOP_2_BIT                      ((uint32_t)(0x2 << 12u))
#define STOP_1_5_BIT                    ((uint32_t)(0x3 << 12u))
#define CHECK_UART_STOPBITS(X)          (((X) == STOP_1_BIT)     ||  \
                                         ((X) == STOP_0_5_BIT)   ||  \
                                         ((X) == STOP_2_BIT)     ||  \
                                         ((X) == STOP_1_5_BIT))

/*********************************************************************************/
#define UART_HARDWARE_DISABLE           ((uint32_t)0x00000000u)
#define UART_CTS_ENBALE                 ((uint32_t)(0x1 << 9u))
#define UART_RTS_ENABLE                 ((uint32_t)(0x1 << 8u))
#define UART_CTS_RTS_ENABLE             ((uint32_t)(UART_CTS_ENBALE | UART_RTS_ENABLE))
#define UART_HARDWARE_STATE(X)          (((X) == UART_HARDWARE_DISABLE) || \
                                         ((X) == UART_CTS_ENBALE)       || \
                                         ((X) == UART_RTS_ENABLE)       || \
                                         ((X) == UART_CTS_RTS_ENABLE))

/*********************************************************************************/
#define CHECK_UART_PORT(X)              (((X) == USART1)    ||  \
                                         ((X) == USART2)    ||  \
                                         ((X) == USART3)    ||  \
                                         ((X) == UART4)     ||  \
                                         ((X) == UART5))

#define CHECK_UART_STATE(X)             (((X) == DISABLE) || ((X) == ENABLE))
#define CHECK_UART_IT(X)                (((X) >= UART_EIE) && ((X) <= UART_CTSIE))

/*************************************************************************************************************/
/*                              global variable                                                              */
/*************************************************************************************************************/
EXTERN LXX_UART_InitTypeDef usart1
#ifdef UART_GLOBALS_VARIABLE_DEFINITION
                                  = {
                                        .BaudRate       = BR_115200,
                                        .WordLength     = WORDLENGTH_8BIT,
                                        .Parity         = PARITY_NONE,
                                        .Mode           = MODE_TRANSMITTER_RECEIVER,
                                        .StopBits       = STOP_1_BIT,
                                        .HWEnable       = UART_HARDWARE_DISABLE,
                                        .Cmd            = ENABLE,
                                        .GroupPriority  = (uint8_t)0x00,
                                        .SubPriority    = (uint8_t)0x00
                                    }
#endif
                                    ;

/*********************************************************************************/
EXTERN LXX_UART_InitTypeDef usart2 
#ifdef UART_GLOBALS_VARIABLE_DEFINITION
                                    = {
                                        .BaudRate       = BR_115200,              
                                        .WordLength     = WORDLENGTH_8BIT,
                                        .Parity         = PARITY_NONE,
                                        .Mode           = MODE_TRANSMITTER_RECEIVER,
                                        .StopBits       = STOP_1_BIT,
                                        .HWEnable       = UART_HARDWARE_DISABLE,
                                        .Cmd            = DISABLE,
                                        .GroupPriority  = (uint8_t)0x00,
                                        .SubPriority    = (uint8_t)0x00
                                    }
#endif
                                    ;
                                    
/*********************************************************************************/
EXTERN LXX_UART_InitTypeDef usart3
#ifdef UART_GLOBALS_VARIABLE_DEFINITION
                                    = {
                                        .BaudRate       = BR_115200,              
                                        .WordLength     = WORDLENGTH_8BIT,
                                        .Parity         = PARITY_NONE,
                                        .Mode           = MODE_TRANSMITTER_RECEIVER,
                                        .StopBits       = STOP_1_BIT,
                                        .HWEnable       = UART_HARDWARE_DISABLE,
                                        .Cmd            = DISABLE,
                                        .GroupPriority  = (uint8_t)0x00,
                                        .SubPriority    = (uint8_t)0x00
                                    }
#endif
                                    ;
                                    
/*********************************************************************************/
EXTERN LXX_UART_InitTypeDef uart4 
#ifdef UART_GLOBALS_VARIABLE_DEFINITION
                                    = {
                                        .BaudRate       = BR_115200,              
                                        .WordLength     = WORDLENGTH_8BIT,
                                        .Parity         = PARITY_NONE,
                                        .Mode           = MODE_TRANSMITTER_RECEIVER,
                                        .StopBits       = STOP_1_BIT,
                                        .HWEnable       = UART_HARDWARE_DISABLE,
                                        .Cmd            = DISABLE,
                                        .GroupPriority  = (uint8_t)0x00,
                                        .SubPriority    = (uint8_t)0x00
                                    }
#endif
                                    ;
                                    
/*********************************************************************************/
EXTERN LXX_UART_InitTypeDef uart5 
#ifdef UART_GLOBALS_VARIABLE_DEFINITION
                                    = {
                                        .BaudRate       = BR_115200,              
                                        .WordLength     = WORDLENGTH_8BIT,
                                        .Parity         = PARITY_NONE,
                                        .Mode           = MODE_TRANSMITTER_RECEIVER,
                                        .StopBits       = STOP_1_BIT,
                                        .HWEnable       = UART_HARDWARE_DISABLE,
                                        .Cmd            = DISABLE,
                                        .GroupPriority  = (uint8_t)0x00,
                                        .SubPriority    = (uint8_t)0x00
                                    }
#endif
                                    ;

EXTERN LXX_UART_InitTypeDef *P_printf 
#ifdef UART_GLOBALS_VARIABLE_DEFINITION
                                    = &usart1
#endif
                                    ;
                                    
/*************************************************************************************************************/
/*                              global function                                                              */
/*************************************************************************************************************/
void MMX_UART_Init(void);
void MMX_UART_Single_Config(LXX_UART_InitTypeDef * huart);
void MMX_UART_Cmd(LXX_UART_InitTypeDef * huart, FunctionalState State);
void MMX_UART_IT_Config(LXX_UART_InitTypeDef * huart, LXX_UART_IT_TypeDef IT_Type, FunctionalState State);
void MMX_Usart_SendByte(LXX_UART_InitTypeDef * huart, uint8_t ch);
void MMX_Usart_SendStatement(LXX_UART_InitTypeDef * huart, uint8_t *p_str);
#endif /* LXX_UART_CFG_H */
