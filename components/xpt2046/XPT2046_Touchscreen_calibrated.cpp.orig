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

#include "XPT2046_Touchscreen_calibrated.h"

#define Z_THRESHOLD     400
#define Z_THRESHOLD_INT	75
#define MSEC_THRESHOLD  3
#define SPI_SETTING     SPISettings(2000000, MSBFIRST, SPI_MODE0)

XPT2046_Touchscreen::XPT2046_Touchscreen(uint8_t cs, uint8_t tirq)
{
	csPin = cs;
	tirqPin = tirq;
	msraw = 0x80000000;
	xraw = 0;
	yraw = 0;
	zraw = 0;
	isrWake = true;
}

static XPT2046_Touchscreen 	*isrPinptr;
void isrPin(void);

bool XPT2046_Touchscreen::begin()
{
	SPI.begin();
	pinMode(csPin, OUTPUT);
	digitalWrite(csPin, HIGH);
	if (255 != tirqPin) {
		pinMode( tirqPin, INPUT );
		attachInterrupt( tirqPin, isrPin, FALLING );
		isrPinptr = this;
	}
	return true;
}

void isrPin( void )
{
	XPT2046_Touchscreen *o = isrPinptr;
	o->isrWake = true;
}

TS_Point XPT2046_Touchscreen::getPoint()
{
	update();
	return TS_Point(xraw, yraw, zraw);
}

bool XPT2046_Touchscreen::touched()
{
	update();
	return (zraw >= Z_THRESHOLD);
}

void XPT2046_Touchscreen::readData(uint16_t *x, uint16_t *y, uint8_t *z)
{
	update();
     *x = xraw;
	*y = yraw;
	*z = zraw;
}

bool XPT2046_Touchscreen::bufferEmpty()
{
	return ((millis() - msraw) < MSEC_THRESHOLD);
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

void XPT2046_Touchscreen::update()
{
	int16_t data[6];

	if (!isrWake) return;
	uint32_t now = millis();
	if (now - msraw < MSEC_THRESHOLD) return;
	
	SPI.beginTransaction(SPI_SETTING);
	digitalWrite(csPin, LOW);
	SPI.transfer(0xB1 /* Z1 */);      //ask for Z1 value
	int16_t z1 = SPI.transfer16(0xC1 /* Z2 */) >> 3;      //store Z1 value, ask for Z2
	int z = z1 + 4095;
	int16_t z2 = SPI.transfer16(0x91 /* X */) >> 3;       //store Z2 value, ask for X
	z -= z2;
	if (z >= Z_THRESHOLD) {
		data[0] = SPI.transfer16(0xD1 /* Y */) >> 3;
		data[1] = SPI.transfer16(0x91 /* X */) >> 3; // make 3 x-y measurements
		data[2] = SPI.transfer16(0xD1 /* Y */) >> 3;
		data[3] = SPI.transfer16(0x91 /* X */) >> 3;
	}
	else data[0] = data[1] = data[2] = data[3] = 0;	// Compiler warns these values may be used unset on early exit.
	data[4] = SPI.transfer16(0xD0 /* Y */) >> 3;	// Last Y touch power down
	data[5] = SPI.transfer16(0) >> 3;
	digitalWrite(csPin, HIGH);
	SPI.endTransaction();
	if (z < 0) z = 0;
	if (z < Z_THRESHOLD) { //	if ( !touched ) {
		zraw = 0;
		if (z < Z_THRESHOLD_INT) { //	if ( !touched ) {
			if (255 != tirqPin) isrWake = false;
		}
		return;
	}
	zraw = z;
	
	// Average pair with least distance between each measured x then y
	int16_t x = besttwoavg( data[0], data[2], data[4] );
	int16_t y = besttwoavg( data[1], data[3], data[5] );
	
	if (z >= Z_THRESHOLD) {
		msraw = now;	// good read completed, set wait
          if (alpha_x) {           //if calibration parameters have been defined,
                                   //calculate pixel coordinates
               xraw = alpha_x * x + beta_x * y + delta_x;
               yraw = alpha_y * x + beta_y * y + delta_y;
               if (displ_rot) {    //and if the screen has been rotated
                    uint16_t rot_x;
                    uint16_t rot_y;
                                   //calculate pixel positions for rotated screen
                    if (displ_rot == 1) {
                         rot_x = yraw;
                         rot_y = displ_height - xraw;
                    }
                    else if (displ_rot == 2) {
                         rot_x = displ_width - xraw;
                         rot_y = displ_height - yraw;
                    }
                    else if (displ_rot == 3) {
                         rot_x = displ_width - yraw;
                         rot_y = xraw;
                    }
                    xraw = rot_x;
                    yraw = rot_y;
               }
          }
          else {
     		xraw = x;
     		yraw = y;
          }
	}
}

void XPT2046_Touchscreen::calibrate(float ax, float bx, int16_t dx, float ay, float by, int16_t dy, uint16_t dwidth, uint16_t dheight, uint8_t drot) { 
     alpha_x = ax;
     beta_x = bx;
     delta_x = dx;
     alpha_y = ay;
     beta_y = by;
     delta_y = dy;
     displ_width = dwidth;
     displ_height = dheight;
     displ_rot = drot;
}