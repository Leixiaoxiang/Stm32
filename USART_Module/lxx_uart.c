/************************************************************************************/
/*                              include file                                        */
/************************************************************************************/
/*  system file */

/*  internal file */
#define UART_GLOBALS_VARIABLE_DEFINITION
#include "lxx_uart_cfg.h"

/*  external file */

/************************************************************************************/
/*                              local variable                                      */
/************************************************************************************/
const static LXX_UART_InitTypeDef UART_PORT_ARRAY[] = {usart1, usart2, usart3,
                                                       uart4,  uart5};
/************************************************************************************/
/*                              local function                                      */
/************************************************************************************/
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
        if(UART_ENABLE == UART_PORT_ARRAY[i].Cmd)
        {
            /* enable corrent uart module */
            MMX_UART_Single_Config(&UART_PORT_ARRAY[i]);
        }
    }  
}

/***********************************************************************************
 * Function      : MMX_UART_Single_Config
 * Description   : configration USART/UART register
 * Input         : usart1, usart2, usart3, uart4, uart5 
 * Output        : NA
 * Others        : NA
************************************************************************************/
void MMX_UART_Single_Config(LXX_UART_InitTypeDef * huart)
{
    __IO uint32_t AFIO_Val;
    GPIO_TypeDef * UART_TXPinPort;
    GPIO_TypeDef * UART_RXPinPort;
    IRQn_Type USARTx_IRQn;
    
    /*  get AFIO_EVCR and configration rcc */
    //assert_param(CHECK_UART_PORT(huart->USARTx));
    switch (*huart)
    {
        default:

        case usart1:
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
                UART_PinPort = GPIOB;
            }
            UART_RXPinPort = UART_TXPinPort;
        break;

        case usart2:
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
        break;

        case usart3:
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
        break;

        case uart4:
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
        break;

        case uart5:
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
        break;
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

    //enable uart
    UART_CMD(huart->USARTx, huart->Cmd);
    //configration IT flag
    LXX_UART_IT_Config(huart->USARTx);
}

static void LXX_UART_Init(LXX_UART_InitTypeDef * huart)
{
    assert_param(CHECK_BAUDRATE(UART_Init->BaudRate));
    assert_param(CHECK_UART_PORT(UART_Init->USARTx));

    if( UART_Init->BaudRate == BR_115200 )
    {
        UART_Init->USARTx->BRR = BAUDRATE_115200;
    }
    else if( UART_Init->BaudRate == BR_9600 )
    {
        UART_Init->USARTx->BRR = BAUDRATE_9600;
    }

    assert_param(CHECK_UART_WORDLENGTH(UART_Init->WordLength));
    UART_Init->USARTx->CR1 |= UART_Init->WordLength;

    assert_param(CHECK_UART_PARITY(UART_Init->Parity));
    UART_Init->USARTx->CR1 |= UART_Init->Parity;

    assert_param(CHECK_UART_MODE(UART_Init->mode));
    UART_Init->USARTx->CR1 |= UART_Init->mode;

    assert_param(CHECK_UART_STOPBITS(UART_Init->StopBits));
    UART_Init->USARTx->CR2 |= UART_Init->StopBits;

    assert_param(UART_HARDWARE_STATE(UART_Init->HWEnable));
    UART_Init->USARTx->CR3 |= UART_Init->HWEnable;

}

static void LXX_UART_IT_Config(USART_TypeDef * USARTx)
{
    USARTx->CR1 |= UART_RXNEIE;
   //USARTx->CR1 |= UART_TCIE;
}

void Usart_SendByte( int ch )
{
    USART1->DR = ch;
    while((USART1->SR & (uint32_t)0x40) == 0x00);	
} 

void Usart_SendStatement(uint8_t *p_str)
{
    while (*p_str != '\0')
    {
        USART1->DR = *p_str++;
        while((USART1->SR & (uint32_t)0x80) == 0x00);	
    }
    while((USART1->SR & (uint32_t)0x40) == 0x00);
}

void USART1_IRQHandler(void)
{
    if(USART1->SR & (uint32_t)0x20)
    {
        i = USART1->DR;
    }
}

