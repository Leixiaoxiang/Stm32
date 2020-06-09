
#ifndef UART_GLOBALS_VARIABLE_DEFINITION
#define UART_GLOBALS_VARIABLE_DEFINITION
/*************************************************************************************************************/
/*                              include file                                                                 */
/*************************************************************************************************************/
/*  internal file */
//#include "lxx_uart.h"
#include "lxx_uart_cfg.h"
/*  external file */
#include "lxx_gpio.h"
#include "lxx_exti.h"
/*  system file */
#include "stdio.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

#undef USE_FULL_ASSERT
/*************************************************************************************************************/
/*                              local variable                                                               */
/*************************************************************************************************************/
static LXX_UART_InitTypeDef* UART_PORT_ARRAY[] = {&usart1, &usart2, &usart3, &uart4, &uart5};

/*************************************************************************************************************/
/*                              local function                                                              */
/*************************************************************************************************************/
static void LXX_UART_Init(LXX_UART_InitTypeDef * huart);

/***********************************************************************************
 * Function      : MMX_UART_Init
 * Description   : initial all uart module
 * Input         : NA
 * Output        : NA
 * Others        : NA
************************************************************************************/
void MMX_UART_Init(void)
{
    uint8_t usart_cnt = sizeof(UART_PORT_ARRAY) / sizeof(UART_PORT_ARRAY[0]);

    for (size_t i = 0; i < usart_cnt; i++)
    {
        /* check corrent uart module if enable */
        if(ENABLE == UART_PORT_ARRAY[i]->Cmd)
        {
            /* enable corrent uart module */
            MMX_UART_Single_Config(UART_PORT_ARRAY[i]);
        }
    }  
}

