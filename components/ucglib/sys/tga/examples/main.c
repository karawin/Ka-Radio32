/*
  
  main.c
  
  Create example pictures for Ucglib

*/



#include "ucg.h"
#include <stdlib.h>
#include <stdio.h>



ucg_t ucg;



unsigned char bitmap[2] = { 0x0f0, 0x0f0 };

ucg_int_t rule_offset = 4;
ucg_int_t ox = 0;

void prepare_picture(ucg_t *ucg)
{
  tga_init(128,64);
  ucg_Init(ucg, &ucg_dev_tga, ucg_ext_none, (ucg_com_fnptr)0);
  ucg_SetFontMode(ucg, UCG_FONT_MODE_TRANSPARENT);
  ucg_SetMaxClipRange(ucg);
  ucg_SetColor(ucg, 0, 0, 0, 0);
  ucg_DrawBox(ucg, ox, 0, 128, 64);
}

void save_picture(ucg_t *ucg, const char *fname)
{
  tga_save("ucg_pic.tga");

  {
    char cmd[256];
    sprintf(cmd, "convert ucg_pic.tga -scale 200%% %s.png", fname);
    system(cmd);
  }
}


void prepare_measure(ucg_t *ucg)
{
  ucg_SetMaxClipRange(ucg);
  ucg_SetColor(ucg, 0, 255, 160, 63);
  ucg_SetFont(ucg, ucg_font_6x12_tf);
  ucg_SetFontMode(ucg, UCG_FONT_MODE_TRANSPARENT);
}

void pos(ucg_t *ucg, ucg_int_t x, ucg_int_t y, int is_right)
{
  char s[20];
  ucg_int_t w;
  prepare_measure(ucg);
  sprintf(s, "(%d,%d)", x-ox, y);
  w = ucg_GetStrWidth(ucg, s);
  ucg_DrawPixel(ucg, x, y);
  ucg_SetFontPosCenter(ucg);
  if (  is_right )
  {
    ucg_DrawString(ucg, x+1, y, 0, s);
    //ucg_DrawHLine(ucg, x+1, y, w);
  }
  else
  {
    ucg_DrawString(ucg, x+1-w, y, 0, s);
    //ucg_DrawHLine(ucg, x+1-w, y, w);
  }
}


void vrule(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t len, int is_right)
{
  char s[10];
  ucg_int_t o = rule_offset;
  ucg_int_t w;
  
  prepare_measure(ucg);
  sprintf(s, "%d", len);
  ucg_SetFontPosBaseline(ucg);
  w = ucg_GetStrWidth(ucg, s);
  if ( is_right )
  {
    ucg_DrawVLine(ucg, x+o, y, len);
    ucg_DrawHLine(ucg, x-1+o, y, 3);
    ucg_DrawHLine(ucg, x-1+o, y+len-1, 3);
    ucg_SetFontPosBottom(ucg);
    ucg_DrawString(ucg, x+o-1, y + len/2 - w/2 + 1, 1, s);
  }
  else
  {
    ucg_DrawVLine(ucg, x-o, y, len);
    ucg_DrawHLine(ucg, x-1-o, y, 3);
    ucg_DrawHLine(ucg, x-1-o, y+len-1, 3);
    ucg_SetFontPosBottom(ucg);
    ucg_DrawString(ucg, x-o+1, y + len - ( len/2 - w/2 + 1), 3, s);
  }
}


/*
  pos = 1 above
  pos = 0 
  pos = -1 below
*/
void hrule(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t len, int is_below)
{
  char s[10];
  ucg_int_t o = rule_offset;
  ucg_int_t w;

  if ( is_below )
  {
    ucg_SetFontPosTop(ucg);
    o  = -o;
  }
  else
  {
    ucg_SetFontPosBottom(ucg);
  }
  
  prepare_measure(ucg);
  ucg_DrawHLine(ucg, x, y-o, len);
  ucg_DrawVLine(ucg, x, y-1-o, 3);
  ucg_DrawVLine(ucg, x+len-1, y-1-o, 3);
  sprintf(s, "%d", len);
  w = ucg_GetStrWidth(ucg, s);
  ucg_DrawString(ucg, x + len/2 - w/2, y-o+1, 0, s);
}


