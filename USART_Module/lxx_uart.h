#ifndef LXX_UART_H
#define LXX_UART_H


/*************************************************************************************************************/
/*                              local typedef                                                                */
/*************************************************************************************************************/
typedef enum
{
    IT_FLAG_CTS  = (((uint32_t)(0x1 << 9u)),
    IT_FLAG_TXE  = (((uint32_t)(0x1 << 7u)),
    IT_FLAG_TC   = (((uint32_t)(0x1 << 6u)),
    IT_FLAG_RXNE = (((uint32_t)(0x1 << 5u)),
    IT_FLAG_IDLE = (((uint32_t)(0x1 << 4u)),
    IT_FLAG_IDLE = (((uint32_t)(0x1 << 3u)),
    IT_FLAG_PE   = (((uint32_t)(0x1 << 0u))
}LXX_UART_ITFlag_TypeDef;



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
#define CHECK_UART_PORT(X)              (((X) == USART1)    ||  \
                                         ((X) == USART2)    ||  \
                                         ((X) == USART3)    ||  \
                                         ((X) == UART4)     ||  \
                                         ((X) == UART5))
/******************************************************************************************************************/

/************************************************************************************/
/*  global type or structure */
/************************************************************************************/


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
