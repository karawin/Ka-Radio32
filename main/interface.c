/******************************************************************************
 * 
 * Copyright 2017 karawin (http://www.karawin.fr)
 *
*******************************************************************************/


#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

#include "interface.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "eeprom.h"
#include "ntp.h"
#include "webclient.h"
#include "webserver.h"
#include "vs1053.h"
#include "gpio.h"
#include "ota.h"
#include "spiram_fifo.h"
#include "addon.h"
#include "addonu8g2.h"
#include "app_main.h"
//#include "rda5807Task.c"
#include "ClickEncoder.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_system.h"
#include "mdns.h"

#include "esp_wifi.h"

char parslashquote[] = {"(\""};
char parquoteslash[] = {"\")"};
char msgsys[] = {"##SYS."};
char msgcli[] = {"##CLI."};

const char stritWIFISTATUS[]  = {"#WIFI.STATUS#\nIP: %d.%d.%d.%d\nMask: %d.%d.%d.%d\nGateway: %d.%d.%d.%d\n##WIFI.STATUS#\n"};
const char stritWIFISTATION[]  = {"#WIFI.STATION#\nSSID: %s\nPASSWORD: %s\n##WIFI.STATION#\n"};
const char stritPATCH[]  = {"#WIFI.PATCH#\nVS1053 Patch will be %s after power Off and On#\n##WIFI.PATCH#\n"};
const char stritCMDERROR[]  = {"##CMD_ERROR#\n"};
const char stritHELP0[]  = {"\
Commands:\n\
---------\n\
 Wifi related commands\n\
//////////////////\n\
wifi.lis or wifi.scan: give the list of received SSID\n\
wifi.con: Display the AP1 and AP2 SSID\n\
wifi.recon: Reconnect wifi if disconnected by wifi.discon\n\
wifi.con(\"ssid\",\"password\"): Record the given AP ssid with password in AP1 for next reboot\n\
wifi.discon: disconnect the current ssid\n\
wifi.station: the current ssid and password\n\
wifi.status: give the current IP GW and mask\n\
wifi.rssi: print the current rssi (power of the reception\n\n\
//////////////////\n\
  Station Client commands\n\
//////////////////\n\
cli.url(\"url\"): the name or ip of the station to instant play\n\
cli.path(\"/path\"): the path of the station to instant play\n\
cli.port(\"xxxx\"): the port number of the station to instant play\n\
cli.instant: play the instant station\n\
cli.start: start to play the current station\n\
cli.play(\"xxx\"): play the xxx recorded station in the list (0 = stop)\n\
"};

const char stritHELP1[]  = {"\
cli.prev (or cli.previous): select the previous station in the list and play it\n\
cli.next: select the next station in the list and play it\
cli.stop: stop the playing station or instant\n\
cli.list: list all recorded stations\n\
cli.list(\"x\"): list only one of the recorded stations. Answer with #CLI.LISTINFO#: followed by infos\n\
cli.vol(\"xxx\"): set the volume to xxx with xxx from 0 to 254 (max volume)\n\
cli.vol: ask for  the current volume. respond with ##CLI.VOL# xxx\n\
cli.vol-: Decrement the volume by 10 \n\
cli.vol+: Increment the volume by 10 \n\
Every vol command from uart or web or browser respond with ##CLI.VOL#: xxx\n\
cli.info: Respond with nameset, all icy, meta, volume and stae playing or stopped. Used to refresh the lcd informations \n\n\
//////////////////\n\
  System commands\n\
//////////////////\n\
sys.uart(\"x\"): Change the baudrate of the uart on the next reset.\n\
 Valid x are: 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 76880, 115200, 230400\n\
sys.i2s: Display the current I2S speed"\
};

const char stritHELP2[]  = {"\
sys.i2s(\"x\"): Change and record the I2S clock speed of the vs1053 GPIO5 MCLK for the i2s interface to external dac.\n\
: 0=48kHz, 1=96kHz, 2=192kHz, other equal 0\n\
sys.erase: erase all recorded configuration and stations.\n\
sys.heap: show the ram heap size\n\
sys.update: start an OTA (On The Air) update of the software\n\
sys.prerelease: start an OTA of the next prerelease\n\
sys.boot: reboot the webradio.\n\
sys.patch(\"x\"): Change the status of the vs1053 patch at power on.\n\
0 = Patch will not be loaded, 1 or up = Patch will be loaded (default) at power On \n\
sys.patch: Display the vs1053 patch status\n\
sys.led(\"x\"): Change the led indication:\n\
1 = Led is in Play mode (lighted when a station is playing), 0 = Led is in Blink mode (default)\n\
sys.led: Display the led indication status\n\
sys.version: Display the Release and Revision numbers\n\
sys.tzo(\"xx\"): Set the timezone offset of your country.\n\
"};

