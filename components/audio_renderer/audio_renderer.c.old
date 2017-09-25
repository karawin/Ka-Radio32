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

#include "freertos/FreeRTOS.h"

#include "esp_log.h"
#include "driver/i2s.h"
#include "MerusAudio.h"

#include "audio_player.h"
#include "audio_renderer.h"

#define TAG "renderer"


static renderer_config_t *renderer_instance = NULL;
static component_status_t renderer_status = UNINITIALIZED;
static QueueHandle_t i2s_event_queue;

static void init_i2s(renderer_config_t *config)
{
    i2s_mode_t mode = I2S_MODE_MASTER | I2S_MODE_TX;

    if(config->output_mode == DAC_BUILT_IN) {
        mode = mode | I2S_MODE_DAC_BUILT_IN;
    }

    if(config->output_mode == PDM) {
        mode = mode | I2S_MODE_PDM;
    }

    i2s_config_t i2s_config = {
            .mode = mode,          // Only TX
            .sample_rate = config->sample_rate,
            .bits_per_sample = config->bit_depth,
            .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,   // 2-channels
            .communication_format = I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB,
            .dma_buf_count = 32,                            // number of buffers, 128 max.
            .dma_buf_len = 32 * 2,                          // size of each buffer
            .intr_alloc_flags = ESP_INTR_FLAG_LEVEL2       // Interrupt level 1
    };

    i2s_pin_config_t pin_config = {
            .bck_io_num = 26,
            .ws_io_num = 25,
            .data_out_num = 22,
            .data_in_num = I2S_PIN_NO_CHANGE    // Not used
    };

    ESP_ERROR_CHECK(i2s_driver_install(config->i2s_num, &i2s_config, 1, &i2s_event_queue));

    if((mode & I2S_MODE_DAC_BUILT_IN) || (mode & I2S_MODE_PDM)) {
        ESP_ERROR_CHECK(i2s_set_pin(config->i2s_num, NULL));
        ESP_ERROR_CHECK(i2s_set_dac_mode(I2S_DAC_CHANNEL_BOTH_EN));
    } else {
        ESP_ERROR_CHECK(i2s_set_pin(config->i2s_num, &pin_config));
    }

    i2s_stop(config->i2s_num);
}

/*const uint16_t VolumeLUT[64]=    
{    
    0x0001,0x0001,0x0001,0x0002,0x0002,0x0002,0x0003,0x0004,
    0x0004,0x0005,0x0006,0x0008,0x0009,0x000B,0x000D,0x0010,
    0x0013,0x0016,0x001A,0x0020,0x0026,0x002D,0x0035,0x0040,
    0x004C,0x005A,0x006B,0x0080,0x0098,0x00B5,0x00D7,0x0100,
    0x0130,0x016A,0x01AE,0x0200,0x0260,0x02D4,0x035D,0x0400,
    0x04C1,0x05A8,0x06BA,0x0800,0x0983,0x0B50,0x0D74,0x1000,
    0x1306,0x16A0,0x1AE8,0x2000,0x260D,0x2D41,0x35D1,0x4000,
    0x4C1B,0x5A82,0x6BA2,0x8000,0x9837,0xB504,0xD744,0xFFFF
};
*/
void renderer_volume(uint32_t vol)
{
	if (vol >256) vol = 256;
	renderer_instance->volume = vol*256;
}


