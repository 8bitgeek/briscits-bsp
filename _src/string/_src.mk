# string

SRC_STRING=${SRC_ROOT}/string
INC += -I $(SRC_STRING)

SRCS_CC += $(SRC_STRING)/string.c

include ${SRC_ROOT}/heap/_src.mk