const char stritHELP3[]  = {"\
sys.tzo: Display the timezone offset\n\
sys.date: Send a ntp request and Display the current locale time\n\
:   Format ISO-8601 local time   https://www.w3.org/TR/NOTE-datetime\n\
:   YYYY-MM-DDThh:mm:ssTZD (eg 2017-07-16T19:20:30+01:00)\n\
sys.version: Display the release and Revision of KaraDio\n\
sys.dlog: Display the current log level\n\
sys.logx: Set log level to x with x=n for none, v for verbose, d for debug, i for info, w for warning, e for error\n\
sys.log: do nothing apart a trace on uart (debug use)\n\
sys.lcdout: Display the timer to switch off the lcd. 0= no timer\n\
sys.lcdout(\"x\"): Timer in seconds to switch off the lcd. 0= no timer\n\
sys.lcd: Display the current lcd type\n\
sys.lcd(\"x\"): Change the lcd type to x on next reset\n\
sys.ledgpio: Display the default Led GPIO\n\
sys.ledgpio(\"x\"): Change the default Led GPIO (4) to x\n\
"};
const char stritHELP4[]  = {"\
sys.ddmm: display the date format\n\
sys.ddmm(\"x\"): Change and display the date format. 0:MMDD, 1:DDMM\n\
sys.host: display the hostname for mDNS\n\
sys.host(\"your hostname\"): change and display the hostname for mDNS\n\
sys.rotat: display the lcd rotation option\n\
sys.rotat(\"x\"): Change and display the lcd rotation option (reset needed). 0:no rotation, 1: rotation\n\
sys.henc0 or sys.henc1: Display the current step setting for the encoder. Normal= 4 steps/notch, Half: 2 steps/notch\
sys.henc0(\"x\") with x=0 Normal, x=1 Half\
sys.henc1(\"x\") with x=0 Normal, x=1 Half\
///////////\n\
  Other\n\
///////////\n\
help: this command\n\
<enter> will display\n\
#INFO:\"\"#\n\
\n\
A command error display:\n\
##CMD_ERROR#\n\r"\
}; 

uint16_t currentStation = 0;
static uint8_t led_gpio = 255;
static IRAM_ATTR uint32_t lcd_out = 0xFFFFFFFF;
static esp_log_level_t s_log_default_level = CONFIG_LOG_BOOTLOADER_LEVEL;
extern void wsVol(char* vol);
extern void playStation(char* id);
void clientVol(char *s);

#define MAX_WIFI_STATIONS 50
bool inside = false;
static uint8_t ddmm;
static uint8_t rotat;
uint8_t getDdmm()
{
	return ddmm;
}
void setDdmm(uint8_t dm)
{
	ddmm = dm;
}
uint8_t getRotat()
{
	return rotat;
}
void setRotat(uint8_t dm)
{
	rotat = dm;
}
static bool autoWifi = true; // auto reconnect wifi if disconnected
bool getAutoWifi(void)
{ return autoWifi;}

void setVolumePlus()
{
	setRelVolume(10);
}
void setVolumeMinus()
{
	setRelVolume(-10);
}		
void setVolumew(char* vol)
{
	setVolume(vol);	
	wsVol(vol);
}	

uint16_t getCurrentStation()
{
	return currentStation;
}
void setCurrentStation( uint16_t cst)
{
	currentStation = cst;
}

unsigned short adcdiv;	

uint8_t startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
}

void readRssi()
{
	int8_t rssi = -30;
	wifi_ap_record_t wifidata;
    esp_wifi_sta_get_ap_info(&wifidata);
    if (wifidata.primary != 0) {
        rssi = wifidata.rssi;
 //       info.channel = wifidata.primary;
    }
//	rssi = wifi_station_get_rssi();
	kprintf("##RSSI: %d\n",rssi);
}

void printInfo(char* s)
{
	kprintf("#INFO:\"%s\"#\n", s);
}


const char htitle []  = {"\
=============================================================================\n \
             SSID                   |    RSSI    |           AUTH            \n\
=============================================================================\n\
"};
const char hscan1 []  = {"#WIFI.SCAN#\n Number of access points found: %d\n"};

void wifiScan()
{
// from https://github.com/VALERE91/ESP32_WifiScan
uint16_t number;
wifi_ap_record_t *records;
wifi_scan_config_t config = {
      .ssid = NULL,
      .bssid = NULL,
      .channel = 0,
      .show_hidden = true
};

	config.scan_type = WIFI_SCAN_TYPE_PASSIVE;
	config.scan_time.passive = 500;
	esp_wifi_scan_start(&config, true);
	esp_wifi_scan_get_ap_num(&number);
	records = malloc(sizeof(wifi_ap_record_t) * number);
	if (records == NULL) return;
	esp_wifi_scan_get_ap_records(&number, records); // get the records
	kprintf(hscan1,number);
    if (number == 0) {
		free (records);
         return ;
	}
	int i;
	kprintf(htitle);

	for (i=0; i<number; i++) {
         char *authmode;
         switch(records[i].authmode) {
            case WIFI_AUTH_OPEN:
               authmode = (char*)"WIFI_AUTH_OPEN";
               break;
            case WIFI_AUTH_WEP:
               authmode = (char*)"WIFI_AUTH_WEP";
               break;           
            case WIFI_AUTH_WPA_PSK:
               authmode = (char*)"WIFI_AUTH_WPA_PSK";
               break;           
            case WIFI_AUTH_WPA2_PSK:
               authmode = (char*)"WIFI_AUTH_WPA2_PSK";
               break;           
            case WIFI_AUTH_WPA_WPA2_PSK:
               authmode = (char*)"WIFI_AUTH_WPA_WPA2_PSK";
               break;
            default:
               authmode = (char*)"Unknown";
               break;
         }
         kprintf("%32.32s    |    % 4d    |    %22.22s\n",records[i].ssid, records[i].rssi, authmode);
	}
	kprintf("##WIFI.SCAN#: DONE\n");

	free (records);
}

