# src-bsp-afx-102

SRC_BSP=${SRC_ROOT}/_bsp/${TARGET}
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

SRCS_CC += $(CHIP)/src/chip.c
# SRCS_CC += $(CHIP)/src/fault.c
SRCS_CC += $(CHIP)/src/gpio.c
SRCS_CC += $(CHIP)/src/uart.c

SRCS_CC += $(SRC_BSP)/system_stm32f7xx.c

SRCS_CC += $(SRC_BSP)/board.c
SRCS_CC += $(SRC_BSP)/diskio.c

SRCS_AS += $(SRC_BSP)/crt0.S
SRCS_AS += $(SRC_BSP)/vectors.S