/***********************************************************************************
 * Function      : MMX_UART_Single_Config
 * Description   : configration USART/UART register
 * Input         : huart = usart1, usart2, usart3, uart4, uart5;
 * Output        : NA
 * Others        : NA
************************************************************************************/
void MMX_UART_Single_Config(LXX_UART_InitTypeDef * huart)
{
    GPIO_TypeDef * UART_TXPinPort;
    GPIO_TypeDef * UART_RXPinPort;
    IRQn_Type USARTx_IRQn;
    
    /*  get AFIO_EVCR and configration rcc */
    if(&usart2 == huart)
    {
        huart->USARTx = USART2;
        USARTx_IRQn = USART2_IRQn;
        __HAL_RCC_USART2_CLK_ENABLE();
        if((uint32_t)0x00 == (AFIO->MAPR & USART2_AFIO))
        {
            __HAL_RCC_GPIOA_CLK_ENABLE();
            /* TX */
            huart->USARTxPin.TX_Pin.pin   = GPIO_PIN_2;
            /* RX */
            huart->USARTxPin.RX_Pin.pin   = GPIO_PIN_3;
            /* PIN PROT */
            UART_TXPinPort = GPIOA;

        }
        else
        {
            __HAL_RCC_GPIOD_CLK_ENABLE();
            /* TX */
            huart->USARTxPin.TX_Pin.pin   = GPIO_PIN_5;
            /* RX */
            huart->USARTxPin.RX_Pin.pin   = GPIO_PIN_6;
            /* PIN PROT */
            UART_TXPinPort = GPIOD;
        }
        UART_RXPinPort = UART_TXPinPort;
    }
    else if(&usart3 == huart)
    {
        huart->USARTx = USART3;
        USARTx_IRQn = USART3_IRQn;
        __HAL_RCC_USART3_CLK_ENABLE();
        if((uint32_t)0x00 == (AFIO->MAPR & USART3_AFIO))
        {
            __HAL_RCC_GPIOB_CLK_ENABLE();
            /* TX */
            huart->USARTxPin.TX_Pin.pin   = GPIO_PIN_10;
            /* RX */
            huart->USARTxPin.RX_Pin.pin   = GPIO_PIN_11;
            /* PIN PROT */
            UART_TXPinPort = GPIOB;
        }
        else if((uint32_t)0x01 == (AFIO->MAPR & USART3_AFIO))
        {
            __HAL_RCC_GPIOC_CLK_ENABLE();
            /* TX */
            huart->USARTxPin.TX_Pin.pin   = GPIO_PIN_10;
            /* RX */
            huart->USARTxPin.RX_Pin.pin   = GPIO_PIN_11;
            /* PIN PROT */
            UART_TXPinPort = GPIOC;
        }
        else if((uint32_t)0x03 == (AFIO->MAPR & USART3_AFIO))
        {
            __HAL_RCC_GPIOD_CLK_ENABLE();
            /* TX */
            huart->USARTxPin.TX_Pin.pin   = GPIO_PIN_8;
            /* RX */
            huart->USARTxPin.RX_Pin.pin   = GPIO_PIN_9;
            /* PIN PROT */
            UART_TXPinPort = GPIOD;
        }
        else
        {
            assert_param(0);
        }
        UART_RXPinPort = UART_TXPinPort;
    }
    else if(&uart4 == huart)
    {
            huart->USARTx = UART4;
            USARTx_IRQn = UART4_IRQn;
            __HAL_RCC_UART4_CLK_ENABLE();
            __HAL_RCC_GPIOC_CLK_ENABLE();
            /* TX */
            huart->USARTxPin.TX_Pin.pin   = GPIO_PIN_10;
            /* RX */
            huart->USARTxPin.RX_Pin.pin   = GPIO_PIN_11;
            /* PIN PROT */
            UART_TXPinPort = GPIOC;
            UART_RXPinPort = UART_TXPinPort;
    }
    else if(&uart5 == huart)
    {
            huart->USARTx = UART5;
            USARTx_IRQn = UART5_IRQn;
            __HAL_RCC_UART5_CLK_ENABLE();
            __HAL_RCC_GPIOC_CLK_ENABLE();
            __HAL_RCC_GPIOD_CLK_ENABLE();
            /* TX */
            huart->USARTxPin.TX_Pin.pin   = GPIO_PIN_10;
            /* RX */
            huart->USARTxPin.RX_Pin.pin   = GPIO_PIN_11;
            /* PIN PROT */
            UART_TXPinPort = GPIOC;
            UART_RXPinPort = GPIOD;
    }
    else /* if(usart1 == *huart) */
    {
        huart->USARTx = USART1;
        USARTx_IRQn = USART1_IRQn;
        __HAL_RCC_USART1_CLK_ENABLE();
        if((uint32_t)0x00 == (AFIO->MAPR & USART1_AFIO))
        {
            __HAL_RCC_GPIOA_CLK_ENABLE();
            /* TX */
            huart->USARTxPin.TX_Pin.pin   = GPIO_PIN_9;
            /* RX */
            huart->USARTxPin.RX_Pin.pin   = GPIO_PIN_10;
            /* PIN PROT */
            UART_TXPinPort = GPIOA;
        }
        else
        {
            __HAL_RCC_GPIOB_CLK_ENABLE();
            /* TX */
            huart->USARTxPin.TX_Pin.pin   = GPIO_PIN_6;
            /* RX */
            huart->USARTxPin.RX_Pin.pin   = GPIO_PIN_7;
            /* PIN PROT */
            UART_TXPinPort = GPIOB;
        }
        UART_RXPinPort = UART_TXPinPort;
    }

    huart->USARTxPin.TX_Pin.mode  = GPIO_CRx_CNFy_OUTPUT_AF_PP;
    huart->USARTxPin.TX_Pin.speed = GPIO_CRx_MODEy_OUTPUT_SPEED_HIGH;
    huart->USARTxPin.RX_Pin.mode  = GPIO_CRx_CNFy_INPUT_FLOATING;
    huart->USARTxPin.RX_Pin.speed = GPIO_CRx_MODEy_INPUT;
    LXX_GPIO_Init(UART_TXPinPort, &(huart->USARTxPin.TX_Pin));
    LXX_GPIO_Init(UART_RXPinPort, &(huart->USARTxPin.RX_Pin));

    LXX_UART_Init(huart);

    //configration NVIC and enable NVIC IRQ
    LXX_NVIC_Config(USARTx_IRQn, huart->GroupPriority, huart->SubPriority);
    NVIC_EnableIRQ(USARTx_IRQn);

    //configration IT flag
    MMX_UART_IT_Config(huart,UART_RXNEIE,ENABLE);

    //enable uart
    MMX_UART_Cmd(huart, huart->Cmd);
}

/***********************************************************************************
 * Function      : MMX_UART_Cmd
 * Description   : configration UE in CR1 register, enable or disable module
 * Input         : huart = usart1, usart2, usart3, uart4, uart5;
 *                 State = DISABLE, ENABLE;
 * Output        : NA
 * Others        : NA
************************************************************************************/
void MMX_UART_Cmd(LXX_UART_InitTypeDef * huart, FunctionalState State)
{
    assert_param(CHECK_UART_PORT(huart->USARTx));
    assert_param(CHECK_UART_STATE(State));

    if(DISABLE == State)
    {
        huart->USARTx->CR1 &= USART_CR1_UE;
        
    }
    else
    {
        huart->USARTx->CR1 |= USART_CR1_UE;
    }
}

