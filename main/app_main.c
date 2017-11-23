#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <nvs.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_heap_trace.h"
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
//#include "mdns_task.h"
#include "audio_player.h"
#include <u8g2.h>
#include "u8g2_esp32_hal.h"
#include "addon.h"

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
//#include "xi2c.h"
//#include "fonts.h"
//#include "ssd1306.h"
#include "nvs_flash.h"
#include "gpio.h"
#include "servers.h"
#include "webclient.h"
#include "webserver.h"
#include "interface.h"
#include "vs1053.h"
#include "ClickEncoder.h"
#include "addon.h"

/* The event group allows multiple bits for each event*/
//   are we connected  to the AP with an IP? */
const int CONNECTED_BIT = 0x00000001;
//
const int CONNECTED_AP  = 0x00000010;

//#define BLINK_GPIO 4
#define I2C_EXAMPLE_MASTER_SCL_IO    PIN_I2C_SCL    /*!< gpio number for I2C master clock */////////////
#define I2C_EXAMPLE_MASTER_SDA_IO    PIN_I2C_SDA    /*!< gpio number for I2C master data  *//////////////
#define I2C_EXAMPLE_MASTER_NUM I2C_NUM_1   			/*!< I2C port number for master dev */
#define I2C_EXAMPLE_MASTER_TX_BUF_DISABLE   0   	/*!< I2C master do not need buffer */
#define I2C_EXAMPLE_MASTER_RX_BUF_DISABLE   0   	/*!< I2C master do not need buffer */
#define I2C_EXAMPLE_MASTER_FREQ_HZ    100000    	/*!< I2C master clock frequency */

#define TAG "main"

//Priorities of the reader and the decoder thread. bigger number = higher prio
#define PRIO_READER configMAX_PRIORITIES -3
#define PRIO_MQTT configMAX_PRIORITIES - 3
#define PRIO_CONNECT configMAX_PRIORITIES -1
#define striWATERMARK  "watermark: %d  heap: %d"

void start_network();
/* */
static EventGroupHandle_t wifi_event_group ;
xQueueHandle event_queue;
static wifi_mode_t mode;
//xSemaphoreHandle print_mux;
static uint16_t FlashOn = 5,FlashOff = 5;
bool ledStatus = true; // true: normal blink, false: led on when playing
player_t *player_config;
static output_mode_t audio_output_mode; 
static uint8_t clientIvol = 0;
//ip
char localIp[20];
// disable 1MS timer interrupt
void noInterrupt1Ms()
{
	timer_disable_intr(TIMERGROUP1MS, msTimer);
}
// enable 1MS timer interrupt
void interrupt1Ms()
{
	timer_enable_intr(TIMERGROUP1MS, msTimer);
}
char* getIp() { return (localIp);}

IRAM_ATTR void   microsCallback(void *pArg) {
	int timer_idx = (int) pArg;
	queue_event_t evt;	
	TIMERG1.hw_timer[timer_idx].update = 1;
	TIMERG1.int_clr_timers.t1 = 1; //isr ack
		evt.type = TIMER_1mS;
        evt.i1 = TIMERGROUP1mS;
        evt.i2 = timer_idx;
	xQueueSendFromISR(event_queue, &evt, NULL);	
	TIMERG1.hw_timer[timer_idx].config.alarm_en = 1;
}
//-----------------------------------
IRAM_ATTR void   msCallback(void *pArg) {
	int timer_idx = (int) pArg;
	queue_event_t evt;	
	TIMERG1.hw_timer[timer_idx].update = 1;
	TIMERG1.int_clr_timers.t0 = 1; //isr ack
		evt.type = TIMER_1MS;
        evt.i1 = TIMERGROUP1MS;
        evt.i2 = timer_idx;
	xQueueSendFromISR(event_queue, &evt, NULL);	
	TIMERG1.hw_timer[timer_idx].config.alarm_en = 1;
}

IRAM_ATTR void   sleepCallback(void *pArg) {
	int timer_idx = (int) pArg;
	queue_event_t evt;	
	TIMERG0.int_clr_timers.t0 = 1; //isr ack
		evt.type = TIMER_SLEEP;
        evt.i1 = TIMERGROUP;
        evt.i2 = timer_idx;
	xQueueSendFromISR(event_queue, &evt, NULL);	
	TIMERG0.hw_timer[timer_idx].config.alarm_en = 0;
}
IRAM_ATTR void   wakeCallback(void *pArg) {

	int timer_idx = (int) pArg;
	queue_event_t evt;	
	TIMERG0.int_clr_timers.t1 = 1;
        evt.i1 = TIMERGROUP;
        evt.i2 = timer_idx;
		evt.type = TIMER_WAKE;
	xQueueSendFromISR(event_queue, &evt, NULL);
	TIMERG0.hw_timer[timer_idx].config.alarm_en = 0;
}


