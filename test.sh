#!/bin/bash
OS_BIN="build/os-image.bin"
make clean
make

if [ $? -eq 0 ]; then
    qemu-system-i386 -drive format=raw,file=$OS_BIN
else
    echo "Compilare esuata"
    exit 1
fi