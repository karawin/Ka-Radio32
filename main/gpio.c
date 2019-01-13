/******************************************************************************
 * 
 * Copyright 2017 karawin (http://www.karawin.fr)
 *
*******************************************************************************/

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#define TAG "gpio"
#include "driver/gpio.h"
#include "gpio.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "app_main.h"

#define hardware "hardware"

// init a gpio as output
void gpio_output_conf(gpio_num_t gpio)
{
	gpio_config_t gpio_conf;
	gpio_conf.pin_bit_mask = ((uint64_t)(((uint64_t)1)<<gpio)) ;
	gpio_conf.mode = GPIO_MODE_OUTPUT;
	gpio_conf.pull_up_en =  GPIO_PULLUP_DISABLE;
	gpio_conf.pull_down_en =  GPIO_PULLDOWN_DISABLE;
	gpio_conf.intr_type = GPIO_INTR_DISABLE;
	gpio_config(&gpio_conf);
	gpio_set_level(gpio,1);
}

// open and read the gpio hardware setting
//
esp_err_t open_partition(const char *partition_label, const char *namespace,nvs_handle *handle)
{
	esp_err_t err;	
	err = nvs_flash_init_partition(partition_label);
	if (err != ESP_OK) {ESP_LOGW(TAG,"Hardware partition not found"); return err;}
	err = nvs_open_from_partition(partition_label, namespace,
		NVS_READONLY, handle);
	if (err != ESP_OK) 
	{
		ESP_LOGI(TAG,"Hardware namespace not found");
		nvs_flash_deinit_partition(partition_label);	
	}	
	return err;
}
void close_partition(nvs_handle handle,const char *partition_label)
{
	nvs_close(handle);
	nvs_flash_deinit_partition(partition_label);	
}

void gpio_get_spi_bus(uint8_t *spi_no,gpio_num_t *miso,gpio_num_t *mosi,gpio_num_t *sclk)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	if (miso != NULL)*miso = PIN_NUM_MISO;	
	if (mosi != NULL)*mosi = PIN_NUM_MOSI;	
	if (sclk != NULL)*sclk = PIN_NUM_CLK;
	if (spi_no != NULL)*spi_no = VSPI_HOST;
	
	if (open_partition(hardware, "gpio_space",&hardware_handle)!= ESP_OK) return;
	err = ESP_OK;
	if (spi_no != NULL)err = nvs_get_u8(hardware_handle, "K_SPI",(uint8_t *) spi_no);
	if (miso != NULL) err |= nvs_get_u8(hardware_handle, "P_MISO",(uint8_t *) miso);
	if (mosi != NULL)err |=nvs_get_u8(hardware_handle, "P_MOSI",(uint8_t *) mosi);
	if (sclk != NULL)err |=nvs_get_u8(hardware_handle, "P_CLK", (uint8_t *)sclk);
	if (err != ESP_OK) ESP_LOGW(TAG,"gpio_get_spi_bus error %d",err);
	close_partition(hardware_handle,hardware);
}


