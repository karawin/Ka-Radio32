#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <nvs.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/i2s.h"
#include "driver/uart.h"

#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/api.h"
#include "lwip/tcp.h"
#include "lwip/dns.h"

#include "app_main.h"

#include "spiram_fifo.h"
#include "audio_renderer.h"
#include "mdns_task.h"
#include "audio_player.h"

#ifdef CONFIG_BT_SPEAKER_MODE
#include "bt_speaker.h"
#endif


#include "eeprom.h"

/////////////////////////////////////////////////////
///////////////////////////
#include "bt_config.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
//#include "esp_wifi.h"
#include "xi2c.h"
#include "fonts.h"
#include "ssd1306.h"
#include "nvs_flash.h"
#include "gpio16.h"
#include "buffer.h"
#include "servers.h"
#include "webclient.h"
#include "webserver.h"
#include "interface.h"
#include "vs1053.h"

/* The event group allows multiple bits for each event*/
//   are we connected  to the AP with an IP? */
const int CONNECTED_BIT = 0x00000001;
//
const int CONNECTED_AP  = 0x00000010;

//#define BLINK_GPIO 4
#define I2C_EXAMPLE_MASTER_SCL_IO    14    /*!< gpio number for I2C master clock */////////////
#define I2C_EXAMPLE_MASTER_SDA_IO    13    /*!< gpio number for I2C master data  *//////////////
#define I2C_EXAMPLE_MASTER_NUM I2C_NUM_1   /*!< I2C port number for master dev */
#define I2C_EXAMPLE_MASTER_TX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_EXAMPLE_MASTER_RX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_EXAMPLE_MASTER_FREQ_HZ    100000     /*!< I2C master clock frequency */

#define TAG "main"

//Priorities of the reader and the decoder thread. bigger number = higher prio
#define PRIO_READER configMAX_PRIORITIES -3
#define PRIO_MQTT configMAX_PRIORITIES - 3
#define PRIO_CONNECT configMAX_PRIORITIES -1
#define striWATERMARK  "watermark: %d  heap: %d"


/* */
EventGroupHandle_t wifi_event_group ;
xQueueHandle timer_queue;
wifi_mode_t mode;
//xSemaphoreHandle print_mux;
uint16_t FlashOn = 5,FlashOff = 5;
bool ledStatus = true; // true: normal blink, false: led on when playing
player_t *player_config;
output_mode_t audio_output_mode; 
uint8_t clientIvol = 0;

output_mode_t get_audio_output_mode() 
{ return audio_output_mode;}

void i2c_state(char* State)
{
	SSD1306_GotoXY(2, 30); 
	SSD1306_DrawRectangle(2, 30, SSD1306_WIDTH - 1, 10, SSD1306_COLOR_BLACK);	
    SSD1306_Puts(State, &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_UpdateScreen();
}

void i2c_test(char* ip)
{
	
    char *url = "Stopped";// get_url(); // play_url();

    SSD1306_Fill(SSD1306_COLOR_BLACK); // clear screen

    SSD1306_GotoXY(20, 4);
    SSD1306_Puts("KaraDio", &Font_11x18, SSD1306_COLOR_WHITE);
    
    SSD1306_GotoXY(2, 20);

    SSD1306_Puts("WiFi Webradio", &Font_7x10, SSD1306_COLOR_WHITE);
    SSD1306_GotoXY(2, 30);
    
    SSD1306_Puts(url, &Font_7x10, SSD1306_COLOR_WHITE);
    if (strlen(url) > 18)  {
      SSD1306_GotoXY(2, 39);
      SSD1306_Puts(url + 18, &Font_7x10, SSD1306_COLOR_WHITE);
    }
    SSD1306_GotoXY(16, 53);

    SSD1306_GotoXY(2, 53);
    SSD1306_Puts("IP:", &Font_7x10, SSD1306_COLOR_WHITE);
    SSD1306_Puts(ip, &Font_7x10, SSD1306_COLOR_WHITE);    

    // Update screen, send changes to LCD 
    SSD1306_UpdateScreen();
   
/* for class-D amplifier system. Dim OLED to avoid noise from panel*/
/* PLEASE comment out next three lines for ESP32-ADB system*/  
 //   vTaskDelay(500);
//    SSD1306_Fill(SSD1306_COLOR_BLACK);
//    SSD1306_UpdateScreen();  
/* The above part is for class-D webradio system*/  
}


/**
 * @brief i2c master initialization
 */
static void i2c_example_master_init()
{
    int i2c_master_port = I2C_EXAMPLE_MASTER_NUM;
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_EXAMPLE_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_EXAMPLE_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_EXAMPLE_MASTER_FREQ_HZ;
    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode,
                       I2C_EXAMPLE_MASTER_RX_BUF_DISABLE,
                       I2C_EXAMPLE_MASTER_TX_BUF_DISABLE, 0);
}

