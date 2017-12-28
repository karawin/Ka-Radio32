### State
KaraDio32 in dev state: Stable<br/>
Works on any esp32 board.<br/>
See the feature on https://hackaday.io/project/11570-wifi-webradio-with-esp8266-and-vs1053 <br/>
The esp32 adds the output on the internal dac or with i2s to an external dac<br/>
but only mp3 stations can be played.<br/>
Adding a vs1053 board, all stations can be played.<br/>
Compatible with esp8266 KaRadio addons.<br/>
<br/>
### Added features
Work with i2s, internal DAC or a vs1053<br/>
Output mode set in Setting panel on web page of KaraDio32:<br/>
I2S for connection to ac external DAC<br/>
I2SMERUS to connect a merus amplifier<br/>
DAC to use the built in DAC of the esp32<br/>
PDM to output a PDM (Pulse Density Modulation) stream<br/>
VS1053 to connect to a vs1053 board.<br/>
<br/>
LCD or Oled support integrated: most common b/w or color oled and lcd can be used.<br/>
IR support integrated. Nec protocol only.<br/>
Rotary encoder support integrated. Common functions: play/stop, volume, station change, date time display.</br/>
<br/>

### Build your own
To build your own release, you must install the idf https://github.com/espressif/esp-idf and the toolchain.
```
To flash all build output, run 'make flash' or:
python /home/yourhome/esp/esp-idf/components/esptool_py/esptool/esptool.py --chip esp32 --port com5 --baud 460800 --before default_reset --after hard_reset write_flash -u --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 /home/yourhome/esp/Ka-Radio32/build/bootloader/bootloader.bin 0x10000 /home/yourhome/esp/Ka-Radio32/build/KaRadio32.bin 0x8000 /home/yourhome/esp/Ka-Radio32/build/partitions.bin
```
#### GPIO Definition Version 0.8
```
//-------------------------------//
// Define GPIO used in KaRadio32 //
//-------------------------------//
// Compatible ESP32 ADB
// https://www.tindie.com/products/microwavemont/esp32-audio-developing-board-esp32-adb/

// HSPI pins
//-----------
#define PIN_NUM_MISO GPIO_NUM_19 	// Master Input, Slave Output
#define PIN_NUM_MOSI GPIO_NUM_23	// Master Output, Slave Input   Named Data or SDA or D1 for oled
#define PIN_NUM_CLK  GPIO_NUM_18 	// Master clock  Named SCL or SCK or D0 for oled

// status led if any.
//------------------- 
#define GPIO_LED	GPIO_NUM_4		// Flashing led or Playing led

// gpio of the vs1053
//-------------------
#define PIN_NUM_XCS  GPIO_NUM_32
#define PIN_NUM_RST  GPIO_NUM_12 
#define PIN_NUM_XDCS GPIO_NUM_33
#define PIN_NUM_DREQ GPIO_NUM_34
// + HSPI pins

// Encoder knob
//-------------
#define PIN_ENC_A   GPIO_NUM_16		// CLK
#define PIN_ENC_B   GPIO_NUM_17		// DT
#define PIN_ENC_BTN GPIO_NUM_5		// SW

// I2C lcd
//----------
#define PIN_I2C_SCL GPIO_NUM_14
#define PIN_I2C_SDA GPIO_NUM_13
#define PIN_I2C_RST	GPIO_NUM_2		// or not used

// SPI lcd
//---------
// HSPI pins +
#define PIN_LCD_CS	GPIO_NUM_13		//CS
#define PIN_LCD_A0	GPIO_NUM_14		//A0 or D/C
#define PIN_LCD_RST	GPIO_NUM_2		//Reset RES RST or not used

// IR Signal
//-----------
#define PIN_IR_SIGNAL GPIO_NUM_21	// Remote IR source


// I2S DAC or PDM output
//-----------------------
#define PIN_I2S_LRCK GPIO_NUM_25
#define PIN_I2S_BCLK GPIO_NUM_26
#define PIN_I2S_DATA GPIO_NUM_22

```
#### Oled and lcd support
The type of lcd can be set with the uart or telnet command sys.lcd("x")<BR/>
Status: Ready.<BR/>
Other type and some color lcd added later.<BR/>
```
// min 128x64
#define LCD_I2C			0
#define LCD_NONE		255

// Black&White
//I2C
#define LCD_I2C_SH1106		0 //128X64
#define LCD_I2C_SSD1306		1 //128X64
#define LCD_I2C_SSD1309		2 //128X64
#define LCD_I2C_SSD1325 	3 //128X64
#define LCD_I2C_SSD1306NN	4 //128X64
#define LCD_I2C_SSD1309NN	5 //128X64
//SPI
#define LCD_SPI_SSD1306 		64 //128X32 (LCD_SPI =0x40)
#define LCD_SPI_SSD1309 		65 //128X64
#define LCD_SPI_ST7565_ZOLEN	66 //128X64
#define LCD_SPI_SSD1322_NHD		67 //256X64
#define LCD_SPI_IL3820_V2		68 //296X128
#define LCD_SPI_SSD1607			69 //200X200
#define LCD_SPI_LS013B7DH03		70 //128X128
#define LCD_SPI_SSD1306NN 		71 //128X64
#define LCD_SPI_SSD1309NN 		72 //128X64

// Colors
#define LCD_SPI_ST7735			192 // 128x160  (LCD_COLOR|LCD_SPI =0xC0)
#define LCD_SPI_SSD1351			193 // 128x128
#define LCD_SPI_ILI9341			194 // 240x320
#define LCD_SPI_ILI9163			195 // 128x128
#define LCD_SPI_PCF8833			196 // 132x132
#define LCD_SPI_SSD1331			197 // 96x64
#define LCD_SPI_SEPS225			198 // 96x64

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

<img src="https://github.com/karawin/Ka-Radio32/blob/master/images/karawin32Flash.jpg" alt="screenshot" border=0> 
<br/><br/>
The scheme from tomasf71</br>
<img src="https://github.com/karawin/Ka-Radio32/blob/master/images/schemekaradio32.jpg" alt="scheme" border=0> 
<br/>

#### List of sources and components adapted for KaRadio32
<br/>
https://github.com/espressif/esp-idf  the espressif IDF<br/>
https://hackaday.io/project/11570-wifi-webradio-with-esp8266-and-vs1053  The esp8266 KaRadio<br/>
https://github.com/karawin/karadio-addons  The KaRadio addons<br/>
https://github.com/kodera2t/ESP32_OLED_webradio  webradio for ESP-ADB module<br/>
https://github.com/MrBuddyCasino/ESP32_MP3_Decoder  webradio with the MP3 decoder software<br/>
https://github.com/olikraus/u8g2  Black/White oled lcd library<br/>
https://github.com/nkolban/esp32-snippets/tree/master/hardware/displays/U8G2  u8g2 Hal for esp32<br/>
https://github.com/soligen2010/encoder  Encoder<br/>



