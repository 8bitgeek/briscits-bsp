# gd32vf103xb

SRC_CHIP=${SRC_ROOT}/_bsp/_chip/gd32/gd32vf103xb
INC += -I $(SRC_CHIP)
INC += -I $(SRC_CHIP)/../

SRCS_AS += $(SRC_CHIP)/vectors.S
SRCS_AS += $(SRC_CHIP)/../boot.S

SRCS_CC += $(SRC_CHIP)/../bss_init.c
SRCS_CC += $(SRC_CHIP)/../gd32vf103_dbg.c
SRCS_CC += $(SRC_CHIP)/../gd32vf103_fwdgt.c
SRCS_CC += $(SRC_CHIP)/../gd32vf103_gpio.c
SRCS_CC += $(SRC_CHIP)/../gd32vf103_rcu.c
SRCS_CC += $(SRC_CHIP)/../gd32vf103_spi.c
SRCS_CC += $(SRC_CHIP)/../gd32vf103_usart.c
SRCS_CC += $(SRC_CHIP)/../n200_func.c
SRCS_CC += $(SRC_CHIP)/../system_gd32vf103.c

include ${SRC_ROOT}/briscits/cpu/riscv/BumbleBee/RV32IMAC/_src.mk