void startSleep(uint32_t delay)
{
	ESP_LOGD(TAG,"Delay:%d\n",delay);
	if (delay == 0) return;
	ESP_ERROR_CHECK(timer_set_counter_value(TIMERGROUP, sleepTimer, 0x00000000ULL));
	ESP_ERROR_CHECK(timer_set_alarm_value(TIMERGROUP, sleepTimer,TIMERVALUE(delay*60)));
	ESP_ERROR_CHECK(timer_enable_intr(TIMERGROUP, sleepTimer));
	ESP_ERROR_CHECK(timer_set_alarm(TIMERGROUP, sleepTimer,TIMER_ALARM_EN));
	ESP_ERROR_CHECK(timer_start(TIMERGROUP, sleepTimer));
}
void stopSleep(){
	ESP_LOGD(TAG,"stopDelayDelay\n");
	ESP_ERROR_CHECK(timer_pause(TIMERGROUP, sleepTimer));
}
void startWake(uint32_t delay)
{
	ESP_LOGD(TAG,"Wake Delay:%d\n",delay);
	if (delay == 0) return;
	ESP_ERROR_CHECK(timer_set_counter_value(TIMERGROUP, wakeTimer, 0x00000000ULL));
	//TIMER_INTERVAL0_SEC * TIMER_SCALE - TIMER_FINE_ADJ
	ESP_ERROR_CHECK(timer_set_alarm_value(TIMERGROUP, wakeTimer,TIMERVALUE(delay*60)));
	ESP_ERROR_CHECK(timer_enable_intr(TIMERGROUP, wakeTimer));
	ESP_ERROR_CHECK(timer_set_alarm(TIMERGROUP, wakeTimer,TIMER_ALARM_EN));
	ESP_ERROR_CHECK(timer_start(TIMERGROUP, wakeTimer));	
}
void stopWake(){
	ESP_LOGD(TAG,"stopDelayWake\n");
	ESP_ERROR_CHECK(timer_pause(TIMERGROUP, wakeTimer));
}


void initTimers()
{
timer_config_t config;
	config.alarm_en = 1;
    config.auto_reload = TIMER_AUTORELOAD_DIS;
    config.counter_dir = TIMER_COUNT_UP;
    config.divider = TIMER_DIVIDER;
    config.intr_type = TIMER_INTR_LEVEL;
    config.counter_en = TIMER_PAUSE;
	
	/*Configure timer sleep*/
    ESP_ERROR_CHECK(timer_init(TIMERGROUP, sleepTimer, &config));
	ESP_ERROR_CHECK(timer_pause(TIMERGROUP, sleepTimer));
	ESP_ERROR_CHECK(timer_isr_register(TIMERGROUP, sleepTimer, sleepCallback, (void*) sleepTimer, 0, NULL));
	/*Configure timer wake*/
    ESP_ERROR_CHECK(timer_init(TIMERGROUP, wakeTimer, &config));
	ESP_ERROR_CHECK(timer_pause(TIMERGROUP, wakeTimer));
	ESP_ERROR_CHECK(timer_isr_register(TIMERGROUP, wakeTimer, wakeCallback, (void*) wakeTimer, 0, NULL));	
	/*Configure timer 1MS*/
	config.auto_reload = TIMER_AUTORELOAD_EN;
	config.divider = TIMER_DIVIDER1MS;
	ESP_ERROR_CHECK(timer_init(TIMERGROUP1MS, msTimer, &config));
	ESP_ERROR_CHECK(timer_pause(TIMERGROUP1MS, msTimer));
	ESP_ERROR_CHECK(timer_isr_register(TIMERGROUP1MS, msTimer, msCallback, (void*) msTimer, 0, NULL));
	/* start 1MS timer*/
	ESP_ERROR_CHECK(timer_set_counter_value(TIMERGROUP1MS, msTimer, 0x00000000ULL));
	ESP_ERROR_CHECK(timer_set_alarm_value(TIMERGROUP1MS, msTimer,TIMERVALUE1MS(1)));
	ESP_ERROR_CHECK(timer_enable_intr(TIMERGROUP1MS, msTimer));
	ESP_ERROR_CHECK(timer_set_alarm(TIMERGROUP1MS, msTimer,TIMER_ALARM_EN));
	ESP_ERROR_CHECK(timer_start(TIMERGROUP1MS, msTimer));
	
	/*Configure timer 1µS*/
	config.auto_reload = TIMER_AUTORELOAD_EN;
	config.divider = TIMER_DIVIDER1mS;
	ESP_ERROR_CHECK(timer_init(TIMERGROUP1mS, microsTimer, &config));
	ESP_ERROR_CHECK(timer_pause(TIMERGROUP1mS, microsTimer));
	ESP_ERROR_CHECK(timer_isr_register(TIMERGROUP1mS, microsTimer, microsCallback, (void*) microsTimer, 0, NULL));
	/* start 1µS timer*/
	ESP_ERROR_CHECK(timer_set_counter_value(TIMERGROUP1mS, microsTimer, 0x00000000ULL));
	ESP_ERROR_CHECK(timer_set_alarm_value(TIMERGROUP1mS, microsTimer,TIMERVALUE1mS(10))); // 10 ms timer
	ESP_ERROR_CHECK(timer_enable_intr(TIMERGROUP1mS, microsTimer));
	ESP_ERROR_CHECK(timer_set_alarm(TIMERGROUP1mS, microsTimer,TIMER_ALARM_EN));
	ESP_ERROR_CHECK(timer_start(TIMERGROUP1mS, microsTimer));
}


