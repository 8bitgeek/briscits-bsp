#include <hw_gpio.h>

caribou_gpio_t gpio_led0		= CARIBOU_GPIO_INIT( GPIOB, CARIBOU_GPIO_PIN_6 );
caribou_gpio_t gpio_led1		= CARIBOU_GPIO_INIT( GPIOB, CARIBOU_GPIO_PIN_7 );
caribou_gpio_t gpio_led2		= CARIBOU_GPIO_INIT( GPIOH, CARIBOU_GPIO_PIN_4 );
caribou_gpio_t gpio_led3		= CARIBOU_GPIO_INIT( GPIOI, CARIBOU_GPIO_PIN_8 );
caribou_gpio_t gpio_rs485_dir   = CARIBOU_GPIO_INIT( GPIOB, CARIBOU_GPIO_PIN_4 );
caribou_gpio_t gpio_nrs485_dir  = CARIBOU_GPIO_INIT( GPIOB, CARIBOU_GPIO_PIN_4 );
caribou_gpio_t gpio_rs485_tx	= CARIBOU_GPIO_INIT( GPIOC, CARIBOU_GPIO_PIN_6 );

caribou_gpio_t gpio_bb_spi_nss	= CARIBOU_GPIO_INIT( GPIOC, CARIBOU_GPIO_PIN_11 );
caribou_gpio_t gpio_bb_spi_sck	= CARIBOU_GPIO_INIT( GPIOC, CARIBOU_GPIO_PIN_12 );
caribou_gpio_t gpio_bb_spi_mosi	= CARIBOU_GPIO_INIT( GPIOD, CARIBOU_GPIO_PIN_2 );
caribou_gpio_t gpio_bb_spi_miso	= CARIBOU_GPIO_INIT( GPIOC, CARIBOU_GPIO_PIN_8 );
caribou_gpio_t gpio_microsd_cd	= CARIBOU_GPIO_INIT( GPIOC, CARIBOU_GPIO_PIN_13 );


extern void hw_gpio_setup( void )
{
	caribou_gpio_reset( &gpio_led0 );
	caribou_gpio_reset( &gpio_led1 );
	caribou_gpio_reset( &gpio_led2 );
	caribou_gpio_reset( &gpio_led3 );
    caribou_gpio_reset( &gpio_rs485_dir );

	caribou_gpio_set( &gpio_bb_spi_nss );
	caribou_gpio_reset( &gpio_bb_spi_sck );
	caribou_gpio_reset( &gpio_bb_spi_mosi );
}

