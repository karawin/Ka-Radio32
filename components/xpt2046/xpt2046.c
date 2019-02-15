/*
 * xpt2046.h
 *
 *  Created on: jan 12, 2019
 *      Author: karawin
 *  adapted from https://github.com/loboris/ESP32_SPI_MASTER_NODMA_EXAMPLE
 */

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_intr_alloc.h"
#include <string.h>
#include "xpt2046.h"
#include "esp_log.h"
#ifdef KaRadio32
#include "gpio.h"
#include "vs1053.h"
#include "eeprom.h"
#include "interface.h"
#endif


#define TAG  "XPT2046"

static	spi_device_handle_t t_handle = NULL; // SPI handle of the spi touch interface.
static spi_host_device_t spiNo;
static gpio_num_t  csPin;
static bool haveTouchOn = false;
static bool inCalibrate = false;

static uint32_t tp_calx = 0x1100BC5; //‭17828805‬
static uint32_t tp_caly = 0x2490ed2;
static int width = 320;
static int height = 240;
xTaskHandle handleTaskLcd;
// ============= Touch panel functions =========================================
void saveCalibration(uint32_t x, uint32_t y)
{
	g_device->tp_calx = x ;
	g_device->tp_caly = y ;
	saveDeviceSettings(g_device);
	ESP_LOGI(TAG, "Calibration saved: X:%x, Y:%x",x,y);
}
void getCalibration()
{
	if (g_device->tp_calx != 0) tp_calx = g_device->tp_calx;
	if (g_device->tp_caly != 0) tp_caly = g_device->tp_caly;
	ESP_LOGI(TAG, "Calibration read: X:%x, Y:%x",tp_calx,tp_caly);
}
void setTouchSize(int w, int h) {width = w; height = h; }
void getTouchSize(int* w, int* h) {*w=width; *h=height; }

bool haveTouch() {return haveTouchOn;}

void  getTaskLcd(xTaskHandle* hdt){handleTaskLcd = *hdt;}

void xpt_init()
{	
  gpio_get_touch(&csPin);
  gpio_get_spi_bus((uint8_t*)&spiNo,NULL,NULL,NULL);
  if ((csPin != GPIO_NONE) )
  {	
	haveTouchOn = true;
	gpio_config_t gpioConfig;
	gpioConfig.mode         = GPIO_MODE_OUTPUT;
	gpioConfig.pull_up_en   = GPIO_PULLUP_ENABLE;
	gpioConfig.intr_type    = GPIO_INTR_DISABLE;
	gpioConfig.pin_bit_mask = ((uint64_t)(((uint64_t)1)<<csPin));
	ESP_ERROR_CHECK(gpio_config(&gpioConfig));		
	gpio_set_level(csPin, 1);
	ESP_LOGI(TAG, "Touch cs: %d init done",csPin);
	
	if (t_handle==NULL)
	{
		spi_device_interface_config_t dev_config={			
		.clock_speed_hz   = 2000000,
		.command_bits	  = 0,
		.spics_io_num     =  -1,
		.cs_ena_posttrans = 1,
		.mode = 0,   
		.flags            = SPI_DEVICE_NO_DUMMY,
		.queue_size       = 1,
		};
		ESP_ERROR_CHECK(spi_bus_add_device(spiNo, &dev_config, &t_handle)); 
		ESP_LOGI(TAG, "... Added touch spi bus  cs: %d,  Speed= %d.",csPin,dev_config.clock_speed_hz);		
	}
	//init tp_calx & tp_caly
	getCalibration();	
  }
}


uint16_t IRAM_ATTR xpt_get_data(uint8_t addressbyte){
	uint16_t result;
    uint8_t datas[3] = {0};
    datas[0] = addressbyte;
	esp_err_t ret;
   spi_transaction_t t = {
        .length = 8 * 3,              // Len is in bytes, transaction length is in bits.
		.cmd = addressbyte,
        .tx_buffer = &datas,              // Data
        .flags = SPI_TRANS_USE_RXDATA,
    };
	ret = spi_device_transmit(t_handle, &t);  //Transmit!
	if (ret != ESP_OK) ESP_LOGE(TAG,"err: %d, xpt_get_data(%d), read: %d",ret,addressbyte,(uint16_t)*t.rx_data);
	result = (t.rx_data[1] << 8 | t.rx_data[2]) >> 3;
	return result;
}


