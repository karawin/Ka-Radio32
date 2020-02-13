#!/bin/bash

NVS_PARTITION_GENERATOR="nvs_partition_gen.py"
#NVS_PARTITION_GENERATOR="nvs_partition_gen.py"
SIZE_PARTITION="0x3000"

cd "$(dirname $0)"
echo "Jump into $PWD directory"

build_binary () {
	if [ ! -f "$1" ]; then
		echo -e "\e[31m$1 file not found\e[m"
		return
	fi

	fname="${1%.*}"
	echo -e "\nBoard \e[33m$fname\e[m"
	comment="$(grep L_COMMENT $1 | sed -E 's/^.*,string,//; s/\s*\.\s*$//')"
	echo -e "\e[34m${comment}\e[m"
	python $NVS_PARTITION_GENERATOR\
		--version v1\
		--input "$1"\
		--output "./build/$fname.bin"\
		--size $SIZE_PARTITION
}

if [ "$#" -eq 0 ]; then
	# clean up !!
	rm -f build/*.bin

	for filename in $(ls *.csv); do
		build_binary "$filename"
	done
else
	MY_BOARD="MY-BOARD"
	if [ "$#" -eq 1 ]; then
		MY_BOARD="${1%.*}"
	fi
	while [ ! -z "$1" ]; do
		build_binary "$1"
		shift
	done
fi

cat << EOT

Minimum NVS Partition Size needed is 0x3000 bytes. Look at this link :
https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/storage/nvs_partition_gen.html#running-the-utility

For flashing, type :
 esptool --chip esp32 write_flash 0x3a2000 build/${MY_BOARD}.bin
EOT
