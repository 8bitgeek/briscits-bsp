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
#include <brisc_thread.h>
#include <brisc_delay.h>
#include <rgb_led.h>
#include <xprintf.h>

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

static void sweep_delay(int* delay);

static void run_red  (void* arg);
static void run_green(void* arg);
static void run_blue (void* arg);
static void run_main (void* arg);


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
    int* delay = (int*)arg;
    for(EVER)
    {
        rgb_led_r(false);
        b_delay_ms(*delay);
        rgb_led_r(true);
        b_delay_ms(*delay);
    }

}

static void run_green(void* arg)
{
    int* delay = (int*)arg;
    for(EVER)
    {
        rgb_led_g(true);
        b_delay_ms(*delay);
        rgb_led_g(false);
        b_delay_ms(*delay);
    }

}

static void run_blue(void* arg)
{
    int* delay = (int*)arg;
    for(EVER)
    {
        rgb_led_b(false);
        b_delay_ms((*delay)*2);
        rgb_led_b(true);
        b_delay_ms((*delay)*2);
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
    char* thread_name;

    xprintf( "CLK = %f GHz\n", (float)board_clkfreq()/1000000000.0f );

    if ( (main_thread_handle  = b_thread_init( (thread_name="main") )) >= 0 )
    {
        if ( (red_thread_handle = b_thread_create( (thread_name="red"),   run_red,   &delay, red_stack,   STACK_WORDS )) >= 0)
        {
            if ( (green_thread_handle = b_thread_create( (thread_name="green"), run_green, &delay, green_stack, STACK_WORDS )) >= 0)
            {
                if ( (blue_thread_handle  = b_thread_create( (thread_name="blue"),  run_blue,  &delay, blue_stack,  STACK_WORDS )) >= 0)
                {
                    b_thread_start( red_thread_handle );
                    b_thread_start( green_thread_handle );
                    b_thread_start( blue_thread_handle );
                    run_main(&delay);
                }
            }
        }
    }
    
    xprintf( "failed to create '%s' thread\n\n", thread_name );

    return 0;
}