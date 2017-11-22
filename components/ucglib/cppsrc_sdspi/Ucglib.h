/*

  Ucglib.h

  ucglib = universal color graphics library
  ucglib = micro controller graphics library
  
  Universal uC Color Graphics Library
  
  Copyright (c) 2014, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of s_t ource code must retain the above copyright notice, this list 
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
  
  Ucglib8BitPortD 
      Arduino AVR boards only
      
  Ucglib8Bit
      All Arduino boards
      
  Ucglib4WireSWSPI
      All Arduino boards
  
  Ucglib4WireHWSPI
      All Arduino boards with SPI library
  
*/

#ifndef _UCGLIB_HH
#define _UCGLIB_HH

#include <Arduino.h>
#include <Print.h>

#ifndef USE_PIN_LIST
#define USE_PIN_LIST
#endif

#include "ucg.h"


// Do not use Ucglib class directly, use Ucglib8Bit or Ucglib4WireSPI instead
class Ucglib : public Print
{
  protected:
    ucg_t ucg;
    ucg_dev_fnptr dev_cb;
    ucg_dev_fnptr ext_cb;  
  private:
    ucg_int_t tx, ty;          // current position for the Print base class procedures
    uint8_t tdir;
  protected:
    uint8_t& get_tdir(void) { return tdir; };
    ucg_int_t& get_tx(void) { return tx; };
    ucg_int_t& get_ty(void) { return ty; };
    ucg_t *get_ucg(void) { return &ucg; };
    void init(void);
  public:
    Ucglib(void) { init(); }
    Ucglib(ucg_dev_fnptr dev, ucg_dev_fnptr ext = ucg_ext_none) { init(); dev_cb = dev; ext_cb = ext; }

    void setPrintPos(ucg_int_t x, ucg_int_t y) { tx = x; ty = y; }
    void setPrintDir(uint8_t dir) { tdir = dir; }
    size_t write(uint8_t c);
    ucg_t *getUcg(void) { return &ucg; }
    
    ucg_int_t getWidth(void) { return ucg_GetWidth(&ucg); }
    ucg_int_t getHeight(void) { return ucg_GetHeight(&ucg); }
    
    
    void setFontRefHeightText(void) 	{ ucg_SetFontRefHeightText(&ucg); }
    void setFontRefHeightExtendedText(void) { ucg_SetFontRefHeightExtendedText(&ucg); }
    void setFontRefHeightAll(void) 	{ ucg_SetFontRefHeightAll(&ucg); }

    void setFontPosBaseline(void) 	{ ucg_SetFontPosBaseline(&ucg); }
    void setFontPosBottom(void) 	{ ucg_SetFontPosBottom(&ucg); }
    void setFontPosTop(void) 		{ ucg_SetFontPosTop(&ucg); }
    void setFontPosCenter(void) 	{ ucg_SetFontPosCenter(&ucg); }
    
    void setFont(const ucg_fntpgm_uint8_t  *font)
      { ucg_SetFont(&ucg, font); }
    void setFontMode(ucg_font_mode_fnptr font_mode) 
      { ucg_SetFontMode(&ucg, font_mode); }
    ucg_int_t getFontAscent(void)
      { return ucg_GetFontAscent(&ucg); }
    ucg_int_t getFontDescent(void)
      { return ucg_GetFontDescent(&ucg); }
    ucg_int_t getStrWidth(const char *s)
      { return ucg_GetStrWidth(&ucg, s); }
    
    void setColor(uint8_t idx, uint8_t r, uint8_t g, uint8_t b)
      { ucg_SetColor(&ucg, idx, r, g, b); }
    void setColor(uint8_t r, uint8_t g, uint8_t b)
      { ucg_SetColor(&ucg, 0, r, g, b); }

      
    void undoRotate(void) { ucg_UndoRotate(&ucg); }
    void setRotate90(void) { ucg_SetRotate90(&ucg); }
    void setRotate180(void) { ucg_SetRotate180(&ucg); }
    void setRotate270(void) { ucg_SetRotate270(&ucg); }

