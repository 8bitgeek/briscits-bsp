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
#include <xprintf.h>

void board_init( void ) 
{

	gpio_set_mode( GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13 );

	gpio_set(BOARD_GPIO_LED);
	
	cpu_int_enable();
}

extern uint32_t board_clkfreq( void )
{
    return SystemCoreClock;
}

extern void peripheral_clock_setup( void )
{
	RCC->AHBENR |=	(	RCC_AHBENR_DMA1EN		|
						RCC_AHBENR_SRAMEN		|
						RCC_AHBENR_CRCEN		);

	RCC->APB1ENR |= (	RCC_APB1ENR_USART2EN	|
						RCC_APB1ENR_WWDGEN		|
						RCC_APB1ENR_PWREN		|
						RCC_APB1ENR_TIM3EN		|
						RCC_APB1ENR_USBEN		);

	RCC->APB2ENR |= (	RCC_APB2ENR_USART1EN	|
						RCC_APB2ENR_AFIOEN		|
						RCC_APB2ENR_IOPAEN		|
						RCC_APB2ENR_IOPBEN		|
						RCC_APB2ENR_IOPCEN		|
						RCC_APB2ENR_IOPDEN		);
}