void wifiConnect(char* cmd)
{
	int i;
	struct device_settings* devset = getDeviceSettings();
	for(i = 0; i < 32; i++) devset->ssid1[i] = 0;
	for(i = 0; i < 64; i++) devset->pass1[i] = 0;	
	char *t = strstr(cmd, parslashquote);
	if(t == 0)
	{
		kprintf(stritCMDERROR);
		free(devset);
		return;
	}
	char *t_end  = strstr(t, "\",\"");
	if(t_end == 0)
	{
		kprintf(stritCMDERROR);
		free(devset);
		return;
	}
	
	strncpy( devset->ssid1, (t+2), (t_end-t-2) );
	
	t = t_end+3;
	t_end = strstr(t, parquoteslash);
	if(t_end == 0)
	{
		kprintf(stritCMDERROR);
		free(devset);
		return;
	}
	
	strncpy( devset->pass1, t, (t_end-t)) ;
	devset->current_ap = 1;
	devset->dhcpEn1 = 1;
	saveDeviceSettings(devset);
	kprintf("#WIFI.CON#\n");
	kprintf("\n##AP1: %s with dhcp on next reset#\n",devset->ssid1);
	kprintf("##WIFI.CON#\n");
	free(devset);
}

void wifiConnectMem()
{
	
	struct device_settings* devset = getDeviceSettings();
	kprintf("#WIFI.CON#\n");
	kprintf("##AP1: %s#",devset->ssid1);
	kprintf("\n##AP2: %s#\n",devset->ssid2);
	kprintf("##WIFI.CON#\n");
	free(devset);
}

void wifiReConnect()
{
	if (autoWifi == false) esp_wifi_connect();
	autoWifi = true;
}

void wifiDisconnect()
{
	esp_err_t err;
	autoWifi = false;
	err=esp_wifi_disconnect();
	if(err== ESP_OK) kprintf("\n##WIFI.NOT_CONNECTED#");
	else kprintf("\n##WIFI.DISCONNECT_FAILED %d#",err);
}

void wifiStatus()
{
	tcpip_adapter_ip_info_t ipi;	
	tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ipi);
	kprintf(stritWIFISTATUS,
			  (ipi.ip.addr&0xff), ((ipi.ip.addr>>8)&0xff), ((ipi.ip.addr>>16)&0xff), ((ipi.ip.addr>>24)&0xff),
			 (ipi.netmask.addr&0xff), ((ipi.netmask.addr>>8)&0xff), ((ipi.netmask.addr>>16)&0xff), ((ipi.netmask.addr>>24)&0xff),
			 (ipi.gw.addr&0xff), ((ipi.gw.addr>>8)&0xff), ((ipi.gw.addr>>16)&0xff), ((ipi.gw.addr>>24)&0xff));
}

void wifiGetStation()
{
	wifi_config_t conf;
	esp_wifi_get_config(ESP_IF_WIFI_STA, &conf);
	kprintf(stritWIFISTATION, conf.sta.ssid, conf.sta.password);
}

void clientParseUrl(char* s)
{
    char *t = strstr(s, parslashquote);
	if(t == 0)
	{
		kprintf(stritCMDERROR);
		return;
	}
	char *t_end  = strstr(t, parquoteslash)-2;
    if(t_end <= (char*)0)
    {
		kprintf(stritCMDERROR);
		return;
    }
    char *url = (char*) malloc((t_end-t+1)*sizeof(char));
    if(url != NULL)
    {
        uint8_t tmp;
        for(tmp=0; tmp<(t_end-t+1); tmp++) url[tmp] = 0;
        strncpy(url, t+2, (t_end-t));
        clientSetURL(url);
        free(url);
    }
}

void clientParsePath(char* s)
{
    char *t = strstr(s, parslashquote);
	if(t == 0)
	{
		kprintf(stritCMDERROR);
		return;
	}
//	kprintf("cli.path: %s\n",t);
	char *t_end  = strstr(t, parquoteslash)-2;
    if(t_end <= (char*)0)
    {
		kprintf(stritCMDERROR);
		return;
    }
    char *path = (char*) malloc((t_end-t+1)*sizeof(char));
    if(path != NULL)
    {
        uint8_t tmp;
        for(tmp=0; tmp<(t_end-t+1); tmp++) path[tmp] = 0;
        strncpy(path, t+2, (t_end-t));
	kprintf("cli.path: %s\n",path);
        clientSetPath(path);
        free(path);
    }
}

