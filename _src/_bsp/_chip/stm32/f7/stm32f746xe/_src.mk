# stm32f7xx

SRC_CHIP_STM32F746XE=${SRC_ROOT}/_bsp/_chip/stm32/f7/stm32f746xe
INC += -I $(SRC_CHIP_STM32F746XE)

SRCS_AS += $(SRC_CHIP_STM32F746XE)/vectors.S

include ${SRC_CHIP_STM32F746XE}/../_src.mk
