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

## RISC-V
```
export BRISC_CPU=riscv/RV32IMAC
export BRISC_GCC=/opt/riscv/bin/riscv32-unknown-elf
cd briscits
make
cd ..
make -f bsp/sipeed-longan-nano/Makefile
```
## Cortex-M7
```
export BRISC_CPU=arm/cortex-m7
export BRISC_GCC=/opt/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi
cd briscits
make
cd ..
make -f bsp/generic-stm32f746/Makefile
```
# OpenOCD

## Using PINE64 USB JTAG with GD32VF103 MCU
```
openocd -c "adapter speed 1000" -f interface/ftdi/um232h.cfg -f target/gd32vf103.cfg
```