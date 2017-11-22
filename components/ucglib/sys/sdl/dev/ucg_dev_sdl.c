/*

  ucg_dev_sdl.c

  Universal uC Color Graphics Library
  
  Copyright (c) 2013, olikraus@gmail.com
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
  
  



#include "ucg.h"
#include "SDL.h"
#include "SDL_video.h"
#include <assert.h>

#define HEIGHT (64)
#define WIDTH 128

SDL_Surface *ucg_sdl_screen;
int ucg_sdl_multiple = 2;
Uint32 ucg_sdl_color[256];

void ucg_sdl_set_pixel(int x, int y, int idx)
{
  Uint32  *ptr;
  Uint32 offset;
  int i, j;
  
  if ( y >= HEIGHT )
    return;
  if ( y < 0 )
    return;
  if ( x >= WIDTH )
    return;
  if ( x < 0 )
    return;
  
  for( i = 0; i < ucg_sdl_multiple; i++ )
    for( j = 0; j < ucg_sdl_multiple; j++ )
    {
      offset = 
	(y * ucg_sdl_multiple + j) * ucg_sdl_screen->w * ucg_sdl_screen->format->BytesPerPixel + 
	(x * ucg_sdl_multiple + i) * ucg_sdl_screen->format->BytesPerPixel;
      assert( offset < ucg_sdl_screen->w * ucg_sdl_screen->h * ucg_sdl_screen->format->BytesPerPixel );
      ptr = ucg_sdl_screen->pixels + offset;
      *ptr = ucg_sdl_color[idx];
    }
}

void ucg_sdl_set_hicolor(int x, int y, uint8_t low, uint8_t high)
{
  Uint32  *ptr;
  Uint32 offset;
  int i, j;
  unsigned int r, g, b;
  Uint32 color;

  if ( y >= HEIGHT )
    return;
  if ( y < 0 )
    return;
  if ( x >= WIDTH )
    return;
  if ( x < 0 )
    return;
  
  r = high & ~7;
  b = low & 31;
  b <<= 3;
  g = high & 7;
  g <<= 3;
  g |= (low>>5)&7;
  g <<= 2;
  
  color = SDL_MapRGB( ucg_sdl_screen->format, r, g, b );  
  for( i = 0; i < ucg_sdl_multiple; i++ )
    for( j = 0; j < ucg_sdl_multiple; j++ )
    {
      offset = 
	(y * ucg_sdl_multiple + j) * ucg_sdl_screen->w * ucg_sdl_screen->format->BytesPerPixel + 
	(x * ucg_sdl_multiple + i) * ucg_sdl_screen->format->BytesPerPixel;
      assert( offset < ucg_sdl_screen->w * ucg_sdl_screen->h * ucg_sdl_screen->format->BytesPerPixel );
      ptr = ucg_sdl_screen->pixels + offset;
      *ptr = color;
    }
  
}

void ucg_sdl_set_fullcolor(int x, int y, unsigned int r, unsigned int g, unsigned int b)
{
  Uint32  *ptr;
  Uint32 offset;
  int i, j;
  Uint32 color;

  if ( y >= HEIGHT )
    return;
  if ( y < 0 )
    return;
  if ( x >= WIDTH )
    return;
  if ( x < 0 )
    return;
  
  color = SDL_MapRGB( ucg_sdl_screen->format, r, g, b );  
  for( i = 0; i < ucg_sdl_multiple; i++ )
    for( j = 0; j < ucg_sdl_multiple; j++ )
    {
      offset = 
	(y * ucg_sdl_multiple + j) * ucg_sdl_screen->w * ucg_sdl_screen->format->BytesPerPixel + 
	(x * ucg_sdl_multiple + i) * ucg_sdl_screen->format->BytesPerPixel;
      assert( offset < ucg_sdl_screen->w * ucg_sdl_screen->h * ucg_sdl_screen->format->BytesPerPixel );
      ptr = ucg_sdl_screen->pixels + offset;
      *ptr = color;
    }
  
}

#define W(x,w) (((x)*(w))/100)

void ucg_sdl_init(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) 
  {
    printf("Unable to initialize SDL:  %s\n", SDL_GetError());
    exit(1);
  }
  
  /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_SetVideoMode */
  ucg_sdl_screen = SDL_SetVideoMode(WIDTH*ucg_sdl_multiple,HEIGHT*ucg_sdl_multiple,32,SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( ucg_sdl_screen == NULL ) 
  {
    printf("Couldn't set video mode: %s\n", SDL_GetError());
    exit(1);
  }
  printf("%d bits-per-pixel mode\n", ucg_sdl_screen->format->BitsPerPixel);
  printf("%d bytes-per-pixel mode\n", ucg_sdl_screen->format->BytesPerPixel);
  
  ucg_sdl_color[0] = SDL_MapRGB( ucg_sdl_screen->format, 0, 0, 0 );
  ucg_sdl_color[1] = SDL_MapRGB( ucg_sdl_screen->format, W(100, 50), W(255,50), 0 );
  ucg_sdl_color[2] = SDL_MapRGB( ucg_sdl_screen->format, W(100, 80), W(255,80), 0 );
  ucg_sdl_color[3] = SDL_MapRGB( ucg_sdl_screen->format, 100, 255, 0 );

  /*
  ucg_sdl_set_pixel(0,0);
  ucg_sdl_set_pixel(1,1);
  ucg_sdl_set_pixel(2,2);
  */

  /* update all */
  /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_UpdateRect */
  SDL_UpdateRect(ucg_sdl_screen, 0,0,0,0);

  atexit(SDL_Quit);
  return;
}


