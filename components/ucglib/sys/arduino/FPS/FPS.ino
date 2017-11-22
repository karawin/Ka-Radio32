/*

  FPS.ino
  
  Do some speed measurements.

  Universal uC Color Graphics Library
  
  Copyright (c) 2014, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  

  1 Feb 2014
  SSD1351, Arduino Due, HW SPI	Text: 13.2  	Box: 28.6		Gradient: 17.9
  SSD1351, Arduino Due, SW SPI	Text: 11.1  	Box: 17.3		Gradient: 12.9		1 May 2014: this has been reduced to get better signal quality
  SSD1351, Arduino Uno, HW SPI	Text:  2.6  	Box: 12.8		Gradient:  4.6
  SSD1351, Arduino Uno, SW SPI	Text:  1.6  	Box:  3.4		Gradient:  2.2

  8 Feb 2014
  SSD1351, Arduino Uno, HW SPI	Text:  5.0  	Box: 15.2		Gradient:  5.3
  SSD1351, Arduino Uno, SW SPI	Text:  2.7  	Box:  3.4		Gradient:  2.2
  ILI9325, Arduino Uno, Port D		Text:  5.8		Box: 17.5		Gradient:  5.5
  ILI9341, Arduino Due, SW SPI		Text: 10.6		Box: 16.5		Gradient: 12.9		1 May 2014: this has been reduced to get better signal quality
  
  28 Feb 2014
  PCF8833, Arduino Uno, HW SPI	Text:  3.3  	Box: 5.6		Gradient:  3.2
  PCF8833, Arduino Due, SW SPI	Text:  1.3  	Box: 1.3		Gradient:  1.2  (display errors)
  
  27 Apr 2014, Issue 14 (SW SPI improvement)
  ST7735, Arduino Uno, SW SPI		Text:  2.2  	Box: 3.4		Gradient:  2.4
  
  1 May 2014, (SW SPI speed reduced for Due)
  ST7735, Arduino Due, SW SPI		Text:  4.9  	Box: 4.9		Gradient:  4.4

  11 Sep 2014
  ILI9341, Arduino Due, HW SPI	Text: 12.4		Box: 22.4		Gradient: 16.5	
  ILI9341, Arduino Due, SW SPI		Text: 4.7		Box: 4.7		Gradient: 4.4

  12 Sep 2014
  ILI9341, Arduino Due, HW SdSpi	Text: 13.9		Box: 30.5		Gradient: 20.2		no multibyte transfer	
  ILI9341, Arduino Due, HW SdSpi	Text: 13.9		Box: 38.0		Gradient: 19.7		with multibyte transfer	

  1 mar 2015
  LD50T6160, Arduino Due, 6Bit	Text: 6.4		Box: 13.1		Gradient: 10.5

  23 May 2015, new font procedures
  ILI9341, Arduino Uno, SW SPI		Text:  1.9  	Box: 3.4		Gradient:  2.4
  ST7735, Arduino Uno, SW SPI		Text:  2.0  	Box: 3.4		Gradient:  2.4
  ST7735, Arduino Uno, HW SPI	Text:  3.1  	Box: 13.1		Gradient:  5.3

  19 Jul 2015
  SSD1331, Arduino Uno, SW SPI	Text:  3.8  	Box: 6.3		Gradient:  4.2
  SSD1331, Arduino Uno, HW SPI	Text:  6.0  	Box: 27.3		Gradient:  8.8

  21 Jul 2015
  SEPS225, Arduino Uno, SW SPI	Text:  1.8  	Box: 4.5		Gradient:  2.7
  SEPS225, Arduino Uno, HW SPI	Text:  2.5  	Box: 14.0		Gradient:  4.9


  25 Jul 2015 (improved speed for SEPS225)
  SEPS225, Arduino Uno, SW SPI	Text:  2.6  	Box: 5.0		Gradient:  2.9
  SEPS225, Arduino Uno, HW SPI	Text:  3.8  	Box: 17.8		Gradient:  5.3
  
*/

