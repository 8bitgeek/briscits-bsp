# xprintf

SRC_XPRINTF=${SRC_ROOT}/xprintf
INC += -I $(SRC_XPRINTF)

SRCS_CC += $(SRC_XPRINTF)/xprintf.c

include ${SRC_ROOT}/math/_src.mk
