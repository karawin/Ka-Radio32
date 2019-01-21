/******************************************************************************
 * 
 * Copyright 2017 karawin (http://www.karawin.fr)
 *
*******************************************************************************/

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#define TAG "GPIO"
#include "driver/gpio.h"
#include "gpio.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "app_main.h"
#include "eeprom.h"

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
esp_err_t open_partition(const char *partition_label, const char *namespace,nvs_open_mode open_mode,nvs_handle *handle)
{
	esp_err_t err;	
	err = nvs_flash_init_partition(partition_label);
	if (err != ESP_OK) {ESP_LOGW(TAG,"Hardware partition not found"); return err;}
	err = nvs_open_from_partition(partition_label, namespace,
		open_mode, handle);
	if (err != ESP_OK) 
	{
		ESP_LOGD(TAG,"Hardware namespace %s not found",namespace);
		nvs_flash_deinit_partition(partition_label);	
	}	
	return err;
}
void close_partition(nvs_handle handle,const char *partition_label)
{
	nvs_commit(handle); // if a write is pending
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
	
	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	err = ESP_OK;
	if (spi_no != NULL)err = nvs_get_u8(hardware_handle, "K_SPI",(uint8_t *) spi_no);
	if (miso != NULL) err |= nvs_get_u8(hardware_handle, "P_MISO",(uint8_t *) miso);
	if (mosi != NULL)err |=nvs_get_u8(hardware_handle, "P_MOSI",(uint8_t *) mosi);
	if (sclk != NULL)err |=nvs_get_u8(hardware_handle, "P_CLK", (uint8_t *)sclk);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_spi_bus error 0x%x",err);
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
	
	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_XCS",(uint8_t *) xcs);
	err |=nvs_get_u8(hardware_handle, "P_RST",(uint8_t *) rst);
	err |=nvs_get_u8(hardware_handle, "P_XDCS", (uint8_t *)xdcs);
	err |=nvs_get_u8(hardware_handle, "P_DREQ", (uint8_t *)dreq);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_vs1053 error 0x%x",err);
	close_partition(hardware_handle,hardware);	
}


