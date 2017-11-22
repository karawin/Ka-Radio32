

#include <stdlib.h>
#include <stdarg.h>
#include "bdf_font.h"

void bf_Error(bf_t *bf, char *fmt, ...)
{
  va_list va;
  va_start(va, fmt);
  vprintf(fmt, va);
  printf("\n");
  va_end(va);
}

void bf_Log(bf_t *bf, char *fmt, ...)
{
  va_list va;
  va_start(va, fmt);
  if ( bf->is_verbose != 0 )
  {
    vprintf(fmt, va);
    printf("\n");
  }
  va_end(va);
}


bf_t *bf_Open(void)
{
  bf_t *bf;
  bf = (bf_t *)malloc(sizeof(bf_t));
  if ( bf != NULL )
  {
    bf->is_verbose = 0;
    bf->glyph_list = NULL;
    bf->glyph_cnt = 0;
    bf->glyph_max = 0;
    bf->str_font = NULL;		/* argument for FONT in bdf file */
    bf->str_copyright = NULL;	/* argument for COPYRIGHT in bdf file */
    bf->target_data = NULL;
    bf->target_max = 0;
    bf->target_cnt = 0;
    bf->selected_glyphs = 0;
    return bf;
  }
  return NULL;
}

void bf_Clear(bf_t *bf)
{
  int i;
  for( i = 0; i < bf->glyph_cnt; i++ )
  {
    free( bf->glyph_list[i] );
  }
  bf->glyph_cnt = 0;
  
  if ( bf->str_font != NULL )
    free(bf->str_font);
  bf->str_font = NULL;
  if ( bf->str_copyright != NULL )
    free(bf->str_copyright);
  bf->str_copyright = NULL;
}

void bf_Close(bf_t *bf)
{
  bf_Clear(bf);
  if ( bf->glyph_list != NULL )
    free(bf->glyph_list);
  if ( bf->target_data != NULL )
    free(bf->target_data);
  bf->glyph_list = NULL;
  bf->glyph_max = 0;
  free(bf);
}

static int bf_extend(bf_t *bf)
{
  int extend = 16;
  void *ptr;
  if ( bf->glyph_list == NULL )
  {
    ptr = malloc(extend*sizeof(bg_t *));
    bf->glyph_max = 0;
  }
  else
  {
    ptr = realloc(bf->glyph_list, (bf->glyph_max + extend)*sizeof(bg_t *));
  }
  if ( ptr == NULL )
    return 0;
  bf->glyph_max += extend;
  bf->glyph_list = (bg_t **)ptr;
  return 1;
}

/* returns glyph position or -1 */
int bf_AddGlyph(bf_t *bf)
{
    while( bf->glyph_max <= bf->glyph_cnt )
      if ( bf_extend(bf) == 0 )
	return -1;
    bf->glyph_list[bf->glyph_cnt] = bg_Open();
    if ( bf->glyph_list[bf->glyph_cnt] == NULL )
      return -1;
    bf->glyph_list[bf->glyph_cnt]->bf = bf;
    bf->glyph_cnt++;
    return bf->glyph_cnt-1;
}


static int bf_extend_target_data(bf_t *bf)
{
  int extend = 16;
  int i;
  void *ptr;
  if ( bf->target_data == NULL )
  {
    ptr = malloc(extend*sizeof(uint8_t));
    bf->target_max = 0;
  }
  else
  {
    ptr = realloc(bf->target_data, (bf->target_max + extend)*sizeof(uint8_t));
  }
  if ( ptr == NULL )
    return 0;
  bf->target_data = (uint8_t *)ptr;
  for( i = bf->target_max; i < bf->target_max + extend; i++ )
      bf->target_data[i] = 0;
  bf->target_max += extend;
  return 1;
}

int bf_AddTargetData(bf_t *bf, uint8_t data)
{
  while( bf->target_max <= bf->target_cnt )
    if ( bf_extend_target_data(bf) == 0 )
      return -1;
  bf->target_data[bf->target_cnt] = data;
  bf->target_cnt++;
  return bf->target_cnt-1;
}

void bf_ClearTargetData(bf_t *bf)
{
  int i;
  for( i = 0; i < bf->target_max; i++ )
    bf->target_data[i] = 0;
  bf->target_cnt = 0;
}

void bf_CalculateSelectedNumberOfGlyphs(bf_t *bf)
{
  int i;
  bg_t *bg;
  bf->selected_glyphs = 0;
  
  
  for( i = 0; i < bf->glyph_cnt; i++ )
  {
    bg = bf->glyph_list[i];
    if ( bg->map_to >= 0 )
    {
      bf->selected_glyphs++;
    }
  }
}


void bf_ReduceAllGlyph(bf_t *bf)
{
  int i;
  bg_t *bg;
  int red_x, red_y;
  
  bf_Log(bf, "Reduce: Start");
  
  for( i = 0; i < bf->glyph_cnt; i++ )
  {
    bg = bf->glyph_list[i];
    if ( bg->map_to >= 0 )
    {
      bg_ReduceGlyph(bg);
      
      red_x = bg->bitmap_width - bg->bbx.w;
      red_y = bg->bitmap_height - bg->bbx.h;
      if ( red_x > 0 || red_y > 0 )
      {
	bf_Log(bf, "Reduce: Encoding %ld, x by %d, y by %d", bg->encoding, red_x, red_y);
      }
    }
  }
}

