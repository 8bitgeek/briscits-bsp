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
#include <string.h>

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

typedef struct _app_state_ {
    float red_count;
    float green_count;
    float blue_count;
    float main_count;
} app_state_t;

app_state_t app_state;

static void run_red  (void* arg);
static void run_green(void* arg);
static void run_blue (void* arg);
static void run_main (void* arg);

static void run_red(void* arg)
{
    brisc_systick_t timeout_start=b_thread_systick();

    for(EVER)
    {
        if ( b_thread_systick() - timeout_start >= 1 )
        {
            app_state.red_count += 0.001f;
            timeout_start=b_thread_systick();
        }
        b_thread_yield();
    }
}

static void run_green(void* arg)
{
    brisc_systick_t timeout_start=b_thread_systick();

    for(EVER)
    {
        if ( b_thread_systick() - timeout_start >= 1 )
        {
            app_state.green_count += 0.001f;
            timeout_start=b_thread_systick();
        }
        b_thread_yield();
    }
}

static void run_blue(void* arg)
{
    brisc_systick_t timeout_start=b_thread_systick();

    for(EVER)
    {
        if ( b_thread_systick() - timeout_start >= 1 )
        {
            app_state.blue_count += 0.001f;
            timeout_start=b_thread_systick();
        }
        b_thread_yield();
    }
}


static void run_main(void* arg)
{
    brisc_systick_t timeout_start=b_thread_systick();

    for(EVER)
    {
        if ( b_thread_systick() - timeout_start >= 1 )
        {
            app_state.main_count = app_state.red_count + app_state.green_count + app_state.blue_count;
            timeout_start=b_thread_systick();
        }
        b_thread_yield();
    }
}


int main( void )
{
    memset(&app_state,0,sizeof(app_state_t));
    if ( (main_thread_handle  = b_thread_init( "main" )) >= 0 )
    {
        if ( (red_thread_handle = b_thread_create( "red", run_red, NULL, red_stack, STACK_WORDS )) >= 0)
        {
            if ( (green_thread_handle = b_thread_create( "green", run_green, NULL, green_stack, STACK_WORDS )) >= 0)
            {
                if ( (blue_thread_handle = b_thread_create( "blue", run_blue, NULL, blue_stack, STACK_WORDS )) >= 0)
                {
                    b_thread_start( red_thread_handle );
                    b_thread_start( blue_thread_handle );
                    b_thread_start( green_thread_handle );
                    run_main( NULL );
                }
            }
        }
    }
    return 0;
}