void option_get_lcd_info(uint8_t *enca,uint8_t* rt)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	uint8_t typ,rot;
	// init default
	struct device_settings* device = getDeviceSettings();
	*enca = device->lcd_type;
	*rt = ((device->options32)&T_ROTAT)?1:0;
	free(device);
	if (open_partition(hardware, "option_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "O_LCD_TYPE",(uint8_t *) &typ);
	err |= nvs_get_u8(hardware_handle, "O_LCD_ROTA",(uint8_t *) &rot);
	if (typ != 255) *enca = typ;
	if (rot != 255) *rt = rot;
	if (*rt) *rt = 1;
	if (err != ESP_OK) ESP_LOGD(TAG,"option_get_lcd_info error 0x%x",err);
	close_partition(hardware_handle,hardware);		
}
void option_set_lcd_info(uint8_t enca, uint8_t rt)
{
	esp_err_t err;
	nvs_handle hardware_handle;

	if (open_partition(hardware, "option_space",NVS_READWRITE,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_set_u8(hardware_handle, "O_LCD_TYPE",enca);
	err |= nvs_set_u8(hardware_handle, "O_LCD_ROTA",rt?1:0);
	if (err != ESP_OK) ESP_LOGD(TAG,"option_set_lcd_info error 0x%x",err);

	close_partition(hardware_handle,hardware);		
}

void option_get_ddmm(uint8_t *enca)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	uint8_t dmm;
	// init default
	struct device_settings* device = getDeviceSettings();
	*enca = ((device->options32)&T_DDMM)?1:0;;	
	free(device);
	
	if (open_partition(hardware, "option_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "O_DDMM_FLAG",(uint8_t *) &dmm);
	if (dmm != 255) *enca = dmm;
	if (*enca) *enca = 1;
	if (err != ESP_OK) ESP_LOGD(TAG,"option_get_ddmm error 0x%x",err);
	
	close_partition(hardware_handle,hardware);		
}
void option_set_ddmm(uint8_t enca)
{
	esp_err_t err;
	nvs_handle hardware_handle;

	if (open_partition(hardware, "option_space",NVS_READWRITE,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_set_u8(hardware_handle, "O_DDMM_FLAG",enca?1:0);
	if (err != ESP_OK) ESP_LOGD(TAG,"option_set_ddmm error 0x%x",err);

	close_partition(hardware_handle,hardware);		
}

void option_get_lcd_out(uint32_t *enca)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	uint32_t lout;
	// init default
	struct device_settings* device = getDeviceSettings();
	if (device->lcd_out==0)
		*enca = 255;
	else
		*enca = device->lcd_out;	
	free(device);
	
	if (open_partition(hardware, "option_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u32(hardware_handle, "O_LCD_OUT",(uint32_t *) &lout);
	if (lout != 255) *enca = lout;
	if (err != ESP_OK) ESP_LOGD(TAG,"option_get_lcd_out error 0x%x",err);
	
	close_partition(hardware_handle,hardware);		
}
void option_set_lcd_out(uint32_t enca)
{
	esp_err_t err;
	nvs_handle hardware_handle;

	if (open_partition(hardware, "option_space",NVS_READWRITE,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_set_u8(hardware_handle, "O_LCD_OUT",enca);
	if (err != ESP_OK) ESP_LOGD(TAG,"option_set_lcd_out error 0x%x",err);

	close_partition(hardware_handle,hardware);		
}



void gpio_get_ledgpio(gpio_num_t *enca)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	struct device_settings* device = getDeviceSettings();
	*enca = device->led_gpio;
	free (device);

	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_LED_GPIO",(uint8_t *) enca);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_ledgpio error 0x%x",err);

	close_partition(hardware_handle,hardware);		
}

void gpio_set_ledgpio(gpio_num_t enca)
{
	esp_err_t err;
	nvs_handle hardware_handle;

	if (open_partition(hardware, "gpio_space",NVS_READWRITE,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_set_u8(hardware_handle, "P_LED_GPIO",enca);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_set_ledgpio error 0x%x",err);

	close_partition(hardware_handle,hardware);		
}
void gpio_get_joystick0(gpio_num_t *enca)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*enca = PIN_JOY_0;
	
	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_JOY_0",(uint8_t *) enca);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_joystick0 error 0x%x",err);

	close_partition(hardware_handle,hardware);		
}

void gpio_get_joystick1(gpio_num_t *enca)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*enca = PIN_JOY_1;
	
	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_JOY_1",(uint8_t *) enca);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_joystick1 error 0x%x",err);

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
	
	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_BTN0_A",(uint8_t *) enca);
	err |=nvs_get_u8(hardware_handle, "P_BTN0_B",(uint8_t *) encb);
	err |=nvs_get_u8(hardware_handle, "P_BTN0_C", (uint8_t *)encc);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_button0 error 0x%x",err);

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
	
	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_BTN1_A",(uint8_t *) enca);
	err |=nvs_get_u8(hardware_handle, "P_BTN1_B",(uint8_t *) encb);
	err |=nvs_get_u8(hardware_handle, "P_BTN1_C", (uint8_t *)encc);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_button1 error 0x%x",err);

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
	
	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_ENC0_A",(uint8_t *) enca);
	err |=nvs_get_u8(hardware_handle, "P_ENC0_B",(uint8_t *) encb);
	err |=nvs_get_u8(hardware_handle, "P_ENC0_BTN", (uint8_t *)encbtn);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_encoder0 error 0x%x",err);

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
	
	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_ENC1_A",(uint8_t *) enca);
	err |=nvs_get_u8(hardware_handle, "P_ENC1_B",(uint8_t *) encb);
	err |=nvs_get_u8(hardware_handle, "P_ENC1_BTN", (uint8_t *)encbtn);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_encoder1 error 0x%x",err);

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

	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_I2C_SCL",(uint8_t *) scl);
	err |=nvs_get_u8(hardware_handle, "P_I2C_SDA",(uint8_t *) sda);
	err |=nvs_get_u8(hardware_handle, "P_I2C_RST", (uint8_t *)rsti2c);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_i2c error 0x%x",err);

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
	
	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_LCD_CS",(uint8_t *) cs);
	err |=nvs_get_u8(hardware_handle, "P_LCD_A0",(uint8_t *) a0);
	err |=nvs_get_u8(hardware_handle, "P_LCD_RST", (uint8_t *)rstlcd);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_spi_lcd error 0x%x",err);

	close_partition(hardware_handle,hardware);			
}

void gpio_get_ir_signal(gpio_num_t *ir)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*ir = PIN_IR_SIGNAL;
	
	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_IR_SIGNAL",(uint8_t *) ir);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_ir_signal error 0x%x",err);

	close_partition(hardware_handle,hardware);		
}

void gpio_get_adc(adc1_channel_t  *channel)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*channel = PIN_ADC;
	
	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_ADC_KBD",(uint8_t *) channel);
	if (err != ESP_OK)ESP_LOGW(TAG,"gpio_get_adc error 0x%x",err);

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
	
	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_I2S_LRCK",(uint8_t *) lrck);
	err |=nvs_get_u8(hardware_handle, "P_I2S_BCLK",(uint8_t *) bclk);
	err |=nvs_get_u8(hardware_handle, "P_I2S_DATA", (uint8_t *)i2sdata);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_i2s error 0x%x",err);

	close_partition(hardware_handle,hardware);	
}

void gpio_get_lcd_backlightl(gpio_num_t *lcdb)
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*lcdb = PIN_LCD_BACKLIGHT;
	
	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_BACKLIGHT",(uint8_t *) lcdb);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_lcd_backlightl error 0x%x",err);

	close_partition(hardware_handle,hardware);		
}

void gpio_get_touch(gpio_num_t *cs )
{
	esp_err_t err;
	nvs_handle hardware_handle;
	// init default
	*cs = PIN_TOUCH_CS;
	
	if (open_partition(hardware, "gpio_space",NVS_READONLY,&hardware_handle)!= ESP_OK) return;
	
	err = nvs_get_u8(hardware_handle, "P_TOUCH_CS",(uint8_t *) cs);
	if (err != ESP_OK) ESP_LOGD(TAG,"gpio_get_touch error 0x%x",err);

	close_partition(hardware_handle,hardware);			
}

uint8_t gpioToChannel(uint8_t gpio)
{
	if (gpio == GPIO_NONE) return GPIO_NONE;
	if (gpio >= 38) return (gpio-36);
	else return (gpio-28);	
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