//////////////////////////////////////////////////////////////////

uint8_t getIvol()
{
	return clientIvol;
}

void setIvol( uint8_t vol)
{
	clientIvol = vol;
}


static renderer_config_t *create_renderer_config()
{
    renderer_config_t *renderer_config = calloc(1, sizeof(renderer_config_t));

    renderer_config->bit_depth = I2S_BITS_PER_SAMPLE_16BIT;
    renderer_config->i2s_num = I2S_NUM_0;
    renderer_config->sample_rate = 44100;
    renderer_config->sample_rate_modifier = 1.0;
    renderer_config->output_mode = audio_output_mode;

    if(renderer_config->output_mode == I2S_MERUS) {
        renderer_config->bit_depth = I2S_BITS_PER_SAMPLE_32BIT;
    }

    if(renderer_config->output_mode == DAC_BUILT_IN) {
        renderer_config->bit_depth = I2S_BITS_PER_SAMPLE_16BIT;
    }

    return renderer_config;
}


void start_network();

/******************************************************************************
 * FunctionName : checkUart
 * Description  : Check for a valid uart baudrate
 * Parameters   : baud
 * Returns      : baud
*******************************************************************************/
uint32_t checkUart(uint32_t speed)
{
	uint32_t valid[] = {1200,2400,4800,9600,14400,19200,28800,38400,57600,76880,115200,230400};
	int i ;
	for (i=0;i<12;i++){
		if (speed == valid[i]) return speed;
	}
	return 115200; // default
}


/******************************************************************************
 * FunctionName : init_hardware
 * Description  : Init all hardware, partitions etc
 * Parameters   : 
 * Returns      : 
*******************************************************************************/
static void init_hardware()
{
	VS1053_HW_init(); // init spi
	VS1053_Start();
	
    //Initialize the SPI RAM chip communications and see if it actually retains some bytes. If it
    //doesn't, warn user.
    if (!spiRamFifoInit()) {
        ESP_LOGE(TAG, "\nSPI RAM chip fail!");
        esp_restart();
    }

    ESP_LOGI(TAG, "hardware initialized");
}



/* event handler for pre-defined wifi events */
static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    EventGroupHandle_t wifi_event = ctx;

    switch (event->event_id)
    {
    case SYSTEM_EVENT_STA_START:
		FlashOn = FlashOff = 50;
        esp_wifi_connect();
        break;
		
	case SYSTEM_EVENT_STA_CONNECTED:
		xEventGroupSetBits(wifi_event, CONNECTED_AP);
		
		break;

    case SYSTEM_EVENT_STA_GOT_IP:
		FlashOn = 10;FlashOff = 190;
        xEventGroupSetBits(wifi_event, CONNECTED_BIT);
        break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
        /* This is a workaround as ESP32 WiFi libs don't currently
           auto-reassociate. */
		FlashOn = FlashOff = 50;
		xEventGroupClearBits(wifi_event, CONNECTED_AP);
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event, CONNECTED_BIT);
		
        break;

	case SYSTEM_EVENT_AP_START:
		FlashOn = 10;FlashOff = 190;
		xEventGroupSetBits(wifi_event, CONNECTED_AP);
		xEventGroupSetBits(wifi_event, CONNECTED_BIT);
		break;
		
	case SYSTEM_EVENT_AP_STADISCONNECTED:
		break;
		
    default:
        break;
    }

    return ESP_OK;
}


