#!/bin/bash
export BRISC_CPU=arm/cortex-m7
export BRISC_GCC=arm-none-eabi
export BRISC_CFLAGS=$2
cd briscits
make
cd ..
make -f bsp/$1/Makefile $3