output_mode_t get_audio_output_mode() 
{ return audio_output_mode;}



//////////////////////////////////////////////////////////////////

uint8_t getIvol()
{
	return clientIvol;
}

void setIvol( uint8_t vol)
{
	clientIvol = vol;
}

// Renderer config creation
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
		FlashOn = FlashOff = 100;
        esp_wifi_connect();
        break;
		
	case SYSTEM_EVENT_STA_CONNECTED:
		xEventGroupSetBits(wifi_event, CONNECTED_AP);
		
		break;

    case SYSTEM_EVENT_STA_GOT_IP:
		FlashOn = 5;FlashOff = 395;
        xEventGroupSetBits(wifi_event, CONNECTED_BIT);
        break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
        /* This is a workaround as ESP32 WiFi libs don't currently
           auto-reassociate. */
		FlashOn = FlashOff = 100;
		xEventGroupClearBits(wifi_event, CONNECTED_AP);
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event, CONNECTED_BIT);
		
        break;

	case SYSTEM_EVENT_AP_START:
		FlashOn = 5;FlashOff = 395;
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


static void start_wifi()
{
    ESP_LOGI(TAG, "starting wifi");
	struct device_settings *device;	
	char ssid[32]; 
	char pass[64];
	tcpip_adapter_ip_info_t info;
		
	device = getDeviceSettings();
	
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	
	tcpip_adapter_init();
	tcpip_adapter_dhcpc_stop(TCPIP_ADAPTER_IF_STA); // Don't run a DHCP client	
    /* FreeRTOS event group to signal when we are connected & ready to make a request */
	wifi_event_group = xEventGroupCreate();	
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, wifi_event_group) );
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_FLASH) );

	IP4_ADDR(&info.ip, device->ipAddr1[0], device->ipAddr1[1],device->ipAddr1[2], device->ipAddr1[3]);
	IP4_ADDR(&info.gw, device->gate1[0],device->gate1[1],device->gate1[2], device->gate1[3]);
	IP4_ADDR(&info.netmask, device->mask1[0], device->mask1[1],device->mask1[2], device->mask1[3]);
	tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_STA, &info); //default
	
	
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
			ESP_ERROR_CHECK( esp_wifi_start() );
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
			ESP_ERROR_CHECK( esp_wifi_start() );
//			esp_wifi_connect();				
		}

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
	free(device);
}

void start_network(){
	struct device_settings *device;	
	tcpip_adapter_ip_info_t info;
	
	ip4_addr_t ipAddr;
	ip4_addr_t mask;
	ip4_addr_t gate;
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
		if (dhcpEn ) // check if ip is valid without dhcp
			tcpip_adapter_dhcpc_start(TCPIP_ADAPTER_IF_STA); //  run a DHCP client
		else
		{
			ESP_ERROR_CHECK(tcpip_adapter_set_ip_info(TCPIP_ADAPTER_IF_STA, &info));
			dns_clear_servers(false);
			IP_SET_TYPE(( ip_addr_t* )&info.gw, IPADDR_TYPE_V4); // mandatory
			(( ip_addr_t* )&info.gw)->type = IPADDR_TYPE_V4;
			dns_setserver(0,( ip_addr_t* ) &info.gw);
			dns_setserver(1,( ip_addr_t* ) &info.gw);				// if static ip	check dns
		}

		
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
		
		vTaskDelay(1);	
		// retrieve the current ip	
		tcpip_adapter_ip_info_t ip_info;
		ip_info.ip.addr =0;		
		while (ip_info.ip.addr ==0)
		{
			if (mode == WIFI_MODE_AP)
				tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_AP, &ip_info);
			else	
				tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ip_info);
		}		
		ip_addr_t ipdns0 = dns_getserver(0);
