/******************************************************************************
 *
 * Copyright 2017 karawin (http://www.karawin.fr)
 *
*******************************************************************************/
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_spi_flash.h"
#include "esp_partition.h"
#include "esp_task_wdt.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
//#include "driver/uart.h"

#include "eeprom.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>
//#include "spi_flash.h"
//#include <esp_libc.h>
#include "interface.h"

#define NBSTATIONS		255
const static char *TAG = "eeprom";
static xSemaphoreHandle muxDevice;

const esp_partition_t * DEVICE;
const esp_partition_t * DEVICE1;
const esp_partition_t * STATIONS;

struct device_settings* g_device;

void partitions_init(void)
{
	DEVICE = esp_partition_find_first(64,0,NULL);
	if (DEVICE == NULL) ESP_LOGE(TAG, "DEVICE Partition not found");
	DEVICE1 = esp_partition_find_first(66,0,NULL);
	if (DEVICE1 == NULL) ESP_LOGE(TAG, "DEVICE1 Partition not found");
	STATIONS = esp_partition_find_first(65,0,NULL);
	if (STATIONS == NULL) ESP_LOGE(TAG, "STATIONS Partition not found");
	muxDevice=xSemaphoreCreateMutex();
	g_device = getDeviceSettings();  // allocate one for all
}




bool eeSetData(int address, void* buffer, int size) { // address, size in BYTES !!!!
uint8_t* inbuf = buffer;
uint32_t* eebuf= malloc(4096);
uint16_t i = 0;
if (eebuf != NULL)
{
	while(1) {

		uint32_t sector = address & 0xFFF000;
		uint8_t* eebuf8 = (uint8_t*)eebuf;
		uint16_t startaddr = address & 0xFFF;
		uint16_t maxsize = 4096 - startaddr;
//printf("set1 startaddr: %x, size:%x, maxsize: %x, sector: %x, eebuf: %x\n",startaddr,size,maxsize,(int)sector,(int)eebuf);
		//spi_flash_read(sector, (uint32_t *)eebuf, 4096);
		ESP_ERROR_CHECK(esp_partition_read(STATIONS, sector,eebuf, 4096));
		vTaskDelay(1);
		ESP_ERROR_CHECK(esp_partition_erase_range(STATIONS,sector,4096));
		//spi_flash_erase_sector(sector >> 12);

//printf("set2 startaddr: %x, size:%x, maxsize: %x, sector: %x, eebuf: %x\n",startaddr,size,maxsize,(int)sector,(int)eebuf);
		for(i=0; (i<size && i<maxsize); i++) eebuf8[i+startaddr] = inbuf[i];
		ESP_ERROR_CHECK(esp_partition_write(STATIONS,sector,eebuf,4096));
		//spi_flash_write(sector, (uint32_t *)eebuf, 4096);
//printf("set3 startaddr: %x, size:%x, maxsize: %x, result:%x, sector: %x, eebuf: %x\n",startaddr,size,maxsize,result,sector,eebuf);
		if(maxsize >= size) break;
		address += i;
		inbuf += i;
		size -= i;
//printf("set2 startaddr: %x, size:%x, maxsize: %x, sector: %x, eebuf: %x\n",startaddr,size,maxsize,sector,eebuf);
	}
	free (eebuf);
} else
{
	ESP_LOGE(TAG,"Warning %s malloc low memory","eebuf");
	return false;
}
return true;
}


void eeEraseAll() { // clear (0) stations and device
uint8_t* buffer= malloc(4096);
int i = 0;
//	printf("erase All\n");
	while (buffer == NULL)
	{
		if (++i > 4) break;
		vTaskDelay(100);
		buffer= malloc(4096); // last chance
	}
	if (buffer != NULL)
	{
		for(i=0; i<4096; i++) buffer[i] = 0;
		ESP_ERROR_CHECK(esp_partition_write(DEVICE,0,buffer,4096));	 //clear device
		ESP_ERROR_CHECK(esp_partition_write(DEVICE1,0,buffer,4096));	 //clear device1
		for (i=0;i<16;i++)
		{
//			printf("erase from %x \n",4096*i);
			ESP_ERROR_CHECK(esp_partition_write(STATIONS,4096*i,buffer,4096));	//clear stations
//			eeSetClear(4096*i,buffer);
			vTaskDelay(1); // avoid watchdog
		}
		kprintf("#erase All done##\n");
		free(buffer);
	} else
		ESP_LOGE(TAG,"erase All fails");

}

void eeErasesettings(void){
	uint8_t* buffer= malloc(4096);
	for(int i=0; i<4096; i++) buffer[i] = 0;
	ESP_ERROR_CHECK(esp_partition_write(DEVICE,0,buffer,4096));	 //clear device
	free(buffer);
}