#include <SPI.h>
#include "Ucglib.h"

/*
  Hardware SPI Pins:
    Arduino Uno		sclk=13, data=11
    Arduino Due		sclk=76, data=75
    Arduino Mega	sclk=52, data=51
    
  >>> Please uncomment (and update) one of the following constructors. <<<  
*/
//Ucglib8BitPortD ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, /* wr= */ 18 , /* cd= */ 19 , /* cs= */ 17, /* reset= */ 16 );
//Ucglib8Bit ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, 0, 1, 2, 3, 4, 5, 6, 7, /* wr= */ 18 , /* cd= */ 19 , /* cs= */ 17, /* reset= */ 16 );

//Ucglib4WireSWSPI ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, /*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	// not working
//Ucglib4WireSWSPI ucg(ucg_dev_ili9325_spi_18x240x320, ucg_ext_ili9325_spi_18, /*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	// not working
//Ucglib3WireILI9325SWSPI ucg(ucg_dev_ili9325_spi_18x240x320, ucg_ext_ili9325_spi_18, /*sclk=*/ 13, /*data=*/ 11, /*cs=*/ 10, /*reset=*/ 8);	// not working
//Ucglib3WireILI9325SWSPI ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, /*sclk=*/ 13, /*data=*/ 11, /*cs=*/ 10, /*reset=*/ 8);	// not working

//Ucglib_ST7735_18x128x160_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);

//Ucglib_ILI9163_18x128x128_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5 , /*cs=*/ 3, /*reset=*/ 4);
//Ucglib_ILI9163_18x128x128_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	/* HW SPI Adapter */

//Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5 , /*cs=*/ 3, /*reset=*/ 4);
//Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 4, /*data=*/ 3, /*cd=*/ 6 , /*cs=*/ 7, /*reset=*/ 5);	/* Elec Freaks Shield */

//Ucglib_SSD1351_18x128x128_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SSD1351_18x128x128_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SSD1351_18x128x128_FT_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SSD1351_18x128x128_FT_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);

//Ucglib_PCF8833_16x132x132_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cs=*/ 9, /*reset=*/ 8);	/* linksprite board */
//Ucglib_PCF8833_16x132x132_HWSPI ucg(/*cs=*/ 9, /*reset=*/ 8);	/* linksprite board */

//Ucglib_LD50T6160_18x160x128_6Bit ucg( /*d0 =*/ d0, /*d1 =*/ d1, /*d2 =*/ d2, /*d3 =*/ d3, /*d4 =*/ d4, /*d5 =*/ d5, /*wr=*/ wr, /*cd=*/ cd, /*cs=*/ cs, /*reset=*/ reset);
//Ucglib_LD50T6160_18x160x128_6Bit ucg( /*d0 =*/ 16, /*d1 =*/ 17, /*d2 =*/ 18, /*d3 =*/ 19, /*d4 =*/ 20, /*d5 =*/ 21, /*wr=*/ 14, /*cd=*/ 15); /* Samsung 160x128 OLED with 6Bit minimal interface with Due */ 
//Ucglib_LD50T6160_18x160x128_6Bit ucg( /*d0 =*/ 5, /*d1 =*/ 4, /*d2 =*/ 3, /*d3 =*/ 2, /*d4 =*/ 1, /*d5 =*/ 0, /*wr=*/ 7, /*cd=*/ 6); /* Samsung 160x128 OLED with 6Bit minimal interface with Uno */ 

//Ucglib_SSD1331_18x96x64_UNIVISION_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SSD1331_18x96x64_UNIVISION_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);

//Ucglib_SEPS225_16x128x128_UNIVISION_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SEPS225_16x128x128_UNIVISION_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);


void setup(void) {
  delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.setColor(0, 0,0,0);
  ucg.setColor(1, 0,0,0);
  ucg.setColor(2, 0,0,0);
  ucg.setColor(3, 0,0,0);
}

