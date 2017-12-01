/*
 * helix_aac_decoder.c
 *
 *  Created on: 2017
 *      Author: karawin
 */

#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/i2s.h"

#include "common_buffer.h"
#include "../libhelix-aac/aacdec.h"
#include "audio_player.h"
#include "audio_renderer.h"
//#include "m4a.h"
#include "spiram_fifo.h"

#define TAG "helixaac_decoder"


/* small, its just a transfer bucket for the internal decoder buffer */
static const uint32_t INPUT_BUFFER_SIZE = 1600;

#define MAX_CHANNELS        2
#define MAX_FRAME_SIZE      2048
#define OUTPUT_BUFFER_SIZE  (MAX_FRAME_SIZE * sizeof(short) * MAX_CHANNELS)

void helixaac_decoder_task(void *pvParameters)
{
    // ESP_LOGI(TAG, "(line %u) free heap: %u", __LINE__, esp_get_free_heap_size());

    HAACDecoder hAACDecoder = NULL;
    // Input buffering
//    uint8_t buff[1600]; // File buffer required to store at least a whole compressed frame
//    int16_t buffValid;
//    int16_t lastFrameEnd;
//    bool FillBufferWithValidFrame(); // Read until we get a valid syncword and min(feof, 2048) butes in the buffer

    player_t *player = pvParameters;
    int err;

    /* allocate sample buffer */
    buffer_t *pcm_buf = buf_create(OUTPUT_BUFFER_SIZE);

    /* allocate bitstream buffer */
    buffer_t *in_buf = buf_create(INPUT_BUFFER_SIZE);
    fill_read_buffer(in_buf);

    pcm_format_t pcm_format = {.buffer_format = PCM_INTERLEAVED};
	
	hAACDecoder = AACInitDecoder();
  if (!hAACDecoder) { 
	ESP_LOGE(TAG, "Out of memory error! hAACDecoder==NULL");
	goto cleanup;
  }
  
    const uint32_t flags = 0;
    uint32_t pcm_size = 0;
    bool first_frame = true;

    ESP_LOGD(TAG, "(line %u) free heap: %u", __LINE__, esp_get_free_heap_size());  
  
 
	while (!player->media_stream->eof) {

        /* re-fill buffer if necessary */
        if (buf_data_unread(in_buf) == 0) {
            fill_read_buffer(in_buf);
        }

        // bytes_avail will be updated and indicate "how much data is left"
        size_t bytes_avail = buf_data_unread(in_buf);
		
/*        aacDecoder_Fill(handle, &in_buf->read_pos, &bytes_avail, &bytes_avail);

        uint32_t bytes_taken = buf_data_unread(in_buf) - bytes_avail;
        buf_seek_rel(in_buf, bytes_taken);


        err = aacDecoder_DecodeFrame(handle, (short int *) pcm_buf->base,
                pcm_buf->len, flags);

        // need more bytes, lets refill
        if(err == AAC_DEC_TRANSPORT_SYNC_ERROR || err == AAC_DEC_NOT_ENOUGH_BITS) {
            continue;
        }

        if (err != AAC_DEC_OK) {
            ESP_LOGD(TAG, "decode error 0x%08x", err);
            continue;
        }
*/
        /* print first frame, determine pcm buffer length */
/*        if(first_frame) {
            first_frame = false;

            CStreamInfo* mStreamInfo = aacDecoder_GetStreamInfo(handle);

            pcm_size = mStreamInfo->frameSize * sizeof(int16_t)
                    * mStreamInfo->numChannels;

            ESP_LOGI(TAG, "pcm_size %d, channels: %d, sample rate: %d, object type: %d, bitrate: %d", pcm_size, mStreamInfo->numChannels,
                    mStreamInfo->sampleRate, mStreamInfo->aot, mStreamInfo->bitRate);

            pcm_format.bit_depth = I2S_BITS_PER_SAMPLE_16BIT;
            pcm_format.num_channels = mStreamInfo->numChannels;
            pcm_format.sample_rate = mStreamInfo->sampleRate;
        }

        render_samples((const char *) pcm_buf->base, pcm_size, &pcm_format);
*/
        // ESP_LOGI(TAG, "fdk_aac_decoder stack: %d\n", uxTaskGetStackHighWaterMark(NULL));
        // ESP_LOGI(TAG, "%u free heap %u", __LINE__, esp_get_free_heap_size());

        // about 32K free heap at this point
    }
 
  
 /* 
 	goto cleanup;
	// exit on internal error
    abort:	
	player->command = CMD_STOP;
*/	
	// exit on external event 
  	cleanup:
    buf_destroy(in_buf);
    buf_destroy(pcm_buf);
    AACFreeDecoder(hAACDecoder);
	spiRamFifoReset();
    player->decoder_status = STOPPED;
	player->decoder_command = CMD_NONE;
    ESP_LOGD(TAG, "decoder finished");

    vTaskDelete(NULL);
  
}