    void undoScale(void) { ucg_UndoScale(&ucg); }
    void setScale2x2(void) { ucg_SetScale2x2(&ucg); }
    
    // Procedures, which are always available as part of the BASIC drawing procedure set
      
    void setClipRange(ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h) { ucg_SetClipRange(&ucg, x,y,w,h); }
    void setMaxClipRange(void) { ucg_SetMaxClipRange(&ucg); }
    void undoClipRange(void) { ucg_SetMaxClipRange(&ucg); }

    void drawPixel(ucg_int_t x, ucg_int_t y) { ucg_DrawPixel(&ucg, x, y); }    
    void drawHLine(ucg_int_t x, ucg_int_t y, ucg_int_t len) { ucg_DrawHLine(&ucg, x, y, len); }
    void drawVLine(ucg_int_t x, ucg_int_t y, ucg_int_t len) { ucg_DrawVLine(&ucg, x, y, len); }
    void drawLine(ucg_int_t x1, ucg_int_t y1, ucg_int_t x2, ucg_int_t y2) { ucg_DrawLine(&ucg, x1, y1, x2, y2); }

    ucg_int_t drawGlyph(ucg_int_t x, ucg_int_t y, uint8_t dir, uint8_t encoding) { return ucg_DrawGlyph(&ucg, x, y, dir, encoding); }
    ucg_int_t drawString(ucg_int_t x, ucg_int_t y, uint8_t dir, const char *str) { return ucg_DrawString(&ucg, x, y, dir, str); }
    
    void drawBox(ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h) { ucg_DrawBox(&ucg, x, y, w, h); }
    void clearScreen(void) { ucg_ClearScreen(&ucg); }
    void drawRBox(ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h, ucg_int_t r) { ucg_DrawRBox(&ucg, x, y, w, h, r); }
    
    void drawFrame(ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h) { ucg_DrawFrame(&ucg, x, y, w, h); }
    void drawRFrame(ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h, ucg_int_t r) { ucg_DrawRFrame(&ucg, x, y, w, h, r); }
 
    void drawDisc(ucg_int_t x0, ucg_int_t y0, ucg_int_t rad, uint8_t option) { ucg_DrawDisc(&ucg, x0, y0, rad, option); }
    void drawCircle(ucg_int_t x0, ucg_int_t y0, ucg_int_t rad, uint8_t option) { ucg_DrawCircle(&ucg, x0, y0, rad, option); }

    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2) { ucg_DrawTriangle(&ucg, x0, y0, x1, y1, x2, y2); }
    /* the polygon procedure only works for convex tetragons (http://en.wikipedia.org/wiki/Convex_polygon) */
    void drawTetragon(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3) { ucg_DrawTetragon(&ucg, x0, y0, x1, y1, x2, y2, x3, y3); }
    
    // Procedures, which are only available with the EXTENDED option
    
    void drawGradientLine(ucg_int_t x, ucg_int_t y, ucg_int_t len, ucg_int_t dir) {ucg_DrawGradientLine(&ucg, x, y, len, dir); }
    void drawGradientBox(ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h) { ucg_DrawGradientBox(&ucg, x, y, w, h); }
};

class Ucglib4WireSWSPI : public Ucglib
{
  public:
    Ucglib4WireSWSPI(ucg_dev_fnptr dev, ucg_dev_fnptr ext, uint8_t scl, uint8_t sda, uint8_t cd, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE)
      { init(); dev_cb = dev; ext_cb = ext; 

	  ucg.pin_list[UCG_PIN_SCL] = scl; 	
	  ucg.pin_list[UCG_PIN_SDA] = sda; 
	  //ucg.data_port[UCG_PIN_RST] =  portOutputRegister(digitalPinToPort(reset));
	  //ucg.data_mask[UCG_PIN_RST] =  digitalPinToBitMask(reset);
	  ucg.pin_list[UCG_PIN_RST] = reset; 
	  //ucg.data_port[UCG_PIN_CD] =  portOutputRegister(digitalPinToPort(cd));
	  //ucg.data_mask[UCG_PIN_CD] =  digitalPinToBitMask(cd);
	  ucg.pin_list[UCG_PIN_CD] = cd;
	  //ucg.data_port[UCG_PIN_CS] =  portOutputRegister(digitalPinToPort(cs));
	  //ucg.data_mask[UCG_PIN_CS] =  digitalPinToBitMask(cs);
	  ucg.pin_list[UCG_PIN_CS] = cs; }
    void begin(ucg_font_mode_fnptr font_mode);
};

