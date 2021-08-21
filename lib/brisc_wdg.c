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
#include <brisc_wdg.h>

typedef struct brisc_wdg
{
    uint32_t    wdg_timeout;    /**< Timeout in jiffies */
    uint32_t    wdg_count_down; /**< Timeout count down to zero */
    bool        enabled;
} brisc_wdg_t __attribute__ ((aligned (8)));

static brisc_wdg_t brisc_wdg[BRISC_THREAD_MAX];

static void b_hw_wdg_service( void );

extern void b_hw_wdg_setup( uint32_t ms )
{
    memset(brisc_wdg,0,sizeof(brisc_wdg));
    b_thread_set_systick_fn(b_hw_wdg_service);
    board_wdg_setup( ms );
}

extern void b_hw_wdg_enable( void )
{
    board_wdg_enable();
}

extern void b_hw_wdg_reload( void )
{
    board_wdg_reload();
}

/** ***************************************************************************
 * @brief Reload the h/w watchdog timer.
******************************************************************************/
static void b_hw_wdg_service( void )
{
    bool checked_in=true;
    for( int id=0; checked_in && id < BRISC_THREAD_MAX; id++ )
    {
        brisc_wdg_t* wd = &brisc_wdg[id];
        if ( wd->enabled )
        {
            if ( wd->wdg_count_down == 0 || 
                    wd->wdg_count_down > brisc_wdg[id].wdg_timeout )
                checked_in=false;
            else
                --wd->wdg_count_down;
    }
    if ( checked_in )
        b_hw_wdg_reload();
}

extern void b_hw_wdg_thread_setup( int id, uint32_t ms )
{
    brisc_wdg[id].wdg_count_down = brisc_wdg[id].wdg_timeout = ms;
}

extern void b_hw_wdg_thread_enable( int id )
{
    brisc_wdg[id].enabled=true;
}

extern void b_hw_wdg_thread_reload( int id )
{
    brisc_wdg[id].wdg_count_down = brisc_wdg[id].wdg_timeout;
}

