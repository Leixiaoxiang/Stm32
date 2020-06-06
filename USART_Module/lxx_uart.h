#ifndef LXX_UART_H
#define LXX_UART_H

#include "main.h"
#include "lxx_gpio.h"
#include "lxx_exti.h"

/******************************************************************************************************************/
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
/******************************************************************************************************************/
#define WORDLENGTH_8BIT                 ((uint32_t)0x0 << 12u)
#define WORDLENGTH_9BIT                 ((uint32_t)0x1 << 12u)
#define CHECK_UART_WORDLENGTH(X)        (((X) == WORDLENGTH_8BIT) || ((X) == WORDLENGTH_9BIT))
/******************************************************************************************************************/
#define PARITY_NONE                     ((uint32_t)(0x0 << 10u))
#define PARITY_EVEN                     ((uint32_t)((0x0 << 8u) | (0x1 << 10u)))
#define PARITY_ODD                      ((uint32_t)((0x1 << 8u) | (0x1 << 10u)))
#define CHECK_UART_PARITY(X)            (((X) == PARITY_NONE)   ||  \
                                         ((X) == PARITY_EVEN)   ||  \
                                         ((X) == PARITY_ODD))
/******************************************************************************************************************/
#define MODE_TRANSMITTER                ((uint32_t)(0x1 << 3u))
#define MODE_RECEIVER                   ((uint32_t)(0x1 << 2u))
#define MODE_TRANSMITTER_RECEIVER       ((uint32_t)(MODE_TRANSMITTER | MODE_RECEIVER))
#define CHECK_UART_MODE(X)              (((X) == MODE_TRANSMITTER)            ||  \
                                         ((X) == MODE_RECEIVER)               ||  \
                                         ((X) == MODE_TRANSMITTER_RECEIVER)   ||  \
                                         ((X) == PARITY_ODD))
/******************************************************************************************************************/
#define STOP_1_BIT                      ((uint32_t)(0x0 << 12u))
#define STOP_0_5_BIT                    ((uint32_t)(0x1 << 12u))
#define STOP_2_BIT                      ((uint32_t)(0x2 << 12u))
#define STOP_1_5_BIT                    ((uint32_t)(0x3 << 12u))
#define CHECK_UART_STOPBITS(X)          (((X) == STOP_1_BIT)     ||  \
                                         ((X) == STOP_0_5_BIT)   ||  \
                                         ((X) == STOP_2_BIT)     ||  \
                                         ((X) == STOP_1_5_BIT))
/******************************************************************************************************************/
#define UART_CLOCK_DISABLE              ((uint32_t)(0x0 << 11u))
#define UART_CLOCK_ENABLE               ((uint32_t)(0x1 << 11u))
#define CHECK_UART_CLOCK(X)             (((X) == UART_CLOCK_DISABLE) || ((X) == UART_CLOCK_ENABLE))
/******************************************************************************************************************/
#define UART_CLOCK_POLARITY_LOW         ((uint32_t)(0x0 << 10u))
#define UART_CLOCK_POLARITY_HIGH        ((uint32_t)(0x1 << 10u))
#define CHECK_UART_CLOCK_POLARITY_(X)   (((X) == UART_CLOCK_POLARITY_LOW) || ((X) == UART_CLOCK_POLARITY_HIGH))
/******************************************************************************************************************/
#define UART_CLOCK_PHASE_FIRST          ((uint32_t)(0x0 << 9u))
#define UART_CLOCK_PHASE_SECOND         ((uint32_t)(0x1 << 9u))
#define CHECK_UART_CLOCK_PHASE(X)       (((X) == UART_CLOCK_PHASE_FIRST) || ((X) == UART_CLOCK_PHASE_SECOND))
/******************************************************************************************************************/
#define UART_HARDWARE_DISABLE           ((uint32_t)0x00000000u)
#define UART_CTS_ENBALE                 ((uint32_t)(0x1 << 9u))
#define UART_RTS_ENABLE                 ((uint32_t)(0x1 << 8u))
#define UART_CTS_RTS_ENABLE             ((uint32_t)(UART_CTS_ENBALE | UART_RTS_ENABLE))
#define UART_HARDWARE_STATE(X)          (((X) == UART_HARDWARE_DISABLE) || \
                                         ((X) == UART_CTS_ENBALE)       || \
                                         ((X) == UART_RTS_ENABLE)       || \
                                         ((X) == UART_CTS_RTS_ENABLE))
/******************************************************************************************************************/
#define CHECK_UART_CMD_STATE(X)         (((X) == UART_DISABLE) || ((X) == UART_ENABLE))
#define UART_CMD(UART, STATE)           do{                                             \
                                            assert_param(CHECK_UART_CMD_STATE(STATE));  \
                                            if(STATE == UART_DISABLE)                   \
                                            {                                           \
                                                UART->CR1 &= UART_DISABLE;              \
                                            }                                           \
                                            else                                        \
                                            {                                           \
                                                UART->CR1 |= UART_ENABLE;               \
                                            }                                           \
                                        }while(0u)
/******************************************************************************************************************/
#define CHECK_UART_PORT(X)              (((X) == USART1)    ||  \
                                         ((X) == USART2)    ||  \
                                         ((X) == USART3)    ||  \
                                         ((X) == UART4)     ||  \
                                         ((X) == UART5))
/******************************************************************************************************************/
#define UART_PEIE                       ((uint32_t)(0x1 << 8u))
#define UART_TXEIE                      ((uint32_t)(0x1 << 7u))
#define UART_TCIE                       ((uint32_t)(0x1 << 6u))
#define UART_RXNEIE                     ((uint32_t)(0x1 << 5u))
#define UART_IDLEIE                     ((uint32_t)(0x1 << 4u))
#define UART_CTSIE                      ((uint32_t)(0x1 << 10u))
#define UART_EIE                        ((uint32_t)(0x1 << 0u))
/******************************************************************************************************************/

/************************************************************************************/
/*  global type or structure */
/************************************************************************************/
typedef enum
{
    UART_DISABLE = ~USART_CR1_UE,
    UART_ENABLE = USART_CR1_UE
}UART_STATE;
/***********************************************/
typedef struct
{
    uint16_t                CTS_Pin;
    uint16_t                RTS_Pin;
    LXX_GPIO_InitTypeDef    TX_Pin;
    LXX_GPIO_InitTypeDef    RX_Pin;
    uint16_t                CK_Pin;
}USART_Pin_Config;
/***********************************************/
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
    UART_STATE Cmd;
    uint8_t GroupPriority;
    uint8_t SubPriority;
}LXX_UART_InitTypeDef;



typedef struct 
{
    uint32_t ClockEnable;
    uint32_t ClockPolarity;
    uint32_t ClockPhase;
}LXX_USART_CLOCK_InitTypeDef;
/******************************************************************************************************************/


void MMX_UART_Config(void);
void Usart_SendStatement(uint8_t *p_str);
#endif /* LXX_UART_H */
