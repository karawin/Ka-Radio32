
/******************************************************************************
 * 
 * Copyright 2017 karawin (http://www.karawin.fr)
 *
 * Receive and decode nec IR. Send result in a queue
 *
*******************************************************************************/


#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include "ClickEncoder.h"
#include "app_main.h"
#include "gpio.h"
#include "webclient.h"
#include "webserver.h"
#include "interface.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/rmt.h"
#include "soc/rmt_reg.h"

//IR
#define RMT_RX_ACTIVE_LEVEL  0   /*!< If we connect with a IR receiver, the data is active low */
#define RMT_RX_CHANNEL    0     /*!< RMT channel for receiver */
#define RMT_CLK_DIV      100    /*!< RMT counter clock divider */
#define RMT_TICK_10_US    (80000000/RMT_CLK_DIV/100000)   /*!< RMT counter value for 10 us.(Source clock is APB clock) */

#define NEC_HEADER_HIGH_US    9300                         /*!< NEC protocol header: positive 9ms */
#define NEC_HEADER_LOW_US     4600                         /*!< NEC protocol header: negative 4.5ms*/
#define NEC_REPEAT_LOW_US	  2300                         /*!< NEC protocol repeat: negative 2.25ms*/
#define NEC_BIT_ONE_HIGH_US    600                         /*!< NEC protocol data bit 1: positive 0.56ms */
#define NEC_BIT_ONE_LOW_US    (2250-NEC_BIT_ONE_HIGH_US)   /*!< NEC protocol data bit 1: negative 1.69ms */
#define NEC_BIT_ZERO_HIGH_US   600                         /*!< NEC protocol data bit 0: positive 0.56ms */
#define NEC_BIT_ZERO_LOW_US   (1120-NEC_BIT_ZERO_HIGH_US)  /*!< NEC protocol data bit 0: negative 0.56ms */
#define NEC_BIT_END            600/*560*/                        /*!< NEC protocol end: positive 0.56ms */
#define NEC_BIT_MARGIN         400/*20*/                          /*!< NEC parse margin time */

#define NEC_ITEM_DURATION(d)  ((d & 0x7fff)*10/RMT_TICK_10_US)  /*!< Parse duration time from memory register value */
#define NEC_DATA_ITEM_NUM   34  /*!< NEC code item number: header + 32bit data + end */
#define rmt_item32_tIMEOUT_US  9500   /*!< RMT receiver timeout value(us) */
#define RTN_REPEAT	0xFF	/*!< return code for a repeat frame*/


static const char* NEC_TAG = "NEC";


 
 /*
 * @brief Check whether duration is around target_us
 */
/*inline*/ bool nec_check_in_range(int duration_ticks, int target_us, int margin_us)
{
//	ESP_LOGD(NEC_TAG,"NEC_ITEM_DURATION(%d)= %d",duration_ticks,NEC_ITEM_DURATION(duration_ticks));
    if(( NEC_ITEM_DURATION(duration_ticks) < (target_us + margin_us))
        && ( NEC_ITEM_DURATION(duration_ticks) > (target_us - margin_us))) {
        return true;
    } else {
        return false;
    }
}

/*
 * @brief Check whether this value represents an NEC header
 */ 
static bool nec_header_if(rmt_item32_t* item)
{
    ESP_LOGD(NEC_TAG,"Header Duration0: %x Level0: %x, Duration1: %x, Level1: %x",item->duration0,item->level0,item->duration1,item->level1);	
	if((item->level0 == RMT_RX_ACTIVE_LEVEL && item->level1 != RMT_RX_ACTIVE_LEVEL)
        && nec_check_in_range(item->duration0, NEC_HEADER_HIGH_US, NEC_BIT_MARGIN)
        && nec_check_in_range(item->duration1, NEC_HEADER_LOW_US, NEC_BIT_MARGIN)) {
        return true;
    }
    return false;
}
/*
 * @brief Check whether this value represents an NEC repeat
 */ 
