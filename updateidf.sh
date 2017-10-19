#!/bin/bash
cd ~/esp/esp-idf
git pull
git submodule update --init --recursive
cd ~/esp/Ka-Radio32
