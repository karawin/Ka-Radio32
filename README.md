#### State
KaraDio32 in dev state: use at your own risk<br/>

Work with i2s or a vs1053<br/>

To flash all build output, run 'make flash' or:<br/>
python /home/jp/esp/esp-idf/components/esptool_py/esptool/esptool.py --chip esp32 --port com5 --baud 460800 --before default_reset --after hard_reset write_flash -u --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 /home/jp/esp/Ka-Radio32/build/bootloader/bootloader.bin 0x10000 /home/jp/esp/Ka-Radio32/build/KaRadio32.bin 0x8000 /home/jp/esp/Ka-Radio32/build/partitions.bin<br/>


For the VS1053 version:<br/>
// spi pins<br/>
#define PIN_NUM_XCS  18<br/>
#define PIN_NUM_RST  21<br/>
#define PIN_NUM_XDCS 16<br/>
#define PIN_NUM_DREQ 17<br/>

#define PIN_NUM_MISO 19<br/>
#define PIN_NUM_MOSI 23<br/>
#define PIN_NUM_CLK  5<br/>


#### First use
- If the acces point of your router is not known, the webradio inits itself as an AP. Connect the wifi of your computer to the ssid "WifiKaRadio",  
- Browse to 192.168.4.1 to display the page, got to "setting" "Wifi" and configure your ssid ap, the password if any, the wanted IP or use dhcp if you know how to retrieve the dhcp given ip (terminal or scan of the network).
- In the gateway field, enter the ip address of your router.
- Validate. The equipment restart to the new configuration. Connect your wifi to your AP and browse to the ip given in configuration.
- Congratulation, you can edit your own station list. Dont forget to save your stations list in case of problem or for new equipments.
- if the AP is already know by the esp8266, the default ip is given by dhcp.
- a sample of stations list is on https://github.com/karawin/ESP8266-WebRadio/blob/master/ESP8266-Firmware/WebStations.txt . Can be uploaded via the web page.        


<br/>
Old readme:<br/>
Modified for OLED display support by kodera2t<br/>

Please use latest esp-idf environment (environment just before will make lots error)<br/>

original code (w/o OLED) is<br/>
https://github.com/MrBuddyCasino/ESP32_MP3_Decoder<br/>

OLED display mode for WiFi Radio/Bluetooth speaker will be set by menuconfig (select BT speaker or Wifi radio)<br/>

Bluetooth device name is defined in bt_config.h in include file folder. (default: "hogehoge_mont")<br/>

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
