#ifndef _HW_GPIO_H_
#define _HW_GPIO_H_

#include <board.h>

extern caribou_gpio_t gpio_led0;
extern caribou_gpio_t gpio_led1;
extern caribou_gpio_t gpio_led2;
extern caribou_gpio_t gpio_led3;
extern caribou_gpio_t gpio_rs485_dir;
extern caribou_gpio_t gpio_nrs485_dir;
extern caribou_gpio_t gpio_rs485_tx;
extern caribou_gpio_t gpio_bb_spi_nss;
extern caribou_gpio_t gpio_bb_spi_sck;
extern caribou_gpio_t gpio_bb_spi_mosi;
extern caribou_gpio_t gpio_bb_spi_miso;
extern caribou_gpio_t gpio_microsd_cd;

extern void hw_gpio_setup( void );

#define hw_gpio_toggle( pin ) 		caribou_gpio_toggle		( (pin) )
#define hw_gpio_set( pin ) 	    	caribou_gpio_set   		( (pin) )
#define hw_gpio_reset( pin ) 		caribou_gpio_reset 		( (pin) )
#define hw_gpio_state( pin ) 		(caribou_gpio_pinstate	( (pin) ) ? 1 : 0)
#define hw_gpio_write( pin, state)	(state?hw_gpio_set((pin)):hw_gpio_reset((pin)))

#endif
