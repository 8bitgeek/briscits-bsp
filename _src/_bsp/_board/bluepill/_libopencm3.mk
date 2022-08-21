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

SRCS_CC += ${SRC_LIBOPENCM3}/lib/usb/usb.c
SRCS_CC += ${SRC_LIBOPENCM3}/lib/stm32/st_usbfs_v1.c
SRCS_CC += ${SRC_LIBOPENCM3}/lib/stm32/common/st_usbfs_core.c
SRCS_CC += ${SRC_LIBOPENCM3}/lib/usb/usb_control.c
SRCS_CC += ${SRC_LIBOPENCM3}/lib/usb/usb_standard.c

include ${SRC_ROOT}/usb-gadget0/_src.mk
