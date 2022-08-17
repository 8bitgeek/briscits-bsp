
CFLAGS_COMMON += -D_BRISCITS_RTOS_=1  -Wl,-ereset_handler 

# bsp
include ${FEATURE_ROOT}/_common/_feature.mk

# sources
include ${SRC_ROOT}/briscits/_src.mk
include ${SRC_ROOT}/watchdog/_src.mk

# # source containing main() function
SRCS_CC += $(FEATURE_ROOT)/briscits/main.c

# # final build
# include ${FEATURE_ROOT}/_common/build.mk
