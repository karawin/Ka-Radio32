#!/bin/bash
filename=$(basename "$1")
fname="${filename%.*}"
echo python ./nvs_partition_gen.py ${fname}.csv build/${fname}.bin 0x2000
python ./nvs_partition_gen.py ${fname}.csv build/${fname}.bin 0x2000
echo done