void draw_pixel(ucg_t *ucg)
{
  prepare_picture(ucg);
  pos(ucg, ox+50, 20,0);
  ucg_SetColor(ucg, 0, 255, 255, 255);
  ucg_DrawPixel(ucg, ox+50, 20);
  save_picture(ucg, "draw_pixel");  
}

void draw_hline(ucg_t *ucg)
{
  prepare_picture(ucg);
  hrule(ucg, ox+50, 40, 45, 0);
  ucg_SetColor(ucg, 0, 255, 255, 255);
  
  ucg_DrawHLine(ucg, ox+50, 40, 45);
  pos(ucg, ox+50, 40,0);
  save_picture(ucg, "draw_hline");  
}

void draw_vline(ucg_t *ucg)
{
  prepare_picture(ucg);
  vrule(ucg, ox+50, 20, 25, 1);
  ucg_SetColor(ucg, 0, 255, 255, 255);
  ucg_DrawVLine(ucg, ox+50, 20, 25);
  pos(ucg, ox+50, 20,0);
  save_picture(ucg, "draw_vline");  
}

void set_clip_range(ucg_t *ucg)
{
  prepare_picture(ucg);
  
  ucg_SetFontPosBaseline(ucg);
  ucg_SetFont(ucg, ucg_font_ncenB18_tf);
  ucg_SetColor(ucg, 0, 255, 255, 255);		/* draw white A */
  ucg_DrawGlyph(ucg, 50, 40, 0, 'A');
  ucg_SetClipRange(ucg, 57, 20, 30, 15);	/* restrict area */
  ucg_SetColor(ucg, 0, 0, 0, 127);
  ucg_DrawBox(ucg, 0, 0, 128, 64);		/* fill the restricted area with dark blue */
  ucg_SetColor(ucg, 0, 0, 0, 255);
  ucg_DrawGlyph(ucg, 50, 40, 0, 'A');	/* draw light blue A */
  
  hrule(ucg, ox+57, 20, 30, 0);
  vrule(ucg, ox+57+30, 20, 15, 1);
  pos(ucg, ox+50, 40, 0);
  save_picture(ucg, "set_clip_range");  
}

void draw_text_baseline(ucg_t *ucg)
{
  prepare_picture(ucg);
  
  ucg_SetFont(ucg, ucg_font_ncenB18_tf);
  ucg_SetFontPosBaseline(ucg);
  ucg_SetColor(ucg, 0, 0, 0, 255);		/* draw blue "baseline" */
  ucg_DrawHLine(ucg, 45+ox, 30, ucg_GetStrWidth(ucg, "Ucg"));
  ucg_SetColor(ucg, 0, 255, 255, 255);		/* draw white "Ucg" */
  ucg_DrawString(ucg, 45+ox, 30, 0, "Ucg");
  pos(ucg, 45+ox, 30, 0);
  
  save_picture(ucg, "draw_text_baseline");  
}

void draw_text_bottom(ucg_t *ucg)
{
  prepare_picture(ucg);
  
  ucg_SetFont(ucg, ucg_font_ncenB18_tf);
  ucg_SetFontPosBottom(ucg);
  ucg_SetColor(ucg, 0, 0, 0, 255);		/* draw blue "baseline" */
  ucg_DrawHLine(ucg, 45+ox, 30, ucg_GetStrWidth(ucg, "Ucg"));
  ucg_SetColor(ucg, 0, 255, 255, 255);		/* draw white "Ucg" */
  ucg_DrawString(ucg, 45+ox, 30, 0, "Ucg");
  pos(ucg, 45+ox, 30, 0);
  
  save_picture(ucg, "draw_text_bottom");  
}

void draw_text_top(ucg_t *ucg)
{
  prepare_picture(ucg);
  
  ucg_SetFont(ucg, ucg_font_ncenB18_tf);
  ucg_SetFontPosTop(ucg);
  ucg_SetColor(ucg, 0, 0, 0, 255);		/* draw blue "baseline" */
  ucg_DrawHLine(ucg, 45+ox, 30, ucg_GetStrWidth(ucg, "Ucg"));
  ucg_SetColor(ucg, 0, 255, 255, 255);		/* draw white "Ucg" */
  ucg_DrawString(ucg, 45+ox, 30, 0, "Ucg");
  pos(ucg, 45+ox, 30, 0);
  
  save_picture(ucg, "draw_text_top");  
}

