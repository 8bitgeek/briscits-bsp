#ifndef _BRISC_BOARD_H_
#define _BRISC_BOARD_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <ch32f103.h>
#include <core_riscv.h>
#include <cpu.h>

extern void     board_init( void );
extern uint32_t board_clkfreq( void );

extern bool     board_wdg_setup( uint32_t ms);
extern void     board_wdg_enable( void );
extern void     board_wdg_reload( void );

extern int      board_getchar( void );

#endif