void gpio_get_vs1053(gpio_num_t * xcs,gpio_num_t *rst,gpio_num_t *xdcs,gpio_num_t *dreq)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*xcs = PIN_NUM_XCS;
	*rst = PIN_NUM_RST;
	*xdcs = PIN_NUM_XDCS;
	*dreq = PIN_NUM_DREQ;
	
	if (open_partition(hardware, "gpio_space",&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_XCS",(uint8_t *) xcs);
	err |=nvs_get_u8(hardware_handle, "P_RST",(uint8_t *) rst);
	err |=nvs_get_u8(hardware_handle, "P_XDCS", (uint8_t *)xdcs);
	err |=nvs_get_u8(hardware_handle, "P_DREQ", (uint8_t *)dreq);
	if (err != ESP_OK) ESP_LOGW(TAG,"gpio_get_vs1053 error %d",err);
	close_partition(hardware_handle,hardware);	
}

void gpio_get_button0(gpio_num_t *enca, gpio_num_t *encb, gpio_num_t *encc)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*enca = PIN_BTN0_A;
	*encb = PIN_BTN0_B;
	*encc = PIN_BTN0_C;
	
	if (open_partition(hardware, "gpio_space",&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_BTN0_A",(uint8_t *) enca);
	err |=nvs_get_u8(hardware_handle, "P_BTN0_B",(uint8_t *) encb);
	err |=nvs_get_u8(hardware_handle, "P_BTN0_C", (uint8_t *)encc);
	if (err != ESP_OK) ESP_LOGW(TAG,"gpio_get_button0 error %d",err);

	close_partition(hardware_handle,hardware);		
}
void gpio_get_button1(gpio_num_t *enca, gpio_num_t *encb, gpio_num_t *encc)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*enca = PIN_BTN1_A;
	*encb = PIN_BTN1_B;
	*encc = PIN_BTN1_C;
	
	if (open_partition(hardware, "gpio_space",&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_BTN1_A",(uint8_t *) enca);
	err |=nvs_get_u8(hardware_handle, "P_BTN1_B",(uint8_t *) encb);
	err |=nvs_get_u8(hardware_handle, "P_BTN1_C", (uint8_t *)encc);
	if (err != ESP_OK) ESP_LOGW(TAG,"gpio_get_button1 error %d",err);

	close_partition(hardware_handle,hardware);		
}
void gpio_get_encoder0(gpio_num_t *enca, gpio_num_t *encb, gpio_num_t *encbtn)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	if (bigSram()) // default is not compatible (gpio 16 & 17)
	{
		*enca = GPIO_NONE;
		*encb= GPIO_NONE;
		*encbtn= GPIO_NONE;	
	} else
	{
		*enca = PIN_ENC0_A;
		*encb= PIN_ENC0_B;
		*encbtn= PIN_ENC0_BTN;
	}
	
	if (open_partition(hardware, "gpio_space",&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_ENC0_A",(uint8_t *) enca);
	err |=nvs_get_u8(hardware_handle, "P_ENC0_B",(uint8_t *) encb);
	err |=nvs_get_u8(hardware_handle, "P_ENC0_BTN", (uint8_t *)encbtn);
	if (err != ESP_OK) ESP_LOGW(TAG,"gpio_get_encoder0 error %d",err);

	close_partition(hardware_handle,hardware);		
}
void gpio_get_encoder1(gpio_num_t *enca, gpio_num_t *encb, gpio_num_t *encbtn)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	if (bigSram())
	{
		*enca = GPIO_NONE;
		*encb= GPIO_NONE;
		*encbtn= GPIO_NONE;	
	} else
	{
		*enca = PIN_ENC1_A;
		*encb= PIN_ENC1_B;
		*encbtn= PIN_ENC1_BTN;
	}
	
	if (open_partition(hardware, "gpio_space",&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_ENC1_A",(uint8_t *) enca);
	err |=nvs_get_u8(hardware_handle, "P_ENC1_B",(uint8_t *) encb);
	err |=nvs_get_u8(hardware_handle, "P_ENC1_BTN", (uint8_t *)encbtn);
	if (err != ESP_OK) ESP_LOGW(TAG,"gpio_get_encoder1 error %d",err);

	close_partition(hardware_handle,hardware);		
}

void gpio_get_i2c(gpio_num_t *scl,gpio_num_t *sda,gpio_num_t *rsti2c)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*scl = PIN_I2C_SCL;
	*sda = PIN_I2C_SDA;
	*rsti2c = PIN_I2C_RST;

	if (open_partition(hardware, "gpio_space",&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_I2C_SCL",(uint8_t *) scl);
	err |=nvs_get_u8(hardware_handle, "P_I2C_SDA",(uint8_t *) sda);
	err |=nvs_get_u8(hardware_handle, "P_I2C_RST", (uint8_t *)rsti2c);
	if (err != ESP_OK) ESP_LOGW(TAG,"gpio_get_i2c error %d",err);

	close_partition(hardware_handle,hardware);		
}

void gpio_get_spi_lcd(gpio_num_t *cs ,gpio_num_t *a0,gpio_num_t *rstlcd)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*cs = PIN_LCD_CS;
	*a0 = PIN_LCD_A0;
	*rstlcd = PIN_LCD_RST;
	
	if (open_partition(hardware, "gpio_space",&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_LCD_CS",(uint8_t *) cs);
	err |=nvs_get_u8(hardware_handle, "P_LCD_A0",(uint8_t *) a0);
	err |=nvs_get_u8(hardware_handle, "P_LCD_RST", (uint8_t *)rstlcd);
	if (err != ESP_OK) ESP_LOGW(TAG,"gpio_get_spi_lcd error %d",err);

	close_partition(hardware_handle,hardware);			
}

void gpio_get_ir_signal(gpio_num_t *ir)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*ir = PIN_IR_SIGNAL;
	
	if (open_partition(hardware, "gpio_space",&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_IR_SIGNAL",(uint8_t *) ir);
	if (err != ESP_OK) ESP_LOGW(TAG,"gpio_get_ir_signal error %d",err);

	close_partition(hardware_handle,hardware);		
}

void gpio_get_adc(adc1_channel_t  *channel)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*channel = PIN_ADC;
	
	if (open_partition(hardware, "gpio_space",&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_ADC",(uint8_t *) channel);
	if (err != ESP_OK)ESP_LOGW(TAG,"gpio_get_adc error %d",err);

	close_partition(hardware_handle,hardware);		
}

void gpio_get_i2s(gpio_num_t *lrck ,gpio_num_t *bclk ,gpio_num_t *i2sdata )
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*lrck = PIN_I2S_LRCK;
	*bclk = PIN_I2S_BCLK;
	*i2sdata = PIN_I2S_DATA;
	
	if (open_partition(hardware, "gpio_space",&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_I2S_LRCK",(uint8_t *) lrck);
	err |=nvs_get_u8(hardware_handle, "P_I2S_BCLK",(uint8_t *) bclk);
	err |=nvs_get_u8(hardware_handle, "P_I2S_DATA", (uint8_t *)i2sdata);
	if (err != ESP_OK) ESP_LOGW(TAG,"gpio_get_i2s error %d",err);

	close_partition(hardware_handle,hardware);	
}

void gpio_get_lcd_backlightl(gpio_num_t *lcdb)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*lcdb = PIN_LCD_BACKLIGHT;
	
	if (open_partition(hardware, "gpio_space",&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_BACKLIGHT",(uint8_t *) lcdb);
	if (err != ESP_OK) ESP_LOGW(TAG,"gpio_get_lcd_backlightl error %d",err);

	close_partition(hardware_handle,hardware);		
}

void gpio_get_touch(gpio_num_t *cs ,gpio_num_t *irq)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*cs = PIN_TOUCH_CS;
	*irq = PIN_TOUCH_IRQ;
	
	if (open_partition(hardware, "gpio_space",&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_TOUCH_CS",(uint8_t *) cs);
	err |=nvs_get_u8(hardware_handle, "P_TOUCH_IRQ",(uint8_t *) irq);
	if (err != ESP_OK) ESP_LOGW(TAG,"gpio_get_touch error %d",err);

	close_partition(hardware_handle,hardware);			
}

bool gpio_get_ir_key(nvs_handle handle,const char *key, int32_t *out_value1 , int32_t *out_value2)
{
	// init default
	bool ret = false; 
	*out_value1 = 0;
	*out_value2 = 0;
	size_t required_size;
	nvs_get_str(handle, key, NULL, &required_size);
	if (required_size >1)
	{
		char* string = malloc(required_size);
		nvs_get_str(handle, key, string, &required_size);	
		sscanf(string,"%x %x",out_value1,out_value2);
//		ESP_LOGV(TAG,"String \"%s\"\n Required size: %d",string,required_size);
		free (string);
		ret = true;
	}
	ESP_LOGV(TAG,"Key: %s, value1: %x, value2: %x, ret: %d\n",key,*out_value1,*out_value2,ret);	
	
	return ret;
}