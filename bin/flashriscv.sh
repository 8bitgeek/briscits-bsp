#!/bin/bash

/opt/riscv-openocd/bin/openocd -c "adapter speed 1000" \
    -f /opt/riscv-openocd/share/openocd/scripts/interface/ftdi/um232h.cfg \
    -f /opt/riscv-openocd/share/openocd/scripts/target/gd32vf103.cfg \
    -c "program main.elf verify reset exit"