static void initialise_wifi_and_network()
{
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	
	tcpip_adapter_init();	
	wifi_event_group = xEventGroupCreate();
	
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, wifi_event_group) );
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_FLASH) );
}

static void start_wifi()
{
    ESP_LOGI(TAG, "starting wifi");
	struct device_settings *device;	
	char ssid[32]; 
	char pass[64];
	
    /* FreeRTOS event group to signal when we are connected & ready to make a request */
//    EventGroupHandle_t wifi_event_group = xEventGroupCreate();

    /* init wifi & network*/
    initialise_wifi_and_network();
	
	device = getDeviceSettings();
	while (1)
	{
		switch (device->current_ap)
		{
			case STA1: //ssid1 used
				strcpy(ssid,device->ssid1);
				strcpy(pass,device->pass1);
				esp_wifi_set_mode(WIFI_MODE_STA) ;
			break;
			case STA2: //ssid2 used
				strcpy(ssid,device->ssid2);
				strcpy(pass,device->pass2);	
				esp_wifi_set_mode(WIFI_MODE_STA) ;			
			break;

			default: // other: AP mode
				device->current_ap = 0;
				esp_wifi_set_mode(WIFI_MODE_AP) ;
		}
	
	
		ESP_ERROR_CHECK(esp_wifi_get_mode(&mode))	
		if (mode == WIFI_MODE_AP)
		{
			wifi_config_t wifi_config = {
				.ap = {
					.ssid = "WifiKaradio",
					.password = "",
					.ssid_len = 0,
					.authmode = WIFI_AUTH_OPEN,
					.max_connection = 4,
					.beacon_interval = 100,
				},
			};
			ESP_LOGE(TAG, "The default AP is  WifiKaRadio. Connect your wifi to it.\nThen connect a webbrowser to 192.168.4.1 and go to Setting\nMay be long to load the first time.Be patient.");
			ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
		}
		else
		{
			wifi_config_t wifi_config = {
				.sta = {
					.bssid_set = 0,
				},
			};
			strcpy((char*)wifi_config.sta.ssid,ssid);
			strcpy((char*)wifi_config.sta.password,pass);
			esp_wifi_disconnect();
			ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
			ESP_LOGI(TAG, "connecting");
			esp_wifi_connect();				
		}

		ESP_ERROR_CHECK( esp_wifi_start() );
		ESP_LOGI(TAG, "Initialised wifi");
// 	   set_wifi_credentials();
 
		/* Wait for the callback to set the CONNECTED_BIT in the event group. */
		if ( (xEventGroupWaitBits(wifi_event_group, CONNECTED_AP,false, true, 2000) & CONNECTED_AP) ==0) //timeout
		{
			device->current_ap++;
			device->current_ap %=3;
			saveDeviceSettings(device);
			printf("\ndevice->current_ap: %d\n",device->current_ap);
			//vTaskDelay(100);
			//esp_restart();		
		}	else break;						
	}					
	i2c_state("Connected to AP");	
	free(device);
}