void clientParsePort(char *s)
{
    char *t = strstr(s, parslashquote);
	if(t == 0)
	{
		kprintf(stritCMDERROR);
		return;
	}
	char *t_end  = strstr(t, parquoteslash)-2;
    if(t_end <= (char*)0)
    {
		kprintf(stritCMDERROR);
		return;
    }
    char *port = (char*) malloc((t_end-t+1)*sizeof(char));
    if(port != NULL)
    {
        uint8_t tmp;
        for(tmp=0; tmp<(t_end-t+1); tmp++) port[tmp] = 0;
        strncpy(port, t+2, (t_end-t));
        uint16_t porti = atoi(port);
        clientSetPort(porti);
        free(port);
    }
}


void clientPlay(char *s)
{
    char *t = strstr(s, parslashquote);
	if(t == 0)
	{
		kprintf(stritCMDERROR);
		return;
	}
	char *t_end  = strstr(t, parquoteslash)-2;
    if(t_end <= (char*)0)
    {
		kprintf(stritCMDERROR);
		return;
    }
   char *id = (char*) malloc((t_end-t+1)*sizeof(char));
    if(id != NULL)
    {
        uint8_t tmp;
        for(tmp=0; tmp<(t_end-t+1); tmp++) id[tmp] = 0;
        strncpy(id, t+2, (t_end-t));
		playStation(id);
        free(id);
    }	
}

const char strilLIST[]  = {"##CLI.LIST#%c"};
const char strilINFOND[]  = {"#CLI.LISTINFO#: %3d: not defined\n"};
const char strilINFO[]  = {"#CLI.LISTINFO#: %3d: %s, %s:%d%s\n"};
const char strilINFO1[]  = {"#CLI.LISTNUM#: %3d: %s, %s:%d%s\n"};
const char strilDINFO[]  = {"\n#CLI.LIST#%c"};


void clientList(char *s)
{
	struct shoutcast_info* si;
	uint16_t i = 0,j = 255;
	bool onlyOne = false;
	
	char *t = strstr(s, parslashquote);
	if(t != NULL) // a number specified
	{	
		char *t_end  = strstr(t, parquoteslash)-2;
		if(t_end <= (char*)0)
		{
			kprintf(stritCMDERROR);
			return;
		}	
		i = atoi(t+2);
		if (i>254) i = 0;
		j = i+1;
		onlyOne = true;
		
	} 
	{	
		kprintf(strilDINFO,0x0d);	
		for ( ;i <j;i++)
		{
			vTaskDelay(1);
			si = getStation(i);
			
			if ((si == NULL) || (si->port ==0))
			{
				//kprintf(strilINFOND,i);
				if (si != NULL) {free(si);}
				continue;
			}

			if (si !=NULL)
			{
				if(si->port !=0)
				{	
					if (onlyOne)
						kprintf(strilINFO,i,si->name,si->domain,si->port,si->file);	
					else
						kprintf(strilINFO1,i,si->name,si->domain,si->port,si->file);
				}
				free(si);
			}	
		}	
		kprintf(strilLIST,0x0d);
	}
}
void clientInfo()
{
	struct shoutcast_info* si;
	si = getStation(currentStation);
	if (si != NULL)
	{
		ntp_print_time();
		clientSetName(si->name,currentStation);
		clientPrintHeaders();
		clientVol((char*)"");
		clientPrintState();
		free(si);
	}
}

char* webInfo()
{
	struct shoutcast_info* si;
	si = getStation(currentStation);
	char* resp = malloc(1024);
	if (si != NULL)
	{
		if (resp != NULL)
		{	
			sprintf(resp,"vol: %d\nnum: %d\nstn: %s\ntit: %s\nsts: %d\n",getVolume(),currentStation,si->name,getMeta(),getState());
		}
		free(si);
	}
	return resp;

}
char* webList(int id)
{
	struct shoutcast_info* si;
	si = getStation(id);
	char* resp = malloc(1024);
	if (si != NULL)
	{
		if (resp != NULL)
		{
			sprintf(resp,"%s\n",si->name);
		}
		free(si);
	}
	return resp;

}

void sysI2S(char* s)
{
    char *t = strstr(s, parslashquote);
	struct device_settings *device;
	device = getDeviceSettings();
	if(t == NULL)
	{
		kprintf("\n##I2S speed: %d, 0=48kHz, 1=96kHz, 2=192kHz#\n",device->i2sspeed);
		free(device);
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		free(device);
		return;
    }	
	uint8_t speed = atoi(t+2);
	VS1053_I2SRate(speed);

	device->i2sspeed = speed;
	saveDeviceSettings(device);	
	kprintf("\n##I2S speed: %d, 0=48kHz, 1=96kHz, 2=192kHz#\n",speed);
	free(device);
}

