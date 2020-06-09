#ifndef LXX_UART_H
#define LXX_UART_H

#include <stdint.h>

/*************************************************************************************************************/
/*                              local typedef                                                                */
/*************************************************************************************************************/


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
#endif /* LXX_UART_H */