void start_network(){
	struct device_settings *device;	
	tcpip_adapter_ip_info_t info;
	
	struct ip4_addr ipAddr;
	struct ip4_addr mask;
	struct ip4_addr gate;
	uint8_t dhcpEn = 0;
	
	device = getDeviceSettings();	
	// Wifi ok .
	
	switch (device->current_ap)
	{
		case STA1: //ssid1 used
			IP4_ADDR(&ipAddr, device->ipAddr1[0], device->ipAddr1[1],device->ipAddr1[2], device->ipAddr1[3]);
			IP4_ADDR(&gate, device->gate1[0],device->gate1[1],device->gate1[2], device->gate1[3]);
			IP4_ADDR(&mask, device->mask1[0], device->mask1[1],device->mask1[2], device->mask1[3]);
			dhcpEn = device->dhcpEn1;
		break;
		case STA2: //ssid2 used
			IP4_ADDR(&ipAddr, device->ipAddr2[0], device->ipAddr2[1],device->ipAddr2[2], device->ipAddr2[3]);
			IP4_ADDR(&gate, device->gate2[0],device->gate2[1],device->gate2[2], device->gate2[3]);
			IP4_ADDR(&mask, device->mask2[0], device->mask2[1],device->mask2[2], device->mask2[3]);
			dhcpEn = device->dhcpEn2;
		break;

		default: // other: AP mode
			IP4_ADDR(&ipAddr, 192,168,4,1);
			IPADDR2_COPY(&gate,&ipAddr);
			IP4_ADDR(&mask,255,255,255,0);
	}	
	
	IPADDR2_COPY(&info.ip,&ipAddr);
	IPADDR2_COPY(&info.gw,&gate);
	IPADDR2_COPY(&info.netmask,&mask);	

	if (mode == WIFI_MODE_AP)
	{
			xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,false, true, 3000);
			IPADDR2_COPY(&info.ip,&ipAddr);
			tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_AP, &info);
			device->dhcpEn1 = device->dhcpEn2 = 1;
			IPADDR2_COPY(&device->mask1, &mask);
			IPADDR2_COPY(&device->mask2, &mask);
			saveDeviceSettings(device);			
	}
	else // mode STA
	{	
		if ((!dhcpEn) ) // check if ip is valid without dhcp
		{
			tcpip_adapter_dhcpc_stop(TCPIP_ADAPTER_IF_STA);  // stop dhcp client	
			tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_STA, &info);
			dns_setserver(0,( ip_addr_t* ) &info.gw);
			//ip_addr_t ipdns = dns_getserver(0);
			//printf("DNS: %s  \n",ip4addr_ntoa(( struct ip4_addr* ) &ipdns));
		}
		vTaskDelay(1);
		// wait for ip
						
		if ( (xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,false, true, 3000) & CONNECTED_BIT) ==0) //timeout	
		{ // enable dhcp and restart
			if (device->current_ap ==1)
				device->dhcpEn1 = 1;
			else
				device->dhcpEn2 = 1;
			saveDeviceSettings(device);	
			esp_restart();
		}				
		tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &info);
		
		if (dhcpEn) // if dhcp enabled update fields
		{  
			IPADDR2_COPY(&device->ipAddr1, &info.ip);
			IPADDR2_COPY(&device->mask1, &info.netmask);
			IPADDR2_COPY(&device->gate1, &info.gw);	
			saveDeviceSettings(device);		
		}
		else
		{
			// if static ip	check dns
//			dns_setserver(0,( ip_addr_t* ) &gate);
			ip_addr_t ipdns = dns_getserver(0);
			printf("\nDNS: %s\n",ip4addr_ntoa(( struct ip4_addr* ) &ipdns));
		}
	}
	
	i2c_state("IP found");	
  /* start mDNS */
    // xTaskCreatePinnedToCore(&mdns_task, "mdns_task", 2048, wifi_event_group, 5, NULL, 0);

	free(device);
}