void draw_text_center(ucg_t *ucg)
{
  prepare_picture(ucg);
  
  ucg_SetFont(ucg, ucg_font_ncenB18_tf);
  ucg_SetFontPosCenter(ucg);
  ucg_SetColor(ucg, 0, 0, 0, 255);		/* draw blue "baseline" */
  ucg_DrawHLine(ucg, 45+ox, 30, ucg_GetStrWidth(ucg, "Ucg"));
  ucg_SetColor(ucg, 0, 255, 255, 255);		/* draw white "Ucg" */
  ucg_DrawString(ucg, 45+ox, 30, 0, "Ucg");
  pos(ucg, 45+ox, 30, 0);
  
  save_picture(ucg, "draw_text_center");  
}

void draw_text_ascent_descent(ucg_t *ucg)
{
  prepare_picture(ucg);
  
  ucg_SetFont(ucg, ucg_font_ncenB24_tf);
  ucg_SetFontPosBaseline(ucg);
  ucg_SetColor(ucg, 0, 0, 0, 255);		/* draw blue "baseline" */
  ucg_DrawHLine(ucg, 42+ox, 30, ucg_GetStrWidth(ucg, "Ucg"));
  ucg_SetColor(ucg, 0, 255, 255, 255);		/* draw white "Ucg" */
  ucg_DrawString(ucg, 42+ox, 30, 0, "Ucg");
  pos(ucg, 42+ox, 30, 0);
  ucg_SetFont(ucg, ucg_font_ncenB24_tf);
  vrule(ucg, 42+ox+ucg_GetStrWidth(ucg, "Ucg"), 30-ucg_GetFontAscent(ucg), ucg_GetFontAscent(ucg), 1);
  ucg_SetFont(ucg, ucg_font_ncenB24_tf);
  vrule(ucg, 42+ox+ucg_GetStrWidth(ucg, "Ucg"), 30, -ucg_GetFontDescent(ucg), 1);
  
  save_picture(ucg, "draw_text_ascent_descent");  
}

void draw_text_dir1(ucg_t *ucg)
{
  prepare_picture(ucg);
  
  ucg_SetFont(ucg, ucg_font_ncenB18_tf);
  ucg_SetFontPosBaseline(ucg);
  ucg_SetColor(ucg, 0, 0, 0, 255);		/* draw blue "baseline" */
  //ucg_DrawHLine(ucg, 45+ox, 30, ucg_GetStrWidth(ucg, "Ucg"));
  ucg_SetColor(ucg, 0, 255, 255, 255);		/* draw white "Ucg" */
  ucg_DrawString(ucg, 45+ox, 10, 1, "Ucg");
  pos(ucg, 45+ox, 10, 0);
  
  save_picture(ucg, "draw_text_dir1");  
}

void draw_frame(ucg_t *ucg)
{
  prepare_picture(ucg);
  hrule(ucg, ox+50, 30, 45, 0);
  vrule(ucg, ox+50+45-1, 30, 20, 1);
  ucg_SetColor(ucg, 0, 255, 255, 255);
  
  ucg_DrawFrame(ucg, ox+50, 30, 45, 20);
  pos(ucg, ox+50, 30,0);
  save_picture(ucg, "draw_frame");  
}

void draw_box(ucg_t *ucg)
{
  prepare_picture(ucg);
  hrule(ucg, ox+50, 30, 45, 0);
  vrule(ucg, ox+50+45-1, 30, 20, 1);
  ucg_SetColor(ucg, 0, 255, 255, 255);
  
  ucg_DrawBox(ucg, ox+50, 30, 45, 20);
  pos(ucg, ox+50, 30,0);
  save_picture(ucg, "draw_box");  
}

