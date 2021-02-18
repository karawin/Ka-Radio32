/*
 * fdk_aac_decoder.c
 *
 *  Created on: 08.05.2017
 *      Author: michaelboeckling
 */

#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
#include "driver/i2s.h"

#include "common_buffer.h"
#include "aacdecoder_lib.h"
#include "audio_player.h"
#include "spiram_fifo.h"
//#include "m4a.h"


#define TAG "fdkaac_decoder"


/* small, its just a transfer bucket for the internal decoder buffer */
static const uint32_t INPUT_BUFFER_SIZE = 1024;

#define MAX_CHANNELS        2
#define MAX_FRAME_SIZE      2048
#define OUTPUT_BUFFER_SIZE  (MAX_FRAME_SIZE * sizeof(INT_PCM) * MAX_CHANNELS)


void fdkaac_decoder_task(void *pvParameters)
{
    // ESP_LOGI(TAG, "(line %u) free heap: %u", __LINE__, esp_get_free_heap_size());
    player_t *player = pvParameters;
    AAC_DECODER_ERROR err;

    /* allocate sample buffer */
    buffer_t *pcm_buf = buf_create(OUTPUT_BUFFER_SIZE);

    /* allocate bitstream buffer */
    buffer_t *in_buf = buf_create(INPUT_BUFFER_SIZE*48);
    fill_read_buffer(in_buf);

    HANDLE_AACDECODER handle = NULL;
    pcm_format_t pcm_format = {.buffer_format = PCM_INTERLEAVED};

    /* select bitstream format */
    if (player->media_stream->content_type == AUDIO_MP4)
		{
		goto cleanup;
    } else {
        /* create decoder instance */
        handle = aacDecoder_Open(TT_MP4_ADTS, /* num layers */1);
        if (handle == NULL) {
            ESP_LOGE(TAG, "malloc failed %d", __LINE__);
            goto cleanup;
        }
    }

    /* configure instance */
    aacDecoder_SetParam(handle, AAC_PCM_OUTPUT_INTERLEAVED, 1);
    aacDecoder_SetParam(handle, AAC_PCM_MIN_OUTPUT_CHANNELS, 2);
    aacDecoder_SetParam(handle, AAC_PCM_MAX_OUTPUT_CHANNELS, 2);
    aacDecoder_SetParam(handle, AAC_PCM_LIMITER_ENABLE, 0);

    const uint32_t flags = 0;
    uint32_t pcm_size = 0;
    bool first_frame = true;

//    ESP_LOGI(TAG, "(line %u) free heap: %u", __LINE__, esp_get_free_heap_size());

    while (!player->media_stream->eof) {

        /* re-fill buffer if necessary */
       if (buf_data_unread(in_buf) == 0) {
            fill_read_buffer(in_buf);
//			vTaskDelay(1);
       if(player->decoder_command == CMD_STOP) {
                goto abort;
        }        }
		
//		watchgog reset 
		TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
		TIMERG0.wdt_feed=1;
		TIMERG0.wdt_wprotect=0;


 /*       if(player->decoder_command == CMD_STOP) {
                goto abort;
        }
*/		
        // bytes_avail will be updated and indicate "how much data is left"
        size_t bytes_avail = buf_data_unread(in_buf);
        aacDecoder_Fill(handle, &in_buf->read_pos, &bytes_avail, &bytes_avail);

        uint32_t bytes_taken = buf_data_unread(in_buf) - bytes_avail;
//        buf_seek_rel(in_buf, bytes_taken);
        in_buf->read_pos += bytes_taken;
        in_buf->bytes_consumed += bytes_taken;

        err = aacDecoder_DecodeFrame(handle, (short int *) pcm_buf->base,
                pcm_buf->len, flags);


        // need more bytes, lets refill
        if(err == AAC_DEC_TRANSPORT_SYNC_ERROR || err == AAC_DEC_NOT_ENOUGH_BITS) {
            continue;
        }

        if ((err != AAC_DEC_OK) && (err != AAC_DEC_INVALID_CODE_BOOK)){
            ESP_LOGI(TAG, "decode error 0x%08x", err);
			//buf_clear(in_buf);
			//buf_clear(pcm_buf);
			//goto abort;
            continue;
        }

        /* print first frame, determine pcm buffer length */
        if(first_frame) {
            first_frame = false;

            CStreamInfo* mStreamInfo = aacDecoder_GetStreamInfo(handle);

            pcm_size = mStreamInfo->frameSize * sizeof(int16_t)
                    * mStreamInfo->numChannels;

            ESP_LOGV(TAG, "pcm_size %d, channels: %d, sample rate: %d, object type: %d, bitrate: %d", pcm_size, mStreamInfo->numChannels,
                    mStreamInfo->sampleRate, mStreamInfo->aot, mStreamInfo->bitRate);

            pcm_format.bit_depth = I2S_BITS_PER_SAMPLE_16BIT;
            pcm_format.num_channels = mStreamInfo->numChannels;
            pcm_format.sample_rate = mStreamInfo->sampleRate;
        }
	
        render_samples((char *) pcm_buf->base, pcm_size, &pcm_format);

        // ESP_LOGI(TAG, "fdk_aac_decoder stack: %d\n", uxTaskGetStackHighWaterMark(NULL));
        // ESP_LOGI(TAG, "%u free heap %u", __LINE__, esp_get_free_heap_size());

    }
	goto cleanup;
	// exit on internal error
    abort:
	player->command = CMD_STOP;

    cleanup:
	ESP_LOGI(TAG, "fdk_aac_decoder stack: %d\n", uxTaskGetStackHighWaterMark(NULL));
	//renderer_zero_dma_buffer();
    player->decoder_status = STOPPED;
    player->decoder_command = CMD_NONE;
    ESP_LOGD(TAG, "Decoder stopped.\n");
    ESP_LOGI(TAG, "aac decoder finished  %x    %x",(int)in_buf,(int)pcm_buf);
    aacDecoder_Close(handle);
    spiRamFifoReset();
    //buf_destroy(in_buf);
    buf_destroy(pcm_buf);
	//esp_task_wdt_delete(NULL);

    vTaskDelete(NULL);
}
