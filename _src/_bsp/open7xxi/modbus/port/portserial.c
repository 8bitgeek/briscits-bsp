/******************************************************************************
* Copyright (C) 2015 Accutron Instruments Inc.
******************************************************************************/
#include <port.h>
#include <mb.h>
#include <mbport.h>
#include <caribou.h>
#include <caribou/lib/stdio.h>

bool modbus_initialized=false;
bool modbus_rx_enabled=false;
bool modbus_tx_enabled=false;

static void rs485tx()
{
	caribou_gpio_set( &gpio_rs485_dir );
}

static void rs485rx()   
{
	/* drain transmitter before switching to RS485 receiver mode... */
	//caribou_thread_sleep_current(3);
	while (!caribou_bytequeue_empty(caribou_uart_tx_queue(RS485_UART)))
		caribou_thread_yield();
	while (caribou_uart_tx_busy(RS485_UART))
		caribou_thread_yield();
    caribou_gpio_reset( &gpio_rs485_dir );
}

void vMBPortSerialEnable(BOOL xRxEnable, BOOL xTxEnable)
{
    /* If xRXEnable enable serial receive interrupts. If xTxENable enable
     * transmitter empty interrupts.
     */
    if ( (modbus_rx_enabled=xRxEnable) )
    {
        rs485rx();
    }
    if ( (modbus_tx_enabled=xTxEnable) )
    {
        rs485tx();
    }
    if ( !modbus_rx_enabled && !modbus_tx_enabled )
    {
        rs485rx();
    }
}

BOOL xMBPortSerialInit(UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity)
{
    caribou_uart_config_t uart_config;
    caribou_uart_init_config(&uart_config);
    uart_config.baud_rate		= (caribou_uart_baud_t)ulBaudRate;
    uart_config.word_size		= (caribou_uart_word_t)ucDataBits;
	uart_config.stop_bits		= CARIBOU_UART_STOPBITS_1;
	uart_config.flow_control	= CARIBOU_UART_FLOW_NONE;
	uart_config.dma_mode		= CARIBOU_UART_DMA_RX /* | CARIBOU_UART_DMA_TX */;
	uart_config.dma_prio		= CARIBOU_UART_DMA_PRIO_HIGH;
	switch(eParity)
	{
		case MB_PAR_NONE: /* No parity. */
			uart_config.parity_bits = CARIBOU_UART_PARITY_NONE;
			break;
		case MB_PAR_ODD: /* Odd parity. */
			uart_config.parity_bits = CARIBOU_UART_PARITY_ODD;
			break;
		case MB_PAR_EVEN: /* Even parity. */
			uart_config.parity_bits = CARIBOU_UART_PARITY_EVEN;
			break;
	}
    caribou_uart_set_config(ucPORT,&uart_config);
    modbus_initialized=true;
    rs485rx();
    return TRUE;
}

BOOL xMBPortSerialPutByte(CHAR ucByte)
{
    /* Put a byte in the UARTs transmit buffer. This function is called
     * by the protocol stack if pxMBFrameCBTransmitterEmpty( ) has been
     * called. */
	caribou_bytequeue_t* txq = caribou_uart_tx_queue(RS485_UART);
	if ( !caribou_bytequeue_full(txq) )
	{
		fputc(ucByte,stdout);
		return TRUE;
	}
	return FALSE;
}

BOOL xMBPortSerialGetByte(CHAR * pucByte)
{
    /* Return the byte in the UARTs receive buffer. This function is called
    * by the protocol stack after pxMBFrameCBByteReceived( ) has been called.
    */
    caribou_bytequeue_t* rxq = caribou_uart_rx_queue(RS485_UART);
	if ( !caribou_bytequeue_empty(rxq) )
	{
		*pucByte = caribou_bytequeue_get(rxq);
		return TRUE;
	}
	return FALSE;
}

/* Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
bool prvvUARTTxReadyISR(void)
{
	/* Since CARIBOU handled the low level UART I/O, we'll
	* simulate tx and rx interrupts for the modbus layer */
	caribou_bytequeue_t* txq = caribou_uart_tx_queue(RS485_UART);
	if ( modbus_tx_enabled && !caribou_bytequeue_full(txq) )
	{
		pxMBFrameCBTransmitterEmpty();
		return TRUE;
	}
	return FALSE;
}

/* Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
bool prvvUARTRxISR(void)
{
	/* Since CARIBOU handled the low level UART I/O, we'll
	* simulate tx and rx interrupts for the modbus layer */
	caribou_bytequeue_t* rxq = caribou_uart_rx_queue(RS485_UART);
	if ( modbus_rx_enabled && !caribou_bytequeue_empty(rxq) )
	{
		pxMBFrameCBByteReceived();
		return TRUE;
	}
	return FALSE;
}

