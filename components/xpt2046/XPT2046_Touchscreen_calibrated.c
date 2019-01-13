/* Touchscreen library for XPT2046 Touch Controller Chip
 * Copyright (c) 2015, Paul Stoffregen, paul@pjrc.com
 * 
 * Calibration code modification
 * Copyright (c) 2016, Paul Postuma
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_intr_alloc.h"
#include <string.h>
#include "esp_log.h"
#ifdef KaRadio32
#include "gpio.h"
#include "vs1053.h"
#endif

#define TAG  "XPT2046"

#include "XPT2046_Touchscreen_calibrated.h"

#define Z_THRESHOLD     400
#define Z_THRESHOLD_INT	75
#define MSEC_THRESHOLD  3
#define SPI_SETTING     SPISettings(2000000, MSBFIRST, SPI_MODE0)

unsigned long IRAM_ATTR millis()
{
    return (unsigned long) (esp_timer_get_time() / 1000);
}

	
static	spi_device_handle_t t_handle = NULL; // SPI handle of the spi touch interface.
static XPT2046_Touchscreen 	*isrPinptr;	
void isrPin(void*);
void update(XPT2046_Touchscreen* ts);


uint16_t transfer16(uint8_t addressbyte){
	uint16_t result;
    uint8_t datas[3] = {0};
    datas[0] = addressbyte;
	esp_err_t ret;
   spi_transaction_t t = {
        .length = 1 * 8 * 3,              // Len is in bytes, transaction length is in bits.
        .tx_buffer = &datas,              // Data
        .flags = SPI_TRANS_USE_RXDATA,
    };
	ret = spi_device_transmit(t_handle, &t);  //Transmit!
	if (ret != ESP_OK) ESP_LOGE(TAG,"err: %d, transfer16(%d), read: %d",ret,addressbyte,(uint16_t)*t.rx_data);
//	result =  (((t.rx_data[1]&0xFF)<<8) | ((t.rx_data[2]>>3)&0xFF)) ;
	result = (t.rx_data[1] << 8 | t.rx_data[2]) >> 3;
	ESP_LOGI(TAG,"transfer16 addr: %d, result: %d",addressbyte,result);
	return result;
}


TS_Point* TS_Point_init(int16_t x,int16_t y,int16_t z) 
{ 
	TS_Point* pt = malloc(sizeof(TS_Point));
	pt->x=x; pt->y=y; pt->z=z;
	return pt;
}
bool isTpEqual(TS_Point* a,TS_Point* b)
{
	return ((a->x == b->x) && (a->y == b->y) && (a->z == b->z));
}
bool isTpDiff(TS_Point* a,TS_Point* b)
{
	return ((a->x != b->x) && (a->y != b->y) && (a->z != b->z));
}


XPT2046_Touchscreen* XPT2046_Touchscreen_init(spi_host_device_t spi_no, gpio_num_t  cspin, gpio_num_t  tirq)
{
	XPT2046_Touchscreen* ts = malloc(sizeof(XPT2046_Touchscreen));
	ts->isrWake = false;
	ts->xraw=0, ts->yraw=0, ts->zraw=0;
	ts->msraw= 0x80000000;
	ts->tirq = (uint8_t)tirq;
	ts->csPin = cspin;
	
	// t_irq is an input
	gpio_config_t gpioConfig;
	gpioConfig.mode         = GPIO_MODE_INPUT;
	gpioConfig.pull_up_en   = GPIO_PULLUP_DISABLE;
	gpioConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
	gpioConfig.intr_type    = GPIO_INTR_NEGEDGE;
	gpioConfig.pin_bit_mask = (1<<tirq);
	if (255 != tirq) ESP_ERROR_CHECK(gpio_config(&gpioConfig));	
	gpioConfig.mode         = GPIO_MODE_OUTPUT;
	gpioConfig.pull_up_en   = GPIO_PULLUP_ENABLE;
	gpioConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
	gpioConfig.intr_type    = GPIO_INTR_DISABLE;
	gpioConfig.pin_bit_mask = (1<<cspin);
	ESP_ERROR_CHECK(gpio_config(&gpioConfig));		
	gpio_set_level(cspin, 1);
	ESP_LOGI(TAG, "Touch irq %d, cs: %d init done",tirq,cspin);
	
	if (t_handle==NULL)
	{
		spi_device_interface_config_t dev_config={			
		.clock_speed_hz   = 1000000,
		.spics_io_num     =  -1, //cspin,
		.mode = 0,                                //SPI mode 0
		.flags            = 0,
		.queue_size       = 2,
		};
		ESP_LOGI(TAG, "... Adding touch spi bus  cs: %d,  Speed= %d.",cspin,dev_config.clock_speed_hz);
		ESP_ERROR_CHECK(spi_bus_add_device(spi_no, &dev_config, &t_handle)); 
		ESP_LOGI(TAG, "... Added touch spi bus  cs: %d,  Speed= %d.",cspin,dev_config.clock_speed_hz);		
	}
	isrPinptr = ts;
	
	if (255 != tirq) {
		ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_IRAM));
		ESP_LOGI(TAG, "gpio_install_isr_service done");
		ESP_ERROR_CHECK(gpio_isr_handler_add(tirq, isrPin, NULL));
		ESP_LOGI(TAG, "gpio_isr_handler_add done");
	}
	return ts;	
}

 void isrPin( void* ts )
{
	XPT2046_Touchscreen *o = isrPinptr;
	o->isrWake = true;
}

//TS_Point* getPoint(XPT2046_Touchscreen* ts )
void getPoint(XPT2046_Touchscreen* ts,TS_Point* tp )
{
	update(ts);
	tp->x = ts->xraw;
	tp->y = ts->yraw;
	tp->z = ts->zraw;
}

bool touched(XPT2046_Touchscreen* ts)
{
	update(ts);
	return (ts->zraw >= Z_THRESHOLD);
}

void readData(XPT2046_Touchscreen* ts,uint16_t *x, uint16_t *y, uint16_t *z)
{
	update(ts);
    *x = ts->xraw;
	*y = ts->yraw;
	*z = ts->zraw;
}

bool bufferEmpty(XPT2046_Touchscreen* ts)
{
	return ((millis() - ts->msraw) < MSEC_THRESHOLD);
}

static int16_t besttwoavg( int16_t x , int16_t y , int16_t z ) {
  int16_t da, db, dc;
  int16_t reta = 0;
  if ( x > y ) da = x - y; else da = y - x;
  if ( x > z ) db = x - z; else db = z - x;
  if ( z > y ) dc = z - y; else dc = y - z;

  if ( da <= db && da <= dc ) reta = (x + y) >> 1;
  else if ( db <= da && db <= dc ) reta = (x + z) >> 1;
  else reta = (y + z) >> 1;   //    else if ( dc <= da && dc <= db ) reta = (x + y) >> 1;

  return (reta);
}

void update(XPT2046_Touchscreen* ts)
{
	int16_t data[6];

	uint32_t now = millis();
//	ESP_LOGI(TAG, "update: isrWake:%d, now:%d, msraw:%d,(now - ts->msraw < MSEC_THRESHOLD):%d", ts->isrWake,now,ts->msraw,(now - ts->msraw < MSEC_THRESHOLD)); 
	if (!ts->isrWake) return;
	else
	{
		ESP_LOGI(TAG, "update: isrWake on");
		ts->isrWake = false;
		return;
	}
		
	if ((now - ts->msraw) < MSEC_THRESHOLD) return;
	gpio_intr_disable(ts->tirq);
	gpio_set_level(ts->csPin, 0);

	int16_t z1 = transfer16(0xB0 /* Z1 */);      //ask and store  Z1 value
	int16_t z2 = transfer16(0xC0 /* Z2 */) ;      //ask for Z2
	int z = z1 + 4095;
