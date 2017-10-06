#!/bin/bash
cd webpage
./generate.sh
cd ..
echo "make flash"
make flash

