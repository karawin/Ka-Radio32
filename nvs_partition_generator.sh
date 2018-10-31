#!/bin/bash
echo python ../esp-idf/components/nvs_flash/nvs_partition_generator/nvs_partition_gen.py $1.csv $1.bin 8KB
python ../esp-idf/components/nvs_flash/nvs_partition_generator/nvs_partition_gen.py $1.csv $1.bin 0x2000
echo done
