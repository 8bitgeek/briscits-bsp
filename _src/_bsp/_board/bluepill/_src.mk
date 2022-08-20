# bluepill

SRC_BOARD_BLUEPILL=${SRC_ROOT}/_bsp/_board/${TARGET}
INC += -I $(SRC_BOARD_BLUEPILL)

SRCS_CC += $(SRC_BOARD_BLUEPILL)/brisc_board.c

include ${SRC_ROOT}/_bsp/_chip/stm32/f1/stm32f103/_src.mk
