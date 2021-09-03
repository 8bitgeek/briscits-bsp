SRC_FILESYSTEM=${SRC_ROOT}/filesystem
INC += -I $(SRC_FILESYSTEM)
INC += -I $(SRC_FILESYSTEM)/ff13c/source

SRCS_CC += $(SRC_FILESYSTEM)/ff13c/source/ff.c
SRCS_CC += $(SRC_FILESYSTEM)/ff13c/source/ffsystem.c
SRCS_CC += $(SRC_FILESYSTEM)/ff13c/source/ffunicode.c
SRCS_CC += $(SRC_FILESYSTEM)/filesystem.c
