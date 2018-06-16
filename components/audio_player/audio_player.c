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

//#include "helix_aac_decoder.h"
//#include "libfaad_decoder.h"
#include "mp3_decoder.h"
//#include "controls.h"
#include "webclient.h"
#include "vs1053.h"
#include "app_main.h"

#define TAG "audio_player"
//#define PRIO_MAD configMAX_PRIORITIES - 4
#define PRIO_MAD 4

static player_t *player_instance = NULL;
static component_status_t player_status = UNINITIALIZED;

static int start_decoder_task(player_t *player)
{
    TaskFunction_t task_func;
    char * task_name;
    uint16_t stack_depth;

    ESP_LOGD(TAG, "RAM left %d", esp_get_free_heap_size());
	if (get_audio_output_mode() == VS1053)
	{
		task_func = vsTask;
        task_name = "vsTask";
        stack_depth = 3000;
	} else
    switch (player->media_stream->content_type)
    {
        case AUDIO_MPEG:
            task_func = mp3_decoder_task;
            task_name = "mp3_decoder_task";
            stack_depth = 8448;
            break;

 /*       case AUDIO_MP4:
            task_func = libfaac_decoder_task;
            task_name = "libfaac_decoder_task";
            stack_depth = 54000; //55000
            break;

		case AUDIO_AAC:
        case OCTET_STREAM: // probably .aac
            task_func = helixaac_decoder_task;
            task_name = "helixaac_decoder_task";
            stack_depth = 3000; //6144; //6144
            break;
*/			
        default:
            ESP_LOGW(TAG, "unknown mime type: %d", player->media_stream->content_type);
			spiRamFifoReset();
            return -1;
    }

	if (((task_func != NULL)) && (xTaskCreatePinnedToCore(task_func, task_name, stack_depth, player,
			PRIO_MAD, NULL, 0) != pdPASS)) {
							
				
		ESP_LOGE(TAG, "ERROR creating decoder task! Out of memory?");
		spiRamFifoReset();
		return -1;
	} else {
		player->decoder_status = RUNNING;
	}
	
		ESP_LOGD(TAG, "created decoder task: %s", task_name);

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
		//audio_player_stop();
//		clientDisconnect("C_Play stop"); 
		clientSilentDisconnect();
		
        //player->decoder_command = CMD_STOP;
        return -1;
    }

    if (bytes_read > 0) {
        spiRamFifoWrite(recv_buf, bytes_read);
    }


	int bytes_in_buf = spiRamFifoFill();
	uint8_t fill_level = (bytes_in_buf * 100) / spiRamFifoLen();

	// seems 4k is enough to prevent initial buffer underflow
	uint8_t min_fill_lvl = player->buffer_pref == BUF_PREF_FAST ? 40 : 90;
	bool buffer_ok = fill_level > min_fill_lvl;
	if (player->decoder_status != RUNNING && buffer_ok) {

		// buffer is filled, start decoder
		if (start_decoder_task(player) != 0) {
			ESP_LOGE(TAG, "failed to start decoder task");
			audio_player_stop();
			clientDisconnect("unsupported mime type"); 
			return -1;
		}
	}

	t = (t + 1) & 255;
	if (t == 0) {
		ESP_LOGV(TAG, "Buffer fill %u%%, %d bytes", fill_level, bytes_in_buf);
	}

    return 0;
}

void audio_player_init(player_t *player)
{
    player_instance = player;
    player_status = INITIALIZED;
}

void audio_player_destroy()
{
    renderer_destroy();
    player_status = UNINITIALIZED;
}

void audio_player_start()
{
	//if (get_audio_output_mode() != VS1053)
	{
		if (get_audio_output_mode() != VS1053) renderer_start();
		player_instance->media_stream->eof = false;
		player_instance->command = CMD_START;
		player_instance->decoder_command = CMD_NONE;	
		player_status = RUNNING;
	}
}

void audio_player_stop()
{ 
    //if (get_audio_output_mode() != VS1053)
	{
		player_instance->decoder_command = CMD_STOP;
		player_instance->command = CMD_STOP;
		player_instance->media_stream->eof = true;
		if (get_audio_output_mode() != VS1053)renderer_stop();
		player_instance->command = CMD_NONE;
		player_status = STOPPED;
	}
	
}

component_status_t get_player_status()
{
    return player_status;
}

