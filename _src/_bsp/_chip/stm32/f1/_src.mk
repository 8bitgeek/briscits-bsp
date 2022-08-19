# stm32f103

SRC_CHIP_STM32F7=${SRC_ROOT}/_bsp/_chip/stm32/f1
INC += -I $(SRC_CHIP_STM32F7)

SRCS_AS += $(SRC_CHIP_STM32F7)/boot.S

SRCS_CC += $(SRC_CHIP_STM32F7)/core_clock.c
SRCS_CC += $(SRC_CHIP_STM32F7)/systick_init.c
SRCS_CC += $(SRC_CHIP_STM32F7)/system_stm32f10x.c

include ${SRC_CHIP_STM32F7}/../_src.mk

include ${SRC_ROOT}/briscits/cpu/arm/cortex-m3/_src.mk
