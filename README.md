#### State
KaraDio32 in dev state: use at your own risk<br/>

Based on KaraDio for esp8266 and https://github.com/kodera2t/ESP32_OLED_webradio<br/>
<br/>
Work with i2s or a vs1053<br/>
Output mode in Setting panel on web page of KaraDio32:<br/>
I2S for connection to a dac<br/>
I2SMERU to connect a merus amplifier<br/>
DAC to use the built in DAC of the esp32<br/>
PDM to output a PDM (Pulse Density Modulation) stream<br/>
VS1053 to connect to a vs1053 board.<br/>
<br/>

You must install the idf https://github.com/espressif/esp-idf and the toolchain.
```
To flash all build output, run 'make flash' or:
python /home/jp/esp/esp-idf/components/esptool_py/esptool/esptool.py --chip esp32 --port com5 --baud 460800 --before default_reset --after hard_reset write_flash -u --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 /home/jp/esp/Ka-Radio32/build/bootloader/bootloader.bin 0x10000 /home/jp/esp/Ka-Radio32/build/KaRadio32.bin 0x8000 /home/jp/esp/Ka-Radio32/build/partitions.bin
```
```
//-------------------------------//
// Define GPIO used in KaRadio32 //
//-------------------------------//
// Compatible ESP32 ADB
// https://www.tindie.com/products/microwavemont/esp32-audio-developing-board-esp32-adb/


// status led if any.
//------------------- 
#define GPIO_LED	GPIO_NUM_4

// gpio of the vs1053
//-------------------
#define PIN_NUM_XCS  GPIO_NUM_32
#define PIN_NUM_RST  GPIO_NUM_21
#define PIN_NUM_XDCS GPIO_NUM_33
#define PIN_NUM_DREQ GPIO_NUM_34
// spi
#define PIN_NUM_MISO GPIO_NUM_19
#define PIN_NUM_MOSI GPIO_NUM_23
#define PIN_NUM_CLK  GPIO_NUM_18

// Encoder knob
//-------------
#define PIN_ENC_A   GPIO_NUM_16
#define PIN_ENC_B   GPIO_NUM_17
#define PIN_ENC_BTN GPIO_NUM_5

// I2C Oled
//----------
#define PIN_I2C_SCL GPIO_NUM_14
#define PIN_I2C_SDA GPIO_NUM_13

// I2S DAC or PDM
//----------------
#define PIN_I2S_LRCK GPIO_NUM_25
#define PIN_I2S_BCLK GPIO_NUM_26
#define PIN_I2S_DATA GPIO_NUM_22
```

#### First use
- If the acces point of your router is not known, the webradio inits itself as an AP. Connect the wifi of your computer to the ssid "WifiKaRadio",  
- Browse to 192.168.4.1 to display the page, got to "setting" "Wifi" and configure your ssid ap, the password if any, the wanted IP or use dhcp if you know how to retrieve the dhcp given ip (terminal or scan of the network).
- In the gateway field, enter the ip address of your router.
- Validate. The equipment restart to the new configuration. Connect your wifi to your AP and browse to the ip given in configuration.
- Congratulation, you can edit your own station list. Dont forget to save your stations list in case of problem or for new equipments.
- if the AP is already know by the esp32, the default ip is given by dhcp.
- a sample of stations list is on http://karadio.karawin.fr/WebStations.txt . Can be uploaded via the web page.        


<br/>
<br/>
To flash your KaRadio32 you will need these files:<br/>
http://karadio.karawin.fr/KaRadio32.bin <br/>
and<br/>
http://karadio.karawin.fr/KaRadio32sup.zip <br/>
The tool to use is here: http://espressif.com/en/support/download/other-tools <br/>
(change the security of the installation directory to permit all)<br/>
See the image at http://karadio.karawin.fr/karawin32Flash.jpg <br/>
<br/><br/>
original code (w/o OLED) is<br/>
https://github.com/MrBuddyCasino/ESP32_MP3_Decoder<br/>
<br/>
original readme:<br/>
Modified for OLED display support by kodera2t<br/>

Please use latest esp-idf environment (environment just before will make lots error)<br/>



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