void draw_rbox(ucg_t *ucg)
{
  prepare_picture(ucg);
  hrule(ucg, ox+50, 30, 45, 0);
  vrule(ucg, ox+50+45-1, 30, 20, 1);
  
  vrule(ucg, ox+50+1, 30+20-8, 8, 0);
  hrule(ucg, ox+50, 30+20-1-1, 8, 1);
  ucg_SetColor(ucg, 0, 255, 255, 255);
  
  ucg_DrawRBox(ucg, ox+50, 30, 45, 20, 8);
  pos(ucg, ox+50, 30,0);
  save_picture(ucg, "draw_rbox");  
}

void draw_rframe(ucg_t *ucg)
{
  prepare_picture(ucg);
  hrule(ucg, ox+50, 30, 45, 0);
  vrule(ucg, ox+50+45-1, 30, 20, 1);
  
  vrule(ucg, ox+50+1, 30+20-8, 8, 0);
  hrule(ucg, ox+50, 30+20-1-1, 8, 1);
  ucg_SetColor(ucg, 0, 255, 255, 255);
  
  ucg_DrawRFrame(ucg, ox+50, 30, 45, 20, 8);
  pos(ucg, ox+50, 30,0);
  save_picture(ucg, "draw_rframe");  
}

void draw_gradient_box(ucg_t *ucg)
{
  prepare_picture(ucg);
  hrule(ucg, ox+50, 30, 45, 0);
  vrule(ucg, ox+50+45-1, 30, 20, 1);
  ucg_SetColor(ucg, 0, 255, 0, 0);
  ucg_SetColor(ucg, 1, 0, 255, 0);
  ucg_SetColor(ucg, 2, 255, 0, 255);
  ucg_SetColor(ucg, 3, 0, 255, 255);

  ucg_DrawGradientBox(ucg, ox+50, 30, 45, 20);
  
  pos(ucg, ox+50, 30,0);
  save_picture(ucg, "draw_gradient_box");  
}

void draw_gradient_line(ucg_t *ucg)
{
  prepare_picture(ucg);
  hrule(ucg, ox+50, 40, 45, 0);
  ucg_SetColor(ucg, 0, 0, 255, 255);
  ucg_SetColor(ucg, 1, 255, 255, 0);
  
  ucg_DrawGradientLine(ucg, ox+50, 40, 45, 0);
  pos(ucg, ox+50, 40,0);
  save_picture(ucg, "draw_gradient_line");  
}

void draw_disc(ucg_t *ucg)
{
  prepare_picture(ucg);
  hrule(ucg, ox+50+1, 30, 20, 0);
  vrule(ucg, ox+50+20-1, 30+1, 20, 1);
  ucg_SetColor(ucg, 0, 255, 255, 255);
  
  ucg_DrawDisc(ucg, ox+50, 30, 20, UCG_DRAW_LOWER_RIGHT);
  pos(ucg, ox+50, 30,0);
  save_picture(ucg, "draw_disc");  
}

void draw_circle(ucg_t *ucg)
{
  prepare_picture(ucg);
  hrule(ucg, ox+50+1, 30, 20, 0);
  vrule(ucg, ox+50+20-1, 30+1, 20, 1);
  ucg_SetColor(ucg, 0, 255, 255, 255);
  
  ucg_DrawCircle(ucg, ox+50, 30, 20, UCG_DRAW_LOWER_RIGHT);
  pos(ucg, ox+50, 30,0);
  save_picture(ucg, "draw_circle");  
}

void draw_triangle(ucg_t *ucg)
{
  prepare_picture(ucg);

  ucg_SetColor(ucg, 0, 255, 255, 255);
 
  ucg_DrawTriangle(ucg, 52, 9,   83,32,      47,42);
  
  ucg_DrawTriangle(ucg, 52,55,  83,32+1,  47,42+1);
  pos(ucg, 52, 9, 0);
  pos(ucg, 83,32, 1);
  pos(ucg, 47,42+1, 0);
  
  
  
  save_picture(ucg, "draw_triangle");  
}

