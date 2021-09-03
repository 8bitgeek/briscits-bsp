# src-bsp-afx-102

SRC_BSP=${SRC_ROOT}/bsp/${TARGET}
INC += -I $(SRC_BSP)

# ** BRISCITS
SRC_BRISCITS  = ${SRC_ROOT}/briscits
INC          += -I $(SRC_BRISCITS)/include
CHIP 		 = $(SRC_BRISCITS)/target/chip/stm32/stm32f746
STM32_LIB	 = $(CHIP)/lib

include $(SRC_BRISCITS)/cpu/arm/$(MCU_CORE)/_src.mk

CHIP_LIB         		= $(STM32_LIB)
CHIP_LIB_SRC     		= $(CHIP_LIB)/STM32F7xx_HAL_Driver/Src
CHIP_LIB_INCLUDE 		= $(CHIP_LIB)/STM32F7xx_HAL_Driver/Inc

LIB_CMSIS 				= $(CHIP_LIB)/CMSIS
LIB_CMSIS_INCLUDE 		= $(LIB_CMSIS)/Include

CHIP_LIB_CMSIS	 		= $(LIB_CMSIS)/Device/ST/STM32F7xx
CHIP_LIB_CMSIS_INCLUDE	= $(CHIP_LIB_CMSIS)/Include

INC += -I $(LIB_CMSIS_INCLUDE)
INC += -I $(CHIP_LIB_INCLUDE) 
INC += -I $(CHIP_LIB_CMSIS_INCLUDE)
INC += -I $(SRC_BRISCITS)/target/chip/stm32/stm32f746/include/stm32f746bgt6

SRCS_CC += $(CHIP_LIB_SRC)/stm32f7xx_ll_fmc.c
SRCS_CC += $(CHIP_LIB_SRC)/stm32f7xx_hal_sdram.c
SRCS_CC += $(CHIP_LIB_SRC)/stm32f7xx_hal_adc.c
SRCS_CC += $(CHIP_LIB_SRC)/stm32f7xx_hal_tim.c
SRCS_CC += $(CHIP_LIB_SRC)/stm32f7xx_hal_rcc.c
SRCS_CC += $(CHIP_LIB_SRC)/stm32f7xx_hal_usart.c 	
SRCS_CC += $(CHIP_LIB_SRC)/stm32f7xx_hal_uart.c 	

SRCS_CC += $(CHIP)/src/chip.c
SRCS_CC += $(CHIP)/src/gpio.c
SRCS_CC += $(CHIP)/src/uart.c

SRCS_CC += $(SRC_BSP)/system_stm32f7xx.c

SRCS_CC += $(SRC_BSP)/board.c
SRCS_CC += $(SRC_BSP)/hw_clocks.c
SRCS_CC += $(SRC_BSP)/hw_dma.c
SRCS_CC += $(SRC_BSP)/hw_exti.c
SRCS_CC += $(SRC_BSP)/hw_fault.c
SRCS_CC += $(SRC_BSP)/hw_gpio.c
SRCS_CC += $(SRC_BSP)/hw_pin.c
SRCS_CC += $(SRC_BSP)/hw_spi.c
SRCS_CC += $(SRC_BSP)/hw_bb_spi.c
SRCS_CC += $(SRC_BSP)/hw_tim.c
SRCS_CC += $(SRC_BSP)/hw_usart.c
SRCS_CC += $(SRC_BSP)/hw_dac.c
SRCS_CC += $(SRC_BSP)/hw_pwm.c
SRCS_CC += $(SRC_BSP)/hw_adc.c
SRCS_CC += $(SRC_BSP)/hw_sdram.c
SRCS_CC += $(SRC_BSP)/diskio.c

SRCS_AS += $(SRC_BSP)/crt0.S
SRCS_AS += $(SRC_BSP)/vectors.S
