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
#include "riscv_encoding.h"

    .global brisc_isr_yield     // eclic_msip_handler
    .global brisc_isr_systick   // eclic_mtip_handler
    .global default_interrupt_handler
    .global reset_handler

    /*
    * Main vector table entries.
    */
    .global vtable
    .type vtable, %object
    .section .vector_table,"a",%progbits
vtable:
    jal briscits_reset_handler
    .align 2
    .word 0
    .word 0
    .word brisc_isr_yield       // eclic_msip_handler
    .word 0
    .word 0
    .word 0
    .word brisc_isr_systick     // eclic_mtip_handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    /* external interrupts  */
    .word eclic_bwei_handler
    .word eclic_pmovi_handler
    .word watchdog_IRQn_handler
    .word LVD_IRQn_handler
    .word tamper_IRQn_handler
    .word RTC_IRQn_handler
    .word FMC_IRQn_handler
    .word RCU_IRQn_handler
    .word EXTI0_IRQn_handler
    .word EXTI1_IRQn_handler
    .word EXTI2_IRQn_handler
    .word EXTI3_IRQn_handler
    .word EXTI4_IRQn_handler
    .word DMA0_chan0_IRQn_handler
    .word DMA0_chan1_IRQn_handler
    .word DMA0_chan2_IRQn_handler
    .word DMA0_chan3_IRQn_handler
    .word DMA0_chan4_IRQn_handler
    .word DMA0_chan5_IRQn_handler
    .word DMA0_chan6_IRQn_handler
    .word ADC0_1_IRQn_handler
    .word CAN0_TX_IRQn_handler
    .word CAN0_RX0_IRQn_handler
    .word CAN0_RX1_IRQn_handler
    .word CAN0_EWMC_IRQn_handler
    .word EXTI5_9_IRQn_handler
    .word TIM0_break_IRQn_handler
    .word TIM0_update_IRQn_handler
    .word TIM0_trigger_commutation_IRQn_handler
    .word TIM0_channel_IRQn_handler
    .word TIM1_IRQn_handler
    .word TIM2_IRQn_handler
    .word TIM3_IRQn_handler
    .word I2C0_EV_IRQn_handler
    .word I2C0_ER_IRQn_handler
    .word I2C1_EV_IRQn_handler
    .word I2C1_ER_IRQn_handler
    .word SPI0_IRQn_handler
    .word SPI1_IRQn_handler
    .word USART0_IRQn_handler
    .word USART1_IRQn_handler
    .word USART2_IRQn_handler
    .word EXTI10_15_IRQn_handler
    .word RTC_alarm_IRQn_handler
    .word USB_wakeup_IRQn_handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word EXMC_IRQn_handler
    .word 0
    .word TIM4_IRQn_handler
    .word SPI2_IRQn_handler
    .word UART3_IRQn_handler
    .word UART4_IRQn_handler
    .word TIM5_IRQn_handler
    .word TIM6_IRQn_handler
    .word DMA1_chan0_IRQn_handler
    .word DMA1_chan1_IRQn_handler
    .word DMA1_chan2_IRQn_handler
    .word DMA1_chan3_IRQn_handler
    .word DMA1_chan4_IRQn_handler
    .word 0
    .word 0
    .word CAN1_TX_IRQn_handler
    .word CAN1_RX0_IRQn_handler
    .word CAN1_RX1_IRQn_handler
    .word CAN1_EWMC_IRQn_handler
    .word USB_IRQn_handler

    /*
    * Weak aliases to point each exception hadnler to the
    * 'default_interrupt_handler', unless the application defines
    * a function with the same name to override the reference.
    */
    .weak eclic_bwei_handler
    .set  eclic_bwei_handler,default_interrupt_handler
    .weak eclic_pmovi_handler
    .set  eclic_pmovi_handler,default_interrupt_handler
    .weak watchdog_IRQn_handler
    .set  watchdog_IRQn_handler,default_interrupt_handler
    .weak LVD_IRQn_handler
    .set  LVD_IRQn_handler,default_interrupt_handler
    .weak tamper_IRQn_handler
    .set  tamper_IRQn_handler,default_interrupt_handler
    .weak RTC_IRQn_handler
    .set  RTC_IRQn_handler,default_interrupt_handler
    .weak FMC_IRQn_handler
    .set  FMC_IRQn_handler,default_interrupt_handler
    .weak RCU_IRQn_handler
    .set  RCU_IRQn_handler,default_interrupt_handler
    .weak EXTI0_IRQn_handler
    .set  EXTI0_IRQn_handler,default_interrupt_handler
    .weak EXTI1_IRQn_handler
    .set  EXTI1_IRQn_handler,default_interrupt_handler
    .weak EXTI2_IRQn_handler
    .set  EXTI2_IRQn_handler,default_interrupt_handler
    .weak EXTI3_IRQn_handler
    .set  EXTI3_IRQn_handler,default_interrupt_handler
    .weak EXTI4_IRQn_handler
    .set  EXTI4_IRQn_handler,default_interrupt_handler
    .weak DMA0_chan0_IRQn_handler
    .set  DMA0_chan0_IRQn_handler,default_interrupt_handler
    .weak DMA0_chan1_IRQn_handler
    .set  DMA0_chan1_IRQn_handler,default_interrupt_handler
    .weak DMA0_chan2_IRQn_handler
    .set  DMA0_chan2_IRQn_handler,default_interrupt_handler
    .weak DMA0_chan3_IRQn_handler
    .set  DMA0_chan3_IRQn_handler,default_interrupt_handler
    .weak DMA0_chan4_IRQn_handler
    .set  DMA0_chan4_IRQn_handler,default_interrupt_handler
    .weak DMA0_chan5_IRQn_handler
    .set  DMA0_chan5_IRQn_handler,default_interrupt_handler
    .weak DMA0_chan6_IRQn_handler
    .set  DMA0_chan6_IRQn_handler,default_interrupt_handler
    .weak ADC0_1_IRQn_handler
    .set  ADC0_1_IRQn_handler,default_interrupt_handler
    .weak CAN0_TX_IRQn_handler
    .set  CAN0_TX_IRQn_handler,default_interrupt_handler
    .weak CAN0_RX0_IRQn_handler
    .set  CAN0_RX0_IRQn_handler,default_interrupt_handler
    .weak CAN0_RX1_IRQn_handler
    .set  CAN0_RX1_IRQn_handler,default_interrupt_handler
    .weak CAN0_EWMC_IRQn_handler
    .set  CAN0_EWMC_IRQn_handler,default_interrupt_handler
    .weak EXTI5_9_IRQn_handler
    .set  EXTI5_9_IRQn_handler,default_interrupt_handler
    .weak TIM0_break_IRQn_handler
    .set  TIM0_break_IRQn_handler,default_interrupt_handler
    .weak TIM0_update_IRQn_handler
    .set  TIM0_update_IRQn_handler,default_interrupt_handler
    .weak TIM0_trigger_commutation_IRQn_handler
    .set  TIM0_trigger_commutation_IRQn_handler,default_interrupt_handler
    .weak TIM0_channel_IRQn_handler
    .set  TIM0_channel_IRQn_handler,default_interrupt_handler
    .weak TIM1_IRQn_handler
    .set  TIM1_IRQn_handler,default_interrupt_handler
    .weak TIM2_IRQn_handler
    .set  TIM2_IRQn_handler,default_interrupt_handler
    .weak TIM3_IRQn_handler
    .set  TIM3_IRQn_handler,default_interrupt_handler
    .weak I2C0_EV_IRQn_handler
    .set  I2C0_EV_IRQn_handler,default_interrupt_handler
    .weak I2C0_ER_IRQn_handler
    .set  I2C0_ER_IRQn_handler,default_interrupt_handler
    .weak I2C1_EV_IRQn_handler
    .set  I2C1_EV_IRQn_handler,default_interrupt_handler
    .weak I2C1_ER_IRQn_handler
    .set  I2C1_ER_IRQn_handler,default_interrupt_handler
    .weak SPI0_IRQn_handler
    .set  SPI0_IRQn_handler,default_interrupt_handler
    .weak SPI1_IRQn_handler
    .set  SPI1_IRQn_handler,default_interrupt_handler
    .weak USART0_IRQn_handler
    .set  USART0_IRQn_handler,default_interrupt_handler
    .weak USART1_IRQn_handler
    .set  USART1_IRQn_handler,default_interrupt_handler
    .weak USART2_IRQn_handler
    .set  USART2_IRQn_handler,default_interrupt_handler
    .weak EXTI10_15_IRQn_handler
    .set  EXTI10_15_IRQn_handler,default_interrupt_handler
    .weak RTC_alarm_IRQn_handler
    .set  RTC_alarm_IRQn_handler,default_interrupt_handler
    .weak USB_wakeup_IRQn_handler
    .set  USB_wakeup_IRQn_handler,default_interrupt_handler
    .weak EXMC_IRQn_handler
    .set  EXMC_IRQn_handler,default_interrupt_handler
    .weak TIM4_IRQn_handler
    .set  TIM4_IRQn_handler,default_interrupt_handler
    .weak SPI2_IRQn_handler
    .set  SPI2_IRQn_handler,default_interrupt_handler
    .weak UART3_IRQn_handler
    .set  UART3_IRQn_handler,default_interrupt_handler
    .weak UART4_IRQn_handler
    .set  UART4_IRQn_handler,default_interrupt_handler
    .weak TIM5_IRQn_handler
    .set  TIM5_IRQn_handler,default_interrupt_handler
    .weak TIM6_IRQn_handler
    .set  TIM6_IRQn_handler,default_interrupt_handler
    .weak DMA1_chan0_IRQn_handler
    .set  DMA1_chan0_IRQn_handler,default_interrupt_handler
    .weak DMA1_chan1_IRQn_handler
    .set  DMA1_chan1_IRQn_handler,default_interrupt_handler
    .weak DMA1_chan2_IRQn_handler
    .set  DMA1_chan2_IRQn_handler,default_interrupt_handler
    .weak DMA1_chan3_IRQn_handler
    .set  DMA1_chan3_IRQn_handler,default_interrupt_handler
    .weak DMA1_chan4_IRQn_handler
    .set  DMA1_chan4_IRQn_handler,default_interrupt_handler
    .weak CAN1_TX_IRQn_handler
    .set  CAN1_TX_IRQn_handler,default_interrupt_handler
    .weak CAN1_RX0_IRQn_handler
    .set  CAN1_RX0_IRQn_handler,default_interrupt_handler
    .weak CAN1_RX1_IRQn_handler
    .set  CAN1_RX1_IRQn_handler,default_interrupt_handler
    .weak CAN1_EWMC_IRQn_handler
    .set  CAN1_EWMC_IRQn_handler,default_interrupt_handler
    .weak USB_IRQn_handler
    .set  USB_IRQn_handler,default_interrupt_handler

