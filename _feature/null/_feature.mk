# bsp
include ${FEATURE_ROOT}/briscits/_feature.mk

# sources
include ${SRC_ROOT}/xprintf/_src.mk

# source containing main() function
SRCS_CC += $(FEATURE_ROOT)/${FEATURE}/main.c

# final build
include ${FEATURE_ROOT}/_common/build.mk