/*
  Linear Congruential Generator (LCG)
  z = (a*z + c) % m;  
  m = 256 (8 Bit)
  
  for period:
  a-1: dividable by 2
  a-1: multiple of 4
  c: not dividable by 2
  
  c = 17
  a-1 = 64 --> a = 65
*/
uint8_t z = 127;	// start value
uint8_t lcg_rnd(void) {
  z = (uint8_t)((uint16_t)65*(uint16_t)z + (uint16_t)17);
  return z;
}




void draw_text(void) {
  ucg.setFont(ucg_font_ncenR14_tr);
  //ucg.setColor(255, 255, 255);
  ucg.setColor(lcg_rnd(),lcg_rnd(),lcg_rnd());
  ucg.setPrintPos(0,20);
  ucg.print("The quick brown");
  ucg.setPrintPos(0,40);
  ucg.print("fox jumps over");
  ucg.setPrintPos(0,60);
  ucg.print("the lazy dog");
}

void draw_box(void) {
  ucg_int_t x, y, w, h;
  ucg.setColor(lcg_rnd(),lcg_rnd(),lcg_rnd());
  x = lcg_rnd() & 31;
  y = lcg_rnd() & 31;
  w = 63;
  w += lcg_rnd() & 31;
  h = 63;
  h += lcg_rnd() & 31;
  ucg.drawBox(x,y,w, h);
}

void draw_gradient_box(void) {
  ucg_int_t x, y, w, h;
  static uint8_t idx = 0;
  switch(idx & 3)
  {
    case 0: ucg.setColor(0, lcg_rnd(),lcg_rnd(),lcg_rnd()); break;
    case 1: ucg.setColor(1, lcg_rnd(),lcg_rnd(),lcg_rnd()); break;
    case 2: ucg.setColor(2, lcg_rnd(),lcg_rnd(),lcg_rnd()); break;
    case 3: ucg.setColor(3, lcg_rnd(),lcg_rnd(),lcg_rnd()); break;
  }
  idx++;
  x = lcg_rnd() & 31;
  y = lcg_rnd() & 31;
  w = 63;
  w += lcg_rnd() & 31;
  h = 63;
  h += lcg_rnd() & 31;
  ucg.drawGradientBox(x,y,w, h);
}


// returns FPS*10
uint16_t measure(void (*draw_fn)(void)) {
  uint16_t FPS10 = 0;
  uint32_t time;

  ucg.clearScreen();

  time = millis() + 10*1000;
  do {
    draw_fn();
    FPS10++;
  } while( millis() < time );
  
  return FPS10;  
}


static const unsigned char u8d_tab[3]  = { 100, 10, 1 } ;
const char *u8dp(char * dest, uint8_t v)
{
  uint8_t pos;
  uint8_t d;
  uint8_t c;
  for( pos = 0; pos < 3; pos++ )
  {
      d = '0';
      c = *(u8d_tab+pos);
      while( v >= c )
      {
	v -= c;
	d++;
      }
      dest[pos] = d;
  }  
  dest[3] = '\0';
  return dest;
}

/* v = value, d = number of digits */
const char *u8d(uint8_t v, uint8_t d)
{
  static char buf[8];
  d = 3-d;
  return u8dp(buf, v) + d;
}

const char *convert_FPS(uint16_t fps) {
  static char buf[6];
  strcpy(buf, u8d( (uint8_t)(fps/10), 3));
  buf[3] =  '.';
  buf[4] = (fps % 10) + '0';
  buf[5] = '\0';
  return buf;
}

void show_result(const char *s, uint16_t fps)  {
  ucg.clearScreen();
  ucg.setFont(ucg_font_helvR18_tr);
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(0,25);
  ucg.print(s);
  ucg.setPrintPos(0,50);
  ucg.print(convert_FPS(fps));  
  delay(2000);
}

void loop(void)
{
  show_result("Text", measure(draw_text));
  show_result("Box", measure(draw_box));
  show_result("Gradient", measure(draw_gradient_box));
  delay(500);
  
}