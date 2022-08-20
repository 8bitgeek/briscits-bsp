# gd32vf103xb

SRC_CHIP_GD32=${SRC_ROOT}/_bsp/_chip/gd32
INC += -I $(SRC_CHIP_GD32)

SRCS_AS += $(SRC_CHIP_GD32)/boot.S

SRCS_CC += $(SRC_CHIP_GD32)/bss_init.c
SRCS_CC += $(SRC_CHIP_GD32)/gd32vf103_dbg.c
SRCS_CC += $(SRC_CHIP_GD32)/gd32vf103_fwdgt.c
SRCS_CC += $(SRC_CHIP_GD32)/gd32vf103_gpio.c
SRCS_CC += $(SRC_CHIP_GD32)/gd32vf103_rcu.c
SRCS_CC += $(SRC_CHIP_GD32)/gd32vf103_spi.c
SRCS_CC += $(SRC_CHIP_GD32)/gd32vf103_usart.c
SRCS_CC += $(SRC_CHIP_GD32)/n200_func.c
SRCS_CC += $(SRC_CHIP_GD32)/system_gd32vf103.c

include ${SRC_ROOT}/briscits/cpu/riscv/BumbleBee/RV32IMAC/_src.mk