//-----------------------------------------------
static int IRAM_ATTR tp_get_data(uint8_t type, int samples)
{
	int n, result, val = 0;
	uint32_t i = 0;
	uint32_t vbuf[18];
	uint32_t minval, maxval, dif;

	vTaskSuspend(handleTaskLcd);
	taskYIELD();
    if (samples < 3) samples = 1;
    if (samples > 18) samples = 18;
	gpio_set_level(csPin, 0);
    // one dummy read
    result = xpt_get_data(type);
//	gpio_set_level(csPin, 1);
    // read data
	while (i < 10) {
    	minval = 5000;
    	maxval = 0;
		// get values
//		gpio_set_level(csPin, 0);
		for (n=0;n<samples;n++) {
		    result = xpt_get_data(type);
			if ((result < 0)||(result >4096)) {vbuf[n] = 5000; continue;}//break;
			vbuf[n] = result;
			if (result < minval) minval = result;
			if (result > maxval) maxval = result;
		}
		if (result < 0) break;
		dif = maxval - minval;
		if (dif < 50) break;
		i++;
    }
	gpio_set_level(csPin, 1);
	vTaskResume(handleTaskLcd);
	if ((result < 0)||(result >4096)) return -1;

	if (samples > 2) {
		// remove one min value
		for (n = 0; n < samples; n++) {
			if (vbuf[n] == minval) {
				vbuf[n] = 5000;
				break;
			}
		}
		// remove one max value
		for (n = 0; n < samples; n++) {
			if (vbuf[n] == maxval) {
				vbuf[n] = 5000;
				break;
			}
		}
		for (n = 0; n < samples; n++) {
			if (vbuf[n] < 5000) val += vbuf[n];
		}
		val /= (samples-2);
	}
	else val = vbuf[0];

    return val;
}

//=============================================
bool IRAM_ATTR xpt_read_touch(int *x, int* y, uint8_t raw)
{
	if (inCalibrate) return false;
	int result = -1;
    int32_t X=0, Y=0, tmp;

    *x = 0;
    *y = 0;
    result = tp_get_data(0xB0, 4);
	if (result > 50)  {
		// tp pressed
		result = tp_get_data(0xD0, 15);
		if (result >= 0) {
			X = result;

			result = tp_get_data(0x90, 15);
			if (result >= 0) Y = result;
		}
	}
	if (result <= 50) return false;

	if (raw) {
		*x = X;
		*y = Y;
		return true;
	}

	int xleft   = (tp_calx >> 16) & 0x3FFF;
	int xright  = tp_calx & 0x3FFF;
	int ytop    = (tp_caly >> 16) & 0x3FFF;
	int ybottom = tp_caly & 0x3FFF;
	
	ESP_LOGV(TAG, "xleft:%d,xright:%d,ytop:%d,ybottom:%d,tp_calx:%d,tp_caly:%d,X:%d,Y:%d",xleft,xright,ytop,ybottom,tp_calx,tp_caly,X,Y);
//	ESP_LOGW(TAG, "X:%d,Y:%d",X,Y);
	
	if (((xright - xleft) != 0) && ((ybottom - ytop) != 0)) {
		X = ((X - xleft) * height) / (xright - xleft);
		Y = ((Y - ytop) * width) / (ybottom - ytop);
	}
	else return false;
//ESP_LOGI(TAG, "X:%d,Y:%d",X,Y);
	if (X < 0) X = 0;
	if (X > height-1) X = height-1;
	if (Y < 0) Y = 0;
	if (Y > width-1) Y = width-1;
	switch (getRotat()) {
		case 0:	//90%
			tmp = X;
			X = width-Y-1;
			Y = tmp;
			break;
		case 1:	// 270%
			tmp = X;
			X = Y;
			Y = height-tmp - 1;
			break;
		default:;
	}
	ESP_LOGD(TAG, "Rotate: %d, X:%d,Y:%d",getRotat(),X,Y);
	*x = X;
	*y = Y;
	return true;
}

bool xpt_touched()
{
	int result = -1;
	result = tp_get_data(0xB0, 4);
	if (result > 50) return true; else return false;
}

bool xpt_read_calibrate(int* x, int* y)
{
	int result = -1;
	result = tp_get_data(0xB0, 4);
	if (result > 50)  {
		// tp pressed
		result = tp_get_data(0xD0, 10);
		if (result >= 0) {
			*x = result;

			result = tp_get_data(0x90, 10);
			if (result >= 0) *y = result;
		}
	}
	if (result <= 50) return false;
	ESP_LOGI(TAG, "X:%d,Y:%d",*x,*y);

	vTaskDelay(10);	
	return true;
}

void userMsg(int val)
{
	if (getRotat()==val)
		kprintf("Touch the top right corner\n");
	else
		kprintf("Touch the bottom left corner\n");
}

void xpt_calibrate()
{
	int xl,yt,xr,yb;
	if (!haveTouchOn)
	{
		kprintf("No Touch screen detected\n");
		return;
	}
	inCalibrate = true;
	kprintf("INSTRUCTIONS:\n");
	userMsg(0);		
	while (!(xpt_read_calibrate(&xl, &yt)))vTaskDelay(1);
	kprintf("Ok\n");
	vTaskDelay(10);
	while (xpt_touched());
	userMsg(1);			
	while (!(xpt_read_calibrate(&xr, &yb)))vTaskDelay(1);
	kprintf("Ok\n");
	while (xpt_touched());
	
	ESP_LOGD(TAG, "xl:%x, yt:%x, xr:%x, yb:%x",xl,yt,xr,yb);
	kprintf("Done\n");

	tp_calx = xl<<16 | xr;
	tp_caly = yt<<16 | yb;

	saveCalibration(tp_calx, tp_caly);	
	inCalibrate = false;
}