void bf_ShowAllGlyphs(bf_t *bf, bbx_t *bbx)
{
  int i;
  bg_t *bg;
  for( i = 0; i < bf->glyph_cnt; i++ )
  {
    bg = bf->glyph_list[i];
    if ( bg->map_to >= 0 )
    {
      bg_ShowBitmap(bg, bbx); 
    }
  }
}

void bf_CalculateMaxBBX(bf_t *bf)
{
  int i;
  int is_first = 1;
  bg_t *bg;
  
  for( i = 0; i < bf->glyph_cnt; i++ )
  {
    bg = bf->glyph_list[i];
    if ( bg->map_to >= 0 )
    {
      if ( is_first != 0 )
      {
	bf->max = bg->bbx;
	is_first = 0;
      }
      else
      {
	bg_Max(bg, &(bf->max));
      }
    }
  }
  bf_Log(bf, "CalculateMaxBBX: x=%ld, y=%ld, w=%ld, h=%ld", bf->max.x, bf->max.y, bf->max.w, bf->max.h);
}

void bf_CalculateMinMaxDWidth(bf_t *bf)
{
  int i;
  bg_t *bg;
  
  bf->dx_min = 0x07fff;
  bf->dx_max = -0x07fff;
  
  bf->x_min = 0x07fff;
  bf->x_max = -0x07fff;
  
  for( i = 0; i < bf->glyph_cnt; i++ )
  {
    bg = bf->glyph_list[i];
    if ( bg->map_to >= 0 )
    {
      if ( bf->dx_min > bg->dwidth_x )
	bf->dx_min = bg->dwidth_x;
      if ( bf->dx_max < bg->dwidth_x )
	bf->dx_max = bg->dwidth_x;

      if ( bf->x_min > bg->bbx.x )
	bf->x_min = bg->bbx.x;
      if ( bf->x_max < bg->bbx.x )
	bf->x_max = bg->bbx.x;
      
    }
  }
  bf_Log(bf, "bf_CalculateMinMaxDWidth: dx_min=%ld, dx_max=%ld", bf->dx_min, bf->dx_max);
  bf_Log(bf, "bf_CalculateMinMaxDWidth: x_min=%ld, x_max=%ld", bf->x_min, bf->x_max);
  if ( bf->dx_min == bf->dx_max && bf->x_min >= 0 )
  {
    bf_Log(bf, "bf_CalculateMinMaxDWidth: Monospaced font.");	/* not sufficient: also bbx.x must be >= 0 for all glyphs */
    /* for a monospaced font, dx must be identical to bbx.w */
  }
}

int get_unsigned_bit_size(unsigned long v)
{
  int i = 0;
  while( v != 0 )
  {
    v = v / 2;
    i++;
  }
  return i;
}

int get_signed_bit_size(long v)
{
  if ( v < 0 )
    return get_unsigned_bit_size(-v-1) + 1;
  return get_unsigned_bit_size(v) + 1;
}

void bf_CalculateMaxBitFieldSize(bf_t *bf, bbx_t *bbx)
{
  int i;
  bg_t *bg;
  int bs;
  bbx_t *local_bbx;
  bf->bbx_x_max_bit_size = 0;
  bf->bbx_y_max_bit_size = 0;
  bf->bbx_w_max_bit_size = 0;
  bf->bbx_h_max_bit_size = 0;
  bf->dx_max_bit_size = 0;
  for( i = 0; i < bf->glyph_cnt; i++ )
  {
    bg = bf->glyph_list[i];
    if ( bg->map_to >= 0 )
    {
      
      if ( bbx == NULL )
	local_bbx = &(bg->bbx);
      else
	local_bbx = bbx;
      
      bs = get_unsigned_bit_size(local_bbx->w);
      if ( bf->bbx_w_max_bit_size < bs )
	bf->bbx_w_max_bit_size = bs;
      
      bs = get_unsigned_bit_size(local_bbx->h);
      if ( bf->bbx_h_max_bit_size < bs )
	bf->bbx_h_max_bit_size = bs;
      
      bs = get_signed_bit_size(local_bbx->x);
      if ( bf->bbx_x_max_bit_size < bs )
	bf->bbx_x_max_bit_size = bs;
      //printf("%d:%d ",(int)local_bbx->x, (int)bs);

      bs = get_signed_bit_size(local_bbx->y);
      if ( bf->bbx_y_max_bit_size < bs )
	bf->bbx_y_max_bit_size = bs;

      bs = get_signed_bit_size(bg->dwidth_x);
      if ( bf->dx_max_bit_size < bs )
	bf->dx_max_bit_size = bs;
      
    }
  }
  bf_Log(bf, "bf_CalculateMaxBitFieldSize: bbx.x=%d, bbx.y=%d, bbx.w=%d, bbx.h=%d, dwidth=%d", 
      bf->bbx_x_max_bit_size, bf->bbx_y_max_bit_size, bf->bbx_w_max_bit_size, bf->bbx_h_max_bit_size, bf->dx_max_bit_size);
  
}

