

#include "ucg.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


extern const ucg_fntpgm_uint8_t *ucg_font_array[];
extern char *ucg_font_name[];



void pic_gen_short_desc(const ucg_pgm_uint8_t *font, const char *fname)
{
  char s[256];
  ucg_t ucg;
  ucg_int_t dx;

  tga_init(1024,500);
  ucg_Init(&ucg, ucg_dev_tga, ucg_ext_none, (ucg_com_fnptr)0);

  ucg_SetFont(&ucg, font);
  ucg_SetFontPosTop(&ucg);
  ucg_SetColor(&ucg, 0, 0, 0, 0);
  
  if ( ucg_IsGlyph(&ucg, 'a') != 0 )
    sprintf(s, "123 ABC abcdefg");
  else
    sprintf(s, "0123456789");

  dx = ucg_DrawString(&ucg, 0, 2, 0, s);

  ucg_SetFont(&ucg, ucg_font_7x13_tf);    
  ucg_DrawString(&ucg, dx+7, 2, 0, fname);
  
  
   tga_save("ucg_font.tga");

  {
    char cmd[256];
    sprintf(cmd, "convert ucg_font.tga -trim %s_short.png", fname);
    system(cmd);
  }
}

void pic_gen_font(const ucg_pgm_uint8_t *font, const char *name, const char *fname )
{
  //ucg_int_t width;
  char s[256];
  const ucg_pgm_uint8_t *disp_font;
  int bbx_mode;
  uint16_t i;
  ucg_int_t x,y,w,h, hcnt, disp_line_height, disp_line_indent;
  ucg_int_t  last_y;
  uint8_t start, end;
  //ucg_int_t indent;
  ucg_t ucg;
  
  pic_gen_short_desc(font, fname);
  
  
  tga_init(1200,1200);
  ucg_Init(&ucg, ucg_dev_tga, ucg_ext_none, (ucg_com_fnptr)0);
  
  disp_font = ucg_font_7x13_tf;
  
  disp_line_height = 14;
  disp_line_indent = 75;
  
  start = ucg_font_GetFontStartEncoding(font);
  end = ucg_font_GetFontEndEncoding(font);
  
  ucg_SetFont(&ucg, font);
  ucg_SetColor(&ucg, 0, 0, 0, 0);
  /*
  hcnt = ucg_GetWidth(&ucg);
  hcnt /= ucg_GetFontBBXWidth(&ucg);
  hcnt -= 4;
  */
  
  //w = ucg_GetFontBBXWidth(&ucg)+2;
  w = ucg_GetGlyphWidth(&ucg, 'W') + 3;
  if ( w < ucg_GetGlyphWidth(&ucg, '0') + 3 )
    w = ucg_GetGlyphWidth(&ucg, '0') + 3;
  if ( w < ucg_GetGlyphWidth(&ucg, ' ') + 3 )
    w = ucg_GetGlyphWidth(&ucg, ' ') + 3;
  if ( w < ucg_GetGlyphWidth(&ucg, ' ') + 3 )
    w = ucg_GetGlyphWidth(&ucg, ' ') + 3;
  if ( w < ucg_GetGlyphWidth(&ucg, '8') + 3 )
    w = ucg_GetGlyphWidth(&ucg, '8') + 3;
  if ( w < ucg_GetGlyphWidth(&ucg, 71) + 3 )
    w = ucg_GetGlyphWidth(&ucg, 71) + 3;
  
  printf("%s w=%d encoding: %d..%d\n", fname, w, (int)start, (int)end);
 
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
  bbx_mode = ucg.font_info.bbx_mode;
  
  ucg_SetFont(&ucg, disp_font);    
  ucg_DrawString(&ucg, 0, disp_line_height*2, 0, s);

  
  sprintf(s, "Font data size %d, build mode %d", ucg_font_GetSize(font), bbx_mode );
  ucg_DrawString(&ucg, 0, disp_line_height*3, 0, s);

  hcnt = 16;
  i = start - start % hcnt;
  last_y = 0;
  for( y = 0; y < 16; y++ )
  {
    ucg_SetFont(&ucg, disp_font);
    if ( i <= end )
    {
      sprintf(s, "%3d/0x%02x", i, i);
      ucg_DrawString(&ucg, 0, y*h+disp_line_height*3+h, 0, s);
      last_y = y;
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

  if ( start <= 'A' && end >= 'z' )
  {
    ucg_SetFont(&ucg, font);
    ucg_DrawString(&ucg, 0, (last_y+1)*h+disp_line_height*3+h, 0, "Woven silk pyjamas exchanged for blue quartz.");
  }
  tga_save("ucg_font.tga");

  {
    char cmd[256];
    sprintf(cmd, "convert ucg_font.tga -trim %s.png", fname);
    system(cmd);
  }
}


const char *get_grp_name(const char *fontname)
{
  if ( strstr(fontname, "p01t") != NULL ) return "fontgroupfontstruct";
  if ( strstr(fontname, "baby") != NULL ) return "fontgroupfontstruct";
  if ( strstr(fontname, "blip") != NULL ) return "fontgroupfontstruct";
  if ( strstr(fontname, "cpc") != NULL ) return "fontgroupfontstruct";
  if ( strstr(fontname, "chik") != NULL ) return "fontgroupfontstruct";
  if ( strstr(fontname, "pixel") != NULL ) return "fontgroupfontstruct";
  if ( strstr(fontname, "trix") != NULL ) return "fontgroupfontstruct";
  if ( strstr(fontname, "robot") != NULL ) return "fontgroupfontstruct";
  if ( strstr(fontname, "lucas") != NULL ) return "fontgroupfontstruct";
  if ( strstr(fontname, "u8glib_4") != NULL ) return "fontgroupu8g";
  if ( strstr(fontname, "m2i") != NULL ) return "fontgroupu8g";
  if ( strstr(fontname, "04b") != NULL ) return "fontgroup04";
  if ( strstr(fontname, "4x6") != NULL ) return "fontgroupx11";
  if ( strstr(fontname, "micro") != NULL ) return "fontgroupx11";
  if ( strstr(fontname, "5x7") != NULL ) return "fontgroupx11";
  if ( strstr(fontname, "5x8") != NULL ) return "fontgroupx11";
  if ( strstr(fontname, "6x10") != NULL ) return "fontgroupx11";
  if ( strstr(fontname, "6x12") != NULL ) return "fontgroupx11";
  if ( strstr(fontname, "6x13") != NULL ) return "fontgroupx11";
  if ( strstr(fontname, "7x13") != NULL ) return "fontgroupx11";
  if ( strstr(fontname, "7x14") != NULL ) return "fontgroupx11";
  if ( strstr(fontname, "8x13") != NULL ) return "fontgroupx11";
  if ( strstr(fontname, "9x15") != NULL ) return "fontgroupx11";
  if ( strstr(fontname, "9x18") != NULL ) return "fontgroupx11";
  if ( strstr(fontname, "10x20") != NULL ) return "fontgroupx11";
  if ( strstr(fontname, "cursor") != NULL ) return "fontgroupx11";
  if ( strstr(fontname, "org") != NULL ) return "fontgrouporgdot";
  if ( strstr(fontname, "tps") != NULL ) return "fontgrouporgdot";
  if ( strstr(fontname, "fixed_v0") != NULL ) return "fontgrouporgdot";
  if ( strstr(fontname, "profont") != NULL ) return "fontgroupprofont";
  if ( strstr(fontname, "_cour") != NULL ) return "fontgroupadobex11";
  if ( strstr(fontname, "_sym") != NULL ) return "fontgroupadobex11";
  if ( strstr(fontname, "_tim") != NULL ) return "fontgroupadobex11";
  if ( strstr(fontname, "_helv") != NULL ) return "fontgroupadobex11";
  if ( strstr(fontname, "_ncen") != NULL ) return "fontgroupadobex11";
  if ( strstr(fontname, "_freed") != NULL ) return "fontgroupcontributed";
  if ( strstr(fontname, "_unifont") != NULL ) return "fontgroupunifont";
  if ( strstr(fontname, "_cu12") != NULL ) return "fontgroupcu12";
  if ( strstr(fontname, "_fub") != NULL ) return "fontgroupfreeuniversal";
  if ( strstr(fontname, "_fur") != NULL ) return "fontgroupfreeuniversal";
  if ( strstr(fontname, "_logi") != NULL ) return "fontgrouplogisoso";
  if ( strstr(fontname, "_osr") != NULL ) return "fontgroupoldstandard";
  if ( strstr(fontname, "_osb") != NULL ) return "fontgroupoldstandard";
  if ( strstr(fontname, "_inr") != NULL ) return "fontgroupinconsolata";
  if ( strstr(fontname, "_inb") != NULL ) return "fontgroupinconsolata";
  
  return "<unknown>";
}


unsigned char bitmap[2] = { 0x0f0, 0x0f0 };

int main(int argc, char **argv)
{
  const char *grp_name;
  int i, a;
  FILE *wiki;
  i = 0;
  for(;;)
  {
    if ( ucg_font_array[i] == NULL )
    {
      if ( ucg_font_name[i] != NULL )
      {
	fprintf(stderr, "font pointer do not match font name, do_combine wrong?\n");
  
      }
      break;
    }
    
    printf("Processing Font %d '%s'\n", i, ucg_font_name[i]);
    // if ( strstr(ucg_font_name[i], "m2i") != NULL )
    pic_gen_font(ucg_font_array[i], ucg_font_name[i], ucg_font_name[i]);
    
    i++;
  }
  
  wiki = fopen("fontsize.md", "w");
  fprintf(wiki, "# All Ucglib Fonts, Captial A Height\n\n");
  for( a = 4;  a < 65; a++ )
  {
    ucg_t ucg;
    int cnt;
    tga_init(100, 100);
    ucg_Init(&ucg, ucg_dev_tga, ucg_ext_none, (ucg_com_fnptr)0);
    
    i = 0;
    cnt = 0;
    for(;;)
    {
      if ( ucg_font_array[i] == NULL )
      {
	break;
      }
      ucg_SetFont(&ucg, ucg_font_array[i]);
      if ( ucg_GetFontCapitalAHeight(&ucg) == a )
	cnt++;
      i++;
    }
    printf("a=%d cnt=%d\n", a, cnt);

    if ( cnt > 0 )
    {
      i = 0;
      fprintf(wiki, "## %d Pixel Height\n",a); 
      for(;;)
      {
	if ( ucg_font_array[i] == NULL )
	{
	  break;
	}
	ucg_SetFont(&ucg, ucg_font_array[i]);
	if ( ucg_GetFontCapitalAHeight(&ucg) == a )
	{
	  //fprintf(wiki, "[http://wiki.ucglib.googlecode.com/hg/font/%s_short.png]\n",ucg_font_name[i]); 
	  fprintf(wiki, "![font/%s_short.png](font/%s_short.png)\n",ucg_font_name[i],ucg_font_name[i]);
	  grp_name = get_grp_name(ucg_font_name[i]);
	  fprintf(wiki, "[%s](%s)\n\n",grp_name, grp_name);
	  
	}
	i++;
      }
    }
  }
  fclose(wiki);
  
  wiki = fopen("fontmono.md", "w");
  fprintf(wiki, "# Ucglib Monospace Fonts, Captial A Height\n\n");
  for( a = 4;  a < 65; a++ )
  {
    ucg_t ucg;
    int cnt;
    tga_init(100, 100);
    ucg_Init(&ucg, ucg_dev_tga, ucg_ext_none, (ucg_com_fnptr)0);
    
    i = 0;
    cnt = 0;
    for(;;)
    {
      if ( ucg_font_array[i] == NULL )
      {
	break;
      }
      ucg_SetFont(&ucg, ucg_font_array[i]);
      if ( ucg_GetFontCapitalAHeight(&ucg) == a && ucg.font_info.bbx_mode >= 2 )
	cnt++;
      i++;
    }
    printf("a=%d cnt=%d\n", a, cnt);

    if ( cnt > 0 )
    {
      i = 0;
      fprintf(wiki, "## %d Pixel Height\n",a); 
      for(;;)
      {
	if ( ucg_font_array[i] == NULL )
	{
	  break;
	}
	ucg_SetFont(&ucg, ucg_font_array[i]);
	if ( ucg_GetFontCapitalAHeight(&ucg) == a && ucg.font_info.bbx_mode >= 2 )
	{
	  //fprintf(wiki, "[http://wiki.ucglib.googlecode.com/hg/font/%s_short.png]\n",ucg_font_name[i]); 
	  fprintf(wiki, "![font/%s_short.png](font/%s_short.png)\n",ucg_font_name[i],ucg_font_name[i]);
	  grp_name = get_grp_name(ucg_font_name[i]);
	  fprintf(wiki, "[%s](%s)\n\n",grp_name, grp_name);
	  
	}
	i++;
      }
    }
  }
  fclose(wiki);
  
  return 0;
}

