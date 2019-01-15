#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_intr_alloc.h"
#include <string.h>
#include "esp_log.h"
#ifdef KaRadio32
#include "gpio.h"
#include "vs1053.h"
#endif

#include "xpt2046.h"
#include "interface.h"

#define TAG  "XPT2046"

static	spi_device_handle_t t_handle = NULL; // SPI handle of the spi touch interface.
static spi_host_device_t spiNo;
static gpio_num_t  csPin;

static uint32_t tp_calx = 7472920;
static uint32_t tp_caly = 122224794;

// ============= Touch panel functions =========================================

void xpt_init(spi_host_device_t spi_num, gpio_num_t  cs_pin, gpio_num_t  tirq)
{
	
	spiNo = spi_num;
	csPin = cs_pin;
	// t_irq is an input
/*	gpio_config_t gpioConfig;
	gpioConfig.mode         = GPIO_MODE_INPUT;
//	gpioConfig.pull_up_en   = GPIO_PULLUP_DISABLE;
//	gpioConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
	gpioConfig.intr_type    = GPIO_INTR_NEGEDGE;
	gpioConfig.pin_bit_mask = (1<<tirq);
	gpio_reset_pin(tirq);
	if (255 != tirq) ESP_ERROR_CHECK(gpio_config(&gpioConfig));	
*/	
	gpio_config_t gpioConfig;
	gpioConfig.mode         = GPIO_MODE_OUTPUT;
	gpioConfig.pull_up_en   = GPIO_PULLUP_ENABLE;
//	gpioConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
	gpioConfig.intr_type    = GPIO_INTR_DISABLE;
	gpioConfig.pin_bit_mask = (1<<csPin);
	ESP_ERROR_CHECK(gpio_config(&gpioConfig));		
	gpio_set_level(csPin, 1);
	ESP_LOGI(TAG, "Touch irq %d, cs: %d init done",tirq,csPin);
	
	if (t_handle==NULL)
	{
		spi_device_interface_config_t dev_config={			
		.clock_speed_hz   = 2000000,
		.spics_io_num     =  -1, //csPin,
		.cs_ena_posttrans = 1,
		.mode = 0,   
		.flags            = SPI_DEVICE_NO_DUMMY,
		.queue_size       = 1,
		};
		ESP_ERROR_CHECK(spi_bus_add_device(spi_num, &dev_config, &t_handle)); 
		ESP_LOGI(TAG, "... Added touch spi bus  cs: %d,  Speed= %d.",csPin,dev_config.clock_speed_hz);		
	}
	
/*	if (255 != tirq) {
		ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_IRAM));
		ESP_LOGD(TAG, "gpio_install_isr_service done");
		ESP_ERROR_CHECK(gpio_isr_handler_add(tirq, isrPin, NULL));
		ESP_LOGD(TAG, "gpio_isr_handler_add done");
	}*/	
}


uint16_t xpt_get_data(uint8_t addressbyte){
	uint16_t result;
    uint8_t datas[3] = {0};
    datas[0] = addressbyte;
	esp_err_t ret;
   spi_transaction_t t = {
        .length = 1 * 8 * 3,              // Len is in bytes, transaction length is in bits.
        .tx_buffer = &datas,              // Data
        .flags = SPI_TRANS_USE_RXDATA,
    };
	ret = spi_device_transmit(t_handle, &t);  //Transmit!
	if (ret != ESP_OK) ESP_LOGE(TAG,"err: %d, xpt_get_data(%d), read: %d",ret,addressbyte,(uint16_t)*t.rx_data);
//	result =  (((t.rx_data[1]&0xFF)<<8) | ((t.rx_data[2]>>3)&0xFF)) ;
	result = (t.rx_data[1] << 8 | t.rx_data[2]) >> 3;
//	ESP_LOGI(TAG,"xpt_get_data addr: %d, result: %d, d0:%d, d1:%d, d2: %d, d3: %d",addressbyte,result,
//	t.rx_data[0],t.rx_data[1],t.rx_data[2],t.rx_data[3]);
	return result;
}






//-----------------------------------------------
static int tp_get_data(uint8_t type, int samples)
{
	int n, result, val = 0;
	uint32_t i = 0;
	uint32_t vbuf[18];
	uint32_t minval, maxval, dif;

    if (samples < 3) samples = 1;
    if (samples > 18) samples = 18;
	gpio_set_level(csPin, 0);
    // one dummy read
    result = xpt_get_data(type);

    // read data
	while (i < 10) {
    	minval = 5000;
    	maxval = 0;
		// get values
		for (n=0;n<samples;n++) {
		    result = xpt_get_data(type);
			if (result < 0) break;

			vbuf[n] = result;
			if (result < minval) minval = result;
			if (result > maxval) maxval = result;
		}
		if (result < 0) break;
		dif = maxval - minval;
		if (dif < 40) break;
		i++;
    }
	gpio_set_level(csPin, 1);
	if (result < 0) return -1;

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
bool xpt_read_touch(int *x, int* y, uint8_t raw)
{
	int result = -1;
    int32_t X=0, Y=0, tmp;

    *x = 0;
    *y = 0;

    result = tp_get_data(0xB0, 3);
	if (result > 50)  {
		// tp pressed
		result = tp_get_data(0xD0, 10);
		if (result >= 0) {
			X = result;

			result = tp_get_data(0x90, 10);
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

	int width = 320;
	int height = 240;
	

	if (((xright - xleft) != 0) && ((ybottom - ytop) != 0)) {
		X = ((X - xleft) * height) / (xright - xleft);
		Y = ((Y - ytop) * width) / (ybottom - ytop);
	}
	else return false;

	if (X < 0) X = 0;
	if (X > height-1) X = height-1;
	if (Y < 0) Y = 0;
	if (Y > width-1) Y = width-1;

	switch (getRotat()) {
		case 2:
			tmp = X;
			X = Y;
			Y = tmp;
			break;
		case 3:
			tmp = X;
			X = Y;
			Y = height - tmp - 1;
			break;
		case 4:
			X = height - X - 1;
			Y = width - Y - 1;
			break;
	}

	*x = X;
	*y = Y;
	return true;
}