//		ip_addr_t ipdns1 = dns_getserver(1);
		printf("\nDNS: %s  \n",ip4addr_ntoa(( struct ip4_addr* ) &ipdns0));
		strcpy(localIp , ip4addr_ntoa(&ip_info.ip));
		printf("IP: %s\n\n",ip4addr_ntoa(&ip_info.ip));



		
		if (dhcpEn) // if dhcp enabled update fields
		{  
			tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &info);
			IPADDR2_COPY(&device->ipAddr1, &info.ip);
			IPADDR2_COPY(&device->mask1, &info.netmask);
			IPADDR2_COPY(&device->gate1, &info.gw);	
			saveDeviceSettings(device);		
		}
	}
	free(device);	
	lcd_state("IP found");	
  /* start mDNS */
    // xTaskCreatePinnedToCore(&mdns_task, "mdns_task", 2048, wifi_event_group, 5, NULL, 0);

}


//blinking led and timer isr
void timerTask(void* p) {
	struct device_settings *device;	
	uint32_t ctime = 0;
	uint32_t cCur;
	bool stateLed = false;
//	int uxHighWaterMark;
	
	initTimers();
	
	gpio_output_conf(GPIO_LED);
	gpio_set_level(GPIO_LED,0);	
	cCur = FlashOff*10;
	
	while(1) {
		// read and treat the timer queue events
		queue_event_t evt;
		while (xQueueReceive(event_queue, &evt, 0))
		{
			switch (evt.type){
					case TIMER_SLEEP:
						clientDisconnect("Timer"); // stop the player
					break;
					case TIMER_WAKE:
					clientConnect(); // start the player	
					break;
					case TIMER_1MS: // 1 ms 
					  ctime++;	// for led
					  if (serviceEncoder != NULL) serviceEncoder(); // for the encoder
					  if (serviceAddon != NULL) serviceAddon(); // for the encoder
					break;
					case TIMER_1mS:  //10µs
					break;
					default:
					break;
			}
			taskYIELD();
		}
		taskYIELD();
		if (ledStatus)
		{
			
			if (ctime >= cCur)
			{
				taskYIELD();
				if (stateLed)
				{
					gpio_set_level(GPIO_LED,0);	
					stateLed = false;
					cCur = FlashOff*10;
				} else
				{
					gpio_set_level(GPIO_LED,1);	
					stateLed = true;
					cCur = FlashOn*10;
					device = getDeviceSettings();
					if (device != NULL)
					{	
						if (device->vol != getIvol()){ 			
							device->vol = getIvol();
							taskYIELD();
							saveDeviceSettingsVolume(device);
//							ESP_LOGD("timerTask",striWATERMARK,uxTaskGetStackHighWaterMark( NULL ),xPortGetFreeHeapSize( ));
						}
						free(device);	
					}											
				}
				ctime = 0;
			}			
		}
		taskYIELD();
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
		ESP_LOGD("uartInterfaceTask",striWATERMARK,uxHighWaterMark,xPortGetFreeHeapSize( ));
				
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
	//initArduino();
	const esp_partition_t *running = esp_ota_get_running_partition();
	ESP_LOGE(TAG, "Running partition type %d subtype %d (offset 0x%08x)",
             running->type, running->subtype, running->address);
    // Initialize NVS.
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
        // OTA app partition table has a smaller NVS partition size than the non-OTA
        // partition table. This size mismatch may cause NVS initialization to fail.
        // If this happens, we erase NVS partition and initialize NVS again.
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );
	
	//init hardware	
	partitions_init();
	ESP_LOGI(TAG, "Partition init done...");
	
	device = getDeviceSettings();

	if (device->cleared != 0xAABB)
	{	
		free(device);
		ESP_LOGE(TAG,"Device config not ok. Try to restore");
		restoreDeviceSettings(); // try to restore the config from the saved one
		device = getDeviceSettings();		
		if (device->cleared != 0xAABB)
		{
			ESP_LOGE(TAG,"Device config not cleared. Clear it.");
			free(device);
			eeEraseAll();
			device = getDeviceSettings();	
			device->cleared = 0xAABB; //marker init done
			device->uartspeed = 115200; // default
			device->audio_output_mode = VS1053; // default
			device->trace_level = ESP_LOG_ERROR; //default
			device->vol = 100; //default
			saveDeviceSettings(device);			
		} else
			ESP_LOGE(TAG,"Device config restored");
	}	
	
	copyDeviceSettings(); // copy in the safe partion

	
	// init softwares
	telnetinit();
	websocketinit();


	// log level
	setLogLevel(device->trace_level);
	
	//SPI init for the vs1053 and lcd if spi.
	VS1053_spi_init(HSPI_HOST);

    init_hardware(); 
	ESP_LOGI(TAG, "Hardware init done...");
	//ESP_LOGE(TAG,"Corrupt1 %d",heap_caps_check_integrity(MALLOC_CAP_DMA,1));
	
	ESP_LOGE(TAG,"LCD Type %d",device->lcd_type);
	lcd_init(device->lcd_type);
	
	// output mode
	//I2S, I2S_MERUS, DAC_BUILT_IN, PDM, VS1053
	audio_output_mode = device->audio_output_mode;
	
	if ((audio_output_mode == VS1053) && (getVsVersion() < 3))
	{
		audio_output_mode = I2S	;
		device->audio_output_mode = audio_output_mode;
		ESP_LOGE(TAG," No vs1053 detected. Fall back to I2S mode");
		saveDeviceSettings(device);
	}
	

	ESP_LOGI(TAG, "audio_output_mode %d\nOne of I2S=0, I2S_MERUS, DAC_BUILT_IN, PDM, VS1053",audio_output_mode);

	setCurrentStation( device->currentstation);

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
	
	// Version infos
	ESP_LOGI(TAG, "Release %s, Revision %s",RELEASE,REVISION);
	ESP_LOGI(TAG, "SDK %s",esp_get_idf_version());
	ESP_LOGI(TAG, "Heap size: %d",xPortGetFreeHeapSize( ));

	lcd_welcome("");
	
// queue for events of the sleep / wake timers
	event_queue = xQueueCreate(10, sizeof(queue_event_t));
	// led blinks
	xTaskCreate(timerTask, "timerTask",1900, NULL, 1, &pxCreatedTask); 
	ESP_LOGI(TAG, "%s task: %x","t0",(unsigned int)pxCreatedTask);		
	
	
//-----------------------------
// start the network
//-----------------------------
    /* init wifi & network*/
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
    renderer_init(create_renderer_config());	

	
	// LCD Display infos
    lcd_welcome(localIp);
	lcd_state("Started");
	vTaskDelay(10);
    ESP_LOGI(TAG, "RAM left %d", esp_get_free_heap_size());

	//start tasks of KaRadio32
	xTaskCreate(uartInterfaceTask, "uartInterfaceTask", 2200, NULL, 2, &pxCreatedTask); 
	ESP_LOGI(TAG, "%s task: %x","uartInterfaceTask",(unsigned int)pxCreatedTask);
	xTaskCreate(clientTask, "clientTask", 2300, NULL, 4, &pxCreatedTask); 
	ESP_LOGI(TAG, "%s task: %x","clientTask",(unsigned int)pxCreatedTask);	
    xTaskCreate(serversTask, "serversTask", 2300, NULL, 3, &pxCreatedTask); 
	ESP_LOGI(TAG, "%s task: %x","serversTask",(unsigned int)pxCreatedTask);	
	xTaskCreate(task_addon, "task_addon", 2500, NULL, 5, &pxCreatedTask);  //high priority for the spi else too slow due to ucglib
	ESP_LOGI(TAG, "%s task: %x","task_addon",(unsigned int)pxCreatedTask);
	
	printf("Init ");
	vTaskDelay(1);
	for (int i=0;i<15;i++)
	{
		printf(".");
		vTaskDelay(10);// wait tasks init
	}
	printf(" Done\n");
	
	
	//autostart	
	kprintf("autostart: playing:%d, currentstation:%d\n",device->autostart,device->currentstation);
	setIvol( device->vol);
	
	
	if (device->autostart ==1)
	{	
		vTaskDelay(50); // wait a bit
		playStationInt(device->currentstation);
	}
	
//
	free(device);
	vTaskDelete( NULL ); 
}
