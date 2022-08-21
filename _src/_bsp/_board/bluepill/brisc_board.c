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
#include <usb-gadget0.h>

gpio_t  gpio_led0 = { GPIOC, GPIO13 };

static usbd_device *usbd_dev=NULL;

void board_init( void ) 
{
	/* Configure the system clock */
	rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);

	/* Enables peripheral clocks */
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOD);
	rcc_periph_clock_enable(RCC_DMA1);
	rcc_periph_clock_enable(RCC_SRAM);
	rcc_periph_clock_enable(RCC_CRC);
	rcc_periph_clock_enable(RCC_USART1);
	rcc_periph_clock_enable(RCC_USART2);
	rcc_periph_clock_enable(RCC_WWDG);
	rcc_periph_clock_enable(RCC_PWR);
	rcc_periph_clock_enable(RCC_TIM8);

	/* Configur pins */
	gpio_set_mode( GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13 );

	/* Set initial gpio pin states */
	b_gpio_set(&gpio_led0);

	/* Configure the systick interrupt to generate systick interrupts at 1000 Hz */
	systick_set_frequency(HZ, board_clkfreq());
	systick_interrupt_enable();
	systick_counter_enable();

	/* Enable global CPU interrupts */
	cpu_int_enable();
}

extern uint32_t board_clkfreq( void )
{
	/** @@NOTE Can we retrieve this from the rcc module? */
    return 72000000;
}

void board_usb_start( void )
{
	/*
	 * Vile hack to reenumerate, physically _drag_ d+ low.
	 * do NOT do this if you're board has proper usb pull up control!
	 * (need at least 2.5us to trigger usb disconnect)
	 */
	gpio_set_mode( GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO12 );
	gpio_clear(GPIOA, GPIO12);

	for (unsigned int i = 0; i < 800000; i++) {
		__asm__("nop");
	}

	rcc_periph_clock_enable(RCC_OTGFS);

	usbd_dev = gadget0_init( &st_usbfs_v1_usb_driver, "0123456789");

	gpio_clear(GPIOC, GPIO13);
}

void board_usb_service( void )
{
	gadget0_run( usbd_dev );
}

void board_stderr_putchar( uint8_t c )
{
	/* do stuff here */
}