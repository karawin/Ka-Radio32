# Interfaces of KaRadio and KaRadio32
____________________________________

## HTML interface for the Wifi Webradio
Any browser or wget can be used to send basic commands to the webradio.  
A command format is http://yourip/?command[&command]  
If a command return some informations, it must be the last of the list or alone.

## Commands:  
- version		: return 'Release: x.x, Revision: x'  
- infos			: return   
				vol: 46						:the current volume  
				num: 240						:the current station number  
				stn: Hotmix 80					:the name of the current station  
				tit: BANANARAMA - Venus 		:the title of the son playing  
				sts: 1							:the state of the player: 0 stopped, 1:   playing.
- list=xxx		: return the name of the station xxx (0 to 254)				
- stop			: stop playing the current station.
- start			: start playing the current station.
- next			: play the next station
- prev			: play the previous station
- play=xxx		: with xxx from 0 to 254  play the station xxx
- volume=xxx		: with xxx from 0 to 254  change the volume to xxx
- volume+		: increment the volume by 5
- volume-		: decrement the volume by -5
- uart			: uart baudrate at 115200 not saved on next reset
- instant="http://your url" : instant play a site  
Example: http://192.168.1.253/?instant=http://api.voicerss.org/?f=32khz_16bit_stereo&key=29334415954d491b85535df4eb4dd821&hl=en-us&src=hello?the-sun-is-yellow?and-i-like-it"  
the url must begin with http:// and be surrounded by " and no space char allowed.

Volume may be combined with other command.  
Example: 192.168.1.253/?volume=50&play=128&infos

Reminder: the url without parameter is the full web interface.



-------------------------------------------------
## Serial ot telnet interface for the Wifi Webradio


The serial inteface can be used to receive events from the webradio and to send commands to it.  
The telnet interface is reached by the port 23.  
The serial interface adds the logs output of the tasks.  

Example of indications received: 
```
##CLI.STOPPED# from playStationInt
##CLI.NAMESET#: 88 Public Domain Classical - Swiss Internet Radio
##CLI.URLSET#: 82.197.165.137
##CLI.PATHSET#: /
##CLI.PORTSET#: 80
##CLI.OVOLSET#: 0
##CLI.VOL#: 110
##CLI.ICY0#: Public Domain Classical - Swiss Internet Radio - Shoutcast Streaming Technology by www.init7.net
##CLI.ICY1#: <BR>This stream requires <a href="http://www.winamp.com/">Winamp</a><BR>
##CLI.ICY2#: SHOUTcast Distributed Network Audio Server/Linux v1.9.8<BR>
##CLI.ICY3#: http://publicdomainproject.org
##CLI.ICY4#: Classical
##CLI.ICY5#: 128
##CLI.META#: Felix Mendelssohn-Bartholdy - String Quartet in E flat major Op. 44 No.3: 4. Molto allegro con fuoco
##CLI.PLAYING#
##CLI.STOPPED# from playStationInt
##CLI.NAMESET#: 92 ALBUMROCK.MIAMI
##CLI.URLSET#: uk4.internet-radio.com
##CLI.PATHSET#: /
##CLI.PORTSET#: 8081
##CLI.OVOLSET#: 0
##CLI.VOL#: 110
##CLI.ICY0#: ALBUMROCK.MIAMI
##CLI.ICY1#: <BR>This stream requires <a href="http://www.winamp.com/">Winamp</a><BR>
##CLI.ICY2#: SHOUTcast Distributed Network Audio Server/Linux v1.9.8<BR>
##CLI.ICY3#: www.AlbumRock.Miami
##CLI.ICY4#: Classic  Rock 60s 70s 80s Miaimi Florida  Album Rock
##CLI.ICY5#: 128
##CLI.META#: The Who - Eminence Front 
##CLI.PLAYING#
#CLI.LIST#
#CLI.LISTINFO#:   2: RTL2, streaming.radio.rtl.fr:80/rtl2-1-44-128.m3u
##CLI.LIST#
(cli.info) typed
##CLI.NAMESET#: 92 ALBUMROCK.MIAMI
##CLI.ICY0#: ALBUMROCK.MIAMI
##CLI.ICY1#: <BR>This stream requires <a href="http://www.winamp.com/">Winamp</a><BR>
##CLI.ICY2#: SHOUTcast Distributed Network Audio Server/Linux v1.9.8<BR>
##CLI.ICY3#: www.AlbumRock.Miami
##CLI.ICY4#: Classic  Rock 60s 70s 80s Miaimi Florida  Album Rock
##CLI.ICY5#: 128
##CLI.ICY6#: 
##CLI.ICY7#: 
##CLI.META#: The Who - Eminence Front
##CLI.VOL#: 108
##CLI.PLAYING#
##CLI.META#: The Beatles - Mother Nature's Son 
##SYS.TZO#: 1
##SYS.DATE#: 2017-04-13T22:47:44+01:00
```

with ICYx: 0:"icy-name:", 1:"icy-notice1:", 2:"icy-notice2:",  3:"icy-url:", 4:"icy-genre:", 5:"icy-br:", 6:"icy-description:", 7:"ice-audio-info:"  
Some other informations may be printed for debug purpose, but usefull events always start with ##


## Commands:

