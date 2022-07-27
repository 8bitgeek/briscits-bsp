#include <brisc_board.h>
#include <brisc_thread.h>
#include <rgb_led.h>
#include <xprintf.h>
#include <ch32v103_rcc.h>
#include <ch32v103_usart.h>
#include <ch32v103_wwdg.h>
#include <ch32v103_dbgmcu.h>

#define DEBUG_UART USART1
#define UART_BAUD 115200U

static unsigned char usart_in(void);
static void usart_out(unsigned char ch);
static void usart_config(USART_TypeDef * usart_periph);
static void spi_config(SPI_TypeDef *spi_periph);

static unsigned char usart_in(void)
{
    if ( USART_GetFlagStatus( DEBUG_UART, USART_FLAG_RXNE ) )
        return USART_ReceiveData( DEBUG_UART );
    return 0;
}

static void usart_out(unsigned char ch)
{
    b_thread_block_while( USART_GetFlagStatus(USART2, USART_FLAG_TXE) );
    USART_SendData( DEBUG_UART, ch );
}

extern int board_getchar( void )
{
    if ( USART_GetFlagStatus( DEBUG_UART, USART_FLAG_RXNE ) )
        return USART_ReceiveData( DEBUG_UART ) & 0xFF;
    return -1;
}

static void usart_config(USART_TypeDef * usart_periph)
{
    USART_InitTypeDef USART_InitStructure = {0};
    USART_InitStructure.USART_BaudRate = UART_BAUD;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStructure);
    USART_Cmd(USART2, ENABLE);
}

static void spi_config(SPI_TypeDef *spi_periph)
{
    SPI_InitTypeDef  SPI_InitStructure = {0};
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(spi_periph, &SPI_InitStructure);
    SPI_SSOutputCmd(spi_periph, DISABLE);
    SPI_Cmd(spi_periph, ENABLE);
}

void board_init( void ) 
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    /* RCU CLOCKS */

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

    /* DBG */

    // DBG_CTL |= DBG_FWDGT_HOLD;      /* hold fwdgt when debug halts cpu */

    /* LEDx */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* UART1 */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    usart_config( DEBUG_UART );
    xdev_out(usart_out);
    xdev_in(usart_in);

    /* SPI */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;               /* SPI FLASH Slave Select */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;               /* MicroSD Slave Select */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;               /* C/D Card Detect */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;               /* SCLK */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;               /* MISO */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;               /* MOSI */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    spi_config( SPI1 );
}

extern uint32_t board_clkfreq( void )
{
    return SystemCoreClock;
}

extern bool board_wdg_setup( uint32_t ms)
{
    uint8_t prescaler_div;
    int16_t reload_value;
    if ( ms < 7 )
    {
        uint16_t ticks_per_ms = 4095 / 409;             // 10.01
        prescaler_div = FWDGT_PSC_DIV4;
        reload_value = ms * ticks_per_ms;
    }
    else
    {
        uint32_t ticks_per_ms = (4095*1000) / 26214;   // 0.156 * 1000 = 156
        prescaler_div = FWDGT_PSC_DIV256;
        reload_value = (ms * ticks_per_ms)/1000;
    }
    return fwdgt_config(reload_value,prescaler_div) == SUCCESS;
}

extern void board_wdg_enable( void )
{
    fwdgt_enable();
}

extern void board_wdg_reload( void )
{
    fwdgt_counter_reload();
}