//blinking led and timer isr
void ledTask(void* p) {
struct device_settings *device;	

	int uxHighWaterMark;

	gpio4_output_conf();	
	while(1) {
		timer_event_t evt;
		if (xQueueReceive(timer_queue, &evt, 0))
		{
			if(evt.type == TIMER_SLEEP) {
				printf("timer Sleep\n");
				clientDisconnect("Timer"); // stop the player
			}
			if(evt.type == TIMER_WAKE) {
				printf("timer Wake\n");
				clientConnect(); // start the player	
			}
		}
		if (ledStatus) gpio4_output_set(0);
		vTaskDelay(FlashOff ); 
		
		if (ledStatus) // on led and save volume if changed
		{		
			gpio4_output_set(1);
			vTaskDelay(FlashOn);
		}	

		// save volume if changed		
		device = getDeviceSettings();
		if (device != NULL)
		{	
			if (device->vol != getIvol()){ 			
				device->vol = getIvol();
				saveDeviceSettings(device);
				uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
				ESP_LOGI("ledTask",striWATERMARK,uxHighWaterMark,xPortGetFreeHeapSize( ));
			}
			free(device);	
		}			
	}
//	printf("t0 end\n");
	vTaskDelete( NULL ); // stop the task (never reached)
}

void uartInterfaceTask(void *pvParameters) {
	char tmp[255];
	int d;
	uint8_t c;
	int t ;
	struct device_settings *device;
	uint32_t uspeed;
	int uxHighWaterMark;
	
	device = getDeviceSettings();
	uspeed = device->uartspeed;	
	free (device);
	
   uart_config_t uart_config0 = {
        .baud_rate = uspeed,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,    //UART_HW_FLOWCTRL_CTS_RTS,
        .rx_flow_ctrl_thresh = 0,
    };	
	uart_param_config(UART_NUM_0, &uart_config0);	
	uart_driver_install(UART_NUM_0, 1024 , 0, 0, NULL, 0);
	
	for(t = 0; t<sizeof(tmp); t++) tmp[t] = 0;
	t = 0;
	
	while(1) {
		while(1) {
			d= uart_read_bytes(UART_NUM_0, &c, 1, 100);
			if (d>0)
			{
				if((char)c == '\r') break;
				if((char)c == '\n') break;
				tmp[t] = (char)c;
				t++;
				if(t == sizeof(tmp)-1) t = 0;
			}
			//else printf("uart d: %d, T= %d\n",d,t);
			//switchCommand() ;  // hardware panel of command
		}
		checkCommand(t, tmp);
		
		uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
		ESP_LOGI("uartInterfaceTask",striWATERMARK,uxHighWaterMark,xPortGetFreeHeapSize( ));
				
		for(t = 0; t<sizeof(tmp); t++) tmp[t] = 0;
		t = 0;
	}	
}

/**
 * entry point
 */
