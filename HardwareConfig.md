# Hardware configuration partition

Version 1.5 and up of KaRadio32 allows you to configure gpio's and two custom IR keys per action.  
This allows you to take advantage of the standard software even if your port configuration and/or your remote control are not the same.  
The configuration must be specified in a csv file.  
A template is given by the pattern.csv file
The default configuration of the current software is in the standard_adb.csv file.  
A csv file is interpreted by an utility to generate a bin file that must be flashed at address 0x3a2000 only one time per esp32

The msys32 and esp-idf environment must be operational.

---------------
1/ Prerequisite
---------------
First, make sure you have an updated partitions.bin file.
This file contains the system partitions:
```
$ make partition_table
Toolchain path: /opt/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc
Toolchain version: crosstool-ng-1.22.0-80-g6c4433a5
Compiler version: 5.2.0
Python requirements from C:/msys32/home/jp/esp/esp-idf/requirements.txt are satisfied.
Partition table binary generated. Contents:
*******************************************************************************
# Espressif ESP32 Partition Table
# Name, Type, SubType, Offset, Size, Flags
nvs,data,nvs,0x9000,16K,
otadata,data,ota,0xd000,8K,
phy_init,data,phy,0xf000,4K,
ota_0,app,ota_0,0x10000,1792K,
ota_1,app,ota_1,0x1d0000,1792K,
device,64,0,0x390000,4K,
stations,65,0,0x391000,64K,
device1,66,0,0x3a1000,4K,
hardware,data,nvs,0x3a2000,8K,
*******************************************************************************
Partition flashing command:
python /home/jp/esp/esp-idf/components/esptool_py/esptool/esptool.py --chip esp32 --port com5 --baud 460800 --before default_reset --after hard_reset write_flash 0x8000 /home/jp/esp/Ka-Radio32/build/partitions.bin
************************************************ *****************************
```
Compared to an old version, it adds the declaration of the partition "hardware" which interests us.

Rename the pattern.csv file with the name of your c
ard, for example lolin32.csv  
Beware: not comment line or empty line allowed in a csv file.

#### WARNING:
The declaration of gpio's is a not so easy task.  
Any error results in an incorrect start of the software.  
If the software does not start properly, please check your values.  
A common mistake is to declare the same number for two functions.  
See the log on the serial interface.

-----------------------
2/ Definition of gpio's
-----------------------
Edit this file to enter your gpio definitions.  
See gpio.h for the default values if missing in the csv file.  
Only modify the lines beginning with P_ by modifying only the last number.  
for example:  
P_MISO, data,u8,19  
Change 19 to the desired number.  
Do this for all P_ lines.  
Never change the string "P_XXXX, data,u8,"  
A value base 10 is mandatory for each P_.  

```
SPI Bus:  
K_SPI		Select the used spi : 1: HSPI, 2: VSPI
P_MISO		Master Input, Slave Output  
P_MOSI		Master Output, Slave Input   Named Data or SDA or D1 for oled  
P_CLK		Master clock  Named SCL or SCK or D0 for oled  

VS1053B:  
P_XCS			XCS  
P_RST			RST  
P_XDCS			XDCS  
P_DREQ			P_DREQ  

ENCODERS 0 & 1:  
P_ENC0_A			pin A clk  
P_ENC0_B			pin B Data  
P_ENC0_BTN			pin SW  
P_ENC1_A			pin A clk  
P_ENC1_B			pin B Data  
P_ENC1_BTN			pin SW  

BUTTONS PANEL 0 & 1 of three buttons (switch to gnd):  
P_BTN0_A		click:start/stop, double click:toggle, help: station  
P_BTN0_B		click: +  
P_BTN0_C		click: -  
P_BTN1_A		start/stop, toggle, volume  
P_BTN1_B		+  
P_BTN1_C		-  

Bus I2C (Oled & Lcd):  
P_I2C_SCL		SCL or SCK  
P_I2C_SDA		SDA  
P_I2C_RST		RST if any  

LCD on SPI bus:  
P_LCD_CS		CS  
P_LCD_A0		A0 or D/C or DC  
P_LCD_RST		RST or RES  

Infrared remote:  
P_IR_SIGNAL		ir Y Signal  

I2S bus:  
P_I2S_LRCK		LRCK  
P_I2S_BCLK		BCLK  
P_I2S_DATA		DATA  

ADC keyboard:  
P_ADC			gpio32 to 39  or 255 if not used.  

LCD Backlight:
P_BACKLIGHT		GPIO of the hardware device.
```

-------------------
## Special cases:
-------------------
### SPI bus

K_SPI,data,u8,2  
   2 is the spi VSPI_HOST (default)  
   1 is the spi HSPI_HOST  
   The spi bus is initialized in any case. It used for the vs1053 and/or the LCD if needed.
   

### Encoders

Two encoders maximun are supported, each with different actions:  
Encoder0: the volume control and stations change when pushed and held,  
Encoder1: the station control and volume change when pushed and heldi.  

