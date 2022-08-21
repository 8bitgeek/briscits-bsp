# bluepill

SRC_BOARD=${SRC_ROOT}/_bsp/_board/${TARGET}
INC += -I $(SRC_BOARD)

SRCS_CC += $(SRC_BOARD)/brisc_board.c

include ${SRC_ROOT}/_bsp/_chip/stm32/f1/stm32f103/_src.mk
include ${SRC_BOARD}/_libopencm3.mk
include ${SRC_ROOT}/b_gpio/_src.mk
include ${SRC_ROOT}/xprintf/_src.mk