void ucg_sdl_start(void)
{
  Uint32 color = SDL_MapRGB( ucg_sdl_screen->format, 0, 0, 0 );
  /* http://www.libsdl.org/cgi/docwiki.cgi/SDL_FillRect */
  SDL_FillRect(ucg_sdl_screen, NULL, color);
  
  /*
  ucg_sdl_set_pixel(0,0,3);
  ucg_sdl_set_pixel(10,0,3);
  ucg_sdl_set_pixel(20,0,3);
  ucg_sdl_set_pixel(30,0,3);
  ucg_sdl_set_pixel(40,0,3);
  ucg_sdl_set_pixel(50,0,3);
  */
}

void ucg_sdl_end(void)
{
}

/* return ascii key value or -1 */
int ucg_sdl_get_key(void)
{
  SDL_Event event;
	/* http://www.libsdl.org/cgi/docwiki.cgi/SDL_PollEvent */
  if ( SDL_PollEvent(&event) != 0 )
  {
    switch (event.type) 
    {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_KEYDOWN:
          switch( event.key.keysym.sym )
          {
            /*     /usr/include/SDL/SDL_keysym.h */
            case SDLK_a: return 'a';
            case SDLK_b: return 'b';
            case SDLK_c: return 'c';
            case SDLK_d: return 'd';
            case SDLK_e: return 'e';
            case SDLK_f: return 'f';
            case SDLK_g: return 'g';
            case SDLK_h: return 'h';
            case SDLK_i: return 'i';
            case SDLK_j: return 'j';
            case SDLK_k: return 'k';
            case SDLK_l: return 'l';
            case SDLK_m: return 'm';
            case SDLK_n: return 'n';
            case SDLK_o: return 'o';
            case SDLK_p: return 'p';
            case SDLK_q: return 'q';
            case SDLK_r: return 'r';
            case SDLK_s: return 's';
            case SDLK_t: return 't';
            case SDLK_u: return 'u';
            case SDLK_v: return 'v';
            case SDLK_w: return 'w';
            case SDLK_x: return 'x';
            case SDLK_y: return 'y';
            case SDLK_z: return 'z';
            case SDLK_SPACE: return ' ';
            case SDLK_UP: return 273;
            case SDLK_DOWN: return 274;
            case SDLK_RIGHT: return 275;
            case SDLK_LEFT: return 276;
            
            default: return 0;
          }
    }
  }
  return -1;
}

ucg_int_t ucg_sdl_dev_cb(ucg_t *ucg, ucg_int_t msg, void *data)
{
  switch(msg)
  {
    case UCG_MSG_DEV_POWER_UP:
      ucg_sdl_init();
      ucg_sdl_start();
      return 1;
    case UCG_MSG_DEV_POWER_DOWN:
      return 1;
    case UCG_MSG_GET_DIMENSION:
      ((ucg_wh_t *)data)->w = WIDTH;
      ((ucg_wh_t *)data)->h = HEIGHT;
      return 1;
    case UCG_MSG_DRAW_PIXEL:
      if ( ucg_clip_is_pixel_visible(ucg) !=0 )
      {
	ucg_sdl_set_fullcolor(
	    ucg->arg.pixel.pos.x,
	    ucg->arg.pixel.pos.y, 
	    ucg->arg.pixel.rgb.color[0], 
	    ucg->arg.pixel.rgb.color[1], 
	    ucg->arg.pixel.rgb.color[2]);
	SDL_UpdateRect(ucg_sdl_screen, 0,0,0,0);
      }
      return 1;
    case UCG_MSG_DRAW_L90FX:
      ucg_handle_l90fx(ucg, ucg_sdl_dev_cb);
      return 1;
#ifdef UCG_MSG_DRAW_L90TC
    case UCG_MSG_DRAW_L90TC:
      ucg_handle_l90tc(ucg, ucg_sdl_dev_cb);
      return 1;
#endif
    case UCG_MSG_DRAW_L90SE:
      ucg_handle_l90se(ucg, ucg_sdl_dev_cb);
      return 1;
#ifdef UCG_MSG_DRAW_L90TC
    case UCG_MSG_DRAW_L90BF:
      ucg_handle_l90bf(ucg, ucg_sdl_dev_cb);
      return 1;
#endif
#ifdef ON_HOLD
    case UCG_MSG_DRAW_L90RL:
      ucg_handle_l90rl(ucg, ucg_sdl_dev_cb);
      return 1;
#endif
  }
  return ucg_dev_default_cb(ucg, msg, data);  
}

