<?php header("Access-Control-Allow-Origin: *"); ?>
<html>
<body>
	<ul id="ordered">
		<li> 1.9 R8: 
		<ul id="ordered">
		<li>vs1053b code cleaning</li>
		<li></li>
		</ul></li>	
		<li> 1.9 R7: 
		<ul id="ordered">
		<li>New vs1053b patch Rev 2.9 .</li>
		<li></li>
		</ul></li>	
		<li> 1.9 R6: 
		<ul id="ordered">
		<li>Parse playlist fix.</li>
		<li></li>
		</ul></li>
		<li> 1.9 R5: 
		<ul id="ordered">
		<li>json parsing correction for char " in a string</li>
		<li></li>
		</ul></li>
		<li> 1.9 R4: 
		<ul id="ordered">
		<li>LWIP layer tuned. Better errno 11 computing.</li>
		</ul>
		<li> 1.9 R3: 
		<ul id="ordered">
		<li>Instant play: new button "Add/Edit", and update fields on cli commands.</li>
		</ul>
		<li> 1.9 R2: 
		<ul id="ordered">
		<li>AP mode no working. A wrong lwip was the cause. Now 192.168.4.1 is working.</li>
		</ul>
		<li> 1.9 R1: 
		<ul id="ordered">
		<li>Keyboard on web page correction.</li>
		<li>cli.list correction.</li>
		</ul>
		<li> 1.9 R0: 
		<ul id="ordered">
		<li>Use of the RTOS SDK 2.0.0.</li>
		</ul>
    </ul>

    <ul id="ordered">
		<li> 1.8 R2: 
		<ul id="ordered">
		<li>Attempt to tune the scarse memory!.</li>
		</ul><li> 1.8 R1: 
		<ul id="ordered">
		<li>Corrected: Drag/drop and save list on web edit panel.</li>
		</ul></li>
		<li>1.8:</li>
		<ul id="ordered">
		<li>New edit panel with play/stop control</li>
		<li>New volume control on web with Ctrl arrow keys</li>
		<li>New upgrade indication on telnet, serial and web</li>
		<li>Web page look changed (a bit),</li>
		<li>Added the TZO on the setting page</li>
		<li>Added the mDNS hostname on the setting page</li>
		</ul></li>	
    </ul>

    <ul id="ordered">
		<li>1.7.1: Title on the web page</li>
		<li>1.7  : mDNS added, web commands next and prev, cli.host command added</li>
		<li>1.6.3: Correction for stations with the char & in path. </li>
		<li>1.6.2: R4 ntp server changed. </li>
		<li>1.6.2: R3 removes a bug on telnet whick block the web display.. </li>
		<li>1.6.2: Add of the rssi (Received Signal Strength Indication -30:best, -99:worst) at top right of the web page. </li>
		<li>1.6.1: Click on the header to rewind to the top </li>
		<li>Header stays on top of the web page </li>
		<li>gzipped html tranfert. More stable and improved speed</li>
		<li>The page content follows the header size.</li>
    </ul>

<font color="#14A692">Release 1.5.2 </font>  <br/>
    <ul>
		<li>Deeply tuned and optimized</li></br>
		<li>Added: a button erase on the station edit</li></br>
		<li>Little change of the menu labels.</li></br>
		<li>If the same meta is repeated in the stream, it is filtered</li></br>
		<li>telnet server now accepts the negociation.</li></br>
		<li>Only one task for all servers: websocket, web interface and telnet.</li><br>
		<li>Optimized threshold to start playing.It depends now of the size of the reception buffer.</li></br>
		<li>New web command: version, infos and list. See the interface.txt file on setting menu.</li><br>
    </ul>
<font color="#14A692">Release 1.4.2 </font>  <br/>
    <ul>
		<li>Unable to make the Espressif RTOS SDK 1.5.0-dev working, so I fed up.</li></br>
		<li>This 1.4.2 is able to play every 320Kb/s stations.</li></br>
		<li>New command: sys.version : Display the current Release and Revision.</li></br>
		<li>As always, more free ram memories. The websocket and telnet tasks are now one task for both.</li></br>
		<li>The web interface loading speed is improved.</li><br>
		<li>cli.list doesn't display anymore empty slot of stations.</li><br>
    </ul>
