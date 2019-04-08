<?php header('Access-Control-Allow-Origin: *'); ?>
<!DOCTYPE html>
<html>
<body>

    <p><span class="label label-success">Release <span id="firmware_last">1.9  Rev 2</span> - Built on 2019/03/09
	</span>
	</p>	
    New:
    <ul id="ordered">
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