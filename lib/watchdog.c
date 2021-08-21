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
#include <watchdog.h>
#include <brisc_board.h>
#include <string.h>

typedef struct watchdog
{
    uint32_t    wdg_timeout;    /**< Timeout in jiffies */
    uint32_t    wdg_count_down; /**< Timeout count down to zero */
    bool        enabled;
} watchdog_t;

typedef struct
{
    watchdog_t watchdog[BRISC_THREAD_MAX];
    void (*watchdog_cb_fn)(int);
} watchdog_state_t;

static watchdog_state_t watchdog_state;

static void watchdog_service( void );

extern void watchdog_setup( uint32_t ms )
{
    memset(&watchdog_state,0,sizeof(watchdog_state));
    b_thread_set_yield_fn(watchdog_service);
    board_wdg_setup( ms );
}

extern void watchdog_enable( void )
{
    board_wdg_enable();
}

extern void watchdog_reload( void )
{
    board_wdg_reload();
}

extern void watchdog_set_callback_fn(void (*watchdog_cb_fn)(int) )
{
    watchdog_state.watchdog_cb_fn = watchdog_cb_fn;
}

/** ***************************************************************************
 * @brief Reload the h/w watchdog timer.
******************************************************************************/
static void watchdog_service( void )
{
    bool checked_in=true;
    for( int id=0; id < BRISC_THREAD_MAX; id++ )
    {
        watchdog_t* wd = &watchdog_state.watchdog[id];
        if ( wd->enabled )
        {
            if ( wd->wdg_count_down )
                --wd->wdg_count_down;

            if ( wd->wdg_count_down == 0 || wd->wdg_count_down > wd->wdg_timeout )
            {
                if ( watchdog_state.watchdog_cb_fn )
                    watchdog_state.watchdog_cb_fn(id);
                checked_in=false;
            }
        }
    }
    if ( checked_in )
        watchdog_reload();
}

extern void watchdog_thread_setup( int id, uint32_t ms )
{
    watchdog_t* wd = &watchdog_state.watchdog[id];
    wd->wdg_count_down = wd->wdg_timeout = ms;
}

extern void watchdog_thread_enable( int id )
{
    watchdog_t* wd = &watchdog_state.watchdog[id];
    wd->enabled=true;
}

extern void watchdog_thread_reload( int id )
{
    watchdog_t* wd = &watchdog_state.watchdog[id];
    if ( wd->enabled && id)
        wd->wdg_count_down = wd->wdg_timeout;
}

