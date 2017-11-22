

#include "ucg.h"
#include <stdlib.h>
#include <stdio.h>


int ucg_sdl_get_key(void);

//extern const ucg_fntpgm_uint8_t ucg_font_ncenB18[] UCG_FONT_SECTION("ucg_font_ncenB18");
//extern const u8g_fntpgm_uint8_t u8g_font_ncenB18[] U8G_FONT_SECTION("u8g_font_ncenB18");

ucg_t ucg;

unsigned char rl_bitmap[] = 
{
  3, 0x033, 0x022, 0x011
};

unsigned char bitmap[2] = { 0x0f0, 0x0f0 };

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
  ucg_SetColor(ucg, 0, 20, 20, 20);
  ucg_DrawDisc(ucg, x+w-1, y+h/2+1, 7, UCG_DRAW_UPPER_LEFT|UCG_DRAW_LOWER_LEFT);
  
  
}

  /* offset 9 */
  int8_t max_char_width;
  int8_t max_char_height;
  int8_t x_offset;
  int8_t y_offset;
  
  /* offset 13 */
  int8_t  ascent_A;
  int8_t  descent_g;
  int8_t  ascent_para;
  int8_t  descent_para;

void show_font_info(ucg_t *ucg)
{
  printf("ucg->font_info.max_char_width = %d\n", ucg->font_info.max_char_width);
  printf("ucg->font_info.max_char_height = %d\n", ucg->font_info.max_char_height);
  printf("ucg->font_info.x_offset = %d\n", ucg->font_info.x_offset);
  printf("ucg->font_info.y_offset = %d\n", ucg->font_info.y_offset);

  printf("ucg->font_info.ascent_A = %d\n", ucg->font_info.ascent_A);
  printf("ucg->font_info.descent_g = %d\n", ucg->font_info.descent_g);
  printf("ucg->font_info.ascent_para = %d\n", ucg->font_info.ascent_para);
  printf("ucg->font_info.descent_para = %d\n", ucg->font_info.descent_para);

}


int main(void)
{
  ucg_int_t a,b;
  
  ucg_Init(&ucg, ucg_sdl_dev_cb, ucg_ext_none, (ucg_com_fnptr)0);
  //ucg_SetFontMode(&ucg, UCG_FONT_MODE_SOLID);
  
  //ucg_SetRotate90(&ucg);
  ucg_SetFont(&ucg, ucg_font_ncenB24_tf);  
  //ucg_SetFont(&ucg, ucg_font_profont10);  
  

  
  a = 2;
  b = 3;
  

  ucg_SetColor(&ucg, 1, 135*a/b,206*a/b,250*a/b);
  ucg_SetColor(&ucg, 2, 176*a/b,226*a/b,255*a/b);
  ucg_SetColor(&ucg, 3, 25*a/b,25*a/b,112*a/b);
  ucg_SetColor(&ucg, 0, 	85*a/b,26*a/b,139*a/b);
  ucg_DrawGradientBox(&ucg, 0, 0, ucg_GetWidth(&ucg), ucg_GetHeight(&ucg));
  
  ucg_SetFont(&ucg, ucg_font_ncenB14_tf);  
  show_font_info(&ucg);
  ucg_SetColor(&ucg, 0, 255, 255, 0);
  ucg_SetColor(&ucg, 1, 0, 0, 0);
  ucg_DrawString(&ucg, 0, 20, 0, "Ucglib");

  ucg_SetFont(&ucg, ucg_font_ncenB14_hf);  
  show_font_info(&ucg);
  ucg_SetColor(&ucg, 0, 255, 255, 0);
  ucg_SetColor(&ucg, 1, 0, 0, 0);
  ucg_DrawString(&ucg, 0, 50, 0, "Ucglib");

  ucg_SetFont(&ucg, ucg_font_ncenB14_hr);  
  show_font_info(&ucg);
  ucg_SetColor(&ucg, 0, 255, 255, 0);
  ucg_SetColor(&ucg, 1, 0, 0, 0);
  ucg_DrawString(&ucg, 64, 50, 0, "Ucglib");


  while( ucg_sdl_get_key() < 0 )
    ;
    
  
  return 0;
}

