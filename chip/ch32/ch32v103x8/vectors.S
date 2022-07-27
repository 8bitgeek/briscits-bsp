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

    .global brisc_isr_yield    
    .global brisc_isr_systick   
    .global default_interrupt_handler
    .global reset_handler

    /*
    * Main vector table entries.
    */
    .global vtable
    .type vtable, %object
    .section .vector_table,"a",%progbits
vtable:
    .align 2
    jal briscits_reset_handler
    .word 0
    .word nmi_isr_handler       // non-maskable interrupt
    .word fault_isr_handler     // hard fault interrupt
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word brisc_isr_systick     // systick isr handler
    .word 0
    .word brisc_isr_yield       // swi_isr_handler  
    .word 0
    /* external interrupts  */
    .word  WWDG_IRQHandler            /* Window Watchdog */
    .word  PVD_IRQHandler             /* PVD through EXTI Line detect */
    .word  TAMPER_IRQHandler          /* TAMPER */
    .word  RTC_IRQHandler             /* RTC */
    .word  FLASH_IRQHandler           /* Flash */
    .word  RCC_IRQHandler             /* RCC */
    .word  EXTI0_IRQHandler           /* EXTI Line 0 */
    .word  EXTI1_IRQHandler           /* EXTI Line 1 */
    .word  EXTI2_IRQHandler           /* EXTI Line 2 */
    .word  EXTI3_IRQHandler           /* EXTI Line 3 */
    .word  EXTI4_IRQHandler           /* EXTI Line 4 */
    .word  DMA1_Channel1_IRQHandler   /* DMA1 Channel 1 */
    .word  DMA1_Channel2_IRQHandler   /* DMA1 Channel 2 */
    .word  DMA1_Channel3_IRQHandler   /* DMA1 Channel 3 */
    .word  DMA1_Channel4_IRQHandler   /* DMA1 Channel 4 */
    .word  DMA1_Channel5_IRQHandler   /* DMA1 Channel 5 */
    .word  DMA1_Channel6_IRQHandler   /* DMA1 Channel 6 */
    .word  DMA1_Channel7_IRQHandler   /* DMA1 Channel 7 */
    .word  ADC1_2_IRQHandler          /* ADC1_2 */
    .word   0
    .word   0
    .word   0
    .word   0
    .word  EXTI9_5_IRQHandler         /* EXTI Line 9..5 */
    .word  TIM1_BRK_IRQHandler        /* TIM1 Break */
    .word  TIM1_UP_IRQHandler         /* TIM1 Update */
    .word  TIM1_TRG_COM_IRQHandler    /* TIM1 Trigger and Commutation */
    .word  TIM1_CC_IRQHandler         /* TIM1 Capture Compare */
    .word  TIM2_IRQHandler            /* TIM2 */
    .word  TIM3_IRQHandler            /* TIM3 */
    .word  TIM4_IRQHandler            /* TIM4 */
    .word  I2C1_EV_IRQHandler         /* I2C1 Event */
    .word  I2C1_ER_IRQHandler         /* I2C1 Error */
    .word  I2C2_EV_IRQHandler         /* I2C2 Event */
    .word  I2C2_ER_IRQHandler         /* I2C2 Error */
    .word  SPI1_IRQHandler            /* SPI1 */
    .word  SPI2_IRQHandler            /* SPI2 */
    .word  USART1_IRQHandler          /* USART1 */
    .word  USART2_IRQHandler          /* USART2 */
    .word  USART3_IRQHandler          /* USART3 */
    .word  EXTI15_10_IRQHandler       /* EXTI Line 15..10 */
    .word  RTCAlarm_IRQHandler        /* RTC Alarm through EXTI Line */
    .word  USBWakeUp_IRQHandler       /* USB Wakeup from suspend */
    .word  USBHD_IRQHandler           /* USBHD */

    .option rvc;

    .section    .text.vector_handler, "ax", @progbits
    .weak   NMI_Handler
    .weak   HardFault_Handler
    .weak   SysTick_Handler
    .weak   SW_handler
    .weak   WWDG_IRQHandler
    .weak   PVD_IRQHandler
    .weak   TAMPER_IRQHandler
    .weak   RTC_IRQHandler
    .weak   FLASH_IRQHandler
    .weak   RCC_IRQHandler
    .weak   EXTI0_IRQHandler
    .weak   EXTI1_IRQHandler
    .weak   EXTI2_IRQHandler
    .weak   EXTI3_IRQHandler
    .weak   EXTI4_IRQHandler
    .weak   DMA1_Channel1_IRQHandler
    .weak   DMA1_Channel2_IRQHandler
    .weak   DMA1_Channel3_IRQHandler
    .weak   DMA1_Channel4_IRQHandler
    .weak   DMA1_Channel5_IRQHandler
    .weak   DMA1_Channel6_IRQHandler
    .weak   DMA1_Channel7_IRQHandler
    .weak   ADC1_2_IRQHandler
    .weak   EXTI9_5_IRQHandler
    .weak   TIM1_BRK_IRQHandler
    .weak   TIM1_UP_IRQHandler
    .weak   TIM1_TRG_COM_IRQHandler
    .weak   TIM1_CC_IRQHandler
    .weak   TIM2_IRQHandler
    .weak   TIM3_IRQHandler
    .weak   TIM4_IRQHandler
    .weak   I2C1_EV_IRQHandler
    .weak   I2C1_ER_IRQHandler
    .weak   I2C2_EV_IRQHandler
    .weak   I2C2_ER_IRQHandler
    .weak   SPI1_IRQHandler
    .weak   SPI2_IRQHandler
    .weak   USART1_IRQHandler
    .weak   USART2_IRQHandler
    .weak   USART3_IRQHandler
    .weak   EXTI15_10_IRQHandler
    .weak   RTCAlarm_IRQHandler
    .weak   USBWakeUp_IRQHandler
    .weak   USBHD_IRQHandler