static bool nec_repeat_if(rmt_item32_t* item)
{
    ESP_LOGD(NEC_TAG,"Repeat Duration0: %x Level0: %x, Duration1: %x, Level1: %x",item->duration0,item->level0,item->duration1,item->level1);	
	ESP_LOGV(NEC_TAG,"NEC_ITEM_DURATION0(%d)= %d",item->duration0,NEC_ITEM_DURATION(item->duration0));
	ESP_LOGV(NEC_TAG,"NEC_ITEM_DURATION1(%d)= %d",item->duration1,NEC_ITEM_DURATION(item->duration1));
	if((item->level0 == RMT_RX_ACTIVE_LEVEL && item->level1 != RMT_RX_ACTIVE_LEVEL)
        && nec_check_in_range(item->duration0, NEC_HEADER_HIGH_US, NEC_BIT_MARGIN)
        && nec_check_in_range(item->duration1, NEC_REPEAT_LOW_US, NEC_BIT_MARGIN)) {
		ESP_LOGD(NEC_TAG,"nec_repeat_if true");
        return true;
    }
    return false;
}
/*
 * @brief Check whether this value represents an NEC data bit 1
 */
 
static bool nec_bit_one_if(rmt_item32_t* item)
{
    ESP_LOGD(NEC_TAG,"nec_bit_one_if Duration0: %x Level0: %x, Duration1: %x, Level1: %x",item->duration0,item->level0,item->duration1,item->level1);
	ESP_LOGV(NEC_TAG,"NEC_ITEM_DURATION0(%d)= %d",item->duration0,NEC_ITEM_DURATION(item->duration0));
	ESP_LOGV(NEC_TAG,"NEC_ITEM_DURATION1(%d)= %d",item->duration1,NEC_ITEM_DURATION(item->duration1));
    if((item->level0 == RMT_RX_ACTIVE_LEVEL && item->level1 != RMT_RX_ACTIVE_LEVEL)
        && nec_check_in_range(item->duration0, NEC_BIT_ONE_HIGH_US, NEC_BIT_MARGIN)
        && nec_check_in_range(item->duration1, NEC_BIT_ONE_LOW_US, NEC_BIT_MARGIN)) {
		ESP_LOGD(NEC_TAG,"nec_bit_one_if true");
        return true;
    }
    return false;
}

/*
 * @brief Check whether this value represents an NEC data bit 0
 */
static bool nec_bit_zero_if(rmt_item32_t* item)
{
    ESP_LOGD(NEC_TAG,"nec_bit_zero_if Duration0: %x Level0: %x, Duration1: %x, Level1: %x",item->duration0,item->level0,item->duration1,item->level1);
	ESP_LOGV(NEC_TAG,"NEC_ITEM_DURATION0(%d)= %d",item->duration0,NEC_ITEM_DURATION(item->duration0));
	ESP_LOGV(NEC_TAG,"NEC_ITEM_DURATION1(%d)= %d",item->duration1,NEC_ITEM_DURATION(item->duration1));
    if((item->level0 == RMT_RX_ACTIVE_LEVEL && item->level1 != RMT_RX_ACTIVE_LEVEL)
        && nec_check_in_range(item->duration0, NEC_BIT_ZERO_HIGH_US, NEC_BIT_MARGIN)
        && nec_check_in_range(item->duration1, NEC_BIT_ZERO_LOW_US, NEC_BIT_MARGIN)) {
		ESP_LOGD(NEC_TAG,"nec_bit_zero_if true");	
        return true;
    }
    return false;
}



 /*
 * @brief Parse NEC 32 bit waveform to address and command.
 */
static int nec_parse_items(rmt_item32_t* item, int item_num, uint16_t* addr, uint16_t* data)
{
	ESP_LOGD(NEC_TAG,"RMT item len: %d",item_num);
//	ESP_LOGD(NEC_TAG,"Duration0: %x, Level0: %x, Duration1: %x, Level1: %x",item->duration0,item->level0,item->duration1,item->level1);
	
//	ESP_LOG_BUFFER_HEXDUMP(NEC_TAG, item, item_num, ESP_LOG_DEBUG);
    int w_len = item_num;
/*    if(w_len < NEC_DATA_ITEM_NUM) {
		ESP_LOGD(NEC_TAG,"Duration0: %x, Level0: %x, Duration1: %x, Level1: %x",item->duration0,item->level0,item->duration1,item->level1);
        return -1;
    }
*/
    int i = 0, j = 0;
	if((w_len == 2)&&(nec_repeat_if(item)))
	{
			ESP_LOGD(NEC_TAG,"Repeat detected");
			return RTN_REPEAT;
	}
    if(!nec_header_if(item++)) {
		item--;
		ESP_LOGD(NEC_TAG,"Duration0: %x, Level0: %x, Duration1: %x, Level1: %x",item->duration0,item->level0,item->duration1,item->level1);
		return -2;
    }
    uint16_t addr_t = 0;
    for(j = 0; j < 16; j++) {
        if(nec_bit_one_if(item)) {
            addr_t |= (1 << j);
        } else if(nec_bit_zero_if(item)) {
            addr_t |= (0 << j);
        } else {
            return -3;
        }
        item++;
        i++;
    }
    uint16_t data_t = 0;
    for(j = 0; j < 16; j++) {
        if(nec_bit_one_if(item)) {
            data_t |= (1 << j);
        } else if(nec_bit_zero_if(item)) {
            data_t |= (0 << j);
        } else {
            return -4;
        }
        item++;
        i++;
    }
    *addr = addr_t ;
    *data = data_t;
    return i;
}



