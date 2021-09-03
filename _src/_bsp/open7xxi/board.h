 
#ifndef _BOARD_H_
#define _BOARD_H_

#include <hw_defs.h>
#include <hw_clocks.h>
#include <hw_gpio.h>

#include "stm32f7xx_hal.h"
#include <stm32f746xx.h>
#include <core_cm7.h>
#include <cpu.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern void early_init ( void );
extern void late_init ( void );
extern void caribou_hw_init ( void );

extern uint32_t HAL_GetTick();

#ifdef __cplusplus
}
#endif


#endif
