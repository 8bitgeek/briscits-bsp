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

Copyright (c) 2021 Mike Sharkey

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
#include <stm32f10x.h>
#include <core_cm3.h>
#include <stdbool.h>

static bool mcu_clock_setup_extern( void );
static void mcu_clock_setup( void );
// static void peripheral_clock_setup( void );

extern void _core_clock_init( void )
{
	if ( !mcu_clock_setup_extern() )
	{
		mcu_clock_setup();
	}
	peripheral_clock_setup();
}

static bool mcu_clock_set_pll(uint32_t mul)
{
	RCC->CFGR &= ~(0xF<<18);
	switch (mul)
	{
		case 3:		RCC->CFGR |= (0x1<<18); break;
		case 4:		RCC->CFGR |= (0x2<<18); break;
		case 5:		RCC->CFGR |= (0x3<<18); break;
		case 6:		RCC->CFGR |= (0x4<<18); break;
		case 7:		RCC->CFGR |= (0x5<<18); break;
		case 8:		RCC->CFGR |= (0x6<<18); break;
		case 9:		RCC->CFGR |= (0x7<<18); break;
		case 10:	RCC->CFGR |= (0x8<<18); break;
		case 11:	RCC->CFGR |= (0x9<<18); break;
		case 12:	RCC->CFGR |= (0xA<<18); break;
		case 13:	RCC->CFGR |= (0xB<<18); break;
		case 14:	RCC->CFGR |= (0xC<<18); break;
		case 15:	RCC->CFGR |= (0xD<<18); break;
		case 16:	RCC->CFGR |= (0xE<<18); break;
		case 17:	RCC->CFGR |= (0xF<<18); break; /* x16 */
		default:
			return false;
	}
	return true;
}

static bool mcu_clock_setup_extern( void )
{
	volatile uint32_t timeout;

	/* Enable External Oscillator */
	RCC->CR |= (RCC_CR_HSEBYP|RCC_CR_HSEON);
	for( timeout=10000; timeout > 0 && !(RCC->CR & RCC_CR_HSERDY); timeout-- );
	if ( timeout > 0 )
	{
		/* SYSCLK is  HSE */
		RCC->CFGR = RCC_CFGR_SW_HSE;

		/* Configure the PLL Source as 6.25MHz HSE/1 */
		RCC->CFGR |= RCC_CFGR_PLLSRC;

		/* Configure the PLL HSE Multiplier */
		mcu_clock_set_pll( HSE_PLLMUL );

		/* APB1 Can't exceed 36 MHz so HCLK / 2 */
		RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

		/* Enable PLLCLK */
		RCC->CR |= RCC_CR_PLLON;
		/* FIXME: timeout.... */
		while( !(RCC->CR & RCC_CR_PLLRDY) );				

		/* Configure FLASH Wait States (2WS required @ 68.75 MHz) */
		FLASH->ACR |= FLASH_ACR_LATENCY_2;

		/* Select PLL as clock source */
		RCC->CFGR |= RCC_CFGR_SW_PLL;
		RCC->CFGR &= ~RCC_CFGR_SW_HSE;
		
		/* FIXME: timeout..... */
		while((RCC->CFGR & RCC_CFGR_SWS)!=RCC_CFGR_SWS_PLL);

	   	SystemCoreClockUpdate();
	   	return true;
	}
	return false;
}

static void mcu_clock_setup( void )
{
    /* Enable Internal 8 MHz Oscillator/2 = 4 Mhz*/
    RCC->CR |= RCC_CR_HSION;
    while ( !(RCC->CR & RCC_CR_HSIRDY) );

    /* SYSCLK is 8MHz HSI */
    RCC->CFGR = RCC_CFGR_SW_HSI;

	/* Configure the PLL Source as 4MHz (HSI/2) */
	RCC->CFGR &= ~RCC_CFGR_PLLSRC;

	/* Configure the PLL Multiplier 4 MHz x 12 = 48 MHz */
	RCC->CFGR |= RCC_CFGR_PLLMULL_3 | RCC_CFGR_PLLMULL_1;

	/* Enable PLLCLK */
	RCC->CR |= RCC_CR_PLLON;
	/* FIXME: timeout.... */
	while( !(RCC->CR & RCC_CR_PLLRDY) );						

	/* Configure FLASH Wait States (1WS required @ 48 MHz) */
	FLASH->ACR |= FLASH_ACR_LATENCY_1;

	/* Select PLL as clock source */
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	RCC->CFGR &= ~RCC_CFGR_SW_HSE;

	/* FIXME: timeout..... */
	while((RCC->CFGR & RCC_CFGR_SWS)!=RCC_CFGR_SWS_PLL);

	SystemCoreClockUpdate();
}

// static void peripheral_clock_setup( void )
// {
// 	RCC->AHBENR		|=	RCC_AHBENR_CLOCKS;
// 	RCC->APB1ENR 	|= 	RCC_APB1ENR_CLOCKS;
// 	RCC->APB2ENR 	|= 	RCC_APB2ENR_CLOCKS;
// }