void sysUart(char* s)
{
	bool empty = false;
	char *t ;
	char *t_end;
	t = NULL;
	if (s != NULL)
	{	
		t = strstr(s, parslashquote);
		if(t == NULL)
		{
			empty = true;
		} else
		{
			t_end  = strstr(t, parquoteslash);
			if(t_end == NULL)
			{
				empty = true;
			}	
		}
	}
	struct device_settings *device;
	device = getDeviceSettings();
	if ((!empty)&&(t!=NULL))
	{
		uint32_t speed = atoi(t+2);
		speed = checkUart(speed);
		device->uartspeed= speed;
		saveDeviceSettings(device);	
		kprintf("Speed: %d\n",speed);
	}
	kprintf("\n%sUART= %d# on next reset\n",msgsys,device->uartspeed);	
	free(device);
}

void clientVol(char *s)
{
    char *t = strstr(s, parslashquote);
	if(t == 0)
	{
		// no argument, return the current volume
		kprintf("%sVOL#: %d\n",msgcli,getVolume());
		return;
	}
	char *t_end  = strstr(t, parquoteslash)-2;
    if(t_end <= (char*) 0)
    {

		kprintf(stritCMDERROR);
		return;
    }
   char *vol = (char*) malloc((t_end-t+1)*sizeof(char));
    if (vol != NULL)
    {
        uint8_t tmp;
        for(tmp=0; tmp<(t_end-t+1); tmp++) vol[tmp] = 0;
        strncpy(vol, t+2, (t_end-t));
		if ((atoi(vol)>=0)&&(atoi(vol)<=254))
		{	
			setVolumew(vol);
//			if (RDA5807M_detection()) RDA5807M_setVolume(atoi(vol)/16);
		}	
		free(vol);
    }	
}

// option for loading or not the pacth of the vs1053
void syspatch(char* s)
{
    char *t = strstr(s, parslashquote);
	struct device_settings *device;
	device = getDeviceSettings();
	if(t == NULL)
	{
		if ((device->options & T_PATCH)!= 0)
			kprintf("\n##VS1053 Patch is not loaded#%c",0x0d);
		else
			kprintf("\n##VS1053 Patch is loaded#%c",0x0d);
		free(device);
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		free(device);
		return;
    }	
	uint8_t value = atoi(t+2);
	if (value ==0) 
		device->options |= T_PATCH; 
	else 
		device->options &= NT_PATCH; // 0 = load patch
	
	saveDeviceSettings(device);	
	kprintf(stritPATCH,(device->options & T_PATCH)!= 0?"unloaded":"Loaded");
	free(device);	
}