class Ucglib3WireILI9325SWSPI : public Ucglib
{
  public:
    Ucglib3WireILI9325SWSPI(ucg_dev_fnptr dev, ucg_dev_fnptr ext, uint8_t scl, uint8_t sda, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE)
      { init(); dev_cb = dev; ext_cb = ext; 

	  ucg.pin_list[UCG_PIN_SCL] = scl; 	
	  ucg.pin_list[UCG_PIN_SDA] = sda; 
	  ucg.pin_list[UCG_PIN_RST] = reset; 
	  ucg.pin_list[UCG_PIN_CS] = cs; }
    void begin(ucg_font_mode_fnptr font_mode);
};

class Ucglib3Wire9bitSWSPI : public Ucglib
{
  public:
    Ucglib3Wire9bitSWSPI(ucg_dev_fnptr dev, ucg_dev_fnptr ext, uint8_t scl, uint8_t sda, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE)
      { init(); dev_cb = dev; ext_cb = ext; 

	  ucg.pin_list[UCG_PIN_SCL] = scl; 	
	  ucg.pin_list[UCG_PIN_SDA] = sda; 
	  ucg.pin_list[UCG_PIN_RST] = reset; 
	  ucg.pin_list[UCG_PIN_CS] = cs; }
    void begin(ucg_font_mode_fnptr font_mode);
};

class Ucglib4WireHWSPI : public Ucglib
{
  public:
    Ucglib4WireHWSPI(ucg_dev_fnptr dev, ucg_dev_fnptr ext, uint8_t cd, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE)
      { init(); dev_cb = dev; ext_cb = ext; 

	ucg.pin_list[UCG_PIN_RST] = reset; 
	ucg.pin_list[UCG_PIN_CD] = cd;
	ucg.pin_list[UCG_PIN_CS] = cs; 

#ifdef __AVR__	
	  ucg.data_port[UCG_PIN_RST] =  portOutputRegister(digitalPinToPort(reset));
	  ucg.data_mask[UCG_PIN_RST] =  digitalPinToBitMask(reset);
	  ucg.data_port[UCG_PIN_CD] =  portOutputRegister(digitalPinToPort(cd));
	  ucg.data_mask[UCG_PIN_CD] =  digitalPinToBitMask(cd);
	  ucg.data_port[UCG_PIN_CS] =  portOutputRegister(digitalPinToPort(cs));
	  ucg.data_mask[UCG_PIN_CS] =  digitalPinToBitMask(cs);
#endif
    }
    void begin(ucg_font_mode_fnptr font_mode);
};

class Ucglib3Wire9bitHWSPI : public Ucglib
{
  public:
    Ucglib3Wire9bitHWSPI(ucg_dev_fnptr dev, ucg_dev_fnptr ext, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE)
      { init(); dev_cb = dev; ext_cb = ext; 

	  ucg.pin_list[UCG_PIN_RST] = reset; 
	  ucg.pin_list[UCG_PIN_CS] = cs; }
    void begin(ucg_font_mode_fnptr font_mode);
};


