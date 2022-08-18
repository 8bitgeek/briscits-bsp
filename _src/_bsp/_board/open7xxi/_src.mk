# open7xxi

SRC_BOARD_OPEN7XXI=${SRC_ROOT}/_bsp/_board/${TARGET}
INC += -I $(SRC_BOARD_OPEN7XXI)

SRCS_CC += $(SRC_BOARD_OPEN7XXI)/brisc_board.c

include ${SRC_ROOT}/_bsp/_chip/stm32/f7/stm32f746xe/_src.mk
