/*
 * audio_renderer.c
 *
 *  Created on: 12.03.2017
 *      Author: michaelboeckling
 *
 *  Rev. 17.4.2017/Jorgen Kragh Jakobsen
 *      Added 32 bit entry for i2s output and setup i2c call for Merus Audio power audio amp.
 */

#include <stdbool.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"
#include <freertos/task.h>
#include <driver/dac.h>
#include "driver/gpio.h"
#include "gpio.h"
#include "app_main.h"
#include "MerusAudio.h"

#include "audio_player.h"
#include "audio_renderer.h"

#define TAG "renderer"


static renderer_config_t *renderer_instance = NULL;
static component_status_t renderer_status = UNINITIALIZED;
//static QueueHandle_t i2s_event_queue;

static void init_i2s(renderer_config_t *config)
{
    i2s_mode_t mode = I2S_MODE_MASTER | I2S_MODE_TX;
    i2s_comm_format_t comm_fmt = I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB;
	int use_apll = 0;
	esp_chip_info_t out_info;
	esp_chip_info(&out_info);
	ESP_LOGI(TAG, "chip revision %d", out_info.revision);
	
    if(config->output_mode == DAC_BUILT_IN)
    {
        mode = mode | I2S_MODE_DAC_BUILT_IN;
        comm_fmt = I2S_COMM_FORMAT_I2S_MSB;
    }

    if(config->output_mode == PDM)
    {
        mode = mode | I2S_MODE_PDM;
		comm_fmt = I2S_COMM_FORMAT_PCM | I2S_COMM_FORMAT_PCM_SHORT;
    }

	if ((config->output_mode == I2S)||(config->output_mode == I2S_MERUS))
	{
	/* don't use audio pll on buggy rev0 chips */
	// don't do it for PDM
		if(out_info.revision > 0) {
			use_apll = 1;
			ESP_LOGI(TAG, "chip revision %d, enabling APLL", out_info.revision);
		} else
			ESP_LOGI(TAG, "chip revision %d, cannot enable APLL", out_info.revision);
	}
    /*
     * Allocate just enough to decode AAC+, which has huge frame sizes.
     *
     * Memory consumption formula:
     * (bits_per_sample / 8) * num_chan * dma_buf_count * dma_buf_len
     *
     * 16 bit: 32 * 256 = 8192 bytes
     * 32 bit: 32 * 256 = 16384 bytes
     */
    i2s_config_t i2s_config = {
            .mode = mode,          // Only TX
            .sample_rate = config->sample_rate,
            .bits_per_sample = config->bit_depth,
            .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,   // 2-channels
            .communication_format = comm_fmt,
            .dma_buf_count = bigSram()?16:16,                            // number of buffers, 128 max.  16
//            .dma_buf_len = bigSram()?256:128,                          // size of each buffer 128
            .dma_buf_len = bigSram()?128:128,                          // size of each buffer 128
//            .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,        // lowest level 1
            .intr_alloc_flags = 0,        // default
			.use_apll = use_apll					
    };

	gpio_num_t lrck;
	gpio_num_t bclk;
	gpio_num_t i2sdata;
	gpio_get_i2s(&lrck ,&bclk ,&i2sdata );

	i2s_pin_config_t pin_config = {
				.bck_io_num = bclk,
				.ws_io_num = lrck,
				.data_out_num = i2sdata,
				.data_in_num = I2S_PIN_NO_CHANGE
	};
	
    if (i2s_driver_install(config->i2s_num, &i2s_config, 0, NULL) != ESP_OK)
	{
		i2s_config.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1;
		if (i2s_driver_install(config->i2s_num, &i2s_config, 0, NULL) != ESP_OK)
			i2s_config.intr_alloc_flags = ESP_INTR_FLAG_LEVEL2;
			if (i2s_driver_install(config->i2s_num, &i2s_config, 0, NULL) != ESP_OK)
				ESP_LOGE(TAG,"i2s Error");
		return;
	}	
	ESP_LOGI(TAG,"i2s intr:%d", i2s_config.intr_alloc_flags);	
    if((mode & I2S_MODE_DAC_BUILT_IN))// || (mode & I2S_MODE_PDM))
    {
        i2s_set_pin(config->i2s_num, NULL);
        i2s_set_dac_mode(I2S_DAC_CHANNEL_BOTH_EN);
    }
    else {
		if ((lrck!=255) && (bclk!=255) && (i2sdata!=255))
			i2s_set_pin(config->i2s_num, &pin_config);
    }

    i2s_stop(config->i2s_num);
}

//KaraDio32
void renderer_volume(uint32_t vol)
{
	// log volume (magic)
	if (vol == 1) return;  // volume 0
//	ESP_LOGI(TAG, "Renderer vol: %d %X",vol,vol );
	if (vol >= 255) 
	{
		renderer_instance->volume = 0x10000;
		ESP_LOGD(TAG, "Renderer volume max:  %d  %X",renderer_instance->volume,renderer_instance->volume );
		return;
	}
	vol = 255  - vol;
	uint32_t value = (log10(255/((float)vol+1)) * 105.54571334);	
//	ESP_LOGI(TAG, "Renderer value: %X",value );
	if (value >= 254) value = 256;
	renderer_instance->volume = value<<8; // *256
	ESP_LOGD(TAG, "Renderer volume:  %X",renderer_instance->volume );
}
//-----------