void app_main()
{
	struct device_settings *device;
	uint32_t uspeed;
	xTaskHandle pxCreatedTask;
	ESP_LOGI(TAG, "starting app_main()");
    ESP_LOGI(TAG, "RAM left: %u", esp_get_free_heap_size());
	
	partitions_init();
	//init hardware
    init_hardware(); 
	

	device = getDeviceSettings();
	// device partition initialized?
	if (device->cleared != 0xAABB)
	{		
		ESP_LOGI(TAG,"Device not cleared. Clear it.");
		eeErasesettings();
		free(device);
		device = getDeviceSettings();
		device->cleared = 0xAABB; //marker init done
		device->uartspeed = 115200; // default
		device->audio_output_mode = VS1053; // default
		device->trace_level = ESP_LOG_ERROR; //default
		saveDeviceSettings(device);
	}	
	
	// output mode
	//I2S, I2S_MERUS, DAC_BUILT_IN, PDM, VS1053
	audio_output_mode = device->audio_output_mode;
	//audio_output_mode = VS1053; // to be removed when ...
	if ((audio_output_mode == VS1053) && (getVsVersion() < 3))
	{
		audio_output_mode = I2S	;
		saveDeviceSettings(device);
	}

	ESP_LOGI(TAG, "audio_output_mode %d\nOne of I2S=0, I2S_MERUS, DAC_BUILT_IN, PDM, VS1053",audio_output_mode);
	// log level
	setLogLevel(device->trace_level);
	
	//uart speed
	uspeed = device->uartspeed;	
	uspeed = checkUart(uspeed);	
	uart_set_baudrate(UART_NUM_0, uspeed);
	ESP_LOGI(TAG, "Set baudrate at %d",uspeed);
	if (device->uartspeed != uspeed)
	{
		device->uartspeed = uspeed;
		saveDeviceSettings(device);
	}	

	// volume
	setIvol( device->vol);
	timer_queue = xQueueCreate(10, sizeof(timer_event_t));

	// led blinks
	xTaskCreate(ledTask, "t0",1700, NULL, 1, &pxCreatedTask); // DEBUG/TEST 130
	ESP_LOGI(TAG, "%s task: %x","t0",(unsigned int)pxCreatedTask);	
	
	//Display if any	
	i2c_example_master_init();
	SSD1306_Init();
	i2c_test("");
	
	// Version infos
	ESP_LOGI(TAG, "Release %s, Revision %s",RELEASE,REVISION);
	ESP_LOGI(TAG, "SDK %s",esp_get_idf_version());
	ESP_LOGI(TAG, "Heap size: %d",xPortGetFreeHeapSize( ));

//-----------------------------
    start_wifi();
	start_network();
	
//-----------------------------------------------------
	//init softwares
//-----------------------------------------------------
	clientInit();	

    // init player config
    player_config = (player_t*)calloc(1, sizeof(player_t));
    player_config->command = CMD_NONE;
    player_config->decoder_status = UNINITIALIZED;
    player_config->decoder_command = CMD_NONE;
    player_config->buffer_pref = BUF_PREF_SAFE;
    player_config->media_stream = calloc(1, sizeof(media_stream_t));

	audio_player_init(player_config);	  
    // init renderer (i2s)
    renderer_init(create_renderer_config());	
	  
	tcpip_adapter_ip_info_t ip_info;

	if (mode == WIFI_MODE_AP)
		tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_AP, &ip_info);
	else	
		tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ip_info);
 
	printf("\nIP: %s\n\n",ip4addr_ntoa(&ip_info.ip));
	
	// LCD Display infos
    i2c_test(ip4addr_ntoa(&ip_info.ip));
	i2c_state("Started");
	
    ESP_LOGI(TAG, "RAM left %d", esp_get_free_heap_size());

	//start tasks
	xTaskCreate(uartInterfaceTask, "uartInterfaceTask", 2000, NULL, 2, &pxCreatedTask); // 350
	ESP_LOGI(TAG, "%s task: %x","uartInterfaceTask",(unsigned int)pxCreatedTask);
	xTaskCreate(clientTask, "clientTask", 2300, NULL, configMAX_PRIORITIES -5, &pxCreatedTask); // 340
	ESP_LOGI(TAG, "%s task: %x","clientTask",(unsigned int)pxCreatedTask);	
    xTaskCreate(serversTask, "serversTask", 2000, NULL, 4, &pxCreatedTask); //380
	ESP_LOGI(TAG, "%s task: %x","serversTask",(unsigned int)pxCreatedTask);	
	printf("Init ");
	vTaskDelay(1);
	for (int i=0;i<30;i++)
	{
		vTaskDelay(10);// wait tasks init
		printf(".");
	}
	printf(" Done\n");
	//autostart	
	kprintf("autostart: playing:%d, currentstation:%d\n",device->autostart,device->currentstation);
	setIvol( device->vol);
	setCurrentStation( device->currentstation);
	
	if (device->autostart ==1)
	{	
		vTaskDelay(50); 
		playStationInt(device->currentstation);
	}
	
//
//	ledStatus = ((device->options & T_LED)== 0);
//
	free(device);
	vTaskDelete( NULL ); 
}
