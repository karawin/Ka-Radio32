KaraDio32 in dev state: use at your own risk

Work with i2s or a vs1053

To flash all build output, run 'make flash' or:
python /home/jp/esp/esp-idf/components/esptool_py/esptool/esptool.py --chip esp32 --port com5 --baud 460800 --before default_reset --after hard_reset write_flash -u --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 /home/jp/esp/Ka-Radio32/build/bootloader/bootloader.bin 0x10000 /home/jp/esp/Ka-Radio32/build/KaRadio32.bin 0x8000 /home/jp/esp/Ka-Radio32/build/partitions.bin


For the VS1053 version:
// spi pins
#define PIN_NUM_XCS  18
#define PIN_NUM_RST  21
#define PIN_NUM_XDCS 16
#define PIN_NUM_DREQ 17

#define PIN_NUM_MISO 19
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK  5



Old readme:
Modified for OLED display support by kodera2t

Please use latest esp-idf environment (environment just before will make lots error)

original code (w/o OLED) is
https://github.com/MrBuddyCasino/ESP32_MP3_Decoder

OLED display mode for WiFi Radio/Bluetooth speaker will be set by menuconfig (select BT speaker or Wifi radio)

Bluetooth device name is defined in bt_config.h in include file folder. (default: "hogehoge_mont")

----
Wiring is same as original, as
ESP pin   - I2S signal
```
----------------------
GPIO25/DAC1   - LRCK
GPIO26/DAC2   - BCLK
GPIO22        - DATA
```
and GPIO25/26 are fixed but GPIO22 can be re-arranged as you wish.
(defined in components/audio_renderer.c)

I2C OLED is connected, as
ESP pin   - I2C signal
```
----------------------
GPIO14   - SCL
GPIO13   - SDA
```
,which defined in app_main.c Please change as you wish...


More details can be found in the original author's explanation at
https://github.com/MrBuddyCasino/ESP32_MP3_Decoder