/***********************************************************************************
 * Function      : LXX_UART_Init
 * Description   : configration CR1, CR2, CR3 register
 * Input         : huart = usart1, usart2, usart3, uart4, uart5;
 * Output        : NA
 * Others        : NA
************************************************************************************/
static void LXX_UART_Init(LXX_UART_InitTypeDef * huart)
{
    assert_param(CHECK_UART_PORT(huart->USARTx));
    assert_param(CHECK_BAUDRATE(huart->BaudRate));

    if( huart->BaudRate == BR_115200 )
    {
        huart->USARTx->BRR = BAUDRATE_115200;
    }
    else if( huart->BaudRate == BR_9600 )
    {
        huart->USARTx->BRR = BAUDRATE_9600;
    }

    assert_param(CHECK_UART_WORDLENGTH(huart->WordLength));
    huart->USARTx->CR1 |= huart->WordLength;

    assert_param(CHECK_UART_PARITY(huart->Parity));
    huart->USARTx->CR1 |= huart->Parity;

    assert_param(CHECK_UART_MODE(huart->Mode));
    huart->USARTx->CR1 |= huart->Mode;

    assert_param(CHECK_UART_STOPBITS(huart->StopBits));
    huart->USARTx->CR2 |= huart->StopBits;

    assert_param(UART_HARDWARE_STATE(huart->HWEnable));
    huart->USARTx->CR3 |= huart->HWEnable;
}

/***********************************************************************************
 * Function      : MMX_UART_IT_Config
 * Description   : configration Interrupt
 * Input         : huart = usart1, usart2, usart3, uart4, uart5;
 *                 IT_Type = UART_EIE, UART_IDLEIE, UART_RXNEIE, UART_TCIE,
 *                           UART_TXEIE, UART_PEIE, UART_CTSIE;
 *                 State = DISABLE, ENABLE;
 * Output        : NA
 * Others        : NA
************************************************************************************/
void MMX_UART_IT_Config(LXX_UART_InitTypeDef * huart, LXX_UART_IT_TypeDef IT_Type, FunctionalState State)
{
    uint32_t ItType = IT_Type;

    assert_param(CHECK_UART_PORT(huart->USARTx));
    assert_param(CHECK_UART_STATE(State));
    assert_param(CHECK_UART_IT(IT_Type));

    if (UART_EIE == (IT_Type & UART_EIE)) 
    {
        if (ENABLE == State)
        {
            SET_BIT(huart->USARTx->CR3,UART_EIE);
        }
        else
        {
            CLEAR_BIT(huart->USARTx->CR3,UART_EIE);
        }   
    }
    else
    {
        /* do nothing */
    }
 
    ItType = (uint32_t)IT_Type & (UART_RXNEIE + UART_TCIE + UART_TXEIE + UART_PEIE);
    if (ItType)
    {
        if (ENABLE == State)
        {
            SET_BIT(huart->USARTx->CR1,ItType);
        }
        else
        {
            CLEAR_BIT(huart->USARTx->CR1,ItType);
        }  
    }
    else
    {
        /* do nothing */
    }

    if (UART_CTSIE == (IT_Type & UART_CTSIE))
    {
        if (ENABLE == State)
        {
            SET_BIT(huart->USARTx->CR2,UART_CTSIE);
        }
        else
        {
            CLEAR_BIT(huart->USARTx->CR2,UART_CTSIE);
        }  
    }
    else
    {
        /* do nothing */
    }
}

/***********************************************************************************
 * Function      : MMX_Usart_SendByte
 * Description   : send a byte data
 * Input         : huart = usart1, usart2, usart3, uart4, uart5;
 *                 ch is data
 * Output        : NA
 * Others        : NA
************************************************************************************/
void MMX_Usart_SendByte(LXX_UART_InitTypeDef * huart, uint8_t ch)
{
    huart->USARTx->DR = ch;
    while((huart->USARTx->SR & IT_FLAG_TXE) == (uint32_t)0x00);	
}

/***********************************************************************************
 * Function      : MMX_Usart_SendByte
 * Description   : send a Statement
 * Input         : huart = usart1, usart2, usart3, uart4, uart5;
 *                 p_str is statement
 * Output        : NA
 * Others        : NA
************************************************************************************/
void MMX_Usart_SendStatement(LXX_UART_InitTypeDef * huart, uint8_t *p_str)
{
    while (*p_str != '\0')
    {
        huart->USARTx->DR = *p_str++;
        while((huart->USARTx->SR & IT_FLAG_TXE) == (uint32_t)0x00);	
    }
    while((huart->USARTx->SR & IT_FLAG_TC) == (uint32_t)0x00);
}

/***********************************************************************************
 * Function      : PUTCHAR_PROTOTYPE & _write
 * Description   : rewrite printf function
 * Input         : NA
 * Output        : NA
 * Others        : NA
************************************************************************************/
PUTCHAR_PROTOTYPE
{
    MMX_Usart_SendByte(P_printf, (uint8_t)ch);

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

/***********************************************************************************
 * Function      : USART1_IRQHandler
 * Description   : NA
 * Input         : NA
 * Output        : NA
 * Others        : NA
************************************************************************************/
void USART1_IRQHandler(void)
{
    if((USART1->SR & IT_FLAG_RXNE) == IT_FLAG_RXNE)
    {
        uint8_t i = USART1->DR;
        printf("%u\n", i);
    }
}

#endif /* UART_GLOBALS_VARIABLE_DEFINITION */
