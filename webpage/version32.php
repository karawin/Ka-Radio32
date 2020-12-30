<?php header('Access-Control-Allow-Origin: *'); ?>
<!DOCTYPE html>
<html>
<body>

    <p><span class="label label-success">Release <span id="firmware_last">1.9  Rev 9</span> - Built on 2020/12/30
	</span>
	</p>	
    New:
    <ul id="ordered">
		<li> 1.9 R9: 
		<ul id="ordered">
		<li>VS1053b detection improved.</li>
		<li>Now ogg stream are played with the vs1053b</li>
		<li>No more glitch with the vs1053b</li>
		<li></li>
		</ul></li>		
		<li> 1.9 R8: 
		<ul id="ordered">
		<li>Add Battery level</li>
		<li>Add SPDIF output. Thanks to R3D4</li>
		<li>VS1053 patch V2.9 updated</li>
		<li></li>
		</ul></li>
		<li> 1.9 R7: 
		<ul id="ordered">
		<li>New telnet or serial commands: cli.wake, cli.sleep:<BR>
		cli.wake("x"):  x in minutes. Start or stop the wake function. A value 0 stop the wake timer<BR>
cli.sleep("x"):  x in minutes. Start or stop the sleep function. A value 0 stop the sleep timer<BR>
cli.wake: Display the current value in seconds<BR>
cli.Sleep: Display the current value in seconds<BR>
</li>
		<li>sys.lcdstop, sys.lcdblv:<BR>
sys.lcdstop and sys.lcdstop("x"): Timer in seconds to switch off the lcd on stop mode. 0= no timer<BR>
sys.lcdblv and sys.lcdblv("x"): Value in percent of the backlight.<BR>	
		</li>
		<li>Fade in and out for backlight driven by a gpio.</li>
		<li>New tool and hardware partition from Bazooka07:<BR>
		Update for boards/nvs_generator.sh<BR>

use nvs_partition_gen.py tool directly from $IDF_PATH folder<BR>
can process one or all boards in one shot.<BR>
Update size for binary partition : 0x3000 now ! Look at :<BR>
https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/storage/nvs_partition_gen.html#running-the-utility</li>
		<li>Decode url correctly for /webStation. included name #149</li>
		<li>Esp-idf Release 3.3.1</li>
		</ul></li>
		<li> 1.9 R6: 
		<ul id="ordered">
		<li>pull request from Bazooka07: Parse playlist fix.</li>
		<li></li>
		</ul></li>
		<li> 1.9 R5: 
		<ul id="ordered">
		<li>json parsing correction for char " in a string</li>
		<li></li>
		</ul></li>
		<li> 1.9 R4: 
		<ul id="ordered">
		<li>wifi.auto command now disable the AP mode if already connected to an AP in the past.</li>
		<li>I2S corrected for 32bit output stream. Thanks to har-in-air github user. </li>
		<li>Instant play: new button "Add/Edit", and update fields on cli commands. </li>
		<li></li>
		</ul></li>
		<li> 1.9 R3: 
		<ul id="ordered">
		<li>blank password accepted.</li>
		<li>New lcd types: LCD_I2C_ST7567, LCD_SPI_ST7567_pi , LCD_SPI_ST7567, LCD_SPI_ST7565_NHD_C12864</li>
		<li>New nvs_partition_generator.sh and nvs_partition_gen.py: comment line # comment, now permitted. </li>
		<li>cli.list correction.</li>
		<li>Minor corrections.</li>
		<li></li>
		</ul></li>
		<li> 1.9 R2: 
		<ul id="ordered">
		<li>New option for the active level of buttons.</li>
		<li>Little bug removed on color lcd.</li>
		<li>Telnet disabled in AP mode.</li>
		<li>Key Ctrl space, Ctrl left, ctrl right, ctrl top, ctrl bottom  on web page for control.</li>
		</ul></li>
		<li> 1.9 R1: 
		<ul id="ordered">
		<li>Labels in the csv hardware configuration.</li>
		<li>Toggle main/time now permanent. On time display, an event go to the main screen for 3 seconds then return to time screen.</li>
		<li>More reactive display on lcd.</li>
		</ul></li>
		<li> 1.9 R0: 
		<ul id="ordered">
		<li>Improved encoder for new chinese device (shorter pulses) (reverse A/B in case of reverse way)</li>
		<li>Better vs1053 detection.</li>
		<li>No more fall back to i2s when the vs1053 is not detected.</li>
		<li>RSSI display needed a click of a button to start.</li>
		<li>AP mode on init: the web page starts on the "Setting" panel and the stations list is skipped.</li>
		<li>Wifi option: If wifi is disconnected choose to reset or wait for the connection  on the same SSID:</li>
		<li>Command wifi.auto("x") with x = 0: reboot, x=1: wait for the SSID </li>
		<li>For internal reasons, the touch screen needs to be calibrated again.</li>
		<li>Many small improvements in the code.</li>
		</ul></li>
    </ul>
	</br></br>
	</p>
</body>
</html>