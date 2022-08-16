#include <brisc_board.h>
#include <string.h>

void brisc_timer_init( void ) 
{
    SystemInit();

    /* Disable interrupts globally. */
    clear_csr( mstatus, MSTATUS_MIE );
    clear_csr( mstatus, MSTATUS_SIE );

    /* Calculate the SyssTick timer reload register to get a 1 millisecond tick */
    SysTick_SetReload(SYSTICK_HZ/1000);
    SysTick_SetCount(0);

    /* Enable the SysTick Interrupt */
    SysTick_EnableIRQ();
    NVIC_EnableIRQ(SysTicK_IRQn);

    /* Re-enable interrupts globally */
    set_csr( mstatus, MSTATUS_MIE );
    set_csr( mstatus, MSTATUS_SIE );

    /* Start the SysTick timmer */
    SysTick_Enable();
}
