#include <hw_bb_spi.h>

#pragma GCC push_options
#pragma GCC optimize ("Os")

#define spi_sck_hi(spi)         hw_gpio_set((spi)->gpio_sck)
#define spi_sck_lo(spi)         hw_gpio_reset((spi)->gpio_sck)

#define spi_nss_hi(spi)         hw_gpio_set((spi)->gpio_nss)
#define spi_nss_lo(spi)         hw_gpio_reset((spi)->gpio_nss)

#define spi_mosi_hi(spi)        hw_gpio_set((spi)->gpio_mosi)
#define spi_mosi_lo(spi)        hw_gpio_reset((spi)->gpio_mosi)
#define spi_mosi_set(spi,state) ((state)?hw_gpio_set((spi)->gpio_mosi):hw_gpio_reset((spi)->gpio_mosi))

#define spi_miso_in(spi)        hw_gpio_state((spi)->gpio_miso)

static void spi_delay( hw_bb_spi_t* spi, uint8_t delay );

extern void hw_bb_spi_setup( hw_bb_spi_t* spi )
{
	spi_nss_hi(spi);
    spi_sck_lo(spi);
    spi_mosi_lo(spi);
}

extern uint8_t hw_bb_spi_write_byte( hw_bb_spi_t* spi, uint8_t byte_out )
{
    uint8_t byte_in = 0;
    uint8_t bit;

    caribou_thread_lock();
    for (bit = 0x80; bit; bit >>= 1) 
    {
        /* Shift-out a bit to the MOSI line */
        spi_mosi_set(spi,(byte_out & bit) ? 1 : 0);

        /* Delay for at least the peer's setup time */
        // spi_delay(spi,spi->lo_delay);

        /* Pull the clock line high */
        spi_sck_hi(spi);

        /* Shift-in a bit from the MISO line */
        byte_in |= ( spi_miso_in(spi) ) ? bit : 0;

        /* Delay for at least the peer's hold time */
        // spi_delay(spi,spi->hi_delay);

        /* Pull the clock line low */
        spi_sck_lo(spi);
    }
    caribou_thread_unlock();

    return byte_in;
}

extern void hw_bb_spi_write_data( hw_bb_spi_t* spi, const void* data, register uint32_t size )
{
    uint8_t* p = (uint8_t*)data;
    while(size--)        
        hw_bb_spi_write_byte(spi,*p++);
}

extern uint8_t hw_bb_spi_read_byte( hw_bb_spi_t* spi )
{
	return hw_bb_spi_write_byte( spi, 0xFF );
}

extern void hw_bb_spi_read_data( hw_bb_spi_t* spi, void* data, uint32_t size )
{
	int count;
	uint8_t* p = (uint8_t*)data;
	for ( count=0; count < size; count++ )
		p[count] = hw_bb_spi_read_byte( spi );
}

void hw_bb_spi_select(hw_bb_spi_t* spi)
{
	caribou_gpio_reset( spi->gpio_nss );
}

void hw_bb_spi_deselect(hw_bb_spi_t* spi)
{
	caribou_gpio_set( spi->gpio_nss );
}

static void spi_delay( hw_bb_spi_t* spi, uint8_t delay )
{
    volatile uint32_t count=delay;
    while(count--);
}

#pragma GCC pop_options
