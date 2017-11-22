

#include "ucg.h"
#include <stdlib.h>
#include <stdio.h>


//extern const ucg_fntpgm_uint8_t ucg_font_ncenB18[] UCG_FONT_SECTION("ucg_font_ncenB18");
//extern const u8g_fntpgm_uint8_t u8g_font_ncenB18[] U8G_FONT_SECTION("u8g_font_ncenB18");

ucg_t ucg;



unsigned char bitmap[2] = { 0x0f0, 0x0f0 };

int main(void)
{
  ucg_int_t i;
  
  tga_init(128,64);
  ucg_Init(&ucg, &ucg_dev_tga, ucg_ext_none, (ucg_com_fnptr)0);
  ucg_SetFont(&ucg, ucg_font_ncenB18);
  
  ucg_SetColor(&ucg, 0, 0, 0, 255);
  ucg_DrawPixel(&ucg, 70,20);
  ucg_SetColor(&ucg, 0, 255, 0, 0);
 
  //ucg_SetFontPosBottom(&ucg);
  
  ucg_DrawGlyph(&ucg, 70, 20, 0, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 1, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 2, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 3, 'A');

  
  ucg_DrawBitmapLine(&ucg, 9,0, 0,16, bitmap);
  ucg_DrawBitmapLine(&ucg, 10,1, 0,16, bitmap);
  
  ucg_DrawBitmapLine(&ucg, 0,9, 1,16, bitmap);
  ucg_DrawBitmapLine(&ucg, 1,10, 1,16, bitmap);
  
  for( i = 0; i < ucg_GetWidth(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, i, 30);
  for( i = 0; i < ucg_GetHeight(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, 30, i);
 
  ucg_SetClipRange(&ucg, 10, 10, 25, 25);

  ucg_SetColor(&ucg, 0, 0, 255, 0);
  for( i = 1; i < ucg_GetWidth(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, i, 30);
  for( i = 1; i < ucg_GetHeight(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, 30, i);

  ucg_SetColor(&ucg, 0, 80, 80, 255);

  
  ucg_DrawHLine(&ucg, 8, 9, 5);
  ucg_DrawHLine(&ucg, 8, 10, 5);
  ucg_DrawHLine(&ucg, 8, 11, 5);
  ucg_DrawHLine(&ucg, 8, 12, 100);

  ucg_DrawHLine(&ucg, 12, 13, 5);
  ucg_DrawHLine(&ucg, 12, 14, 100);

  ucg_DrawHLine(&ucg, 2, 15, 5);
  ucg_DrawHLine(&ucg, 40, 16, 5);

  ucg_DrawHRLine(&ucg, 12, 17, 1);
  ucg_DrawHRLine(&ucg, 12, 18, 2);
  ucg_DrawHRLine(&ucg, 12, 19, 3);
  ucg_DrawHRLine(&ucg, 12, 20, 4);

  ucg_DrawHRLine(&ucg, 36, 17, 1);
  ucg_DrawHRLine(&ucg, 36, 18, 2);
  ucg_DrawHRLine(&ucg, 36, 19, 3);
  ucg_DrawHRLine(&ucg, 36, 20, 4);

  ucg_DrawBitmapLine(&ucg, 9,22, 0,16, bitmap);
  ucg_DrawBitmapLine(&ucg, 10,23, 0,16, bitmap);

/*
  ucg_SetClipRange(&ucg, 70-9, 20-9, 20, 20);

  ucg_DrawGlyph(&ucg, 70, 20, 0, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 1, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 2, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 3, 'A');
*/

  ucg_SetMaxClipRange(&ucg);
  ucg_SetColor(&ucg, 0, 255, 0, 0);
  ucg_SetColor(&ucg, 1, 0, 255, 0);
  
  ucg_SetColor(&ucg, 0, 255, 0, 0);
  ucg_SetColor(&ucg, 1, 0, 255, 0);
  ucg_SetColor(&ucg, 2, 255, 0, 255);
  ucg_SetColor(&ucg, 3, 0, 255, 255);

  ucg_DrawGradientLine(&ucg, 10, 40, 100, 0);

  ucg_DrawGradientBox(&ucg, 10, 43, 100, 20);


  tga_save("test.tga");
    
  
  return 0;
}

