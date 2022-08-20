# libopencm3
#
include ${SRC_ROOT}/libopencm3/_src.mk
#
SRCS_CC += ${SRC_LIBOPENCM3}/lib/cm3/systick.c
SRCS_CC += ${SRC_LIBOPENCM3}/lib/stm32/f1/rcc.c
SRCS_CC += ${SRC_LIBOPENCM3}/lib/stm32/f1/flash.c
SRCS_CC += ${SRC_LIBOPENCM3}/lib/stm32/f1/gpio.c
#
SRCS_CC += ${SRC_LIBOPENCM3}/lib/stm32/common/rcc_common_all.c
SRCS_CC += ${SRC_LIBOPENCM3}/lib/stm32/common/flash_common_all.c
SRCS_CC += ${SRC_LIBOPENCM3}/lib/stm32/common/gpio_common_all.c
