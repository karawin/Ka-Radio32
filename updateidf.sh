#!/bin/bash
cd /home/jp/esp/esp-idf
git pull
git submodule update --init --recursive
cd /home/jp/esp/Ka-Radio32