//	int16_t z2 = transfer16(0x91 /* X */) ;       //ask for X
	z -= z2;
	if (z >= Z_THRESHOLD) {
		data[0] = transfer16(0x90 ) ; //X
		data[1] = transfer16(0xd0 ) ; //Y  // make 3 x-y measurements
		data[2] = transfer16(0x90 ) ; //X
		data[3] = transfer16(0xd0 ) ; //Y
	}
	else data[0] = data[1] = data[2] = data[3] = 0;	// Compiler warns these values may be used unset on early exit.
	data[4] = transfer16(0x90 ) ;	//X   // Last Y touch power down
	data[5] = transfer16(0xd0) ; //Y
//	transfer16(00);

	gpio_set_level(ts->csPin, 1);
	gpio_intr_enable(ts->tirq);
	if (z < 0) z = 0;
	if (z < Z_THRESHOLD) { //	if ( !touched ) {
		ts->zraw = 0;
		if (z < Z_THRESHOLD_INT) { //	if ( !touched ) {
			ts->isrWake = false;
		}
		return;
	}
	ts->zraw = z;
	
	// Average pair with least distance between each measured x then y
	int16_t x = besttwoavg( data[0], data[2], data[4] );
	int16_t y = besttwoavg( data[1], data[3], data[5] );
	
	if (z >= Z_THRESHOLD) {
		ts->msraw = now;	// good read completed, set wait
          if (ts->alpha_x) {           //if calibration parameters have been defined,
                                   //calculate pixel coordinates
               ts->xraw = ts->alpha_x * x + ts->beta_x * y + ts->delta_x;
               ts->yraw = ts->alpha_y * x + ts->beta_y * y + ts->delta_y;
               if (ts->displ_rot) {    //and if the screen has been rotated
                    uint16_t rot_x = 0;
                    uint16_t rot_y = 0;
                                   //calculate pixel positions for rotated screen
                    if (ts->displ_rot == 1) {
                         rot_x = ts->yraw;
                         rot_y = ts->displ_height - ts->xraw;
                    }
                    else if (ts->displ_rot == 2) {
                         rot_x = ts->displ_width - ts->xraw;
                         rot_y = ts->displ_height - ts->yraw;
                    }
                    else if (ts->displ_rot == 3) {
                         rot_x = ts->displ_width - ts->yraw;
                         rot_y = ts->xraw;
                    }
                    ts->xraw = rot_x;
                    ts->yraw = rot_y;
               }
          }
          else {
     		ts->xraw = x;
     		ts->yraw = y;
          }
	}

}

void calibrate(XPT2046_Touchscreen* ts,float ax, float bx, int16_t dx, float ay, float by, int16_t dy, uint16_t dwidth, uint16_t dheight, uint8_t drot) { 
     ts->alpha_x = ax;
     ts->beta_x = bx;
     ts->delta_x = dx;
     ts->alpha_y = ay;
     ts->beta_y = by;
     ts->delta_y = dy;
     ts->displ_width = dwidth;
     ts->displ_height = dheight;
     ts->displ_rot = drot;
}