NMI_Handler:  1:  j default_interrupt_handler
HardFault_Handler:  1:  j default_interrupt_handler
SysTick_Handler:  1:  j default_interrupt_handler
SW_handler:  1:  j default_interrupt_handler
WWDG_IRQHandler:  1:  j default_interrupt_handler
PVD_IRQHandler:  1:  j default_interrupt_handler
TAMPER_IRQHandler:  1:  j default_interrupt_handler
RTC_IRQHandler:  1:  j default_interrupt_handler
FLASH_IRQHandler:  1:  j default_interrupt_handler
RCC_IRQHandler:  1:  j default_interrupt_handler
EXTI0_IRQHandler:  1:  j default_interrupt_handler
EXTI1_IRQHandler:  1:  j default_interrupt_handler
EXTI2_IRQHandler:  1:  j default_interrupt_handler
EXTI3_IRQHandler:  1:  j default_interrupt_handler
EXTI4_IRQHandler:  1:  j default_interrupt_handler
DMA1_Channel1_IRQHandler:  1:  j default_interrupt_handler
DMA1_Channel2_IRQHandler:  1:  j default_interrupt_handler
DMA1_Channel3_IRQHandler:  1:  j default_interrupt_handler
DMA1_Channel4_IRQHandler:  1:  j default_interrupt_handler
DMA1_Channel5_IRQHandler:  1:  j default_interrupt_handler
DMA1_Channel6_IRQHandler:  1:  j default_interrupt_handler
DMA1_Channel7_IRQHandler:  1:  j default_interrupt_handler
ADC1_2_IRQHandler:  1:  j default_interrupt_handler
EXTI9_5_IRQHandler:  1:  j default_interrupt_handler
TIM1_BRK_IRQHandler:  1:  j default_interrupt_handler
TIM1_UP_IRQHandler:  1:  j default_interrupt_handler
TIM1_TRG_COM_IRQHandler:  1:  j default_interrupt_handler
TIM1_CC_IRQHandler:  1:  j default_interrupt_handler
TIM2_IRQHandler:  1:  j default_interrupt_handler
TIM3_IRQHandler:  1:  j default_interrupt_handler
TIM4_IRQHandler:  1:  j default_interrupt_handler
I2C1_EV_IRQHandler:  1:  j default_interrupt_handler
I2C1_ER_IRQHandler:  1:  j default_interrupt_handler
I2C2_EV_IRQHandler:  1:  j default_interrupt_handler
I2C2_ER_IRQHandler:  1:  j default_interrupt_handler
SPI1_IRQHandler:  1:  j default_interrupt_handler
SPI2_IRQHandler:  1:  j default_interrupt_handler
USART1_IRQHandler:  1:  j default_interrupt_handler
USART2_IRQHandler:  1:  j default_interrupt_handler
USART3_IRQHandler:  1:  j default_interrupt_handler
EXTI15_10_IRQHandler:  1:  j default_interrupt_handler
RTCAlarm_IRQHandler:  1:  j default_interrupt_handler
USBWakeUp_IRQHandler:  1:  j default_interrupt_handler
USBHD_IRQHandler:  1:  j default_interrupt_handler