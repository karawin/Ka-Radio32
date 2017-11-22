

#include "ucg.h"
#include <stdlib.h>
#include <stdio.h>


int ucg_sdl_get_key(void);

//extern const ucg_fntpgm_uint8_t ucg_font_ncenB18[] UCG_FONT_SECTION("ucg_font_ncenB18");
//extern const u8g_fntpgm_uint8_t u8g_font_ncenB18[] U8G_FONT_SECTION("u8g_font_ncenB18");

ucg_t ucg;


int main(void)
{
  
  ucg_Init(&ucg, &ucg_sdl_dev_cb, ucg_ext_none, (ucg_com_fnptr)0);
  ucg_SetFontMode(&ucg, UCG_FONT_MODE_TRANSPARENT);
  ucg_SetFont(&ucg, ucg_font_9x15_67_75);
  ucg_SetColor(&ucg, 0, 255, 180, 40);
  
  ucg_DrawGlyph(&ucg, 20,20, 0, 'A');
  ucg_SetScale2x2(&ucg);

  ucg_DrawHLine(&ucg, 1,1,11);
  ucg_DrawVLine(&ucg, 1,1,11);

  ucg_SetColor(&ucg, 0,  0, 255, 0);
  ucg_SetColor(&ucg, 1,  255, 255, 0);
  ucg_SetColor(&ucg, 2, 0, 0, 255);
  ucg_SetColor(&ucg, 3, 	255, 0, 0);
  ucg_DrawGradientBox(&ucg, 2, 2, 10, 10);
  
  ucg_SetColor(&ucg, 0,  255, 255, 0);
  //ucg_DrawPixel(&ucg,7,20);
  //ucg_DrawPixel(&ucg,20,20);
  ucg_SetColor(&ucg, 0, 255, 180, 40);
  
  /*
  ucg_DrawTransparentGlyph(&ucg, 20,20, 0, 'A');
  ucg_DrawTransparentGlyph(&ucg, 20,20, 1, 'A');
  ucg_DrawTransparentGlyph(&ucg, 20,20, 2, 'A');
  ucg_DrawTransparentGlyph(&ucg, 20,20, 3, 'A');
  */
  ucg_SetFontMode(&ucg, UCG_FONT_MODE_SOLID);
  /*
  ucg_DrawSolidGlyph(&ucg, 20,20, 0, 'A');
  ucg_DrawSolidGlyph(&ucg, 20,20, 1, 'A');
  */
  ucg_DrawGlyph(&ucg, 20,20, 2, 'A');
  //ucg_DrawSolidGlyph(&ucg, 20,20, 3, 'A');

  while( ucg_sdl_get_key() < 0 )
    ;
    
  
  return 0;
}

