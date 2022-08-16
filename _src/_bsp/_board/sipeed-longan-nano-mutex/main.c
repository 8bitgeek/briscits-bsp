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
#include <brisc_mutex.h>
#include <xprintf.h>
#include <string.h>

#define MAX_TEXT        (64)
#define MAX_NAME        (8)
#define MAX_WORKERS     (2)
#define MIN_DELAY       (2)
#define MAX_DELAY       (50)

#define EVER            ;;
#define STACK_BYTES     (1024)
#define STACK_WORDS     STACK_BYTES / sizeof(cpu_reg_t)

static brisc_mutex_t    thread_lock;

typedef struct
{  
    cpu_reg_t       stack[ STACK_WORDS ];
    int             thread_handle;
    char            name[ MAX_NAME ];
    int             delay;
    char            text[ MAX_TEXT ];
    brisc_mutex_t*  lock;
    bool            do_lock;
} thread_data_t;

static void start_threads( thread_data_t thread_data_array[] );
static void run_main     ( thread_data_t thread_data_array[] );
static void run_worker   ( void* arg );


static void run_worker(void* arg)
{
    thread_data_t* thread_data = (thread_data_t* )arg;

    for(EVER)
    {   
        bool do_lock = thread_data->do_lock;

        if ( do_lock )
            b_mutex_lock( thread_data->lock );
        
        xprintf( "%s", thread_data->text );
        
        if ( do_lock ) 
            b_mutex_unlock( thread_data->lock );
        
        b_delay_ms( thread_data->delay );
    }
}


static void run_main( thread_data_t thread_data_array[] )
{
    for(EVER)
    {
        int ch = xfunc_in();
        if ( ch == 'm' || ch == 'M' )
        {
            for(int n=0; n < MAX_WORKERS; n++)
            {
                thread_data_t* thread_data = &thread_data_array[n];
                thread_data->do_lock = !thread_data->do_lock;
            }
        }
        b_thread_yield();
    }
}

static void start_threads( thread_data_t thread_data_array[] )
{
    b_mutex_init(&thread_lock);

    for(int n=0; n < MAX_WORKERS; n++)
    {
        thread_data_t* thread_data = &thread_data_array[n];
        
        memset( thread_data, 0, sizeof(thread_data_t) );

        thread_data->lock = &thread_lock;
        thread_data->delay = MIN_DELAY;
        xsprintf( thread_data->name, "thrd%d", n );
        xsprintf( thread_data->text, "this is thread number thrd%d\n", n );

        thread_data->thread_handle = b_thread_create(
                                        thread_data->name,
                                        run_worker,
                                        thread_data,
                                        thread_data->stack,
                                        STACK_WORDS ); 

        b_thread_start( thread_data->thread_handle );
    }
}

int main( void )
{
    thread_data_t thread_data_array[ MAX_WORKERS ];

    b_thread_init( "main" );
    xprintf( "CLK = %f GHz\n", (float)board_clkfreq()/1000000000.0f );
    start_threads( thread_data_array );
    run_main( thread_data_array );

    return 0;
}