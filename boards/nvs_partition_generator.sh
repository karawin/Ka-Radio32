#!/bin/bash

NVS_PARTITION_GENERATOR="$IDF_PATH/components/nvs_flash/nvs_partition_generator/nvs_partition_gen.py"
SIZE_PARTITION="0x3000"

cd "$(dirname $0)"
cat << EOT

jump into $PWD directory

Minimum NVS Partition Size needed is 0x3000 bytes.
https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/storage/nvs_partition_gen.html#running-the-utility
EOT

# clean up !!
rm -f build/*.bin

for filename in $(ls *.csv); do
	fname="${filename%.*}"
	echo -e "\nBoard \e[33m$fname\e[m"
	comment="$(grep L_COMMENT $filename | sed -E 's/^.*,string,//; s/\s*\.\s*$//')"
	echo -e "\e[34m${comment}\e[m"
	python $NVS_PARTITION_GENERATOR\
		--version v1\
		--outdir build\
		--input $filename\
		--output $fname.bin\
		--size $SIZE_PARTITION
done

cat << EOT

for flashing :
Select one board "MY-BOARD"
esptool --chip esp32 write_flash 0x3a2000 build/MY-BOARD.bin
EOT
