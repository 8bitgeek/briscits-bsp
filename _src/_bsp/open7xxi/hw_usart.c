#include <hw_usart.h>

extern void hw_usart_setup( void )
{
	caribou_uart_config_t config;

   _stdout = _stdin = fopen(RS485_UART,"rw");
	caribou_uart_init_config(&config);
    config.gpio         = &gpio_rs485_dir;
	config.baud_rate	= RS485_SPEED_DEF;
	config.word_size	= CARIBOU_UART_WORDSIZE_8;
	config.stop_bits	= CARIBOU_UART_STOPBITS_1;
	config.parity_bits	= CARIBOU_UART_PARITY_NONE;
	#if RS485_USE_RX_DMA
		config.dma_mode		= CARIBOU_UART_DMA_RX /* | CARIBOU_UART_DMA_TX */;
		config.dma_prio		= CARIBOU_UART_DMA_PRIO_HIGH;
	#endif
	caribou_uart_set_config(RS485_UART,&config);
 
    _stderr = fopen(DEBUG_USART,"rw");
	caribou_uart_init_config(&config);
	config.baud_rate	= CARIBOU_UART_BAUD_RATE_115200;
	config.word_size	= CARIBOU_UART_WORDSIZE_8;
	config.stop_bits	= CARIBOU_UART_STOPBITS_1;
	config.parity_bits	= CARIBOU_UART_PARITY_NONE;
	config.flow_control	= CARIBOU_UART_FLOW_NONE;
	config.dma_mode		= CARIBOU_UART_DMA_RX /* | CARIBOU_UART_DMA_TX */;
    config.dma_prio		= CARIBOU_UART_DMA_PRIO_MEDIUM;
	caribou_uart_set_config(DEBUG_USART,&config);
}
