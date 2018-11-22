#!/bin/bash
filename=$(basename "$1")
fname="${filename%.*}"
echo python ${IDF_PATH}/components/nvs_flash/nvs_partition_generator/nvs_partition_gen.py ${fname}.csv build/${fname}.bin 8192
python ${IDF_PATH}/components/nvs_flash/nvs_partition_generator/nvs_partition_gen.py ${fname}.csv build/${fname}.bin 8192
echo done