<font color="#14A692">Release 1.4 </font>  <br/>
    <ul>
		<li>A telnet server multi clients on port 23. It is the same interface as the uart one. So the low level management can be done via the network and it offer a complete interface for remote addons.</li></br>
		<li>A deep modification of the memory management. More free room.</li></br>
		<li>new commands: help and sys.adc.</li><br>
		<li>The web volume command is now on a POST if the websocket is not ready.</li></br>
    </ul>
	</br>
    <ul>
		<li>a problem on the web interface close resolved.</li><br>
    </ul>
<font color="#14A692">Release 1.3.4 </font>  <br/>
   <ul>
		<li>Internal optimization on websocket. More free ram for the web interface multi-user.</li><br>
		<li>1.3.3 A problem when a control panel and an addon are present is removed</li><br>
		<li>1.3.3A problem with the AP2 password not working is removed (regression).</li><br>
    </ul>
<font color="#14A692">Release 1.3.2 </font>  <br/>
<ul>
		<li>The test task is replaced with an os timer to have more free memories</li><br>
		<li>Edit station now in modal window</li><br>
		<li> Added a mouse event on full url</li><br/>
		<li>Many internal optimizations</li><br/>
		<li>New control buttons on the web interface</li><br/>
		<li>A potential huge bug removed</li><br/>
 </ul>
<font color="#14A692">Release 1.2.2 </font>  <br/>
<ul>
		<li>Volume correction for the control panel.</li></br>
		<li>The volume is now saved every second if needed (less stress for the flash).</li></br>
		<li>Stability</li></br>
		<li>New uart command: <code>sys.date</code> Send a ntp request and Display the current locale time.</li></br>
		<li>New uart command: <code>sys.tzo</code> Display or change the timezone offset. See Interface.txt.</li></br>
		<li>New No needs to parse the url of stations on the web interface. Now it can be done automatically.</li>
</ul>		
<font color="#14A692">Release 1.1.8 </font>  <br/>
- New uart command: cli.info   Display nameSet, all icy and volume. Used to synchronize the lcd extension.<br/>
- cli.list command modified.<br/>
<font color="#14A692">Release 1.1.7+ </font>  <br/>
- Now Both AP SSID and AP Password are encoded to permit special characters like & : etc<BR/>
- "Restore stations" corrected for some heavy lists<BR/>
- Station information now gives the number of the current station<BR/>
- retry client connection modified to avoid blocking situation.<br/>
- (1.1.7+) Volume offset on playlist was not working.<br/>
<font color="#14A692">Release 1.1.6 </font>  <br/>
- Modification of the list of uart command. See  <a href="http://karadio.karawin.fr/Interface.txt"  target="_blank"><font color="#14A692">uart and html interfaces</font></a><br/>
- New sys.patch command. Inhibit or permit (default) the load of a vs1053 patch for AAC stations.<BR/>
- New sys.led command. Default is blinking mode, or Play mode: the led is on when a station is playing.</br>
- Modification of the wifi.con command. Now the AP can be set in the AP mode (192.168.4.1) without the need of the web interface.</br>
- New print button on the Stations panel: Print the list of stations, number and name.<br/>
- New logo ;-)<br/>
<font color="#14A692">Release 1.1.5 </font>  <br/>
- Modification of the list of uart command. See  <a href="http://karadio.karawin.fr/Interface.txt"  target="_blank"><font color="#14A692">uart and html interfaces</font></a><br/>
- New IR and LCD software<BR/>
- Autoplay corrected</br>
<font color="#14A692">Release 1.1.4 </font>  <br/>
- Now 2 AP's can be set. The second one will be tested if the first is not detected.<br/>
- The Mac address of the radio is displayed<BR/>
- An offset volume can be set for each station in Station editor.<br/>
- Pb on Autostart not correctly checked: corrected<br/>
- Added: a reset button for the equalizer<br/>
- Added a new uart command: cli.boot<br/>
<font color="#14A692">Release 1.1.3 </font>  <br/>
- New html command: instant="http://your url"<br/>
- The path of a station can now include some & parameters.<BR/>
<font color="#14A692">Release 1.1.2 </font>  <br/>
- uart command list now can take a parameter: the number of the station to display.<br/>
.If no parameter, the complete list is sent.<br/>
- New wake and sleep features. Two modes: Time mode: "hh:mm" to wake or sleep at a given hour, or the delay mode "mm".<BR/>
- Many minors html adjustments.<BR/>
- Many bugs removed thanks to users feedback's.<BR/>
<font color="#14A692">Release 1.1.1 </font>  <br/>
- The user agent for http request can be set for some special streams.<br/>
&nbsp&nbsp&nbspExample: http://pcradio.ru/player/listradio/pcradio_ru.xml which need a user agent= pcradio.<br/>
&nbsp&nbsp&nbspThis pcradio user agent is already implemented automatically in the code when a pcradio station is encountered.<br/>
- Better station start and stop. (no more strange noises).<BR/>
- Many bugs removed thanks to users feedback's.
<BR/>
<font color="#14A692">Release 1.1.0 </font>  <br/>
- Drag an drop on the stations list: rearrange the list by dragging a line to another one. Save the change when asked.<br/>
- Themes toggle between light blue and dark marron theme with a click on the logo.<br/>
- Sleep mode to stop the play after a delay.<br/>
- Functions on the web page are optimized. <br/>
- Many minor improvements on the code and the web page.<br/>
<font color="#14A692">Release 1.0.10 </font>  <br/>
- New uart interface command: cli.uart("x")<br/>
 With x the uart baudrate at the next reset and permanently.<br/>
