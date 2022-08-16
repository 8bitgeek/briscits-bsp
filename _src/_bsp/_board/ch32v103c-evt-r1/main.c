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
#include <brisc_delay.h>
#include <rgb_led.h>
#include <xprintf.h>
#include <watchdog.h>

#define HW_WD_TO        (100)
#define SW_WD_TO        (50)

#define DEC_DELAY       (2)
#define INC_DELAY       DEC_DELAY
#define MIN_DELAY       (2)
#define MAX_DELAY       (50)

#define EVER            ;;
#define STACK_BYTES     (1024)
#define STACK_WORDS     STACK_BYTES / sizeof(cpu_reg_t)

static cpu_reg_t red_stack   [ STACK_WORDS ];
static cpu_reg_t green_stack [ STACK_WORDS ];
static cpu_reg_t blue_stack  [ STACK_WORDS ];

static int red_thread_handle   = (-1);
static int green_thread_handle = (-1);
static int blue_thread_handle  = (-1);
static int main_thread_handle  = (-1);

static void input( void );
static void sweep_delay(int* delay);
static void blocking_cb(void);
static void run_red  (void* arg);
static void run_green(void* arg);
static void run_blue (void* arg);
static void run_main (void* arg);

static void input( void )
{
    if ( xgetchar() == 'w' )
        for(;;);
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

static void sweep_delay(int* delay)
{
    static bool dir=false;

    if ( dir )
    {
        *delay = *delay + INC_DELAY;
        if ( *delay >= MAX_DELAY )
            dir = !dir;
    }
    if ( !dir )
    {
        *delay = *delay - DEC_DELAY;
        if ( *delay <= MIN_DELAY )
            dir = !dir;
    }
} 

static void run_red(void* arg)
{
    for(EVER)
    {
        int* delay = (int*)arg;
        
        rgb_led_r(false);
        b_delay_ms(*delay);
        rgb_led_r(true);
        b_delay_ms(*delay);
        input();
    }
}

static void run_green(void* arg)
{
    for(EVER)
    {
        int* delay = (int*)arg;
        
        rgb_led_g(true);
        b_delay_ms(*delay);
        rgb_led_g(false);
        b_delay_ms(*delay);
        input();
    }
}

static void run_blue(void* arg)
{
    for(EVER)
    {
        int* delay = (int*)arg;
        
        rgb_led_b(false);
        b_delay_ms((*delay)*2);
        rgb_led_b(true);
        b_delay_ms((*delay)*2);
        input();
    }
}

// 'main' thread - sweeps the delay
static void run_main(void* arg)
{
    int* delay = (int*)arg;
    for(EVER)
    {
        sweep_delay(delay);
        b_delay_ms((*delay)*2);
    }
}

int main( void )
{
    int delay = MAX_DELAY;

    if ( (main_thread_handle  = b_thread_init( "main" )) >= 0 )
    {
        watchdog_setup(HW_WD_TO);
        watchdog_enable();
        b_thread_set_block_fn(blocking_cb);
        watchdog_set_callback_fn(watchdog_cb);

        watchdog_thread_setup( main_thread_handle, SW_WD_TO );
        watchdog_thread_enable( main_thread_handle );

        xprintf( "CLK = %f GHz\n", (float)board_clkfreq()/1000000000.0f );
        xprintf( "Press 'w' to trigger watchdog timeout...\n" );

        if ( (red_thread_handle = b_thread_create( "red", run_red, &delay, red_stack, STACK_WORDS )) >= 0)
        {
            watchdog_thread_setup( red_thread_handle, SW_WD_TO );
            watchdog_thread_enable( red_thread_handle );
            if ( (green_thread_handle = b_thread_create( "green", run_green, &delay, green_stack, STACK_WORDS )) >= 0)
            {
                watchdog_thread_setup( green_thread_handle, SW_WD_TO );
                watchdog_thread_enable( green_thread_handle );
                if ( (blue_thread_handle = b_thread_create( "blue", run_blue, &delay, blue_stack, STACK_WORDS )) >= 0)
                {
                    watchdog_thread_setup( blue_thread_handle, SW_WD_TO );
                    watchdog_thread_enable( blue_thread_handle );

                    b_thread_start( red_thread_handle );
                    b_thread_start( blue_thread_handle );
                    b_thread_start( green_thread_handle );
        
                    run_main( &delay );
                }
            }
        }
    }
    
    xprintf( "failed to create a thread\n\n" );

    return 0;
}