/*
 * @brief RMT receiver initialization
 */
static bool nec_rx_init()
{
	esp_err_t err = ESP_OK;
	gpio_num_t ir;
	gpio_get_ir_signal(&ir);
	if (ir == GPIO_NONE) return false; //no IR needed
    rmt_config_t rmt_rx;
    rmt_rx.channel = RMT_RX_CHANNEL;
    rmt_rx.gpio_num = ir;
    rmt_rx.clk_div = RMT_CLK_DIV;
    rmt_rx.mem_block_num = 1;
    rmt_rx.rmt_mode = RMT_MODE_RX;
    rmt_rx.rx_config.filter_en = true;
    rmt_rx.rx_config.filter_ticks_thresh = 100;
    rmt_rx.rx_config.idle_threshold = rmt_item32_tIMEOUT_US / 10 * (RMT_TICK_10_US);
    ESP_ERROR_CHECK(rmt_config(&rmt_rx));
    err = rmt_driver_install(rmt_rx.channel, 1000, 0);
	if (err != ESP_OK) {ESP_LOGE(NEC_TAG,"Rrmt_driver_install failed %x",err); return false;}
	return true;
}


/**
 * @brief RMT receiver , this task will send each received NEC data to a queue.
 *
 */
void rmt_nec_rx_task()
{
	event_ir_t evt;
	event_ir_t last_evt;
    int channel = RMT_RX_CHANNEL;
    if (nec_rx_init())
	{
		RingbufHandle_t rb = NULL;
		bool flagFirstRepeat = false;
		//get RMT RX ringbuffer
		ESP_ERROR_CHECK(rmt_get_ringbuf_handle(channel, &rb) );
		ESP_ERROR_CHECK(rmt_rx_start(channel, 1));
		ESP_LOGD(NEC_TAG,"RMT started");
		while(rb) {
			size_t rx_size = 0;
			//try to receive data from ringbuffer.
			//RMT driver will push all the data it receives to its ringbuffer.
			//We just need to parse the value and return the spaces of ringbuffer.
			rmt_item32_t* item = (rmt_item32_t*) xRingbufferReceive(rb, &rx_size, 1000);
			if(item) {
				uint16_t rmt_addr;
				uint16_t rmt_cmd;
				int offset = 0;
				while(1) {
					//parse data value from ringbuffer.
					int res = nec_parse_items(item + offset, rx_size / 4 - offset, &rmt_addr, &rmt_cmd);
					if (res == RTN_REPEAT)
					{
						if (flagFirstRepeat ==  true)
							xQueueSend(event_ir,&last_evt, 0);
						flagFirstRepeat = true;	// not the first one
						offset += 3;		
					}
					else if(res > 0) {
						offset += res + 1;
						ESP_LOGD(NEC_TAG, "RMT RCV --- addr: 0x%04x cmd: 0x%04x", rmt_addr, rmt_cmd);
						evt.channel = channel;
						evt.addr = rmt_addr;
						evt.cmd =  rmt_cmd;
						evt.repeat_flag = false;
						last_evt.addr = evt.addr;
						last_evt.cmd = evt.cmd;
						last_evt.repeat_flag = true;
						flagFirstRepeat = false;
						xQueueSend(event_ir,&evt, 0);
					} else {
						ESP_LOGD(NEC_TAG, "RMT Res: %d",res);
						break;
					}
				}
				//after parsing the data, return spaces to ringbuffer.
				vRingbufferReturnItem(rb, (void*) item);
			} else 	{
				vTaskDelay(10);
				//break;
			}
		}
	}
	ESP_LOGD(NEC_TAG,"RMT finished");
    vTaskDelete(NULL);
}

