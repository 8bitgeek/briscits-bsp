# gd32vf103xb

SRC_CHIP_STM32F7=${SRC_ROOT}/_bsp/_chip/stm32/f7
INC += -I $(SRC_CHIP_STM32F7)

SRCS_AS += $(SRC_CHIP_STM32F7)/boot.S

SRCS_CC += $(SRC_CHIP_STM32F7)/core_clock.c
SRCS_CC += $(SRC_CHIP_STM32F7)/systick_init.c
SRCS_CC += $(SRC_CHIP_STM32F7)/system_stm32f7xx.c
# SRCS_CC += $(SRC_CHIP_STM32F7)/stm32f7xx_hal_rcc.c

include ${SRC_CHIP_STM32F7}/../_src.mk

include ${SRC_ROOT}/briscits/cpu/arm/cortex-m7/_src.mk
