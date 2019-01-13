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

#ifndef _XPT2046_Touchscreen_h_
#define _XPT2046_Touchscreen_h_
//my adaptation. Comment for a generic product
#define KaRadio32 

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/i2c.h"

#ifdef __cplusplus
class TS_Point {
public:
	TS_Point(void) : x(0), y(0), z(0) {}
	TS_Point(int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z) {}
	bool operator==(TS_Point p) { return ((p.x == x) && (p.y == y) && (p.z == z)); }
	bool operator!=(TS_Point p) { return ((p.x != x) || (p.y != y) || (p.z != z)); }
	int16_t x, y, z;
};
#else
typedef
	struct {
		int16_t x, y, z;
	}	TS_Point;
	
	TS_Point* TS_Point_init(int16_t x,int16_t y,int16_t z) ;
	bool isTpEqual(TS_Point* a,TS_Point* b);
	bool isTpDiff(TS_Point* a,TS_Point* b);
#endif
	
#ifdef __cplusplus	
class XPT2046_Touchscreen {
public:
	XPT2046_Touchscreen();
	bool begin(spi_host_device_t spi_num, gpio_num_t  cspin, gpio_num_t  tirq=(gpio_num_t)255);
	TS_Point getPoint();
	bool touched();
	void readData(uint16_t *x, uint16_t *y, uint8_t *z);
	bool bufferEmpty();
	uint8_t bufferSize() { return 1; }
     void calibrate(float ax, float bx, int16_t dx, float ay, float by, int16_t dy, uint16_t dwidth, uint16_t dheight, uint8_t drot=0);
// protected:
	bool isrWake;

private:
	void update();
	uint8_t displ_rot;
	int16_t xraw, yraw, zraw, delta_x, delta_y, displ_width, displ_height;
	uint32_t msraw;
     float alpha_x, beta_x, alpha_y, beta_y;
};

#else
typedef
    struct {
		bool isrWake ;
		spi_device_handle_t t_handle; // SPI handle of the spi touch interface.
		gpio_num_t  csPin, tirqPin;
		spi_host_device_t spi_no;
		uint8_t displ_rot, tirq;
		int16_t xraw, yraw, zraw, delta_x, delta_y, displ_width, displ_height;
		uint32_t msraw;
		float alpha_x, beta_x, alpha_y, beta_y;				
	}  XPT2046_Touchscreen;	

XPT2046_Touchscreen* XPT2046_Touchscreen_init(spi_host_device_t spi_num, gpio_num_t  cspin, gpio_num_t  tirq);
void getPoint(XPT2046_Touchscreen* ts,TS_Point* tp );
bool touched(XPT2046_Touchscreen* ts);
void readData(XPT2046_Touchscreen* ts,uint16_t *x, uint16_t *y, uint16_t *z);
bool bufferEmpty(XPT2046_Touchscreen* ts);
//void update(XPT2046_Touchscreen* ts);
void calibrate(XPT2046_Touchscreen* ts,float ax, float bx, int16_t dx, float ay, float by, int16_t dy, uint16_t dwidth, uint16_t dheight, uint8_t drot);	
#endif

#endif
