# stm32f103

SRC_CHIP_STM32F103=${SRC_ROOT}/_bsp/_chip/stm32/f1/stm32f103
INC += -I $(SRC_CHIP_STM32F103)

SRCS_AS += $(SRC_CHIP_STM32F103)/vectors.S

include ${SRC_CHIP_STM32F103}/../_src.mk
