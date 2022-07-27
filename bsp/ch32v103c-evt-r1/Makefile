TARGET=main

# Board
BOARD=sipeed-longan-nano
CFLAGS += -DHXTAL_VALUE=8000000
CFLAGS += -DBRISC_THREAD_MAX=4

# CPU
CPU_COMMON=briscits/cpu/riscv
CPU=$(CPU_COMMON)/Qingke/RV32IMAC

# Chip
CHIP_FAMILY=ch32
CHIP_COMMON=chip/$(CHIP_FAMILY)
CHIP=$(CHIP_COMMON)/ch32v103x8

# GCC toolchain programs.
CC = ${BRISC_GCC}-gcc
OC = ${BRISC_GCC}-objcopy
OS = ${BRISC_GCC}-size
GDB = ${BRISC_GCC}-gdb

include briscits/cpu/$(BRISC_CPU)/cflags.mk

# Assembly directives.
ASFLAGS += -c
ASFLAGS += -Wall
ASFLAGS += -march=rv32imac
ASFLAGS += -mabi=ilp32

# C compilation directives
CFLAGS += -c
CFLAGS += -Wall
CFLAGS += ${BRISC_CFLAGS}
CFLAGS += -march=rv32imac
CFLAGS += -mabi=ilp32

# Linker directives.
LFLAGS +=  -Xlinker -Map=$(TARGET).map 
LFLAGS += -Wall
LFLAGS += -Wl,--no-relax
LFLAGS += -Wl,--gc-sections
LFLAGS += -nostartfiles
LFLAGS += -lc
LFLAGS += -lgcc
LFLAGS += -lm
LFLAGS += -march=rv32imac
LFLAGS += -mabi=ilp32
LFLAGS += -Wl,--gc-sections
LFLAGS += -T$(CHIP)/linker.ld

# xprintf
CFLAGS += -DXPRINTF_USE_XFUNC_OUT=1
CFLAGS += -DXPRINTF_USE_XFUNC_IN=1
CFLAGS += -DXPRINTF_USE_FLOAT=1

# Header file directories.
INCLUDE += -I bsp/$(BOARD)
INCLUDE += -I $(CPU)
INCLUDE += -I $(CPU_COMMON)
INCLUDE += -I $(CHIP)
INCLUDE += -I $(CHIP_COMMON)
INCLUDE += -I lib

# CPU and CHIP Source files.
AS_SRC  += $(CHIP)/vectors.S
AS_SRC  += $(CHIP_COMMON)/boot.S
C_SRC  += $(CHIP_COMMON)/bss_init.c
C_SRC  += $(CHIP_COMMON)/n200_func.c
C_SRC  += $(CHIP_COMMON)/system_ch32v103.c
C_SRC  += $(CHIP_COMMON)/ch32v103_gpio.c
C_SRC  += $(CHIP_COMMON)/ch32v103_rcc.c
C_SRC  += $(CHIP_COMMON)/ch32v103_spi.c
C_SRC  += $(CHIP_COMMON)/ch32v103_usart.c
C_SRC  += $(CHIP_COMMON)/ch32v103_wwdg.c
C_SRC  += $(CPU)/cpu.c
C_SRC  += $(CPU)/core_riscv.c

# LIB Source files
C_SRC  += lib/xprintf.c
C_SRC  += lib/ftoa.c
C_SRC  += lib/ftoa.c
C_SRC  += lib/watchdog.c

# BOARD Source files
C_SRC  += bsp/$(BOARD)/main.c
C_SRC  += bsp/$(BOARD)/brisc_board.c
C_SRC  += bsp/$(BOARD)/brisc_timer.c
C_SRC  += bsp/$(BOARD)/rgb_led.c

# BRISCIT Include Files
INCLUDE += -I briscits/inc

# Object files to build.
OBJS  = $(AS_SRC:.S=.o)
OBJS += $(C_SRC:.c=.o)

# Default rule to build the whole project.
.PHONY: all
all: $(TARGET).bin

# Rule to build assembly files.
%.o: %.S
	$(CC) -x assembler-with-cpp $(ASFLAGS) $(INCLUDE) $< -o $@

# Rule to compile C files.
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@

# Rule to create an ELF file from the compiled object files.
$(TARGET).elf: $(OBJS)
	$(CC) $^ $(LFLAGS) briscits/libbrisc.a -o $@

# Rule to create a raw binary file from an ELF file.
$(TARGET).bin: $(TARGET).elf
	$(OC) -S -O binary $< $@
	$(OS) $<

# Rule to clear out generated build files.
.PHONY: clean
clean:
	rm -f $(OBJS)

cleanall: clean
	rm -f $(TARGET).elf
	rm -f $(TARGET).bin
	rm -f $(TARGET).map

# Rule to start openocd
start:
	$(OPENOCD) -f $(OPENOCD_JTAG_CFG) -f $(OPENOCD_TARGET_CFG)  2> /dev/null > /dev/null &

stop:
	killall $(OPENOCD)

# Rule to start debugger
debug: $(TARGET).bin
	$(GDB) -x bsp/$(BOARD)/gdbinit

flash: $(TARGET).elf
		$(OPENOCD) -f $(OPENOCD_JTAG_CFG) -f $(OPENOCD_TARGET_CFG) -c "program $(TARGET).elf verify reset exit"

