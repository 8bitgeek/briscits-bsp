# stm32

SRC_CHIP_STM32=${SRC_ROOT}/_bsp/_chip/stm32
INC += -I $(SRC_CHIP_STM32)

SRCS_CC += $(SRC_CHIP_STM32)/bss_init.c
SRCS_CC += $(SRC_CHIP_STM32)/cpp_init.c