/**
 * I2S is MSB first (big-endian) two's complement (signed) integer format.
 * The I2S module receives and transmits left-channel data first.
 *
 * ESP32 is little-endian.
 */
void render_samples(char *buf, uint32_t buf_len, pcm_format_t *buf_desc)
{
//    ESP_LOGV(TAG, "buf_desc: bit_depth %d format %d num_chan %d sample_rate %d", buf_desc->bit_depth, buf_desc->buffer_format, buf_desc->num_channels, buf_desc->sample_rate);
//    ESP_LOGV(TAG, "renderer_instance: bit_depth %d, output_mode %d", renderer_instance->bit_depth, renderer_instance->output_mode);
	 //ESP_LOGI(TAG, "render_samples len: %d",buf_len);
	int res = 0;
	uint8_t* outBuf8;
	uint32_t* outBuf32;
	uint64_t* outBuf64;
	if (buf_len == 0) return; // decoder error
    // handle changed sample rate
    if(renderer_instance->sample_rate != buf_desc->sample_rate)
    {
        ESP_LOGD(TAG, "changing sample rate from %d to %d", renderer_instance->sample_rate, buf_desc->sample_rate);
        uint32_t rate = buf_desc->sample_rate * renderer_instance->sample_rate_modifier;
       res =  i2s_set_sample_rates(renderer_instance->i2s_num, rate);
//		res = i2s_set_clk(renderer_instance->i2s_num, rate, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO);
		if (res != ESP_OK) {
			ESP_LOGE(TAG, "i2s_set_clk error %d",res);
		}
        renderer_instance->sample_rate = buf_desc->sample_rate;
    }

    uint8_t buf_bytes_per_sample = (buf_desc->bit_depth / 8);
    uint32_t num_samples = buf_len / buf_bytes_per_sample / buf_desc->num_channels;
//KaraDio32 Volume control
	register uint32_t mult = renderer_instance->volume;
	
	if ((mult!= 0x10000)) // && (renderer_instance->output_mode != DAC_BUILT_IN) && (renderer_instance->output_mode != PDM))// need volume?
	{	
		if (buf_bytes_per_sample ==2)
		{
			int16_t *psample;
			uint32_t pmax;
			psample = (int16_t*)buf;
			pmax = num_samples*buf_desc->num_channels;
			for (int32_t i = 0; i < pmax; i++) 
			{
				int32_t temp = (int32_t)psample[i] * mult;
				psample[i] = (temp>>16) & 0xFFFF;	
			}
		} else
		{
			int32_t *psample;
			uint32_t pmax;
			psample = (int32_t*)buf;
			pmax = num_samples*buf_desc->num_channels;
			for (int32_t i = 0; i < pmax; i++) 
			{
				int64_t temp = psample[i] * mult;
				psample[i] = (temp>>16) & 0xFFFFFFFF;	
			}
		}			
	}
//-------------------------
//ESP_LOGD(TAG, "I2S CHECK:  buf_desc->bit_depth %d, renderer_instance->bit_depth %d, buf_desc->buffer_format %d, PCM_INTERLEAVED %d, buf_desc->num_channels %d (2), renderer_instance->output_mode %d, DAC_BUILT_IN %d ",buf_desc->bit_depth,renderer_instance->bit_depth,buf_desc->buffer_format,PCM_INTERLEAVED,buf_desc->num_channels,renderer_instance->output_mode,DAC_BUILT_IN);

    // formats match, we can write the whole block
    if (buf_desc->bit_depth == renderer_instance->bit_depth
            && buf_desc->buffer_format == PCM_INTERLEAVED
            && buf_desc->num_channels == 2
            && renderer_instance->output_mode != DAC_BUILT_IN 
			&& renderer_instance->output_mode != PDM
			)
	{

        // do not wait longer than the duration of the buffer
//        TickType_t max_wait = buf_desc->sample_rate / num_samples / 2;

        // don't block, rather retry
        size_t bytes_left = buf_len;
        size_t bytes_written = 0;
        while((bytes_left > 0) && (renderer_status == RUNNING)) {
            res = i2s_write(renderer_instance->i2s_num, buf, bytes_left,& bytes_written, 0);
			if (res != ESP_OK) {
				ESP_LOGE(TAG, "i2s_write error %d",res);
			}
            bytes_left -= bytes_written;
            buf += bytes_written;
        }

        return;
    }

    // support only 16 bit buffers for now
    if(buf_desc->bit_depth != I2S_BITS_PER_SAMPLE_16BIT) {
        ESP_LOGD(TAG, "unsupported decoder bit depth: %d", buf_desc->bit_depth);
		renderer_stop();
        return;
    }

    // pointer to left / right sample position
    char *ptr_l = buf;
    char *ptr_r = buf + buf_bytes_per_sample;
    uint8_t stride = buf_bytes_per_sample * 2;

    // right half of the buffer contains all the right channel samples
    if(buf_desc->buffer_format == PCM_LEFT_RIGHT)
    {
        ptr_r = buf + buf_len / 2;
        stride = buf_bytes_per_sample;
    }

    if (buf_desc->num_channels == 1)  // duplicate 
	{
        ptr_r = ptr_l;
    }

    TickType_t max_wait = 20 / portTICK_PERIOD_MS; // portMAX_DELAY = bad idea

// har-in-air correction	
	uint32_t outBufBytes = buf_len*(2/buf_desc->num_channels);
	if (renderer_instance->bit_depth == I2S_BITS_PER_SAMPLE_32BIT) outBufBytes <<= 1;
	
	outBuf8 = malloc(outBufBytes);
	
//	outBuf8 = malloc(buf_len*(2/buf_desc->num_channels));
//
	if (outBuf8 == NULL) 
	{
		ESP_LOGE(TAG, "malloc buf failed len:%d ",buf_len);
		renderer_stop();
		return;
	}
//	outBuf16 =(uint16_t*)outBuf8;
	outBuf32 =(uint32_t*)outBuf8;
	outBuf64 = (uint64_t*)outBuf8;

	
    for (int i = 0; i < num_samples; i++) {
        if (renderer_status == STOPPED) break;

        if((renderer_instance->output_mode == DAC_BUILT_IN))//||(renderer_instance->output_mode == PDM))
        {
            // assume 16 bit src bit_depth
            int16_t left = *(int16_t *) ptr_l;
            int16_t right = *(int16_t *) ptr_r;
			
            // The built-in DAC wants unsigned samples, so we shift the range
            // from -32768-32767 to 0-65535.
            left  = left  + 0x8000;
            right = right + 0x8000;					

            uint32_t sample = (uint16_t) left;
            sample = (sample << 16 & 0xffff0000) | ((uint16_t) right);

			outBuf32[i] = sample;
        }
		
/*		else if (renderer_instance->output_mode == PDM)
		{
            const char samp16[2] = {ptr_l[0], ptr_l[1]};
		    outBuf16[i] = *((uint16_t*)samp16);		
		
		} */
        else {

            switch (renderer_instance->bit_depth)
            {
                case I2S_BITS_PER_SAMPLE_16BIT:
                    ; // workaround
                    /* low - high / low - high */
                    const char samp32[4] = {ptr_l[0], ptr_l[1], ptr_r[0], ptr_r[1]};
					outBuf32[i] = *((uint32_t*)samp32);					
                    break;

                case I2S_BITS_PER_SAMPLE_32BIT:
                    ; // workaround

                    const char samp64[8] = {0, 0, ptr_l[0], ptr_l[1], 0, 0, ptr_r[0], ptr_r[1]};					
					outBuf64[i] = *((uint64_t*)samp64);
                    break;

                default:
                    ESP_LOGE(TAG, "bit depth unsupported: %d", renderer_instance->bit_depth);
            }
        }

        ptr_r += stride;
        ptr_l += stride;
    }
//
// har-in-air correction	
	size_t bytes_left = outBufBytes  ;
	size_t bytes_written = 0;
		
	
	while(bytes_left > 0 && renderer_status != STOPPED) {
		res = i2s_write(renderer_instance->i2s_num, (const char*) outBuf8, bytes_left,& bytes_written, max_wait);
		if (res != ESP_OK) {
			ESP_LOGE(TAG, "i2s_write error %d",res);
		}
//		if (bytes_written != bytes_left) ESP_LOGV(TAG, "written: %d, len: %d",bytes_written,bytes_left);


        bytes_left -= bytes_written;
        buf += (bytes_written  );
    }
	free (outBuf8);
}


