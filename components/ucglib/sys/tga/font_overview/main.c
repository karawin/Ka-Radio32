/*
  
  this will generate a picture of a single font.
  not required with the new font format

*/

#include "ucg.h"
#include <stdlib.h>
#include <stdio.h>


extern const ucg_fntpgm_uint8_t ucg_font_7x13_tf[] UCG_FONT_SECTION("ucg_font_7x13") ;
extern const ucg_fntpgm_uint8_t ucg_font[] UCG_FONT_SECTION("ucg_font") ;

/*
void pic_gen_short_desc(const u8g_pgm_uint8_t *font, const char *name, u8g_uint_t width, const char *real_name)
{
  char s[256];
  u8g_t u8g;
  u8g_Init(&u8g, &u8g_dev_pbm);
    u8g_SetFont(&u8g, font);
  
  if ( u8g_IsGlyph(&u8g, 'a') != 0 )
    sprintf(s, "%s: 123 ABC abcdefg", name);
  else
    sprintf(s, "0123456789");
    
  u8g_FirstPage(&u8g);
  do
  {
    u8g_SetFont(&u8g, font);
    u8g_DrawStr(&u8g, 0, 100, s);    
  }while( u8g_NextPage(&u8g) );
  
  {
    char cmd[256];
    u8g_SetFont(&u8g, font);
    sprintf(cmd, "convert u8g.pbm -trim %s_short.png", name );
    system(cmd);
  }
}
*/

void pic_gen_font(const ucg_pgm_uint8_t *font, const char *name )
{
  //ucg_int_t width;
  char s[256];
  const ucg_pgm_uint8_t *disp_font;
  uint16_t i;
  ucg_int_t x,y,w,h, hcnt, disp_line_height, disp_line_indent;
  uint8_t start, end;
  //ucg_int_t indent;
  ucg_t ucg;
  
  //pic_gen_short_desc(font, name, width, real_name);
  
  
  tga_init(1024,800);
  ucg_Init(&ucg, ucg_dev_tga, ucg_ext_none, (ucg_com_fnptr)0);
  
  disp_font = ucg_font_7x13_tf;
  
  disp_line_height = 14;
  disp_line_indent = 75;
  
  start = ucg_font_GetFontStartEncoding(font);
  end = ucg_font_GetFontEndEncoding(font);
  
  ucg_SetFont(&ucg, font);
  /*
  hcnt = ucg_GetWidth(&ucg);
  hcnt /= ucg_GetFontBBXWidth(&ucg);
  hcnt -= 4;
  */
  
  //w = ucg_GetFontBBXWidth(&ucg)+2;
  w = ucg_GetGlyphWidth(&ucg, 'W') + 3;
  if ( w < ucg_GetGlyphWidth(&ucg, '3') + 3 )
    w = ucg_GetGlyphWidth(&ucg, '3') + 3;
    //w = width;
  h = ucg_GetFontBBXHeight(&ucg);
  if ( h < disp_line_height )
    h = disp_line_height ;

  sprintf(s, "%s", name);
  
  ucg_SetFont(&ucg, disp_font);
  ucg_DrawString(&ucg, 0, disp_line_height, 0, s);
  
  ucg_SetFont(&ucg, font);
  sprintf(s, "BBX Width %d, Height %d,  Capital A %d", 
      ucg_GetFontBBXWidth(&ucg), 
      ucg_GetFontBBXHeight(&ucg), 
      ucg_GetFontCapitalAHeight(&ucg));
  
  
  ucg_SetFont(&ucg, disp_font);    
  ucg_DrawString(&ucg, 0, disp_line_height*2, 0, s);

  
  sprintf(s, "Font data size: %d", ucg_font_GetSize(font));
  ucg_DrawString(&ucg, 0, disp_line_height*3, 0, s);

  hcnt = 16;
  i = start - start % hcnt;
  for( y = 0; y < 16; y++ )
  {
    ucg_SetFont(&ucg, disp_font);
    if ( i <= end )
    {
      sprintf(s, "%3d/0x%02x", i, i);
      ucg_DrawString(&ucg, 0, y*h+disp_line_height*3+h, 0, s);
    }
    
    for( x = 0; x < hcnt; x++ )
    {
      if ( i <= end )
      {
	ucg_SetFont(&ucg, font);
	ucg_DrawGlyph(&ucg, x*w+disp_line_indent, y*h+disp_line_height*3+h, 0, i);
	i++;
      }
    }
  }

  tga_save("ucg_font.tga");

  {
    char cmd[256];
    sprintf(cmd, "convert ucg_font.tga -trim ucg_font.png");
    system(cmd);
  }
}



unsigned char bitmap[2] = { 0x0f0, 0x0f0 };

int main(int argc, char **argv)
{
  ucg_int_t i;
  char *name = "";
  if ( argc <= 1 )
  {
    printf("%s <fonttitle>\n", argv[0]);
    return 0;
  }
  name = argv[1];
  
  
  tga_init(128,64);
  pic_gen_font(ucg_font, name);
  /*
  ucg_Init(&ucg, &ucg_dev_tga, (ucg_com_fnptr)0);
  ucg_SetFont(&ucg, u8g_font_7x13);
  
  ucg_SetColor(&ucg, 0, 0, 0, 0255);
  ucg_DrawPixel(&ucg, 70,20);
  ucg_SetColor(&ucg, 0, 255, 0, 0);
 
  //ucg_SetFontPosBottom(&ucg);
  
  ucg_DrawGlyph(&ucg, 70, 20, 0, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 1, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 2, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 3, 'A');
  */

    
  
  return 0;
}

