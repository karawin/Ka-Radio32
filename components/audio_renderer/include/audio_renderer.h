/*
 * audio_renderer.h
 *
 *  Created on: 12.03.2017
 *      Author: michaelboeckling
 */

#ifndef INCLUDE_AUDIO_RENDERER_H_
#define INCLUDE_AUDIO_RENDERER_H_

#include "freertos/FreeRTOS.h"
#include "driver/i2s.h"
#include "common_component.h"

typedef enum {
    I2S, I2S_MERUS, DAC_BUILT_IN, PDM, VS1053, SPDIF, BTOOTH
} output_mode_t;


typedef struct
{
    output_mode_t output_mode;
    int sample_rate;
    float sample_rate_modifier;
    i2s_bits_per_sample_t bit_depth;
    i2s_port_t i2s_num;
	uint32_t volume;
	uint8_t frame_num;
	uint8_t rate_multiplier;
} renderer_config_t;

typedef enum
{
    PCM_INTERLEAVED, PCM_LEFT_RIGHT
} pcm_buffer_layout_t;

typedef struct
{
    uint32_t sample_rate;
    i2s_bits_per_sample_t bit_depth;
    uint8_t num_channels;
    pcm_buffer_layout_t buffer_format;
} pcm_format_t;

enum {
	LEFTCHANNEL	 = 0,
	RIGHTCHANNEL = 1
};

typedef struct
{
	void (*render_samples)(char *buf, uint32_t len, pcm_format_t *format);
	void (*set_volume)(uint32_t volume);
	void (*init)(renderer_config_t *config);
	void (*start)(void);
	void (*stop)(void);
	void (*destroy)(void);
	void (*zero_dma_buffer)(void);
} renderer_t;


/* render callback for libmad */
void render_sample_block(short *sample_buff_ch0, short *sample_buff_ch1, int num_samples, unsigned int num_channels);

renderer_t *spdif_renderer_get(void);
renderer_t *i2s_renderer_get(void);


#endif /* INCLUDE_AUDIO_RENDERER_H_ */
