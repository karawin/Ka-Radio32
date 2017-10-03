deps_config := \
	/home/jp/esp/esp-idf/components/app_trace/Kconfig \
	/home/jp/esp/esp-idf/components/aws_iot/Kconfig \
	/home/jp/esp/esp-idf/components/bt/Kconfig \
	/home/jp/esp/esp-idf/components/esp32/Kconfig \
	/home/jp/esp/esp-idf/components/ethernet/Kconfig \
	/home/jp/esp/esp-idf/components/fatfs/Kconfig \
	/home/jp/esp/esp-idf/components/freertos/Kconfig \
	/home/jp/esp/esp-idf/components/heap/Kconfig \
	/home/jp/esp/esp-idf/components/log/Kconfig \
	/home/jp/esp/esp-idf/components/lwip/Kconfig \
	/home/jp/esp/esp-idf/components/mbedtls/Kconfig \
	/home/jp/esp/esp-idf/components/openssl/Kconfig \
	/home/jp/esp/esp-idf/components/pthread/Kconfig \
	/home/jp/esp/esp-idf/components/spi_flash/Kconfig \
	/home/jp/esp/esp-idf/components/spiffs/Kconfig \
	/home/jp/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/jp/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/jp/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/jp/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/jp/esp/Ka-Radio32/main/Kconfig.projbuild \
	/home/jp/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/jp/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
