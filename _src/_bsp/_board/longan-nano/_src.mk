# longan-nano

SRC_BOARD=${SRC_ROOT}/_bsp/_board/${TARGET}
INC += -I $(SRC_BOARD)

SRCS_CC += $(SRC_BOARD)/brisc_board.c
SRCS_CC += $(SRC_BOARD)/brisc_timer.c
SRCS_CC += $(SRC_BOARD)/rgb_led.c

include ${SRC_ROOT}/_bsp/_chip/gd32/gd32vf103xb/_src.mk
