/*

  HowToUseFonts.ino
  
  A demonstration on how to use the different types of fonts.
  The following fonts will be used:
    ucg_font_helvB08_hr
    ucg_font_helvB08_tr
    ucg_font_amstrad_cpc_8r
  Good and bad examples are shown.

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
uint32_t lcg_rnd(void) {
  z = (uint8_t)((uint16_t)65*(uint16_t)z + (uint16_t)17);
  return (uint32_t)z;
}


void setup(void)
{
  delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);

  ucg.setColor(0, 120, 0, 0);
  ucg.setColor(2, 0, 120, 0);
  ucg.setColor(1, 120, 0, 120);
  ucg.setColor(3, 0, 120, 120);

  ucg.drawGradientBox(0, 0, ucg.getWidth(), ucg.getHeight());
}

void loop(void)
{
  // get a random value between 0 and 255
  uint8_t rnd = lcg_rnd();
  ucg_int_t y = 0;
  ucg_int_t h = 14;


  // You can not overwrite the previous number with a transparent font
  y += h;
  ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setPrintPos(4,y);
  ucg.setFont(ucg_font_helvB08_tr);
  ucg.print("Does not work:");
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_helvB08_tr);
  ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  ucg.setPrintPos(80,y);
  ucg.print(rnd);

  // Using the same transparent font in solid mode works better,
  // but still some pixel are not overwritten
  y += h;
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setPrintPos(4,y);
  ucg.setFont(ucg_font_helvB08_tr);
  ucg.print("Pixel errors:");
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(ucg_font_helvB08_tr);
  ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  ucg.setColor(1, 64, 64, 255);			// use blue as background for SOLID mode
  ucg.setPrintPos(80,y);
  ucg.print(rnd);

  // Using the "h" or "m" type of font in solid mode will almost work
  // however, if the number changes from 100 to 99, the last number 
  // will not be overwritten.
  y += h;
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setPrintPos(4,y);
  ucg.setFont(ucg_font_helvB08_tr);
  ucg.print("Value errors:");
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(ucg_font_helvB08_hr);
  ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  ucg.setColor(1, 64, 64, 255);			// use blue as background for SOLID mode
  ucg.setPrintPos(80,y);
  ucg.print(rnd);

  // Using the "h" or "m" type of font in solid mode will work fine, if
  // there are extra spaced after the string to overwrite the previous value.
  // As long as a "h" font is used, the number of spaces is not fixed.
  // This means, even two spaced my not be sufficent. Better use a monospace font.
  y += h;
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setPrintPos(4,y);
  ucg.setFont(ucg_font_helvB08_tr);
  ucg.print("Almost ok:");
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(ucg_font_helvB08_hr);
  ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  ucg.setColor(1, 64, 64, 255);			// use blue as background for SOLID mode
  ucg.setPrintPos(80,y);
  ucg.print(rnd);
  ucg.print("  ");  // two extra spaces (not sufficient here)

  // The transparent font and mode can be used, if the previous content
  // is fully erased or overwritten
  y += h;
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setPrintPos(4,y);
  ucg.setFont(ucg_font_helvB08_tr);
  ucg.print("Manual erase:");  
  ucg.setColor(0, 255, 40, 80);
  ucg.setColor(1, 0, 255, 0);
  ucg.setColor(2, 255, 0, 0);
  ucg.setColor(3, 65, 255, 40);
  ucg.drawGradientBox(80-2, y-10, 22, 12);  // red to green bar will erase the previous value
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_helvB08_tr);
  ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  ucg.setPrintPos(80,y);
  ucg.print(rnd);

  // The is will use the solid font with the extra spaces to erase the previous value
  // A monospaced 8x8 pixel font is used (here: ucg_font_amstrad_cpc_8r).
  y += h;
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setPrintPos(4,y);
  ucg.setFont(ucg_font_helvB08_tr);
  ucg.print("8x8 font:");
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(ucg_font_amstrad_cpc_8r);
  ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  ucg.setColor(1, 64, 64, 255);			// use blue as background for SOLID mode
  ucg.setPrintPos(80,y);
  ucg.print(rnd);
  ucg.print("  ");  // extra spaces

  // The is will use the solid font with the extra spaces to erase the previous value
  // Any monospaced font can be used (here: ucg_font_7x13_mr).
  y += h;
  ucg.setFontMode(UCG_FONT_MODE_TRANSPARENT);
  ucg.setPrintPos(4,y);
  ucg.setFont(ucg_font_helvB08_tr);
  ucg.print("_mr font:");
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(ucg_font_7x13_mr);
  ucg.setColor(0, 255, 255, 255);		// use white as main color for the font
  ucg.setColor(1, 64, 64, 255);			// use blue as background for SOLID mode
  ucg.setPrintPos(80,y);
  ucg.print(rnd);
  ucg.print("  ");  // extra spaces


  delay(100);  
}