### Wifi related commands
```
wifi.list			: give the list of received SSID
wifi.con			: Display the AP1 and AP2 SSID
wifi.con("ssid","password")	: Record the given AP ssid with password in AP1 for next reboot
wifi.discon			: disconnect the current ssid
wifi.station		: the current ssid and password
wifi.status			: give #WIFI.STATUS#			start of the answer
				5						the connection state
				192.168.1.40			the current ip
				255.255.255.0			the network mask
				192.168.1.70			the network gateway
				##WIFI.STATUS#			end of the answer
wifi.rssi			: print the current rssi (reception level)
```				

### Station Client commands
```
// instant play
cli.url("url")		: the name or ip of the station to instant play
cli.path("/path")	: the path of the station to instant play
cli.port("xxxx")	: the port number of the station to instant play
cli.instant:		: play the instant station
// Stations play					
cli.start			: start to play the current station
cli.play("xxx")		: play the xxx recorded station in the list (0 = stop)
cli.prev (or cli.previous)	: select the previous station in the list and play it
cli.next			: select the next station in the list and play it
// Station stop
cli.stop			: stop the playing station or instant
// station list
cli.list			: list all recorded stations
cli.list("x")		: list only one of the recorded stations. Answer with #CLI.LISTINFO#: followed by infos
// volume commands
cli.vol("xxx")		: set the volume to xxx with xxx from 0 to 254 (max volume)
cli.vol				: ask for  the current volume. respond with ##CLI.VOL# xxx
cli.vol-			: Decrement the volume by 10
cli.vol+			: Increment the volume by 10
Every vol command from uart or web or browser respond with ##CLI.VOL#: xxx
// Wake and sleep timers
cli.wake(\"x\")		:  x in minutes. Start or stop the wake function. A value 0 stop the wake timer
cli.sleep(\"x\")	:  x in minutes. Start or stop the sleep function. A value 0 stop the sleep timer
cli.wake			: Display the current value in secondes\n\
cli.Sleep			: Display the current value in secondes\n\

// Client information
cli.info			: Respond with nameset, all icy, meta, volume and stae playing or stopped. Used to refresh the lcd informations
					: see Example of indications received
```
### System commands
```
sys.uart("x")	: Change the baudrate of the uart on the next reset. 
			Valid x are: 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 76880, 115200, 230400	
sys.i2s			: Display the current I2S speed			
sys.i2s("x")	: Change and record the I2S clock speed of the vs1053 GPIO5 MCLK for the i2s interface to external dac. 
				: 0=48kHz, 1=96kHz, 2=192kHz, other equal 0
sys.erase		: erase all recorded configuration and stations. Dangerous command.
sys.heap		: show the ram heap size
sys.update		: start an OTA (On The Air) update of the software
sys.prerelease	: start an OTA of the prerelease for test purpose.
sys.boot		: reboot the webradio.
sys.patch("x")	: Change the status of the vs1053 patch at power on. 
				  0 = Patch will not be loaded, 1 or up = Patch will be loaded (default) at power On
sys.patch		: Display the vs1053 patch status
sys.led("x")	: Change the led indication: 
				  1 = Led is in Play mode (lighted when a station is playing), 0 = Led is in Blink mode (default)
sys.led			: Display the led indication status
sys.tzo("h:m")	: Set the timezone offset of your country.
sys.tzo			: Display the timezone offset
sys.date		: Send a ntp request and Display the current locale time
				: Format ISO-8601 local time   https://www.w3.org/TR/NOTE-datetime
				: YYYY-MM-DDThh:mm:ssTZD (eg 2017-07-16T19:20:30+01:00)
sys.adc			: Read the current value of the adc input. (Not for KaRadio32)
sys.log			: Do nothing. Used for debug of the addon.	
sys.version		: Display the release and Revision of KaraDio
sys.host		: display the hostname for mDNS			
sys.host("your hostname"): change and display the hostname for mDNS
```
### Other
```
<enter> will display 
#INFO:""#

help			: list the available commands.
```
A command error display:
```
##CMD_ERROR#
```
### Extension for KaRadio32 only:
```
sys.dlog		: Display the current log level
sys.logx		: Set log level to x with x=n for none, v for verbose, d for debug, i for info, w for warning, e for error
sys.lcdout		: Display the timer to switch off the lcd. 0= no timer
sys.lcdout("x")	: Timer in seconds to switch off the lcd. 0= no timer
sys.lcdstop		: Display the timer to switch off the lcd on stop. 0= no timer
sys.lcdstop("x"): Timer in seconds to switch off the lcd on stop. 0= no timer
sys.lcdblv		: Display current backlight percent value.
sys.lcdblv("x")	: Set the backlight percent value (if the hardware provide it) (range 1 to 100)
sys.lcd			: Display the current lcd type
sys.lcd("x")	: Change the lcd type to x on next reset
sys.ledgpio		: Display the default Led GPIO
sys.ledgpio("x"): Change the default Led GPIO (4) to x
sys.ddmm: display the date format
sys.ddmm("x"): Change the date format. 0:MMDD, 1:DDMM
sys.rotat: display the lcd rotation option
sys.rotat("x"): Change and display the lcd rotation option (reset needed). 0:no rotation, 1: rotation
sys.henc0 or sys.henc1: Display the current step setting for the encoder. Normal= 4 steps/notch, Half: 2 steps/notch
sys.henc0("x") with x=0 Normal, x=1 Half
sys.henc1("x") with x=0 Normal, x=1 Half
sys.cali[brate]: start a touch screen calibration
sys.ledpola and sys.ledpola("x"): display or set the polarity of the system led
sys.conf: Display the labels of the csv file.
```