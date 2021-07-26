#!/bin/bash
export BRISC_CPU=riscv/RV32IMAC
export BRISC_GCC=riscv32-unknown-elf
export BRISC_CFLAGS=$2
cd briscits
make
cd ..
make -f bsp/$1/Makefile $3