// the gpio to use for the led indicator
void sysledgpio(char* s)
{
    char *t = strstr(s, parslashquote);
	struct device_settings *device;
	device = getDeviceSettings();
	if(t == NULL)
	{
		kprintf("##Led GPIO is %d#\n",device->led_gpio);
		free(device);
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
	uint8_t value = atoi(t+2);
    if ((t_end == NULL)||(value >= GPIO_NUM_MAX))
    {
		kprintf(stritCMDERROR);
		free(device);
		return;
    }	
	device->led_gpio = value; 
	led_gpio = value;
	gpio_output_conf(value);
	saveDeviceSettings(device);	
	kprintf("##Led GPIO is now %d\n",value);
	free(device);	
}
uint8_t getLedGpio()
{
	struct device_settings *device;
	if (led_gpio == 255)
	{
		device = getDeviceSettings();
		uint8_t ledgpio = device->led_gpio;
		if (ledgpio == 0) {
			ledgpio = GPIO_LED;
			device->led_gpio = ledgpio;
			led_gpio = ledgpio;
			saveDeviceSettings(device);
		}
		free (device);
		return ledgpio;	
	} 
	return led_gpio;	
}

// display or change the lcd type
void syslcd(char* s)
{
    char *t = strstr(s, parslashquote);
	struct device_settings *device;
	device = getDeviceSettings();
	if(t == NULL)
	{
		kprintf("##LCD is %d#\n",device->lcd_type);
		free(device);
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		free(device);
		return;
    }	
	uint8_t value = atoi(t+2);
	device->lcd_type = value; 
	saveDeviceSettings(device);	
	kprintf("##LCD is in %d on next reset#\n",value);
	free(device);	

}

// display or change the DDMM display mode
void sysddmm(char* s)
{
    char *t = strstr(s, parslashquote);
	struct device_settings *device;

	if(t == NULL)
	{
		if (ddmm)
			kprintf("##Time is DDMM#\n");
		else
			kprintf("##Time is MMDD#\n");
		
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		return;
    }	
	uint8_t value = atoi(t+2);
	device = getDeviceSettings();
	if (value == 0)
		device->options32 &= NT_DDMM;
	else 
		device->options32 |= T_DDMM;
	ddmm = value;
	saveDeviceSettings(device);	
	if (ddmm)
		kprintf("##Time is DDMM#\n");
	else
		kprintf("##Time is MMDD#\n");
	free(device);	
}

// get or set the encoder half resolution. Must be set depending of the hardware
void syshenc(int nenc,char* s)
{
    char *t = strstr(s, parslashquote);
	struct device_settings *device;
	Encoder_t *encoder;
	bool encvalue;
	encoder = (Encoder_t *)getEncoder(nenc);
	if (encoder == NULL) {kprintf("Encoder not defined#\n"); return;}
	device = getDeviceSettings();
	uint8_t options32 = device->options32;
	free (device);
	if (nenc == 0) encvalue = options32&T_ENC0;
	else encvalue = options32&T_ENC1;
	
	kprintf("##Step for encoder%d is ",nenc);
	if(t == NULL)
	{
		if (encvalue)
			kprintf("half#\n");
		else
			kprintf("normal#\n");
		
//		kprintf("Current value: %d\n",getHalfStep(encoder) );
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		return;
    }	
	uint8_t value = atoi(t+2);
	device = getDeviceSettings();
	if (value == 0)
	{
		if (nenc ==0) device->options32 &= NT_ENC0;
		else device->options32 &= NT_ENC1;
	}
	else 
	{
		if (nenc ==0) device->options32 |= T_ENC0;
		else device->options32 |= T_ENC1;
	}
	setHalfStep(encoder, value);
	if (nenc == 0) encvalue = device->options32&T_ENC0;
	else encvalue = device->options32&T_ENC1;
	if (encvalue)
		kprintf("half ");
	else
		kprintf("normal ");
	kprintf("#\n");
	
	saveDeviceSettings(device);	
	free(device);		
}

// display or change the rotation lcd mode
void sysrotat(char* s)
{
    char *t = strstr(s, parslashquote);
	struct device_settings *device;

	kprintf("##Lcd rotation is ");
	if(t == NULL)
	{
		if (rotat)
			kprintf("on#\n");
		else
			kprintf("off#\n");
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		return;
    }	
	uint8_t value = atoi(t+2);
	device = getDeviceSettings();
	if (value == 0)
		device->options32 &= NT_ROTAT;
	else 
		device->options32 |= T_ROTAT;
	rotat = value;
	saveDeviceSettings(device);	
	if (rotat)
		kprintf("on#\n");
	else
		kprintf("off#\n");
	free(device);	
}


// Timer in seconds to switch off the lcd
void syslcdout(char* s)
{
    char *t = strstr(s, parslashquote);
	struct device_settings *device;
	device = getDeviceSettings();
	kprintf("##LCD out is ");
	lcd_out = device->lcd_out; 
	if(t == NULL)
	{
		kprintf("%d#\n",lcd_out);
		free(device);
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		free(device);
		return;
    }	
	uint8_t value = atoi(t+2);
	device->lcd_out = value; 
	lcd_out = value;
	saveDeviceSettings(device);	
	kprintf("%d#\n",value);
	wakeLcd();
	free(device);	

}
uint32_t getLcdOut()
{
	struct device_settings *device;
	int increm = 0;
	if (lcd_out == 0xFFFFFFFF)
	{
		device = getDeviceSettings();
		lcd_out = device->lcd_out;
		free (device);
	} 
	if (lcd_out >0) increm++; //adjust
	return lcd_out+increm;	
}

// mode of the led indicator. Blink or play/stop
void sysled(char* s)
{
    char *t = strstr(s, parslashquote);
	struct device_settings *device;
	device = getDeviceSettings();
	extern bool ledStatus;
	if(t == NULL)
	{
		kprintf("##Led is in %s mode#\n",((device->options & T_LED)== 0)?"Blink":"Play");
		free(device);
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		free(device);
		return;
    }	
	uint8_t value = atoi(t+2);
	if (value !=0) 
	{device->options |= T_LED; ledStatus = false; if (getState()) gpio_set_level(getLedGpio(),0);}
	else 
	{device->options &= NT_LED; ledStatus =true;} // options:0 = ledStatus true = Blink mode
	
	saveDeviceSettings(device);	
	kprintf("##LED is in %s mode#\n",(ledStatus)?"Blink":"Play");
	free(device);
	
}



// display or change the tzo for ntp
void tzoffset(char* s)
{
	char *t = strstr(s, parslashquote);
	struct device_settings *device;
	
	device = getDeviceSettings();
	if(t == NULL)
	{
		kprintf("##SYS.TZO#: %d\n",device->tzoffset);
		free(device);
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		free(device);
		return;
    }	
	uint8_t value = atoi(t+2);
	device->tzoffset = value;	
	saveDeviceSettings(device);	
	kprintf("##SYS.TZO#: %d\n",device->tzoffset);
	free(device);	
	addonDt(); // for addon, force the dt fetch
}

// print the heapsize
void heapSize()
{
	int hps = xPortGetFreeHeapSize( );
	kprintf("%sHEAP: %d #\n",msgsys,hps);
}

//display or change the hostname and services
void hostname(char* s)
{
	char *t = strstr(s, parslashquote);
	struct device_settings *device;
	
	device = getDeviceSettings();
	if(t == NULL)
	{
		kprintf("##SYS.HOST#: %s.local\n  IP:%s #\n",device->hostname,getIp());
		free(device);
		return;
	}
	
	t +=2;
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		free(device);
		return;
    }
		
    char *hn = (char*) malloc((t_end-t+1)*sizeof(char));
    if(hn != NULL)
    {
		if (t_end-t ==0)
			strcpy(	device->hostname, "karadio32");
		else
		{	
			if (t_end-t >= HOSTLEN) t_end = t+HOSTLEN;
			strncpy(device->hostname,t,(t_end-t)*sizeof(char));
			device->hostname[(t_end-t)*sizeof(char)] = 0;
		}
		saveDeviceSettings(device);	
		ESP_ERROR_CHECK(mdns_service_remove("_http", "_tcp"));
		ESP_ERROR_CHECK(mdns_service_remove("_telnet", "_tcp"));
		vTaskDelay(1);
		kprintf("##SYS.HOST#: %s.local\n  IP:%s #\n",device->hostname,getIp());
		ESP_ERROR_CHECK(mdns_hostname_set(device->hostname));
		ESP_ERROR_CHECK(mdns_instance_name_set(device->hostname));
		vTaskDelay(1);
		ESP_ERROR_CHECK(mdns_service_add(NULL, "_http", "_tcp", 80, NULL, 0));	
		ESP_ERROR_CHECK(mdns_service_add(NULL, "_telnet", "_tcp", 23, NULL, 0));
		free(hn);
	}
	free(device);	
	
}

