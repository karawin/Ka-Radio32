

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
  ucg_SetFontMode(&ucg, UCG_FONT_MODE_SOLID);
  ucg_SetFont(&ucg, ucg_font_ncenB24_hf);

  
  /*
  ucg_SetColor(&ucg, 0, 255, 180, 40);
  ucg_DrawGlyph(&ucg, 64, 32,0, 'A');
  ucg_SetColor(&ucg, 0, 255, 200, 70);
  ucg_DrawGlyph(&ucg, 64, 32,1, 'A');
  ucg_SetColor(&ucg, 0, 255, 180, 40);
  ucg_DrawGlyph(&ucg, 64, 32,2, 'A');
  ucg_SetColor(&ucg, 0, 255, 200, 70);
  ucg_DrawGlyph(&ucg, 64, 32,3, 'A');
  */
  
  ucg_SetColor(&ucg, 1, 0, 0, 255);
  ucg_SetColor(&ucg, 0, 255, 180, 40);
  ucg_DrawString(&ucg, 64, 32,0, "AB");
  ucg_SetColor(&ucg, 0, 255, 200, 70);
  ucg_DrawString(&ucg, 64, 32,1, "AB");
  ucg_SetColor(&ucg, 0, 255, 180, 40);
  ucg_DrawString(&ucg, 64, 32,2, "AB");
  ucg_SetColor(&ucg, 0, 255, 200, 70);
  ucg_DrawString(&ucg, 64, 32,3, "AB");

  ucg_SetColor(&ucg, 0, 128, 128, 255);
  ucg_DrawPixel(&ucg, 64, 32);

  //ucg_DrawHLine(&ucg, 0,64,20);
  

  while( ucg_sdl_get_key() < 0 )
    ;
    
  
  return 0;
}

