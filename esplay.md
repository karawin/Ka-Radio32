#  Flashing esplay 

## With the ESP32 DOWNLOAD TOOL

All files can be foud at [https://github.com/karawin/Ka-Radio32/tree/master/binaries]

![download tool](http://karadio.karawin.fr/images/esplay.jpg)

# Initial configuration

If the access point of your router is not known, the webradio initializes itself as an AP (access point: it delivers a WIFI SSID).  
 
Connect the wifi of your computer to the ssid "WifiKaRadio",  
Browse to 192.168.4.1 to display the configuration page, 
 
go to "setting" "Wifi" and  

**configure:**  
* your ssid ap, the password if any, 
* the wanted IP or use dhcp if you know how to retrieve the dhcp given ip (terminal or scan of the network).  

In the gateway field, enter the ip address of your router. 
 
**Validate**.  

The equipment restart to the new configuration.  
Connect your wifi to your AP and browse to the ip given in configuration. 
 
Congratulation, you can edit your own station list.  
Don't forget to save your stations list in case of problem or for new equipments.

If the AP is already know by the esp32, the default ip is given by dhcp.  
A sample of stations list is on :  
[http://karadio.karawin.fr/WebStations.txt] .  
Can be uploaded via the web page.


# Commands

Volume + : **R or Right**  
Volume - : **L or Left**

Station + : **Up**  
Station - : **Down**

Start/Stop : **Start or Menu**  

Toggle Time/Webradio : **Select**

Backlight + : B
Backlight - : A


   