void render_samples(char *buf, uint32_t len, pcm_format_t *format)
{
    // handle changed sample rate
    if(renderer_instance->sample_rate != format->sample_rate)
    {
        ESP_LOGI(TAG, "changing sample rate from %d to %d", renderer_instance->sample_rate, format->sample_rate);
        uint32_t rate = format->sample_rate * renderer_instance->sample_rate_modifier;
        i2s_set_sample_rates(renderer_instance->i2s_num, rate);
        renderer_instance->sample_rate = format->sample_rate;
    }

	uint8_t buf_bytes_per_sample = (format->bit_depth / 8);
    uint32_t num_samples = len / buf_bytes_per_sample / format->num_channels; // thats stereo samples
	int16_t *psample;
	uint32_t mult = renderer_instance->volume;
	// Volume control
	psample = (int16_t*)buf;
	for (int i = 0; i < num_samples*format->num_channels; i++) {
			
//		int temp = psample[i] * VolumeLUT[renderer_instance->volume];
		int temp = psample[i] * mult;
		psample[i] = temp>>16 & 0xFFFF;		
	}

	
    // formats match, we can write the whole block
    if (format->bit_depth == renderer_instance->bit_depth
            && format->buffer_format == PCM_INTERLEAVED
            && renderer_instance->output_mode != DAC_BUILT_IN) {

		// duplicate channel for a stereophonic sound spectacular
        if (format->num_channels == 1) {
            i2s_write_bytes(renderer_instance->i2s_num, buf, len,
            portMAX_DELAY);
        }
		
        i2s_write_bytes(renderer_instance->i2s_num, buf, len, 1000 / portTICK_RATE_MS);
        return;
    }

    // support only 16 bit buffers for now
    if(format->bit_depth != I2S_BITS_PER_SAMPLE_16BIT) {
        ESP_LOGE(TAG, "unsupported decoder bit depth: %d", format->bit_depth);
        return;
    }

    // pointer to left / right sample position
    char *ptr_l = buf;
    char *ptr_r = buf + buf_bytes_per_sample;
    uint8_t stride = buf_bytes_per_sample * 2;

    // right half of the buffer contains all the right channel samples
    if(format->buffer_format == PCM_LEFT_RIGHT)
    {
        ptr_r = buf + len / 2;
        stride = buf_bytes_per_sample;
    }


    int bytes_pushed = 0;
    for (int i = 0; i < num_samples; i++) {
        if (renderer_status == STOPPED) break;

        // assume 16 bit src bit_depth for now
        short left = *(short *) ptr_l;
        short right = *(short *) ptr_r;

        if(renderer_instance->output_mode == DAC_BUILT_IN)
        {
            // The built-in DAC wants unsigned samples, so we shift the range
            // from -32768-32767 to 0-65535.
            left = left + 0x8000;
            right = right + 0x8000;
        }

        switch (renderer_instance->bit_depth)
        {
            case I2S_BITS_PER_SAMPLE_16BIT:
                ; // workaround
                uint32_t sample = (uint16_t) left;
                sample = (sample << 16 & 0xffff0000) | ((uint16_t) right);
                bytes_pushed = i2s_push_sample(renderer_instance->i2s_num,
                                (const char*) &sample, portMAX_DELAY);
                break;

            case I2S_BITS_PER_SAMPLE_32BIT:
                ; // workaround
                // not sure which order is correct?
                // uint64_t samp64 = ( ((uint64_t) left << 48 & 0xffff000000000000) | ((uint64_t) right << 16) );
                uint64_t samp64_2 = ( ((uint64_t) left << 16 & 0x00000000ffffffff) | ((uint64_t) right << 48) );

                /* this is equivalent:
                char high0 = left >> 8;
                char mid0  = left & 0xff;
                char high1 = right >> 8;
                char mid1  = right & 0xff;
                const char samp32[8] = {0, 0, mid0, high0, 0, 0, mid1, high1};
                */

                bytes_pushed = i2s_push_sample(renderer_instance->i2s_num, (const char*) &samp64_2, portMAX_DELAY);
                break;

            default:
                ESP_LOGE(TAG, "bit depth unsupported: %d", renderer_instance->bit_depth);
        }

        // DMA buffer full - retry
        if (bytes_pushed == 0) {
            i--;
        } else {
            ptr_r += stride;
            ptr_l += stride;
        }
    }

    /* takes too long
    i2s_event_t evt = {0};
    if(xQueueReceive(i2s_event_queue, &evt, 0)) {
        if(evt.type == I2S_EVENT_TX_DONE) {
            ESP_LOGE(TAG, "DMA Buffer Underflow");
        }
    }
    */
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

    ESP_LOGI(TAG, "init I2S mode %d, port %d, %d bit, %d Hz", config->output_mode, config->i2s_num, config->bit_depth, config->sample_rate);
    init_i2s(config);

    if(config->output_mode == I2S_MERUS) {
        init_ma120(0x50); // setup ma120x0p and initial volume
    }
}


void renderer_start()
{
    renderer_status = RUNNING;
    i2s_start(renderer_instance->i2s_num);

    // buffer might contain noise
    i2s_zero_dma_buffer(renderer_instance->i2s_num);
}

void renderer_stop()
{
    renderer_status = STOPPED;
    i2s_stop(renderer_instance->i2s_num);
}

void renderer_destroy()
{
    renderer_status = UNINITIALIZED;
    i2s_driver_uninstall(renderer_instance->i2s_num);
}