void displayLogLevel()
{
	switch (s_log_default_level){
		case ESP_LOG_NONE:
		  kprintf("Log level is now ESP_LOG_NONE\n");
		  break;
		case ESP_LOG_ERROR:
		  kprintf("Log level is now ESP_LOG_ERROR\n");
		  break;
		case ESP_LOG_WARN:
		  kprintf("Log level is now ESP_LOG_WARN\n");
		  break;
		case ESP_LOG_INFO:
		  kprintf("Log level is now ESP_LOG_INFO\n");
		  break;
		case ESP_LOG_DEBUG:
		  kprintf("Log level is now ESP_LOG_DEBUG\n");
		  break;
		case ESP_LOG_VERBOSE:
		  kprintf("Log level is now ESP_LOG_VERBOSE\n");
		  break;
		default:
		  kprintf("Log level is now Unknonwn\n");	
	}
}

esp_log_level_t getLogLevel()
{
	 return s_log_default_level;
}


void setLogLevel(esp_log_level_t level)
{
	struct device_settings *device;
	device = getDeviceSettings();
	esp_log_level_set("*", level);
	s_log_default_level=level; 
	if (device != NULL)
	{
		device->trace_level = level;
		saveDeviceSettings(device);
		free(device);
	}	
	displayLogLevel();
} 

/*
void fmSeekUp()
{seekUp();seekingComplete(); kprintf("##FM.FREQ#: %3.2f MHz\n",getFrequency());}
void fmSeekDown()
{seekDown();seekingComplete(); kprintf("##FM.FREQ#: %3.2f MHz\n",getFrequency());}
void fmVol(char* tmp)
{clientVol(tmp);}
void fmMute()
{RDA5807M_unmute(RDA5807M_FALSE); }
void fmUnmute()
{RDA5807M_unmute(RDA5807M_TRUE);}
*/

