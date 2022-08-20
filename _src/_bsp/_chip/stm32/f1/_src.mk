# stm32f103

SRC_CHIP_STM32F1=${SRC_ROOT}/_bsp/_chip/stm32/f1
INC += -I $(SRC_CHIP_STM32F1)

SRCS_AS += $(SRC_CHIP_STM32F1)/boot.S

SRCS_CC += $(SRC_CHIP_STM32F1)/core_clock.c
SRCS_CC += $(SRC_CHIP_STM32F1)/systick_init.c
SRCS_CC += $(SRC_CHIP_STM32F1)/system_stm32f10x.c

include ${SRC_CHIP_STM32F1}/../_src.mk

include ${SRC_ROOT}/briscits/cpu/arm/cortex-m3/_src.mk

ASFLAGS	+= -mlittle-endian -mthumb -mthumb-interwork -mcpu=$(MCU_CORE)
