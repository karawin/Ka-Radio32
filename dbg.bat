#!/bin/bash
xtensa-esp32-elf-gdb ./build/KaRadio32.elf -b 115200 -ex "target remote com%1"
