/******************************************************************************
 ________  ________  ___  ________  ________  ___  _________  ________      
|\   __  \|\   __  \|\  \|\   ____\|\   ____\|\  \|\___   ___\\   ____\     
\ \  \|\ /\ \  \|\  \ \  \ \  \___|\ \  \___|\ \  \|___ \  \_\ \  \___|_    
 \ \   __  \ \   _  _\ \  \ \_____  \ \  \    \ \  \   \ \  \ \ \_____  \   
  \ \  \|\  \ \  \\  \\ \  \|____|\  \ \  \____\ \  \   \ \  \ \|____|\  \  
   \ \_______\ \__\\ _\\ \__\____\_\  \ \_______\ \__\   \ \__\  ____\_\  \ 
    \|_______|\|__|\|__|\|__|\_________\|_______|\|__|    \|__| |\_________\
                            \|_________|                        \|_________|
                            
MIT License

Copyright (c) 2022 Mike Sharkey

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************/
#include <brisc_board.h>
#include <brisc_thread.h>
#include <rgb_led.h>
#include <xprintf.h>

static unsigned char usart_in(void);
static void usart_out(unsigned char ch);
static void usart_config(uint32_t usart_periph);

unsigned char usart_in(void)
{
    if ( usart_flag_get( USART0, USART_FLAG_RBNE ) )
        return ( usart_data_receive( USART0 ) & 0xFF );
    return 0;
}

void usart_out(unsigned char ch)
{
    b_thread_block_while( !usart_flag_get( USART0, USART_FLAG_TBE ) );
    usart_data_transmit( USART0, (uint8_t) ch );
}

static void usart_config(uint32_t usart_periph)
{
    /* USART configure */
    usart_deinit(usart_periph);
    usart_baudrate_set(usart_periph, 115200U);
    usart_word_length_set(usart_periph, USART_WL_8BIT);
    usart_stop_bit_set(usart_periph, USART_STB_1BIT);
    usart_parity_config(usart_periph, USART_PM_NONE);
    usart_hardware_flow_rts_config(usart_periph, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(usart_periph, USART_CTS_DISABLE);
    usart_receive_config(usart_periph, USART_RECEIVE_ENABLE);
    usart_transmit_config(usart_periph, USART_TRANSMIT_ENABLE);
    usart_enable(usart_periph);
}

void spi_config(uint32_t spi_periph)
{
    spi_parameter_struct spi_init_struct;
    /* deinitilize SPI and the parameters */
    spi_i2s_deinit(spi_periph);
    spi_struct_para_init(&spi_init_struct);

    /* SPIx parameter config */
    spi_init_struct.trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode          = SPI_MASTER;
    spi_init_struct.frame_size           = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
    spi_init_struct.nss                  = SPI_NSS_SOFT;
    spi_init_struct.prescale             = SPI_PSC_8;
    spi_init_struct.endian               = SPI_ENDIAN_MSB;
    spi_init(spi_periph, &spi_init_struct);
}

void board_init( void ) 
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_DMA0);
    rcu_periph_clock_enable(RCU_USART0);
    rcu_periph_clock_enable(RCU_SPI1);

    /* RGB LEDx */
    gpio_init(  GPIOB, 
                GPIO_MODE_OUT_PP, 
                GPIO_OSPEED_2MHZ, 
                GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_5 );
    gpio_bit_set( GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_5 );

    /* USART0 */
    gpio_init( GPIOA, GPIO_MODE_AF_PP,       GPIO_OSPEED_50MHZ, GPIO_PIN_9  );    /* connect port to USARTx_Tx */
    gpio_init( GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10 );    /* connect port to USARTx_Rx */
    usart_config( USART0 );
    xdev_out(usart_out);
    xdev_in(usart_in);

    /* SPI1 GPIO CS/PB12, SCK/PB13, MISO/PB14, MOSI/PB15 */
    gpio_init( GPIOB, GPIO_MODE_OUT_PP,      GPIO_OSPEED_50MHZ, GPIO_PIN_12 );
    gpio_init( GPIOB, GPIO_MODE_AF_PP,       GPIO_OSPEED_50MHZ, GPIO_PIN_13 | GPIO_PIN_15 );
    gpio_init( GPIOB, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_14 );
    spi_config( SPI1 );
}
