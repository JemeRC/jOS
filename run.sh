#!/bin/bash
OS_BIN="build/os.bin"
make

if [ $? -eq 0 ]; then
    qemu-system-i386 -drive format=raw,file=$OS_BIN,index=0,if=floppy
else
    echo "Compilare esuata"
    exit 1
fi