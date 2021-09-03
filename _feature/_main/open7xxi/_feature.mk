# bsp
COOK_OS=${FEATURE_ROOT}/_os/${ENV_COOK_OS}
include $(COOK_OS)/_feature.mk

# sources
include ${SRC_ROOT}/util/_src.mk
include ${SRC_ROOT}/led/_src.mk
include ${SRC_ROOT}/xprintf/_src.mk


# source containing main() function
SRCS_CC += $(FEATURE_ROOT)/${FEATURE}/main.c

# final build
include ${FEATURE_ROOT}/_common/build.mk