List of valid baudrate: 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 76880, 115200, 230400<br/>
The command will reply with<br/>
##CLI.UART= 115200# on the next reset.<br/>
- New Station selection with number<br/>
- Stations management in one page<br/>
- abort button on station edition.<br/>
<font color="red">Corrected:</font><br/>
- The I2S interface was not working. Thanks  Discover1977 for the test<BR/>
<font color="#14A692">Release 1.0.9 </font>  <br/>
- New html interface see  <a href="http://karadio.karawin.fr/Interface.txt"  target="_blank"><font color="#14A692">uart and html interfaces</font></a><br/>
- New I2S external DAC interface on the vs1053. The I2S is enabled by default to 48kHz. To change the speed permanently use the uart interface with the command 
	cli.i2s("x") with x =0 for 48kHz, x=1 for 96kHz and x=2 for 192kHz<br/>
	The i2s interface is available on the alientek vs1053 with i2s_sclk on SCLK (GPIO16), i2s_sdata on SDIN (GPIO07), i2s_mclk on MCLK (GPIO05), i2s_lrout on LRCK (GPIO04).<br/>
- New Autostart: If autoplay is checked on the web interface, the current station is started at power on even with no web browser.<br/>
<font color="#14A692">Release 1.0.8 </font>  <br/>
- Corrected: <br/>
Some chunked html stations was wrong.<BR/>
If no metadata, the station name is displayed in place<BR/>
A station not found is indicated in the name on the web interface<BR/>

<font color="#14A692">Release 1.0.7 </font>  <br/>
- Corrected: The webstation lists was wrong on empty station.<BR/>
<font color="#14A692">Release 1.0.6 </font>  <br/>
- New sdk patch from Espressif see <a href="http://bbs.espressif.com/viewtopic.php?f=46&t=2349" target="_blank">http://bbs.espressif.com/viewtopic.php?f=46&t=2349</a> <BR/>
- Now the maximum number of stations is 256<BR/>
- Detection of external ram is working. If your chip has a /Vhold in place of /VBAT, the pin 7 must be wired to VCC (pin8)<BR/>
- Save stations from... now working with the right filename for edge browser<BR/>
- The AP Password field is masked.<BR/>
- Increased spi clock for external ram<BR/>
    </body>
</html>


