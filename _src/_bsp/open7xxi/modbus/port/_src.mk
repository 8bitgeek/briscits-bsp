# modbus port
INC += -I $(SRC_BSP)/modbus/port
SRCS_CC += $(SRC_BSP)/modbus/port/portevent.c
SRCS_CC += $(SRC_BSP)/modbus/port/portserial.c
SRCS_CC += $(SRC_BSP)/modbus/port/porttimer.c
SRCS_CC += $(SRC_BSP)/modbus/port/port.c