void renderer_zero_dma_buffer()
{
    i2s_zero_dma_buffer(renderer_instance->i2s_num);
}


renderer_config_t *renderer_get()
{
    return renderer_instance;
}


/* init renderer sink */
void renderer_init(renderer_config_t *config)
{
    // update global
    renderer_instance = config;
    renderer_status = INITIALIZED;

    ESP_LOGD(TAG, "init I2S mode %d, port %d, %d bit, %d Hz", config->output_mode, config->i2s_num, config->bit_depth, config->sample_rate);
    init_i2s(config);

    if(config->output_mode == I2S_MERUS) {
        if (init_ma120(0x50))			// setup ma120x0p and initial volume
			config->output_mode = I2S;	// error, back to I2S
    }
}


void renderer_start()
{
    if(renderer_status == RUNNING)
        return;

    // buffer might contain noise
    i2s_zero_dma_buffer(renderer_instance->i2s_num);
	ESP_LOGD(TAG, "Start" );
    i2s_start(renderer_instance->i2s_num);
    renderer_status = RUNNING;		
}

void renderer_stop()
{
    if(renderer_status == STOPPED)
        return;
    renderer_status = STOPPED;	
	ESP_LOGD(TAG, "Stop" );	
	i2s_stop(renderer_instance->i2s_num);
}

void renderer_destroy()
{
    renderer_status = UNINITIALIZED;
    i2s_driver_uninstall(renderer_instance->i2s_num);
}