void set_scale2x2(ucg_t *ucg)
{
  prepare_picture(ucg);
  
  ucg_SetFont(ucg, ucg_font_ncenB18_tf);
  ucg_SetFontPosBaseline(ucg);
  //ucg_SetColor(ucg, 0, 0, 0, 255);		/* draw blue "baseline" */
  //ucg_DrawHLine(ucg, 45+ox, 30, ucg_GetStrWidth(ucg, "Ucg"));
  ucg_SetColor(ucg, 0, 255, 255, 255);		/* draw white "Ucg" */
  ucg_SetScale2x2(ucg);
  ucg_DrawString(ucg, 20+ox, 20, 0, "Ucg");
  ucg_UndoScale(ucg);
  pos(ucg, 40+ox, 40, 0);
  
  save_picture(ucg, "set_scale2x2");  
}

void set_font_mode_1(ucg_t *ucg)
{
  prepare_picture(ucg);

  ucg_SetColor(ucg, 0, 255, 0, 0);
  ucg_SetColor(ucg, 1, 0, 255, 0);
  ucg_SetColor(ucg, 2, 255, 0, 255);
  ucg_SetColor(ucg, 3, 0, 255, 255);

  ucg_DrawGradientBox(ucg, ox+0, 0, 128, 64);
  
  ucg_SetFontMode(ucg, UCG_FONT_MODE_TRANSPARENT);
  ucg_SetFont(ucg, ucg_font_ncenB18_tf);
  ucg_SetFontPosBaseline(ucg);  
  ucg_SetColor(ucg, 0, 0, 0, 0);		/* draw black "Ucg" */
  ucg_DrawString(ucg, 40+ox, 40, 0, "Ucg");
  pos(ucg, 42+ox, 40, 0);
  
  save_picture(ucg, "set_font_mode_1");  
}

void set_font_mode_2(ucg_t *ucg)
{
  prepare_picture(ucg);

  ucg_SetColor(ucg, 0, 255, 0, 0);
  ucg_SetColor(ucg, 1, 0, 255, 0);
  ucg_SetColor(ucg, 2, 255, 0, 255);
  ucg_SetColor(ucg, 3, 0, 255, 255);

  ucg_DrawGradientBox(ucg, ox+0, 0, 128, 64);
  
  ucg_SetFontMode(ucg, UCG_FONT_MODE_SOLID);
  ucg_SetFont(ucg, ucg_font_ncenB18_hr);
  ucg_SetFontPosBaseline(ucg);  
  ucg_SetColor(ucg, 0, 0, 0, 0);		/* draw black "Ucg" */
  ucg_SetColor(ucg, 1, 150, 220, 255);		/* light blue background */
  ucg_DrawString(ucg, 40+ox, 40, 0, "Ucg");
  pos(ucg, 42+ox, 40, 0);
  
  save_picture(ucg, "set_font_mode_2");  
}

void solid_font_variants(ucg_t *ucg)
{
  prepare_picture(ucg);

  ucg_SetColor(ucg, 0, 250, 0, 0);
  ucg_SetColor(ucg, 1, 255, 255, 30);
  ucg_SetColor(ucg, 2, 220, 235, 10);
  ucg_SetColor(ucg, 3, 205, 0, 30);

  ucg_DrawGradientBox(ucg, ox+0, 0, 128, 64);

  ucg_SetColor(ucg, 0, 0, 0, 0);		/* draw black "Ucg" */
  ucg_SetColor(ucg, 1, 150, 220, 255);		/* light blue background */  
  ucg_SetFontMode(ucg, UCG_FONT_MODE_SOLID);
  ucg_SetFontPosBaseline(ucg);  
  
  ucg_SetFont(ucg, ucg_font_fur11_tf);
  ucg_DrawString(ucg, 3+ox, 20, 0, "fur11_tf");

  ucg_SetFont(ucg, ucg_font_fur11_hf);
  ucg_DrawString(ucg, 3+ox, 50, 0, "fur11_hf");

  ucg_SetFont(ucg, ucg_font_fur11_hr);
  ucg_DrawString(ucg, 68+ox, 50, 0, "fur11_hr");
  
  
  //pos(ucg, 42+ox, 40, 0);
  
  save_picture(ucg, "solid_font_variants");  
}

