/*
 */

#include "port.h"
#include "mb.h"
#include "mbport.h"

#include <caribou/kernel/timer.h>

void prvvTIMERExpiredISR( void );

static caribou_tick_t soft_timer_period=0L;
static caribou_tick_t soft_timer_start=0; 
static bool soft_timer_enabled=false;

BOOL xMBPortTimersInit( USHORT usTim1Timerout50us )
{
    soft_timer_period = usTim1Timerout50us;
    return TRUE;
}

void vMBPortTimersEnable(  )
{
    /* Enable the timer with the timeout passed to xMBPortTimersInit( ) */
    soft_timer_start=caribou_timer_ticks();
    soft_timer_enabled=true;
}

void vMBPortTimersDisable(  )
{
    /* Disable any pending timers. */
    soft_timer_enabled=false;
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
void prvvTIMERExpiredISR( void )
{
    if( soft_timer_enabled )
    {
        if ( caribou_timer_ticks()-soft_timer_start > soft_timer_period )
        {
            pxMBPortCBTimerExpired();
        }
    }
}

