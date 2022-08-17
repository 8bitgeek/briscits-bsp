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
#include <brisc_thread.h>

#if !defined(HW_WD_TO)
	#define HW_WD_TO        (100)
#endif 

#if !defined(SW_WD_TO)
	#define SW_WD_TO        (50)
#endif

#if !defined(THREAD_STK_SZ)
	#define THREAD_STK_SZ	(1024*4)
#endif

static uint32_t	feature_stack[ THREAD_STK_SZ/sizeof(uint32_t) ];
static int 		feature_thread_handle  = (-1);
static int 		main_thread_handle  = (-1);

static void 	watchdog_cb(int id);
static void 	blocking_cb(void);

extern void __attribute__((weak)) feature_main( void* arg );
extern void __attribute__((weak)) board_idle( void );

extern int main(void)
{
   if ( (main_thread_handle  = b_thread_init( "main" )) >= 0 )
    {
        watchdog_setup(HW_WD_TO);
        watchdog_enable();
        b_thread_set_block_fn(blocking_cb);
        watchdog_set_callback_fn(watchdog_cb);

        watchdog_thread_setup( main_thread_handle, SW_WD_TO );
        watchdog_thread_enable( main_thread_handle );

        if ( (feature_thread_handle = b_thread_create( "feature_main", feature_main, NULL, feature_stack, THREAD_STK_SZ )) >= 0)
        {
            watchdog_thread_setup( feature_thread_handle, SW_WD_TO );
            watchdog_thread_enable( feature_thread_handle );
            
            b_thread_start( feature_thread_handle );
            board_idle();
        }
    }
	return 0;
}

static void watchdog_cb(int id)
{
    xprintf( "w/d t/o %d\n", id );
}

static void blocking_cb(void)
{
    int id = b_thread_current_id();
    if ( id == 0 )
        watchdog_thread_reload( 0 );
    else
        watchdog_thread_reload( id );
}

void* _sbrk ( int incr )
{
	/** trap stdlib linkages */
	chip_reset();
	return NULL;
}

void feature_main( void* arg )
{
    for(;;);
}

void board_idle( void )
{
    for(;;)
	{
		b_thread_yield();
	}
}
