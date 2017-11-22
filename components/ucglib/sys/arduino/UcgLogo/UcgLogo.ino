/*

  UcgLogo.ino
  
  Draw the Ucglib Logo

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


void upper_pin(ucg_t *ucg, ucg_int_t x, ucg_int_t y)
{
  ucg_int_t w = 7;
  ucg_int_t h = 6;
  ucg_SetColor(ucg, 0, 212, 212, 212);
  ucg_SetColor(ucg, 1, 200, 200, 200);
  ucg_SetColor(ucg, 2, 200, 200, 200);
  ucg_SetColor(ucg, 3, 188, 188, 188);
  ucg_DrawGradientBox(ucg, x, y, w, h);

  //ucg_DrawVLine(ucg, x+w, y+1, len);
  ucg_SetColor(ucg, 0, 220, 220, 220);
  ucg_SetColor(ucg, 1, 232, 232, 232);
  ucg_DrawGradientLine(ucg, x+w, y, h, 1);
}

void lower_pin(ucg_t *ucg, ucg_int_t x, ucg_int_t y)
{
  ucg_int_t w = 7;
  ucg_int_t h = 5;
  ucg_SetColor(ucg, 0, 212, 212, 212);
  ucg_SetColor(ucg, 1, 200, 200, 200);
  ucg_SetColor(ucg, 2, 200, 200, 200);
  ucg_SetColor(ucg, 3, 188, 188, 188);
  ucg_DrawGradientBox(ucg, x, y, w, h);

  //ucg_DrawVLine(ucg, x+w, y+1, len);
  ucg_SetColor(ucg, 0, 220, 220, 220);
  ucg_SetColor(ucg, 1, 232, 232, 232);
  ucg_DrawGradientLine(ucg, x+w, y, h, 1);
  ucg_SetColor(ucg, 0, 220, 220, 220);
  ucg_SetColor(ucg, 1, 232, 232, 232);
  ucg_DrawGradientLine(ucg, x, y+h, w, 0);
  ucg_SetColor(ucg, 0, 240, 240, 240);
  ucg_DrawPixel(ucg, x+w, y+h);
}

void ic_body(ucg_t *ucg, ucg_int_t x, ucg_int_t y)
{
  ucg_int_t w = 4*14+4;
  ucg_int_t h = 31;
  ucg_SetColor(ucg, 0, 60, 60, 60);
  ucg_SetColor(ucg, 1, 40, 40, 40);
  ucg_SetColor(ucg, 2, 48, 48, 48);
  ucg_SetColor(ucg, 3, 30, 30, 30);
  ucg_DrawGradientBox(ucg, x, y, w, h);
  
  ucg_SetColor(ucg, 0, 255, 168, 0);
  //ucg_SetColor(ucg, 0, 225, 168, 30);
  ucg_DrawDisc(ucg, x+w-1, y+h/2-1, 7, UCG_DRAW_UPPER_LEFT|UCG_DRAW_LOWER_LEFT);

  ucg_SetColor(ucg, 0, 60, 30, 0);
  //ucg_DrawDisc(ucg, x+w-1, y+h/2+1, 7, UCG_DRAW_UPPER_LEFT|UCG_DRAW_LOWER_LEFT);

  ucg_SetColor(ucg, 0, 50, 50, 50);
  ucg_SetColor(ucg, 0, 25, 25, 25);
  ucg_DrawDisc(ucg, x+w-1, y+h/2+1, 7, UCG_DRAW_UPPER_LEFT|UCG_DRAW_LOWER_LEFT);
  
  
}


void draw_ucg_logo(ucg_t *ucg)
{
  ucg_int_t a,b;
  
  //ucg_Init(ucg, ucg_sdl_dev_cb, ucg_ext_none, (ucg_com_fnptr)0);
  ucg_SetFont(ucg, ucg_font_ncenB24_tr);  
  
  //ucg_SetRotate270(ucg);  
  //ucg_SetClipRange(ucg, 10,5,40,20);


  
  a = 2;
  b = 3;
  
  ucg_SetColor(ucg, 0, 135*a/b,206*a/b,250*a/b);
  ucg_SetColor(ucg, 1, 176*a/b,226*a/b,255*a/b);
  ucg_SetColor(ucg, 2, 25*a/b,25*a/b,112*a/b);
  ucg_SetColor(ucg, 3, 	85*a/b,26*a/b,139*a/b);
  ucg_DrawGradientBox(ucg, 0, 0, ucg_GetWidth(ucg)/4, ucg_GetHeight(ucg));

  ucg_SetColor(ucg, 1, 135*a/b,206*a/b,250*a/b);
  ucg_SetColor(ucg, 0, 176*a/b,226*a/b,255*a/b);
  ucg_SetColor(ucg, 3, 25*a/b,25*a/b,112*a/b);
  ucg_SetColor(ucg, 2, 	85*a/b,26*a/b,139*a/b);
  ucg_DrawGradientBox(ucg, ucg_GetWidth(ucg)/4, 0, ucg_GetWidth(ucg)/4, ucg_GetHeight(ucg));

  ucg_SetColor(ucg, 0, 135*a/b,206*a/b,250*a/b);
  ucg_SetColor(ucg, 1, 176*a/b,226*a/b,255*a/b);
  ucg_SetColor(ucg, 2, 25*a/b,25*a/b,112*a/b);
  ucg_SetColor(ucg, 3, 	85*a/b,26*a/b,139*a/b);
  ucg_DrawGradientBox(ucg, ucg_GetWidth(ucg)*2/4, 0, ucg_GetWidth(ucg)/4, ucg_GetHeight(ucg));

  ucg_SetColor(ucg, 1, 135*a/b,206*a/b,250*a/b);
  ucg_SetColor(ucg, 0, 176*a/b,226*a/b,255*a/b);
  ucg_SetColor(ucg, 3, 25*a/b,25*a/b,112*a/b);
  ucg_SetColor(ucg, 2, 	85*a/b,26*a/b,139*a/b);
  ucg_DrawGradientBox(ucg, ucg_GetWidth(ucg)*3/4, 0, ucg_GetWidth(ucg)/4, ucg_GetHeight(ucg));
  
  
  upper_pin(ucg, 7+0*14, 4);
  upper_pin(ucg, 7+1*14, 4);
  upper_pin(ucg, 7+2*14, 4);
  upper_pin(ucg, 7+3*14, 4);
  
  ic_body(ucg, 2, 10);

  lower_pin(ucg, 7+0*14, 41);
  lower_pin(ucg, 7+1*14, 41);
  lower_pin(ucg, 7+2*14, 41);
  lower_pin(ucg, 7+3*14, 41);

  ucg_SetColor(ucg, 0, 135*a/b, 206*a/b, 250*a/b);
  ucg_DrawString(ucg, 63+1, 33+1, 0, "glib");

  ucg_SetColor(ucg, 0, 255, 168, 0);
  ucg_DrawGlyph(ucg, 26, 38, 0, 'U');
  ucg_DrawString(ucg, 63, 33, 0, "glib");

  ucg_SetColor(ucg, 0, 135*a/b, 206*a/b, 250*a/b);
  ucg_SetColor(ucg, 1, 135*a/b, 206*a/b, 250*a/b);
  ucg_SetColor(ucg, 2, 135*a/b, 206*a/b, 250*a/b);
  ucg_SetColor(ucg, 3, 135*a/b, 206*a/b, 250*a/b);
  ucg_DrawGradientBox(ucg, 84+1, 42+1-6, 42, 4);

  ucg_SetColor(ucg, 0, 255, 180, 40);
  ucg_SetColor(ucg, 1, 235, 148, 0);
  //ucg_DrawGradientLine(ucg, 79, 42, 20, 0);
  ucg_SetColor(ucg, 2, 245, 158, 0);
  ucg_SetColor(ucg, 3, 220, 138, 0);
  ucg_DrawGradientBox(ucg, 84, 42-6, 42, 4);

  ucg_SetColor(ucg, 0, 255, 168, 0);
  //ucg_SetFont(ucg, ucg_font_5x8_tr);
  ucg_SetFont(ucg, ucg_font_7x13B_tr);
  //ucg_SetFont(ucg, ucg_font_courB08_tr);
  //ucg_SetFont(ucg, ucg_font_timR08_tr);
  ucg_DrawString(ucg, 2, 54+5, 0, "http://github.com");
  ucg_DrawString(ucg, 2, 61+10, 0, "/olikraus/ucglib");
  //ucg_DrawString(ucg, 1, 61, 0, "code.google.com/p/ucglib/");
  


}



void setup(void)
{
  delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.clearScreen();
}



void loop(void)
{
  ucg.setRotate180();
  draw_ucg_logo(ucg.getUcg());
  for(;;)
    ;
}

