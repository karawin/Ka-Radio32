/*
 * audio_player.c
 *
 *  Created on: 12.03.2017
 *      Author: michaelboeckling
 */

#include <stdlib.h>
#include "freertos/FreeRTOS.h"

#include "audio_player.h"
#include "spiram_fifo.h"
#include "freertos/task.h"
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_system.h"
#include "esp_log.h"

#include "fdk_aac_decoder.h"
//#include "helix_aac_decoder.h"
//#include "libfaad_decoder.h"
#include "mp3_decoder.h"
#include "webclient.h"
#include "vs1053.h"
#include "app_main.h"

#define TAG "audio_player"
//#define PRIO_MAD configMAX_PRIORITIES - 4


static player_t *player_instance = NULL;
static component_status_t player_status = UNINITIALIZED;


// Renderer config creation
static renderer_config_t *create_renderer_config()
{
    renderer_config_t *renderer_config = calloc(1, sizeof(renderer_config_t));

    renderer_config->bit_depth = I2S_BITS_PER_SAMPLE_16BIT;
    renderer_config->i2s_num = I2S_NUM_0;
    renderer_config->sample_rate = 44100;
    renderer_config->sample_rate_modifier = 1.0;
    renderer_config->output_mode = player_instance->output_mode;

    if(renderer_config->output_mode == I2S_MERUS) {
        renderer_config->bit_depth = I2S_BITS_PER_SAMPLE_32BIT;
    }

    if(renderer_config->output_mode == DAC_BUILT_IN) {
        renderer_config->bit_depth = I2S_BITS_PER_SAMPLE_16BIT;
    }

    return renderer_config;
}

static int start_decoder_task(player_t *player)
{
    TaskFunction_t task_func;
    char * task_name;
    uint16_t stack_depth;
	int priority = PRIO_MAD;

    ESP_LOGD(TAG, "RAM left %d", esp_get_free_heap_size());
	if (get_audio_output_mode() == VS1053)
	{
		task_func = vsTask;
        task_name = (char*)"vsTask";
        stack_depth = 3000;
		priority = PRIO_VS1053;
	} else
    switch (player->media_stream->content_type)
    {
        case AUDIO_MPEG:
            task_func = mp3_decoder_task;
            task_name = (char*)"mp3_decoder_task";
            stack_depth = 8448;
            break;

 /*       case AUDIO_MP4:
            task_func = libfaac_decoder_task;
            task_name = (char*)"libfaac_decoder_task";
            stack_depth = 55000;
            break;
*/

		case AUDIO_AAC:
        case OCTET_STREAM: // probably .aac
			if (!bigSram())
			{
            ESP_LOGW(TAG, "aac mime not supported type: %d", player->media_stream->content_type);
			spiRamFifoReset();
            return -1;				
			}
		
            task_func = fdkaac_decoder_task;
            task_name = (char*)"fdkaac_decoder_task";
            stack_depth = 7000; //6144; 
            break;
			
/*
		case AUDIO_AAC:
        case OCTET_STREAM: // probably .aac
            task_func = helixaac_decoder_task;
            task_name = (char*)"helixaac_decoder_task";
            stack_depth = 6144; //6144; //6144
            break;
*/
/*				
        case AUDIO_AAC:
        case OCTET_STREAM: // probably .aac
            task_func = libfaac_decoder_task;
            task_name = "libfaac_decoder_task";
            stack_depth = 55000;
            break;
*/
        default:
            ESP_LOGW(TAG, "unknown mime type: %d", player->media_stream->content_type);
			spiRamFifoReset();
            return -1;
    }

	if (((task_func != NULL)) && (xTaskCreatePinnedToCore(task_func, task_name, stack_depth, player,
			priority, NULL, CPU_MAD) != pdPASS)) 
	{
									
		ESP_LOGE(TAG, "ERROR creating decoder task! Out of memory?");
		spiRamFifoReset();
		return -1;
	} else {
		player->decoder_status = RUNNING;
	}
	
	spiRamFifoReset();
	ESP_LOGD(TAG, "decoder task created: %s", task_name);

    return 0;
}

static int t;

/* Writes bytes into the FIFO queue, starts decoder task if necessary. */
int audio_stream_consumer(const char *recv_buf, ssize_t bytes_read,
        void *user_data)
{
    player_t *player = user_data;
    // don't bother consuming bytes if stopped
    if(player->command == CMD_STOP) {
		clientSilentDisconnect();
        return -1;
    }

    if (bytes_read > 0) {
        spiRamFifoWrite(recv_buf, bytes_read);
    }


	int bytes_in_buf = spiRamFifoFill();
	uint8_t fill_level = (bytes_in_buf * 100) / spiRamFifoLen();

	// seems 4k is enough to prevent initial buffer underflow
//	uint8_t min_fill_lvl = player->buffer_pref == BUF_PREF_FAST ? 40 : 90;
//	bool buffer_ok = fill_level > min_fill_lvl;

	if (player->decoder_status != RUNNING ) 
	{
		t = 0;
		uint32_t trigger = (bigSram())? (70*1024):(20*1024);
		bool buffer_ok = (bytes_in_buf > trigger);
		if (buffer_ok)
		{
		// buffer is filled, start decoder
			ESP_LOGV(TAG,"trigger: %d",trigger);
			if (start_decoder_task(player) != 0) {
				ESP_LOGE(TAG, "failed to start decoder task");
				audio_player_stop();
				clientDisconnect("decoder failed"); 
				return -1;
			}
		}
	}

	t = (t+1) & 255;
	if (t == 0) {
		ESP_LOGI(TAG, "Buffer fill %u%%, %d // %d bytes", fill_level, bytes_in_buf,spiRamFifoLen());
	}

    return 0;
}

void audio_player_init(player_t *player)
{
    player_instance = player;
    player_status = INITIALIZED;

    player_instance->renderer->init(create_renderer_config());
}

void audio_player_destroy()
{
    if (get_audio_output_mode() != VS1053) player_instance->renderer->destroy();
    player_status = UNINITIALIZED;
}

void audio_player_start()
{
		if (get_audio_output_mode() != VS1053) player_instance->renderer->start();
		player_instance->media_stream->eof = false;
		player_instance->command = CMD_START;
		player_instance->decoder_command = CMD_NONE;	
		player_status = RUNNING;
}

void audio_player_stop()
{ 
		player_instance->decoder_command = CMD_STOP;
		player_instance->command = CMD_STOP;
		player_instance->media_stream->eof = true;
		if (get_audio_output_mode() != VS1053)player_instance->renderer->stop();
		player_instance->command = CMD_NONE;
		player_status = STOPPED;
}

void audio_player_clear()
{
	player_instance->renderer->zero_dma_buffer();
}

void audio_player_set_volume(uint32_t vol)
{
	player_instance->renderer->set_volume(vol);
}

void audio_player_play(char *buf, uint32_t buf_len, pcm_format_t *buf_desc)
{
	player_instance->renderer->render_samples(buf, buf_len, buf_desc);
}

component_status_t get_player_status()
{
    return player_status;
}