#ifdef __AVR__	
class Ucglib8BitPortD : public Ucglib
{
  public:
    Ucglib8BitPortD(ucg_dev_fnptr dev, ucg_dev_fnptr ext, uint8_t wr, uint8_t cd, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE)
      { init(); dev_cb = dev; ext_cb = ext; 
	  ucg.pin_list[UCG_PIN_RST] = reset;
	  ucg.pin_list[UCG_PIN_CD] = cd;
	  ucg.pin_list[UCG_PIN_CS] = cs;
	  ucg.pin_list[UCG_PIN_WR] = wr; 
	  ucg.data_port[UCG_PIN_RST] =  portOutputRegister(digitalPinToPort(reset));
	  ucg.data_mask[UCG_PIN_RST] =  digitalPinToBitMask(reset);
	  ucg.data_port[UCG_PIN_CD] =  portOutputRegister(digitalPinToPort(cd));
	  ucg.data_mask[UCG_PIN_CD] =  digitalPinToBitMask(cd);
	  ucg.data_port[UCG_PIN_CS] =  portOutputRegister(digitalPinToPort(cs));
	  ucg.data_mask[UCG_PIN_CS] =  digitalPinToBitMask(cs);
	  ucg.data_port[UCG_PIN_WR] =  portOutputRegister(digitalPinToPort(wr));
	  ucg.data_mask[UCG_PIN_WR] =  digitalPinToBitMask(wr);
    }
    void begin(ucg_font_mode_fnptr font_mode);
};
#endif

class Ucglib8Bit : public Ucglib
{
  public:
    Ucglib8Bit(ucg_dev_fnptr dev, ucg_dev_fnptr ext, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t wr, uint8_t cd, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE)
      { init(); dev_cb = dev; ext_cb = ext; 
	  //ucg.data_port[UCG_PIN_RST] =  portOutputRegister(digitalPinToPort(reset));
	  //ucg.data_mask[UCG_PIN_RST] =  digitalPinToBitMask(reset);
	  ucg.pin_list[UCG_PIN_RST] = reset;
	  //ucg.data_port[UCG_PIN_CD] =  portOutputRegister(digitalPinToPort(cd));
	  //ucg.data_mask[UCG_PIN_CD] =  digitalPinToBitMask(cd);
	  ucg.pin_list[UCG_PIN_CD] = cd;
	  //ucg.data_port[UCG_PIN_CS] =  portOutputRegister(digitalPinToPort(cs));
	  //ucg.data_mask[UCG_PIN_CS] =  digitalPinToBitMask(cs);
	  ucg.pin_list[UCG_PIN_CS] = cs;
	  //ucg.data_port[UCG_PIN_WR] =  portOutputRegister(digitalPinToPort(wr));
	  //ucg.data_mask[UCG_PIN_WR] =  digitalPinToBitMask(wr);
	  ucg.pin_list[UCG_PIN_WR] = wr; 
	  ucg.pin_list[UCG_PIN_D0] = d0;
	  ucg.pin_list[UCG_PIN_D1] = d1;
	  ucg.pin_list[UCG_PIN_D2] = d2;
	  ucg.pin_list[UCG_PIN_D3] = d3;
	  ucg.pin_list[UCG_PIN_D4] = d4;
	  ucg.pin_list[UCG_PIN_D5] = d5;
	  ucg.pin_list[UCG_PIN_D6] = d6;
	  ucg.pin_list[UCG_PIN_D7] = d7; }
    void begin(ucg_font_mode_fnptr font_mode);
};

class Ucglib_ST7735_18x128x160_HWSPI : public Ucglib4WireHWSPI
{
  public:
  Ucglib_ST7735_18x128x160_HWSPI( uint8_t cd, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE) : 
    Ucglib4WireHWSPI(ucg_dev_st7735_18x128x160, ucg_ext_st7735_18, /*cd=*/ cd , /*cs=*/ cs, /*reset=*/ reset)
    { }
};

class Ucglib_ST7735_18x128x160_SWSPI : public Ucglib4WireSWSPI
{
  public:
  Ucglib_ST7735_18x128x160_SWSPI( uint8_t scl, uint8_t sda, uint8_t cd, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE) : 
    Ucglib4WireSWSPI(ucg_dev_st7735_18x128x160, ucg_ext_st7735_18, /*scl=*/ scl, /*sda=*/ sda, /*cd=*/ cd , /*cs=*/ cs, /*reset=*/ reset)
    { }
};