void eeEraseStations() {
	uint8_t* buffer = malloc(4096);
	int i=0;
	while (buffer == NULL)
	{
		if (++i > 10) break;
		vTaskDelay(10);
		buffer= malloc(4096); // last chance
	}
	if (buffer != NULL)
	{
		for(i=0; i<4096; i++) buffer[i] = 0;
		for (i=0;i<16;i++)
		{
//			printf("erase from %x \n",4096*i);
			ESP_ERROR_CHECK(esp_partition_write(STATIONS,4096*i,buffer,4096));	//clear stations
//			eeSetClear(4096*i,buffer);
			vTaskDelay(1); // avoid watchdog
		}
		free(buffer);
	} else ESP_LOGE(TAG,"Warning %s malloc low memory","eeEraseStations");
}

void saveStation(struct shoutcast_info *station, uint16_t position) {
	uint32_t i = 0;
	if (position > NBSTATIONS-1) {ESP_LOGE(TAG,"saveStation fails pos=%d",position);return;}
	while (!eeSetData((position)*256, station, 256))
	{
		ESP_LOGW(TAG,"Retrying %d on saveStation",i);
		vTaskDelay ((i+1)*20+100) ;
		i++;
		if (i == 10) return;
	}
}
void saveMultiStation(struct shoutcast_info *station, uint16_t position, uint8_t number) {
	uint32_t i = 0;
	while ((position +number-1) > NBSTATIONS-1) {ESP_LOGE(TAG,"saveStation fails pos=%d",position+number-1); number--; }
	if (number <= 0) return;
	while (!eeSetData((position)*256, station, number*256))
	{
		ESP_LOGW(TAG,"Retrying %d on SaveMultiStation for %d stations",i,number);
		vTaskDelay ((i++)*20+100) ;
//		if (i == 3) {clientDisconnect("saveMultiStation low Memory"); vTaskDelay (300) ;}
		if (i == 10) return;
	}
}


struct shoutcast_info* getStation(uint8_t position) {
	if (position > NBSTATIONS-1) {kprintf("getStation fails pos=%d\n",position); return NULL;}
	uint8_t* buffer = malloc(256);
	uint8_t i = 0;

	while (buffer == NULL)
	{
//		ESP_LOGE(TAG,"getStation fails pos=%d",256);
		if (++i > 2) break;
		vTaskDelay(400);
		buffer= malloc(256); // last chance
	}
	ESP_ERROR_CHECK(esp_partition_read(STATIONS, (position)*256, buffer, 256));
	//eeGetData((position+1)*256, buffer, 256);

	return (struct shoutcast_info*)buffer;
}

void copyDeviceSettings()
{
	uint8_t* buffer= malloc(4096);
	if(buffer) {
		ESP_ERROR_CHECK(esp_partition_read(DEVICE, 0, buffer, sizeof(struct device_settings)));
		ESP_ERROR_CHECK(esp_partition_erase_range(DEVICE1,0,DEVICE1->size));
		ESP_ERROR_CHECK(esp_partition_write(DEVICE1,0,buffer,DEVICE1->size));
	}
	free (buffer);
}

void restoreDeviceSettings()
{
	uint8_t* buffer= malloc(4096);
	if(buffer) {
		ESP_ERROR_CHECK(esp_partition_read(DEVICE1, 0, buffer, sizeof(struct device_settings)));
		ESP_ERROR_CHECK(esp_partition_erase_range(DEVICE,0,DEVICE->size));
		ESP_ERROR_CHECK(esp_partition_write(DEVICE,0,buffer,DEVICE->size));
	}
	free (buffer);
}


void saveDeviceSettings(struct device_settings *settings) {
	if (settings == NULL) { ESP_LOGE(TAG,"saveDeviceSetting fails");return;}
	ESP_LOGD(TAG,"saveDeviceSettings");
	xSemaphoreTake(muxDevice, portMAX_DELAY);
	ESP_ERROR_CHECK(esp_partition_erase_range(DEVICE,0,DEVICE->size));
	vTaskDelay(1);
	ESP_ERROR_CHECK(esp_partition_write(DEVICE,0,settings,DEVICE->size));
	xSemaphoreGive(muxDevice);

}
void saveDeviceSettingsVolume(struct device_settings *settings) {
	if (settings == NULL) { ESP_LOGE(TAG,"saveDeviceSetting fails");return;}
	ESP_LOGD(TAG,"saveDeviceSettingsVolume");
	if (xSemaphoreTake(muxDevice, 0) == pdFALSE) return; // not important. An other one in progress
	ESP_ERROR_CHECK(esp_partition_erase_range(DEVICE,0,DEVICE->size));
	vTaskDelay(1);
	ESP_ERROR_CHECK(esp_partition_write(DEVICE,0,settings,DEVICE->size));
	xSemaphoreGive(muxDevice);

}

struct device_settings* getDeviceSettingsSilent() {
	uint16_t size = sizeof(struct device_settings);
	uint8_t* buffer = malloc(size);
	if(buffer) {
		ESP_ERROR_CHECK(esp_partition_read(DEVICE, 0, buffer, size));
		return (struct device_settings*)buffer;
	}
	return NULL;
}

struct device_settings* getDeviceSettings() {
	struct device_settings* buffer ;
	if ((buffer = getDeviceSettingsSilent())==NULL)
		ESP_LOGE(TAG,"getDeviceSetting fails");
//		printf(streGETDEVICE,0);
	return buffer;

}
