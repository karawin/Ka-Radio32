

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