If P_ENC0_A = 255 the encoder (P_ENC0_A, P_ENC0_B, P_ENC0_BTN) is disabled (not used, the gpio's may be reused elsewhere).    
If P_ENC1_A = 255 the encoder (P_ENC1_A, P_ENC1_B, P_ENC1_BTN) is disabled (not used, the gpio's may be reused elsewhere).  
If If P_ENC0_A is not 255 and P_ENC0_BTN = 255, the push button is disabled.  
If If P_ENC1_A is not 255 and P_ENC1_BTN = 255, the push button is disabled.  

### Buttons
Two set of three buttons can be configured in place or with encoder(s). The only limit is the available gpio's.  
Each set has functions equivalent to Encoder0 and Encoder1:  
click on button A: Start/Stop playing  
click on button B and C: volume down and up for set 0 (P_BTN0), Station down and up for set 1 (P_BTN1)  
held on button A: click on button B and C: volume down and up for set 1 (P_BTN1), Station down and up for set 0 (P_BTN0)  

If a set is not used, P_BTNx_A must be set to 255. In this case P_BTNx_B P_BTNx_C are disabled too.

### I2C
If I2C is not used (ie no lcd or spi lcd) the gpio of the i2C can be reused elsewhere.  
To disable I2C even a I2C LCD is used: P_I2S_LRCK	and/or P_I2S_BCLK	must be set to 255  

### VS1053b
If not used P_XCS must be set to 255. Gpio of P_RST P_XDCS P_DREQ may be reused elsewhere.  

### IR
If IR remote control is not used P_IR_SIGNAL must be set to 255

### ADC keyboard
If the ADC keyboard is missing, set P_ADC  to 255.  
Compatible with https://github.com/…/Ka-…/blob/master/Hardware/controles.pdf and the one found at https://www.drive2.ru/b/487463808323813881/  
The stop button is replaced with "Toggle Time/Infos" and "start replaced with "Start/Stop"  
The ESP32 ADC can be sensitive to noise leading to large discrepancies in ADC readings. To minimize noise, users may connect a 0.1uF capacitor to the ADC input pad in use

### Lcd backlight
Thanks to Vadim Polyakovsky:
> A small optional schematics update which allows to switch LCD backlight on and off in case of battery powered KaRadio. The switching off timeout in x sec could be defined by sys.lcdout("x") terminal command. The display and its' backlight will wake up automatically in case of new meta, encoder or IR event. This way the battery life on one charge will be extended. Obviously not needed for OLED displays and wall plug power socket operation. A software support is done by Jean-Pierre in the new custom.c file. A GPIO number could be chosen among not used ones and defined respectively. Enjoy!
 
This external device turns off the LCD backlight in addition to the screen clear.    
Usefull if a battery is used.  
If the hardware device is missing, set it to 255

![Screenshoot of download tool](http://karadio.karawin.fr/images/backlight.jpg)
---------------------
3/ IR key definitions
---------------------
If you use a remote control with different codes from the default ones, you can give your codes by key.
Two codes per key are possible:

For example for the K_OK key  
K_OK, data, string, 0xFF0040 0xFF0040  
or  
K_OK, data, string, 0xFF0040  
if you only have one code per key.  
or  
K_OK, data, string,  
if no code is given for the OK key  

Never change "K_XXXX,data,string,"  

Reminder: to see the code of a key on your remote control, change the log level to sys.logi  
Press a key and see the log. You will see something like that:  
I (1204396) addon: IR event: Channel: 0, ADDR: ff00, CMD: bf40 = FF0040, REPEAT: 0  
Where FF0040 is the 0xFF0040 code needed.  
```
The keys and actions are:
K_UP  		Change to next Station 
K_LEFT		Volume Down -5
K_OK		Toggle play/Stop
K_RIGHT		Volume up +5
K_DOWN		Change to previous station
K_0			Enter number of the wanted station
K_1			Enter number of the wanted station
K_2			Enter number of the wanted station
K_3			Enter number of the wanted station
K_4			Enter number of the wanted station
K_5			Enter number of the wanted station
K_6			Enter number of the wanted station
K_7			Enter number of the wanted station
K_8			Enter number of the wanted station
K_9			Enter number of the wanted station
K_STAR		Play
K_DIESE		Stop
K_INFO		Toggle time/info display
```
No comment is allowed in this csv file.  
Save the csv file.


------------------------
4/ Generating the bin
------------------------
Some samples are in the boards directory.   

Start the command  
`./nvs_partition_generator.sh yourname[.csv]`  
to generate build/yourname.bin

For example  
`  ./nvs_partition_generator.sh standard_adb`  

generates the build/standard_adb.bin file from the standard_adb.csv file
```
$ ./nvs_partition_generator.sh standard_adb
python ../esp-idf/components/nvs_flash/nvs_partition_generator/nvs_partition_gen.py standard_adb.csv build/standard_adb.bin 8KB
done
```


------------
5/ Flash the bin
------------
With ESP DOWNLOAD TOOL   
![Screenshoot of download tool](https://raw.githubusercontent.com/karawin/Ka-Radio32/master/images/downloadtool32.jpg)


or esptool.py command at address 0x3a2000  

It seems that there is a problem with this ESP DOWNLOAD TOOL for flashing the bin alone.  
In case of problem, flash it with another bin (bootloader.bin or KaRadio32.bin) 
 
This binary is to flash one time and on each modification of the csv.

Now you can enjoy the standart OTA. No needs to generate your own KaRadio32.bin.

JP 2018  