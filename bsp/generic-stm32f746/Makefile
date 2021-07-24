# Board
MCU_CHIP	 	= stm32f7xx
MCU_CORE     	= cortex-m7
MCU_FLOAT    	= softfp
MCU_FPU 		= fpv4-sp-d16

BOARD=generic-stm32f746
TARGET=$(BOARD)

# CPU
CPU_COMMON=briscits/cpu/arm
CPU=$(CPU_COMMON)/cortex-m7

# Chip
CHIP_FAMILY=chip/stm32
CHIP_COMMON=$(CHIP_FAMILY)/f7
CHIP=$(CHIP_COMMON)/stm32f746xe

CFLAGS += -DBRISC_THREAD_MAX=4 -DARM_FVP_LAZY_STACKING -DHSE_VALUE=8000000

# GCC toolchain programs.
CC = arm-none-eabi-gcc
OC = arm-none-eabi-objcopy
OS = arm-none-eabi-size
GDB = arm-none-eabi-gdb

# OpenOCD
OPENOCD=openocd
OPENOCD_LOCAL_CFG=-f bsp/$(BOARD)/openocd-local.cfg

# Assembly directives.
ASFLAGS += -c
ASFLAGS += -O0
ASFLAGS += -Wall
ASFLAGS += -fshort-enums -fsigned-char -mlittle-endian -mthumb -mthumb-interwork -mcpu=$(MCU_CORE) -mfloat-abi=$(MCU_FLOAT) -mfpu=$(MCU_FPU)

# C compilation directives
CFLAGS += -DSTM32F746xx
CFLAGS += -c
CFLAGS += -Wall
CFLAGS += -ggdb
CFLAGS += -fshort-enums -fsigned-char -mlittle-endian -mthumb -mthumb-interwork -mcpu=$(MCU_CORE) -mfloat-abi=$(MCU_FLOAT) -mfpu=$(MCU_FPU)

# Linker directives.
LFLAGS +=  -Xlinker -Map=$(TARGET).map 
LFLAGS += -Wall
LFLAGS += -Wl,--no-relax
LFLAGS += -Wl,--gc-sections
LFLAGS += -nostartfiles
LFLAGS += -lc
LFLAGS += -lgcc
LFLAGS += -lm
LFLAGS += --specs=nosys.specs
LFLAGS += -fshort-enums -fsigned-char -mlittle-endian -mthumb -mthumb-interwork -mcpu=$(MCU_CORE) -mfloat-abi=$(MCU_FLOAT) -mfpu=$(MCU_FPU)
LFLAGS += -Wl,--gc-sections
LFLAGS += -T$(CHIP)/linker.ld

# xprintf
CFLAGS += -DXPRINTF_USE_XFUNC_OUT=1
CFLAGS += -DXPRINTF_USE_XFUNC_IN=1
CFLAGS += -DXPRINTF_USE_FLOAT=1
C_SRC  += lib/xprintf.c
C_SRC  += lib/ftoa.c

# Header file directories.
INCLUDE += -I bsp/$(BOARD)
INCLUDE += -I $(CPU)
INCLUDE += -I $(CPU_COMMON)
INCLUDE += -I $(CHIP)
INCLUDE += -I $(CHIP_COMMON)
INCLUDE += -I $(CHIP_FAMILY)
INCLUDE += -I lib

# CPU and CHIP Source files.
AS_SRC	+= $(CHIP)/vectors.S
AS_SRC	+= $(CHIP_COMMON)/boot.S
C_SRC  	+= $(CHIP_COMMON)/core_clock.c
C_SRC  	+= $(CHIP_COMMON)/system_stm32f7xx.c
C_SRC  	+= $(CHIP_COMMON)/systick_init.c
C_SRC  	+= $(CHIP_FAMILY)/bss_init.c
C_SRC  	+= $(CHIP_FAMILY)/cpp_init.c

# BOARD Source files
C_SRC  += bsp/$(BOARD)/brisc_board.c

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

################# main.c ######################

# Rule to create an ELF file from the compiled object files.
$(TARGET).elf:  bsp/$(BOARD)/main.o $(OBJS)
	$(CC) $^ $(LFLAGS) briscits/libbrisc.a -o $@

# Rule to create a raw binary file from an ELF file.
$(TARGET).bin: $(TARGET).elf
	$(OC) -S -O binary $< $@
	$(OS) $<

################# main-test-mutex.c ######################

# Rule to create an ELF file from the compiled object files.
main-test-mutex.elf:  bsp/$(BOARD)/main-test-mutex.o $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@

# Rule to create a raw binary file from an ELF file.
main-test-mutex.bin: main-test-mutex.elf
	$(OC) -S -O binary $< $@
	$(OS) $<

main-test-mutex: main-test-mutex.bin
	mv main-test-mutex.bin $(TARGET).bin 
	mv main-test-mutex.elf $(TARGET).elf

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
	$(OPENOCD) $(OPENOCD_LOCAL_CFG) 2> /dev/null > /dev/null &

stop:
	killall $(OPENOCD)

# Rule to start debugger
debug: $(TARGET).bin
	$(GDB) -tui -x bsp/$(BOARD)/gdbinit

flash: $(TARGET).elf
		$(OPENOCD) $(OPENOCD_LOCAL_CFG) -c "program $(TARGET).elf verify reset exit"

