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
#include <stm32f746xx.h>

static void peripheral_clock_setup( void );

void board_init( void ) 
{
    peripheral_clock_setup();
	cpu_int_enable();
}

static void peripheral_clock_setup( void )
{
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	RCC->AHB1ENR |= (	RCC_AHB1ENR_CRCEN		|
						RCC_AHB1ENR_DMA1EN		|
						RCC_AHB1ENR_DMA2EN		|
						RCC_AHB1ENR_DTCMRAMEN	|
						RCC_AHB1ENR_GPIOAEN		|
						RCC_AHB1ENR_GPIOBEN		|
						RCC_AHB1ENR_GPIOCEN		|
						RCC_AHB1ENR_GPIODEN		|
						RCC_AHB1ENR_GPIOEEN		|
						RCC_AHB1ENR_GPIOFEN		|
						RCC_AHB1ENR_GPIOGEN		|
						RCC_AHB1ENR_GPIOHEN		|
						RCC_AHB1ENR_GPIOIEN		|
						RCC_AHB1ENR_GPIOJEN		);
	
	RCC->AHB2ENR |= (	RCC_AHB2ENR_RNGEN		);

	RCC->APB1ENR |= (	RCC_APB1ENR_DACEN		|
						RCC_APB1ENR_SPI2EN		|
						RCC_APB1ENR_USART2EN	|
						RCC_APB1ENR_USART3EN	|
						RCC_APB1ENR_UART7EN		|
						RCC_APB1ENR_TIM2EN		|
                        RCC_APB1ENR_TIM3EN      |
						RCC_APB1ENR_TIM4EN		|
						RCC_APB1ENR_TIM5EN		);

	RCC->APB2ENR |= (	RCC_APB2ENR_ADC1EN		|
						RCC_APB2ENR_ADC2EN		|
						RCC_APB2ENR_SPI1EN		|
						RCC_APB2ENR_SYSCFGEN	|
						RCC_APB2ENR_USART1EN	|
                        RCC_APB2ENR_USART6EN	|
						RCC_APB2ENR_TIM1EN		|
                        RCC_APB2ENR_TIM8EN      );

	RCC->AHB3ENR |= (	RCC_AHB3ENR_FMCEN		);
}

extern uint32_t board_clkfreq( void )
{
    return SystemCoreClock;
}