void string_overwrite(ucg_t *ucg, int cnt)
{
  char s[40];
  int i;
  prepare_picture(ucg);

  ucg_SetColor(ucg, 0, 250, 0, 0);
  ucg_SetColor(ucg, 1, 255, 255, 30);
  ucg_SetColor(ucg, 2, 220, 235, 10);
  ucg_SetColor(ucg, 3, 205, 0, 30);

  ucg_DrawGradientBox(ucg, ox+0, 0, 128, 64);

  ucg_SetColor(ucg, 0, 0, 0, 0);		/* draw black "Ucg" */
  ucg_SetColor(ucg, 1, 150, 220, 255);		/* light blue background */  
  ucg_SetFontMode(ucg, UCG_FONT_MODE_SOLID);
  ucg_SetFontPosBaseline(ucg);  
  
  for( i = 11; i < 11+cnt; i++ )
  {
    sprintf(s, "cu12_tf %d", i);
    ucg_SetFont(ucg, ucg_font_cu12_tf);
    ucg_DrawString(ucg, 1+ox, 15, 0, s);

    sprintf(s, "cu12_hf %d", i);
    ucg_SetFont(ucg, ucg_font_cu12_hf);
    ucg_DrawString(ucg, 1+ox, 35, 0, s);

    sprintf(s, "7x14_mf %d", i);
    ucg_SetFont(ucg, ucg_font_7x14_mf);
    ucg_DrawString(ucg, 1+ox, 55, 0, s);
  }  
  
  //pos(ucg, 42+ox, 40, 0);
  
  sprintf(s, "string_overwrite_%d", cnt);
  save_picture(ucg, s);  
}


int main(void)
{
  
  tga_init(128,64);
  ucg_Init(&ucg, &ucg_dev_tga, ucg_ext_none, (ucg_com_fnptr)0);
  ucg_SetFontMode(&ucg, UCG_FONT_MODE_TRANSPARENT);
  
  ucg_SetColor(&ucg, 0, 0, 0, 0);
  ucg_DrawBox(&ucg, 0, 0, 128, 64);
  
  
  
  ucg_SetFont(&ucg, ucg_font_ncenB18_tf);
  
  ucg_SetColor(&ucg, 0, 0, 0, 255);
  ucg_DrawPixel(&ucg, 70,20);
  ucg_SetColor(&ucg, 0, 255, 0, 0);
 
  //ucg_SetFontPosBottom(&ucg);
  /*
  ucg_DrawGlyph(&ucg, 70, 20, 0, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 1, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 2, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 3, 'A');

  ucg_SetColor(&ucg, 0, 255, 255, 255);
  
  vrule(&ucg, 30, 0, 20, 1);
  vrule(&ucg, 30, 0, 20, 0);
  */
  //pos(&ucg, 70, 20, 0);
  
  //hrule(&ucg, 0, 20, 70, 1);
  //hrule(&ucg, 0, 20, 70, 0);
  
  
  ucg_SetColor(&ucg, 0, 255, 0, 0);
  ucg_SetColor(&ucg, 1, 0, 255, 0);
  ucg_SetColor(&ucg, 2, 255, 0, 255);
  ucg_SetColor(&ucg, 3, 0, 255, 255);

  ucg_DrawGradientLine(&ucg, 10, 40, 100, 0);

  ucg_DrawGradientBox(&ucg, 10, 43, 100, 20);


  tga_save("test.tga");
  
  draw_pixel(&ucg);
  draw_hline(&ucg);
  draw_vline(&ucg);
  set_clip_range(&ucg);
  draw_text_baseline(&ucg);
  draw_text_bottom(&ucg);
  draw_text_top(&ucg);
  draw_text_center(&ucg);
  draw_text_ascent_descent(&ucg);
  draw_text_dir1(&ucg);
  draw_box(&ucg);
  draw_frame(&ucg);
  draw_rbox(&ucg);
  draw_rframe(&ucg);
  draw_gradient_box(&ucg);
  draw_gradient_line(&ucg);
  draw_disc(&ucg);
  draw_circle(&ucg);
  draw_triangle(&ucg);
  set_scale2x2(&ucg);
  set_font_mode_1(&ucg);
  set_font_mode_2(&ucg);
  solid_font_variants(&ucg);
  string_overwrite(&ucg, 1);
  string_overwrite(&ucg, 5);
  string_overwrite(&ucg, 10);
  return 0;
  
}

