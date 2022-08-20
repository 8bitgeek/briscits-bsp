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

		.macro	vector v 
			.word 	v
			.weak	v
			.set    v,default_interrupt_handler
		.endm

		.extern	briscits_reset_handler			/* Reset Vector */
		.global default_interrupt_handler
		.extern PendSV_IRQ_Handler
		.extern SysTick_IRQ_Handler
		.extern BusFault_IRQ_Handler
		.extern MemoryManagement_IRQ_Handler
		.extern NonMaskableInt_IRQ_Handler 
		.global _hard_fault

		.global _vectors
		.section .vectors, "ax"
		.code 16
		.align 4
		.thumb_func

_vectors:
		.word 	__main_stack_end__	
		.word 	briscits_reset_handler				/* Reset Vector 						 */
		vector 	NonMaskableInt_IRQ_Handler			/* Non Maskable Interrupt       		 */
		.word 	_hard_fault							/* Hard Fault */
		vector 	MemoryManagement_IRQ_Handler		/* Cortex-M7 Memory Management Interrupt */
		vector 	BusFault_IRQ_Handler				/* Cortex-M7 Bus Fault Interrupt 		 */
		vector 	UsageFault_IRQ_Handler				/* Cortex-M7 Usage Fault Interrupt 		 */
		.word 	default_interrupt_handler
		.word 	default_interrupt_handler
		.word 	default_interrupt_handler
		.word 	default_interrupt_handler
		.word 	default_interrupt_handler			/* Cortex-M7 SV Call Interrupt 			 */
		vector 	DebugMonitor_IRQ_Handler			/* Cortex-M7 Debug Monitor Interrupt 	 */
		.word 	default_interrupt_handler
		.word 	PendSV_IRQ_Handler					/* Cortex-M7 Pend SV Interrupt  		 */
		.word 	SysTick_IRQ_Handler					/* Cortex-M7 System Tick Interrupt  	 */
		/* ---- */
		vector 	WWDG_IRQ_Handler					/* Window WatchDog Interrupt                                         */
		vector	PVD_IRQ_Handler                     /* PVD through EXTI Line detection Interrupt                         */
		vector	TAMP_STAMP_IRQ_Handler              /* Tamper and TimeStamp interrupts through the EXTI line             */
		vector	RTC_WKUP_IRQ_Handler                /* RTC Wakeup interrupt through the EXTI line                        */
		vector	FLASH_IRQ_Handler                   /* FLASH global Interrupt                                            */
		vector	RCC_IRQ_Handler                     /* RCC global Interrupt                                              */
		vector	EXTI0_IRQ_Handler                   /* EXTI Line0 Interrupt                                              */
		vector	EXTI1_IRQ_Handler                   /* EXTI Line1 Interrupt                                              */
		vector	EXTI2_IRQ_Handler                   /* EXTI Line2 Interrupt                                              */
		vector	EXTI3_IRQ_Handler                   /* EXTI Line3 Interrupt                                              */
		vector	EXTI4_IRQ_Handler                   /* EXTI Line4 Interrupt                                              */
		vector	DMA1_Stream0_IRQ_Handler            /* DMA1 Stream 0 global Interrupt                                    */
		vector	DMA1_Stream1_IRQ_Handler            /* DMA1 Stream 1 global Interrupt                                    */
		vector	DMA1_Stream2_IRQ_Handler            /* DMA1 Stream 2 global Interrupt                                    */
		vector	DMA1_Stream3_IRQ_Handler            /* DMA1 Stream 3 global Interrupt                                    */
		vector	DMA1_Stream4_IRQ_Handler            /* DMA1 Stream 4 global Interrupt                                    */
		vector	DMA1_Stream5_IRQ_Handler            /* DMA1 Stream 5 global Interrupt                                    */
		vector	DMA1_Stream6_IRQ_Handler            /* DMA1 Stream 6 global Interrupt                                    */
		# STM32F10X_MD
		vector	ADC_IRQ_Handler                     /* ADC1, ADC2 and ADC3 global Interrupts                             */
		vector	USB_HP_CAN1_TX_IRQ_Handler          /* USB Device High Priority or CAN1 TX Interrupts                    */
		vector	USB_LP_CAN1_RX0_IRQ_Handler         /* USB Device Low Priority or CAN1 RX0 Interrupts                    */
		vector	CAN1_RX1_IRQ_Handler                /* CAN1 RX1 Interrupt                                                */
		vector	CAN1_SCE_IRQ_Handler                /* CAN1 SCE Interrupt                                                */
		vector	EXTI9_5_IRQ_Handler                 /* External Line[9:5] Interrupts                                     */
		vector	TIM1_BRK_IRQ_Handler           		/* TIM1 Break Interrupt  											 */
		vector	TIM1_UP_IRQ_Handler           		/* TIM1 Update Interrupt 										     */
		vector	TIM1_TRG_COM_IRQ_Handler      		/* TIM1 Trigger and Commutation Interrupt							 */
		vector	TIM1_CC_IRQ_Handler                 /* TIM1 Capture Compare Interrupt                                    */
		vector	TIM2_IRQ_Handler                    /* TIM2 global Interrupt                                             */
		vector	TIM3_IRQ_Handler                    /* TIM3 global Interrupt                                             */
		vector	TIM4_IRQ_Handler                    /* TIM4 global Interrupt                                             */
		vector	I2C1_EV_IRQ_Handler                 /* I2C1 Event Interrupt                                              */
		vector	I2C1_ER_IRQ_Handler                 /* I2C1 Error Interrupt                                              */
		vector	I2C2_EV_IRQ_Handler                 /* I2C2 Event Interrupt                                              */
		vector	I2C2_ER_IRQ_Handler                 /* I2C2 Error Interrupt                                              */  
		vector	SPI1_IRQ_Handler                    /* SPI1 global Interrupt                                             */
		vector	SPI2_IRQ_Handler                    /* SPI2 global Interrupt                                             */
		vector	USART1_IRQ_Handler                  /* USART1 global Interrupt                                           */
		vector	USART2_IRQ_Handler                  /* USART2 global Interrupt                                           */
		vector	USART3_IRQ_Handler                  /* USART3 global Interrupt                                           */
		vector	EXTI15_10_IRQ_Handler               /* External Line[15:10] Interrupts                                   */
		vector	RTC_Alarm_IRQ_Handler               /* RTC Alarm (A and B) through EXTI Line Interrupt                   */
		vector	USBWakeUp_IRQ_Handler             	/* USB Device WakeUp from suspend through EXTI Line Interrupt        */    
		#
_vectors_end:

		.end
