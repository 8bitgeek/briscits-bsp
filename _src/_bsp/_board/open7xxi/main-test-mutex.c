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

#define EVER            ;;
#define STACK_BYTES     (1024)
#define STACK_WORDS     STACK_BYTES / sizeof(cpu_reg_t)

static cpu_reg_t black_stack [ STACK_WORDS ];
static cpu_reg_t white_stack [ STACK_WORDS ];

static int black_handle = (-1);
static int white_handle = (-1);
static int main_handle  = (-1);

static void run_black (void* arg);
static void run_white (void* arg);
static void run_main (void* arg);

static char buf[256];
static BRISC_MUTEX_DECL(mutex);

static void run_black(void* arg)
{
    for(EVER)
    {
        b_mutex_lock(&mutex);
        strcpy(buf,"black");
        b_thread_yield();
        if ( strcmp(buf,"black") != 0 )
            xprintf("got '%s' expected 'black'", buf);
        b_mutex_unlock(&mutex);
    }
}

static void run_white(void* arg)
{
    for(EVER)
    {
        b_mutex_lock(&mutex);
        strcpy(buf,"white");
        b_thread_yield();
        if ( strcmp(buf,"white") != 0 )
            xprintf("got '%s' expected 'white'", buf);
        b_mutex_unlock(&mutex);
    }
}

static void run_main(void* arg)
{
    for(EVER)
    {
        b_mutex_lock(&mutex);
        strcpy(buf,"main");
        b_thread_yield();
        if ( strcmp(buf,"main") != 0 )
            xprintf("got '%s' expected 'main'", buf);
        b_mutex_unlock(&mutex);
    }
}

int main( void )
{
    char* name;

    if ( (main_handle  = b_thread_init( (name="main") )) >= 0 )
    {
        if ( (black_handle = b_thread_create( (name="red"), run_black, NULL, black_stack, STACK_WORDS )) >= 0)
        {
            if ( (white_handle = b_thread_create( (name="green"), run_white, NULL, white_stack, STACK_WORDS )) >= 0)
            {
                b_thread_start( black_handle );
                b_thread_start( white_handle );
                run_main(NULL);
            }
        }
    }
    
    xprintf( "failed to create '%s' thread\n\n", name );

    return 0;
}