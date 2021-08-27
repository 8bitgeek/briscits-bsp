```
 ________  ________  ___  ________  ________  ___  _________  ________      
|\   __  \|\   __  \|\  \|\   ____\|\   ____\|\  \|\___   ___\\   ____\     
\ \  \|\ /\ \  \|\  \ \  \ \  \___|\ \  \___|\ \  \|___ \  \_\ \  \___|_    
 \ \   __  \ \   _  _\ \  \ \_____  \ \  \    \ \  \   \ \  \ \ \_____  \   
  \ \  \|\  \ \  \\  \\ \  \|____|\  \ \  \____\ \  \   \ \  \ \|____|\  \  
   \ \_______\ \__\\ _\\ \__\____\_\  \ \_______\ \__\   \ \__\  ____\_\  \ 
    \|_______|\|__|\|__|\|__|\_________\|_______|\|__|    \|__| |\_________\
                            \|_________|                        \|_________|
      BOARD SUPPORT

```

# BRISCITS

This is a Board Support project for [BRISCITS](https://github.com/8bitgeek/briscits-bsp).

# Prerequisite 

## RISCV OpenOCD

### Git Repository
https://github.com/riscv/riscv-openocd

### Pre-compiled binary for 64-bit ARM (aarch64) Linux Host
[riscv-openod-0.00.0-aarch64.tar.gz](http://8bitgeek.net/uploads/riscv-openod-0.00.0-aarch64.tar.gz)

## RISCV GCC

### Git Repository
https://github.com/riscv/riscv-gnu-toolchain

### Pre-compiled binary for 64-bit ARM (aarch64) Linux Host
`./configure --prefix=/opt/riscv --with-arch=rv32i --with-abi=ilp32 --enable-multilib`

[riscv32-unknown-elf-gcc-aarch64-11.1.0.tar.gz](http://8bitgeek.net/uploads/riscv32-unknown-elf-gcc-aarch64-11.1.0.tar.gz)

# Initialize 

```
git clone https://github.com/8bitgeek/briscits-bsp.git
cd briscits-bsp
git submodule init
git submodule update
```

# Environment Setup

Prior to compiling for a particular CPU target, some environment variables need to be set up.

* BRISC_CPU should reference one of the CPU support packages under the cpu/ folder.
* BRISC_GCC should contain the 'gcc' compiler prefix.
* BRISC_CFLAGS should contains compiler flags for instance "-ggdb" or "-Os"

## RISC-V
```
export BRISC_CPU=riscv/RV32IMAC
export BRISC_GCC=riscv64-unknown-elf
```
## Cortex-M7
```
export BRISC_CPU=arm/cortex-m7
export BRISC_GCC=arm-none-eabi
```
## Debug
```
export BRISC_CFLAGS=-ggdb
```
## Release
```
export BRISC_CFLAGS=-Os
```
# Make BRISCITS scheduler (libbrisc.a)
```
cd briscits
make
cd ..
```

## SiPEED Longan Nano (GD32VF103CBT6) 32-bit RISCV RV32IMAC
```
make -f bsp/sipeed-longan-nano/Makefile
```
## WaveShare (SSTM332F746) 32-bit Cortex-M7
```
make -f bsp/generic-stm32f746/Makefile
```
# OpenOCD RISCV

## Using PINE64 USB JTAG with GD32VF103 MCU and GDB

```
/opt/riscv-openocd/bin/openocd -c "adapter speed 1000" \
    -f /opt/riscv-openocd/share/openocd/scripts/interface/ftdi/um232h.cfg \
    -f /opt/riscv-openocd/share/openocd/scripts/target/gd32vf103.cfg
```

## Attach GDB on RISCV target
```
riscv64-unknown-elf-gdb ./main.elf
target extended-remote localhost:3333
load main.elf
break main
continue
```

## Flash GD32VF103 MCU
```
/opt/riscv-openocd/bin/openocd -c "adapter speed 1000" \
    -f /opt/riscv-openocd/share/openocd/scripts/interface/ftdi/um232h.cfg \
    -f /opt/riscv-openocd/share/openocd/scripts/target/gd32vf103.cfg \
    -c "program main.elf verify reset exit"
```