void checkCommand(int size, char* s)
{
	char *tmp = (char*)malloc((size+1)*sizeof(char));
	int i;
	for(i=0;i<size;i++) tmp[i] = s[i];
	tmp[size] = 0;
//	kprintf("size: %d, cmd=%s\n",size,tmp);
/*	if(startsWith ("fm.", tmp))
	{
		if(strcmp(tmp+3, "up") == 0) 	fmSeekUp();
		else if(strcmp(tmp+3, "down") == 0) 	fmSeekDown();
		else if(strcmp(tmp+3, "stop") == 0) 	fmMute(); 
		else if(strcmp(tmp+3, "start") == 0) 	fmUnmute(); 
		else if(startsWith (  "vol",tmp+3)) 	clientVol(tmp);	
		else printInfo(tmp);
	} else
*/		
	if(startsWith ("dbg.", tmp))
	{
		if     (strcmp(tmp+4, "fifo") == 0) 	kprintf( "Buffer fill %u%%, %d bytes, OverRun: %ld, UnderRun: %ld\n",
												(spiRamFifoFill() * 100) / spiRamFifoLen(), spiRamFifoFill(),spiRamGetOverrunCt(),spiRamGetUnderrunCt());
		else if(strcmp(tmp+4, "clear") == 0) 	spiRamFifoReset();
		
		else printInfo(tmp);
	} else
	if(startsWith ("wifi.", tmp))
	{
		if     (strcmp(tmp+5, "list") == 0) 	wifiScan();
		else if(strcmp(tmp+5, "scan") == 0) 	wifiScan();
		else if(strcmp(tmp+5, "con") == 0) 	wifiConnectMem();
		else if(strcmp(tmp+5, "recon") == 0) 	wifiReConnect();
		else if(startsWith ("con", tmp+5)) 	wifiConnect(tmp);
		else if(strcmp(tmp+5, "rssi") == 0) 	readRssi();
		else if(strcmp(tmp+5, "discon") == 0) wifiDisconnect();
		else if(strcmp(tmp+5, "status") == 0) wifiStatus();
		else if(strcmp(tmp+5, "station") == 0) wifiGetStation();
		else printInfo(tmp);
	} else
	if(startsWith ("cli.", tmp))
	{
		if     (startsWith (  "url", tmp+4)) 	clientParseUrl(tmp);
		else if(startsWith (  "path", tmp+4))	clientParsePath(tmp);
		else if(startsWith (  "port", tmp+4)) 	clientParsePort(tmp);
		else if(strcmp(tmp+4, "instant") == 0) {clientDisconnect("cli instantplay");clientConnectOnce();}
		else if(strcmp(tmp+4, "start") == 0) 	clientPlay((char*)"(\"255\")"); // outside value to play the current station
		else if(strcmp(tmp+4, "stop") == 0) 	clientDisconnect("cli stop");
		else if(startsWith (  "list", tmp+4)) 	clientList(tmp);
		else if(strcmp(tmp+4, "next") == 0) 	wsStationNext();
		else if(strncmp(tmp+4,"previous",4) == 0) wsStationPrev();
		else if(startsWith (  "play",tmp+4)) 	clientPlay(tmp);
		else if(strcmp(tmp+4, "vol+") == 0) 	setVolumePlus();
		else if(strcmp(tmp+4, "vol-") == 0) 	setVolumeMinus();
		else if(strcmp(tmp+4, "info") == 0) 	clientInfo();
		else if(startsWith (  "vol",tmp+4)) 	clientVol(tmp);
		else printInfo(tmp);
	} else
	if(startsWith ("sys.", tmp))
	{
			 if(startsWith (  "i2s",tmp+4)) 	sysI2S(tmp);
//		else if(strcmp(tmp+4, "adc") == 0) 		readAdc();
		else if(startsWith (  "uart",tmp+4)) 	sysUart(tmp);
		else if(strcmp(tmp+4, "erase") == 0) 	eeEraseAll();
		else if(strcmp(tmp+4, "heap") == 0) 	heapSize();
		else if(strcmp(tmp+4, "boot") == 0) 	esp_restart();
		else if(strcmp(tmp+4, "update") == 0) 	update_firmware((char*)"KaRadio32");
//bouchon		else if(strcmp(tmp+4, "prerelease") == 0) 	update_firmware("prv");
		else if(startsWith (  "patch",tmp+4)) 	syspatch(tmp);
		else if(startsWith (  "ledg",tmp+4)) 	sysledgpio(tmp); //ledgpio
		else if(startsWith (  "led",tmp+4)) 	sysled(tmp);
		else if(strcmp(tmp+4, "date") == 0) 	ntp_print_time();
		else if(strncmp(tmp+4, "vers",4) == 0) 	kprintf("Release: %s, Revision: %s\n",RELEASE,REVISION);
		else if(startsWith(   "tzo",tmp+4)) 	tzoffset(tmp);
		else if(strcmp(tmp+4, "logn") == 0) 	setLogLevel(ESP_LOG_NONE);
		else if(strcmp(tmp+4, "loge") == 0) 	setLogLevel(ESP_LOG_ERROR); 
		else if(strcmp(tmp+4, "logw") == 0) 	setLogLevel(ESP_LOG_WARN); 
		else if(strcmp(tmp+4, "logi") == 0) 	setLogLevel(ESP_LOG_INFO); 
		else if(strcmp(tmp+4, "logd") == 0) 	setLogLevel(ESP_LOG_DEBUG); 
		else if(strcmp(tmp+4, "logv") == 0) 	setLogLevel(ESP_LOG_VERBOSE); 
		else if(strcmp(tmp+4, "dlog") == 0) 	displayLogLevel();
		else if(startsWith(   "log",tmp+4)) 	; // do nothing
		else if(startsWith (  "lcdo",tmp+4)) 	syslcdout(tmp); // lcdout timer to switch off the lcd
		else if(startsWith (  "lcd",tmp+4)) 	syslcd(tmp);
		else if(startsWith (  "ddmm",tmp+4)) 	sysddmm(tmp);
		else if(startsWith (  "host",tmp+4)) 	hostname(tmp);
		else if(startsWith (  "rotat",tmp+4)) 	sysrotat(tmp);
		else if(startsWith (  "henc0",tmp+4)) 	syshenc(0,tmp);
		else if(startsWith (  "henc1",tmp+4)) 	syshenc(1,tmp);
		else printInfo(tmp);
	}
	else 
	{
		if(strcmp(tmp, "help") == 0)
		{
			kprintfl(stritHELP0);
			vTaskDelay(1);
			kprintfl(stritHELP1);
			vTaskDelay(1);
			kprintfl(stritHELP2);
			vTaskDelay(1);
			kprintfl(stritHELP3);
			vTaskDelay(1);
			kprintfl(stritHELP4);		}
		else printInfo(tmp);
	}	
	free(tmp);
	
}
