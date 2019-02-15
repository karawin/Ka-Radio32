/******************************************************************************
 * 
 * Copyright 2018 karawin (http://www.karawin.fr)
 *
*******************************************************************************/


#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#define TAG "Interface"
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
#include "xpt2046.h"
//#include "rda5807Task.c"
#include "ClickEncoder.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_system.h"
#include "mdns.h"

#include "esp_wifi.h"

const char parslashquote[] = {"(\""};
const char parquoteslash[] = {"\")"};
const char msgsys[] = {"##SYS."};
const char msgcli[] = {"##CLI."};

const char stritWIFISTATUS[]  = {"#WIFI.STATUS#\nIP: %d.%d.%d.%d\nMask: %d.%d.%d.%d\nGateway: %d.%d.%d.%d\n##WIFI.STATUS#\n"};
const char stritWIFISTATION[]  = {"#WIFI.STATION#\nSSID: %s\nPASSWORD: %s\n##WIFI.STATION#\n"};
const char stritPATCH[]  = {"#WIFI.PATCH#: VS1053 Patch will be %s after power Off and On#\n"};
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
wifi.rssi: print the rssi (power of the reception\n\
wifi.auto[(\"x\")]  show the auto state or set it to x. x=0: reboot on wifi disconnect or 1: try reconnection.\n\n\
//////////////////\n\
  Station Client commands\n\
//////////////////\n\
cli.url(\"url\"): the name or ip of the station on instant play\n\
cli.path(\"/path\"): the path of the station on instant play\n\
cli.port(\"xxxx\"): the port number of the station on instant play\n\
cli.instant: play the instant station\n\
cli.start: start to play the current station\n\
cli.play(\"x\"): play the x recorded station in the list\n\
"};

const char stritHELP1[]  = {"\
cli.prev (or cli.previous): select the previous station in the list and play it\n\
cli.next: select the next station in the list and play it\
cli.stop: stop the playing station or instant\n\
cli.list: list all recorded stations\n\
cli.list(\"x\"): list only one of the recorded stations. Answer with #CLI.LISTINFO#: followed by infos\n\
cli.vol(\"x\"): set the volume to x with x from 0 to 254 (volume max)\n\
cli.vol: display the current volume. respond with ##CLI.VOL# xxx\n\
cli.vol-: Decrement the volume by 10 \n\
cli.vol+: Increment the volume by 10 \n\
Every vol command from uart or web or browser respond with ##CLI.VOL#: xxx\n\
cli.info: Respond with nameset, all icy, meta, volume and stae playing or stopped. Used to refresh the lcd informations \n\n\
//////////////////\n\
  System commands\n\
//////////////////\n\
sys.uart(\"x\"): Change the baudrate of the uart on the next reset.\n\
 Valid x are: 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, 76880, 115200, 230400\n\
sys.i2s: Display the current I2S speed\n\
"};

const char stritHELP2[]  = {"\
sys.i2s(\"x\"): Change and record the I2S clock speed of the vs1053 GPIO5 MCLK of the i2s interface to external dac.\n\
: 0=48kHz, 1=96kHz, 2=192kHz, other equal 0\n\
sys.erase: erase all recorded configuration and stations.\n\
sys.heap: show the ram heap size\n\
sys.update: start an OTA (On The Air) update of the software\n\
sys.prerelease: start an OTA of the next release in alpha stage\n\
sys.boot: reboot.\n\
sys.patch and sys.patch(\"x\"): Display and Change the status of the vs1053 patch at power on.\n\
 0 = Patch will not be loaded, 1 or up = Patch will be loaded (default) at power On \n\
sys.led and sys.led(\"x\"): Display and Change the led indication:\n\
 1 = Led is in Play mode (lighted when a station is playing), 0 = Led is in Blink mode (default)\n\
sys.version: Display the Release and Revision numbers\n\
sys.tzo and sys.tzo(\"xx\"): Display and Set the timezone offset of your country.\n\
"};

const char stritHELP3[]  = {"\
sys.date: Send a ntp request and Display the current locale time\n\
sys.dlog: Display the current log level\n\
sys.logx: Set log level to x with x=n for none, v for verbose, d for debug, i for info, w for warning, e for error\n\
sys.log: do nothing apart a trace on uart (debug use)\n\
sys.lcdout and sys.lcdout(\"x\"): Timer in seconds to switch off the lcd. 0= no timer\n\
sys.lcd and sys.lcd(\"x\"): Display and Change the lcd type to x on next reset\n\
sys.ledgpio and sys.ledgpio(\"x\"): Display and Change the default Led GPIO (4) to x\n\
"};

const char stritHELP4[]  = {"\
sys.ddmm and sys.ddmm(\"x\"):  Display and Change  the date format. 0:MMDD, 1:DDMM\n\
sys.host and sys.host(\"your hostname\"): display and change the hostname for mDNS\n\
sys.rotat and sys.rotat(\"x\"): Change and display the lcd rotation option (reset needed). 0:no rotation, 1: rotation\n\
sys.henc0 or sys.henc1: Display the current step setting for the encoder. Normal= 4 steps/notch, Half: 2 steps/notch\n\
sys.hencx(\"y\") with y=0 Normal, y=1 Half\n\
sys.cali[brate]: start a touch screen calibration\n\
sys.ledpola and sys.ledpola(\"x\"): display or set the polarity of the system led\n\
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
static gpio_num_t led_gpio = GPIO_NONE;
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
	if (dm == 0)ddmm= 0;
	else ddmm = 1;
}
uint8_t getRotat()
{
	return rotat;
}
void setRotat(uint8_t dm)
{
	if (dm == 0) rotat = 0;
	else rotat = 1;
}

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
	for(i = 0; i < 32; i++) g_device->ssid1[i] = 0;
	for(i = 0; i < 64; i++) g_device->pass1[i] = 0;	
	char *t = strstr(cmd, parslashquote);
	if(t == 0)
	{
		kprintf(stritCMDERROR);
		return;
	}
	char *t_end  = strstr(t, "\",\"");
	if(t_end == 0)
	{
		kprintf(stritCMDERROR);
		return;
	}
	
	strncpy( g_device->ssid1, (t+2), (t_end-t-2) );
	
	t = t_end+3;
	t_end = strstr(t, parquoteslash);
	if(t_end == 0)
	{
		kprintf(stritCMDERROR);
		return;
	}
	
	strncpy( g_device->pass1, t, (t_end-t)) ;
	g_device->current_ap = 1;
	g_device->dhcpEn1 = 1;
	saveDeviceSettings(g_device);
	// test Save g_device to device1
	copyDeviceSettings();
	//
	kprintf("#WIFI.CON#\n");
	kprintf("\n##AP1: %s with dhcp on next reset#\n",g_device->ssid1);
	kprintf("##WIFI.CON#\n");
}

void wifiConnectMem()
{
	kprintf("#WIFI.CON#\n");
	kprintf("##AP1: %s#",g_device->ssid1);
	kprintf("\n##AP2: %s#\n",g_device->ssid2);
	kprintf("##WIFI.CON#\n");
}

static bool autoConWifi = true; // control for wifiReConnect & wifiDisconnect
static bool autoWifi = false; // auto reconnect wifi if disconnected
bool getAutoWifi(void)
{ return autoWifi;}
void setAutoWifi()
{ autoWifi = (g_device->options32& T_WIFIAUTO)?true:false;}

void wifiAuto(char* cmd)
{
	char *t = strstr(cmd, parslashquote);
	if(t == 0)
	{
		kprintf("##Wifi Auto is %s#\n",autoWifi?"On":"Off");
//		kprintf(stritCMDERROR);
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		return;
    }	
	uint8_t value = atoi(t+2);
	
	if (value == 0)
		g_device->options32 &= NT_WIFIAUTO;
	else 
		g_device->options32 |= T_WIFIAUTO;
	autoWifi = value;
	saveDeviceSettings(g_device);

	wifiAuto((char*)"");
}

void wifiReConnect()
{
	if (autoConWifi == false) esp_wifi_connect();
	autoConWifi = true;
}

void wifiDisconnect()
{
	esp_err_t err;
	autoConWifi = false;
	err=esp_wifi_disconnect();
	if(err== ESP_OK) kprintf("\n##WIFI.NOT_CONNECTED#\n");
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

const char strilLIST[]  = {"##CLI.LIST#\n"};
const char strilINFO[]  = {"#CLI.LISTNUM#: %3d: %s, %s:%d%s%%%d\n"};
const char strilDINFO[]  = {"\n#CLI.LIST#\n"};


void clientList(char *s)
{
	struct shoutcast_info* si;
	uint16_t i = 0,j = 255;
//	bool onlyOne = false;
	
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
//		onlyOne = true;		
	} 
	{	
		kprintf(strilDINFO);	
		for ( ;i <j;i++)
		{
			vTaskDelay(1);
			si = getStation(i);
			
			if ((si == NULL) || (si->port ==0))
			{
				if (si != NULL) {free(si);}
				continue;
			}

			if (si !=NULL)
			{
				if(si->port !=0)
				{	
						kprintf(strilINFO,i,si->name,si->domain,si->port,si->file,si->ovol);	
				}
				free(si);
			}	
		}	
		kprintf(strilLIST);
	}
}
// parse url
bool parseUrl(char* src, char* url, char* path, uint16_t *port)
{
	char* teu,*tbu,*tbpa;
	char* tmp = src;
	tmp = strstr(src,"://");
	if (tmp) tmp +=3;
	else tmp = src;
	tbu = tmp;
//printf("tbu: %s\n",tbu);
	teu = strchr(tbu,':');
	if (teu)
	{
		tmp = teu+1;
		*port = atoi(tmp);
	}	
	tbpa = strchr(tmp,'/');	
	if (tbpa)
	{
		if(!teu) teu = tbpa-1;
		strcpy(path,tbpa);
	}
	if (teu)
	{
		strncpy(url,tbu,teu-tbu);
		url[teu-tbu] = 0;
	} else
		strcpy(url,src);
	return true;
}

//edit a station
void clientEdit(char *s)
{
struct shoutcast_info* si;
uint8_t id = 0xff;
char* tmp; 
char* tmpend ;
char url[200];

	si = malloc(sizeof(struct shoutcast_info));	
	if (si == NULL) { kprintf("##CLI.EDIT#: ERROR MEM#") ; return;}
	memset(si->domain, 0, sizeof(si->domain));
    memset(si->file, 0, sizeof(si->file));
    memset(si->name, 0, sizeof(si->name));
	memset(url,0,200);
    si->port = 80;
	si->ovol = 0;
//	printf("##CLI.EDIT: %s",s);
	ESP_LOGI(TAG,"%s",s);
	tmp = s+10;
	tmpend = strchr(tmp,':');
	if (tmpend-tmp) id = atoi(tmp);	
	tmp = ++tmpend;//:
	tmpend = strchr(tmp,',');
	if (tmpend-tmp) {strncpy(si->name,tmp,tmpend-tmp);} //*tmpend = 0; }
	tmp = ++tmpend;//,
	tmpend = strchr(tmp,'%');
	if (tmpend == NULL )tmpend = strchr(tmp,'"');
	if (tmpend-tmp){ strncpy(url,tmp,tmpend-tmp);} //*tmpend = 0; }
	else url[0] = 0;
	tmp = ++tmpend;//%
	tmpend = strchr(tmp,'"');
	if ((tmpend != NULL)&&(tmpend-tmp)) si->ovol = atoi(tmp);	
	
	
//printf("==> id: %d, name: %s, url: %s\n",id,si->name,url);	
	
    // Parsing
	if (url[0] != 0)
		parseUrl(url, si->domain, si->file, &(si->port));
	
//printf(" id: %d, name: %s, url: %s, port: %d, path: %s\n",id,si->name,si->domain,si->port,si->file);
	if (id < 0xff) {
		if (si->domain[0]==0) {si->port = 0;si->file[0] = 0;}
		saveStation(si, id); 
		kprintf("##CLI.EDIT#: OK (%d)\n",id);
	}
	else
		kprintf("##CLI.EDIT#: ERROR\n");	
	
}
void clientInfo()
{
	struct shoutcast_info* si;
	kprintf("##CLI.INFO#\n");
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
	if(t == NULL)
	{
		kprintf("\n##I2S speed of the vs1053: %d, 0=48kHz, 1=96kHz, 2=192kHz#\n",g_device->i2sspeed);
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		return;
    }	
	uint8_t speed = atoi(t+2);
	VS1053_I2SRate(speed);

	g_device->i2sspeed = speed;
	saveDeviceSettings(g_device);
	sysI2S((char*)"");
//	kprintf("\n##I2S speed: %d, 0=48kHz, 1=96kHz, 2=192kHz#\n",speed);
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
	if ((!empty)&&(t!=NULL))
	{
		uint32_t speed = atoi(t+2);
		speed = checkUart(speed);
		g_device->uartspeed= speed;
		saveDeviceSettings(g_device);	
		kprintf("Speed: %d\n",speed);
	}
	kprintf("\n%sUART= %d# on next reset\n",msgsys,g_device->uartspeed);	
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
	if(t == NULL)
	{
		if ((g_device->options & T_PATCH)!= 0)
			kprintf("##VS1053 Patch is not loaded#\n");
		else
			kprintf("##VS1053 Patch is loaded#\n");
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		return;
    }	
	uint8_t value = atoi(t+2);
	if (value ==0) 
		g_device->options |= T_PATCH; 
	else 
		g_device->options &= NT_PATCH; // 0 = load patch
	
	saveDeviceSettings(g_device);	
	kprintf(stritPATCH,(g_device->options & T_PATCH)!= 0?"unloaded":"Loaded");
}

// the gpio to use for the led indicator
void sysledgpio(char* s)
{
    char *t = strstr(s, parslashquote);
	if(t == NULL)
	{
		kprintf("##Led GPIO is %d#\n",g_device->led_gpio);
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
	uint8_t value = atoi(t+2);
    if ((t_end == NULL)||(value >= GPIO_NUM_MAX))
    {
		kprintf(stritCMDERROR);
		return;
    }	
	g_device->led_gpio = value; 
	led_gpio = value;
	gpio_output_conf(value);
	saveDeviceSettings(g_device);	
	gpio_set_ledgpio(value); // write in nvs if any
	sysledgpio((char*) "");
	led_gpio = GPIO_NONE; // for getLedGpio
}

uint8_t getLedGpio()
{
	if (led_gpio == GPIO_NONE)
	{
		gpio_get_ledgpio(&led_gpio);
		if (led_gpio != g_device->led_gpio) 
		{
			g_device->led_gpio = led_gpio;
			saveDeviceSettings(g_device);
		} 
	} 
	return led_gpio;	
}

// display or change the lcd type
void syslcd(char* s)
{
    char *t = strstr(s, parslashquote);
	if(t == NULL)
	{
		kprintf("##LCD is %d#\n",g_device->lcd_type);
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		return;
    }	
	uint8_t value = atoi(t+2);
	g_device->lcd_type = value; 
	saveDeviceSettings(g_device);	
	option_set_lcd_info(value,rotat );
	kprintf("##LCD is %d on next reset#\n",value);
}

// display or change the DDMM display mode
void sysddmm(char* s)
{
    char *t = strstr(s, parslashquote);

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
	if (value == 0)
		g_device->options32 &= NT_DDMM;
	else 
		g_device->options32 |= T_DDMM;
	ddmm = (value)?1:0;
	saveDeviceSettings(g_device);	
	option_set_ddmm(ddmm);
	sysddmm((char*) "");
}

// get or set the encoder half resolution. Must be set depending of the hardware
void syshenc(int nenc,char* s)
{
    char *t = strstr(s, parslashquote);
	Encoder_t *encoder;
	bool encvalue;
	encoder = (Encoder_t *)getEncoder(nenc);
	if (encoder == NULL) {kprintf("Encoder not defined#\n"); return;}
	uint8_t options32 = g_device->options32;
	if (nenc == 0) encvalue = options32&T_ENC0;
	else encvalue = options32&T_ENC1;
	
	if(t == NULL)
	{
		kprintf("##Step for encoder%d is ",nenc);
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
	if (value == 0)
	{
		if (nenc ==0) g_device->options32 &= NT_ENC0;
		else g_device->options32 &= NT_ENC1;
	}
	else 
	{
		if (nenc ==0) g_device->options32 |= T_ENC0;
		else g_device->options32 |= T_ENC1;
	}
	setHalfStep(encoder, value);
	if (nenc == 0) encvalue = g_device->options32&T_ENC0;
	else encvalue = g_device->options32&T_ENC1;
	syshenc(nenc,(char*)"");
	saveDeviceSettings(g_device);	
}

// display or change the rotation lcd mode
void sysrotat(char* s)
{
    char *t = strstr(s, parslashquote);

	if(t == NULL)
	{
		kprintf("##Lcd rotation is ");
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
	if (value == 0)
		g_device->options32 &= NT_ROTAT;
	else 
		g_device->options32 |= T_ROTAT;
	rotat = value;
	option_set_lcd_info(g_device->lcd_type,rotat );
	saveDeviceSettings(g_device);	
	sysrotat((char*) "");
}


// Timer in seconds to switch off the lcd
void syslcdout(char* s)
{
    char *t = strstr(s, parslashquote);
	lcd_out = g_device->lcd_out; 
	if(t == NULL)
	{
		kprintf("##LCD out is ");
		kprintf("%d#\n",lcd_out);
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		return;
    }	
	uint8_t value = atoi(t+2);
	g_device->lcd_out = value; 
	lcd_out = value;
	saveDeviceSettings(g_device);	
	option_set_lcd_out(lcd_out);
	syslcdout((char*) "");
	wakeLcd();
}

uint32_t getLcdOut()
{
	int increm = 0;
	option_get_lcd_out(&lcd_out);
	if (lcd_out == 0xFFFFFFFF)
	{
		lcd_out = g_device->lcd_out;
	} 
	if (lcd_out >0) increm++; //adjust
	return lcd_out+increm;	
}

// mode of the led indicator. Blink or play/stop
void sysled(char* s)
{
    char *t = strstr(s, parslashquote);
	extern bool ledStatus;
	if(t == NULL)
	{
		kprintf("##Led is in %s mode#\n",((g_device->options & T_LED)== 0)?"Blink":"Play");
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		return;
    }	
	uint8_t value = atoi(t+2);
	if (value !=0) 
	{g_device->options |= T_LED; ledStatus = false; if (getState()) gpio_set_level(getLedGpio(),0);}
	else 
	{g_device->options &= NT_LED; ledStatus =true;} // options:0 = ledStatus true = Blink mode
	
	saveDeviceSettings(g_device);
	sysled((char*) "");	
}

// mode of the led indicator. polarity 0 or 1
void sysledpol(char* s)
{
    char *t = strstr(s, parslashquote);
	extern bool ledPolarity;
	if(t == NULL)
	{
		kprintf("##Led polarity is %d#\n",((g_device->options & T_LEDPOL)== 0)?0:1);
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		return;
    }	
	uint8_t value = atoi(t+2);
	if (value !=0) 
	{g_device->options |= T_LEDPOL; ledPolarity = true; if (getState()) gpio_set_level(getLedGpio(),0);}
	else 
	{g_device->options &= NT_LEDPOL; ledPolarity =false;} // options:0 = ledPolarity 
	
	saveDeviceSettings(g_device);	
	sysledpol((char*) "");
}


// display or change the tzo for ntp
void tzoffset(char* s)
{
	char *t = strstr(s, parslashquote);
	if(t == NULL)
	{
		kprintf("##SYS.TZO#: %d\n",g_device->tzoffset);
		return;
	}
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		return;
    }	
	uint8_t value = atoi(t+2);
	g_device->tzoffset = value;	
	saveDeviceSettings(g_device);	
	tzoffset((char*) "");
	addonDt(); // for addon, force the dt fetch
}

// print the heapsize
void heapSize()
{
	int hps = xPortGetFreeHeapSize( );
	kprintf("%sHEAP: %d #\n",msgsys,hps);
}

// set hostname in mDNS
void setHostname(char* s)
{
		ESP_ERROR_CHECK(mdns_service_remove("_http", "_tcp"));
		ESP_ERROR_CHECK(mdns_service_remove("_telnet", "_tcp"));
		vTaskDelay(10);
		ESP_ERROR_CHECK(mdns_hostname_set(s));
		ESP_ERROR_CHECK(mdns_instance_name_set(s));
		vTaskDelay(10);
		ESP_ERROR_CHECK(mdns_service_add(NULL, "_http", "_tcp", 80, NULL, 0));	
		ESP_ERROR_CHECK(mdns_service_add(NULL, "_telnet", "_tcp", 23, NULL, 0));	
}

//display or change the hostname and services
void hostname(char* s)
{
	char *t = strstr(s, parslashquote);
	if(t == NULL)
	{
		kprintf("##SYS.HOST#: %s.local\n  IP:%s #\n",g_device->hostname,getIp());
		return;
	}
	
	t +=2;
	char *t_end  = strstr(t, parquoteslash);
    if(t_end == NULL)
    {
		kprintf(stritCMDERROR);
		return;
    }

	if (t_end-t ==0)
		strcpy(	g_device->hostname, "karadio32");
	else
	{	
		if (t_end-t >= HOSTLEN) t_end = t+HOSTLEN;
		strncpy(g_device->hostname,t,(t_end-t)*sizeof(char));
		g_device->hostname[(t_end-t)*sizeof(char)] = 0;
	}
	saveDeviceSettings(g_device);	
	setHostname(g_device->hostname);
	hostname((char*) "");
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
	esp_log_level_set("*", level);
	s_log_default_level=level; 
	g_device->trace_level = level;
	saveDeviceSettings(g_device);
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
		else if(startsWith("auto", tmp+5)) wifiAuto(tmp);
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
		else if(startsWith (  "edit",tmp+4)) 	clientEdit(tmp);
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
		else if(strcmp(tmp+4, "prerelease") == 0) 	update_firmware((char*)"KaRadio32prv");
		else if(startsWith (  "patch",tmp+4)) 	syspatch(tmp);
		else if(startsWith (  "ledg",tmp+4)) 	sysledgpio(tmp); //ledgpio
		else if(startsWith (  "ledpol",tmp+4)) 	sysledpol(tmp);
		else if(startsWith (  "led",tmp+4)) 	sysled(tmp);
		else if(strcmp(tmp+4, "date") == 0) 	ntp_print_time();
		else if(strncmp(tmp+4, "vers",4) == 0) 	kprintf("Release: %s, Revision: %s, KaRadio32\n",RELEASE,REVISION);
		else if(startsWith(   "tzo",tmp+4)) 	tzoffset(tmp);
		else if(strcmp(tmp+4, "logn") == 0) 	setLogLevel(ESP_LOG_NONE);
		else if(strcmp(tmp+4, "loge") == 0) 	setLogLevel(ESP_LOG_ERROR); 
		else if(strcmp(tmp+4, "logw") == 0) 	setLogLevel(ESP_LOG_WARN); 
		else if(strcmp(tmp+4, "logi") == 0) 	setLogLevel(ESP_LOG_INFO); 
		else if(strcmp(tmp+4, "logd") == 0) 	setLogLevel(ESP_LOG_DEBUG); 
		else if(strcmp(tmp+4, "logv") == 0) 	setLogLevel(ESP_LOG_VERBOSE); 
		else if(strcmp(tmp+4, "dlog") == 0) 	displayLogLevel();
		else if(strncmp(tmp+4, "cali",4) == 0) 	xpt_calibrate();
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