class Ucglib_ILI9341_18x240x320_HWSPI : public Ucglib4WireHWSPI
{
  public:
  Ucglib_ILI9341_18x240x320_HWSPI( uint8_t cd, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE) : 
    Ucglib4WireHWSPI(ucg_dev_ili9341_18x240x320, ucg_ext_ili9341_18, /*cd=*/ cd , /*cs=*/ cs, /*reset=*/ reset)
    { }
};

class Ucglib_ILI9341_18x240x320_SWSPI : public Ucglib4WireSWSPI
{
  public:
  Ucglib_ILI9341_18x240x320_SWSPI( uint8_t scl, uint8_t sda, uint8_t cd, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE) : 
    Ucglib4WireSWSPI(ucg_dev_ili9341_18x240x320, ucg_ext_ili9341_18, /*scl=*/ scl, /*sda=*/ sda, /*cd=*/ cd , /*cs=*/ cs, /*reset=*/ reset)
    { }
};

class Ucglib_SSD1351_18x128x128_HWSPI : public Ucglib4WireHWSPI
{
  public:
  Ucglib_SSD1351_18x128x128_HWSPI( uint8_t cd, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE) : 
    Ucglib4WireHWSPI(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*cd=*/ cd , /*cs=*/ cs, /*reset=*/ reset)
    { }
};

class Ucglib_SSD1351_18x128x128_SWSPI : public Ucglib4WireSWSPI
{
  public:
  Ucglib_SSD1351_18x128x128_SWSPI( uint8_t scl, uint8_t sda, uint8_t cd, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE) : 
    Ucglib4WireSWSPI(ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, /*scl=*/ scl, /*sda=*/ sda, /*cd=*/ cd , /*cs=*/ cs, /*reset=*/ reset)
    { }
};


class Ucglib_SSD1351_18x128x128_FT_HWSPI : public Ucglib4WireHWSPI
{
  public:
  Ucglib_SSD1351_18x128x128_FT_HWSPI( uint8_t cd, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE) : 
    Ucglib4WireHWSPI(ucg_dev_ssd1351_18x128x128_ft, ucg_ext_ssd1351_18, /*cd=*/ cd , /*cs=*/ cs, /*reset=*/ reset)
    { }
};

class Ucglib_SSD1351_18x128x128_FT_SWSPI : public Ucglib4WireSWSPI
{
  public:
  Ucglib_SSD1351_18x128x128_FT_SWSPI( uint8_t scl, uint8_t sda, uint8_t cd, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE) : 
    Ucglib4WireSWSPI(ucg_dev_ssd1351_18x128x128_ft, ucg_ext_ssd1351_18, /*scl=*/ scl, /*sda=*/ sda, /*cd=*/ cd , /*cs=*/ cs, /*reset=*/ reset)
    { }
};


class Ucglib_PCF8833_16x132x132_HWSPI : public Ucglib3Wire9bitHWSPI
{
  public:
  Ucglib_PCF8833_16x132x132_HWSPI( uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE) : 
    Ucglib3Wire9bitHWSPI(ucg_dev_pcf8833_16x132x132, ucg_ext_pcf8833_16, /*cs=*/ cs, /*reset=*/ reset)
    { }
};


class Ucglib_PCF8833_16x132x132_SWSPI : public Ucglib3Wire9bitSWSPI
{
  public:
  Ucglib_PCF8833_16x132x132_SWSPI( uint8_t scl, uint8_t sda, uint8_t cs = UCG_PIN_VAL_NONE, uint8_t reset = UCG_PIN_VAL_NONE) : 
    Ucglib3Wire9bitSWSPI(ucg_dev_pcf8833_16x132x132, ucg_ext_pcf8833_16, /*scl=*/ scl, /*sda=*/ sda, /*cs=*/ cs, /*reset=*/ reset)
    { }
};


#endif /* _UCGLIB_HH */
