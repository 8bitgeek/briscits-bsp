#ifndef _HW_BB_SPI_H_
#define _HW_BB_SPI_H_

#include <board.h>
#include <hw_gpio.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
	caribou_gpio_t* gpio_nss;
	caribou_gpio_t* gpio_sck;
    caribou_gpio_t* gpio_miso;
    caribou_gpio_t* gpio_mosi;
    uint8_t         hi_delay;
    uint8_t         lo_delay;
} hw_bb_spi_t;

extern void    hw_bb_spi_setup      ( hw_bb_spi_t* spi );

extern uint8_t hw_bb_spi_write_byte ( hw_bb_spi_t* spi, uint8_t data );
extern void    hw_bb_spi_write_data ( hw_bb_spi_t* spi, const void* data, uint32_t size );

extern uint8_t hw_bb_spi_read_byte  ( hw_bb_spi_t* spi );
extern void    hw_bb_spi_read_data  ( hw_bb_spi_t* spi, void* data, uint32_t size );

extern void	   hw_bb_spi_select     ( hw_bb_spi_t* spi );
extern void	   hw_bb_spi_deselect   ( hw_bb_spi_t* spi );

#ifdef __cplusplus
}
#endif

#endif
