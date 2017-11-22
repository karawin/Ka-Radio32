/*

  bdf_rle.c
  
  run length glyph encoding
  
*/

/* font information */
/*
    glyph_cnt = *font++;
    bits_per_0 = *font++;
    bits_per_1 = *font++;
    bits_per_char_width = *font++;
    bits_per_char_height = *font++;
    bits_per_char_x = *font++;
    bits_per_char_y = *font++;
    bits_per_delta_x = *font++;

*/

  /* apply glyph information */
  /*  
    ~		encoding			unsigned, 1 byte
    ~		total size			unsigned, 1 byte
    ~             BBX width                                       unsigned	5
    ~             BBX height                                      unsigned	5
    ~             BBX xoffset                                    signed		2
    ~             BBX yoffset                                    signed		5
    ~             DWIDTH                                          unsigned		3


*/


#include <stdio.h>
#include <assert.h>
#include "bdf_font.h"

#define SCREEN_W 140
#define SCREEN_H 140

uint8_t screen_buf[SCREEN_H][SCREEN_W];
unsigned screen_max_y;

void screen_init(void)
{
  unsigned x, y;
  screen_max_y = 0;
  for( y = 0; y < SCREEN_H; y++ )
  {
    for( x = 0; x < SCREEN_W; x++ )
    {
      screen_buf[y][x] = '.';
    }
  }
}

void screen_set_pixel(unsigned x, unsigned y, uint8_t c)
{
  if ( screen_max_y < y)
    screen_max_y = y;
  screen_buf[y][x] = c;
}

void screen_show(void)
{
  unsigned x, y;
  printf("\n");
  for( y = 0; y <= screen_max_y; y++ )
  {
    for( x = 0; x < SCREEN_W; x++ )
    {
      printf("%c", screen_buf[y][x]);
    }
    printf("\n");
  }
}

/*===================================================*/

/* font decode */
struct fd_struct
{
  unsigned x;						/* local coordinates, (0,0) is upper left */
  unsigned y;
  unsigned glyph_width;	
  unsigned glyph_height;

  
  const uint8_t *decode_ptr;			/* pointer to the compressed data */
  unsigned decode_bit_pos;			/* bitpos inside a byte of the compressed data */
  
  uint8_t bbx_x_max_bit_size;
  uint8_t bbx_y_max_bit_size;
  uint8_t bbx_w_max_bit_size;
  uint8_t bbx_h_max_bit_size;
  uint8_t dx_max_bit_size;
  
};
typedef struct fd_struct fd_t;

/* increment x and consider line wrap (inc y)*/
void fd_inc(fd_t *f)
{
  unsigned x = f->x;
  x++;
  if ( x == f->glyph_width )
  {
    x = 0;
    f->y++;
  }
  f->x = x;
}


unsigned fd_get_unsigned_bits(fd_t *f, unsigned cnt)
{
  unsigned val;
  unsigned bit_pos = f->decode_bit_pos;
  
  val = *(f->decode_ptr);
  
  val >>= bit_pos;
  if ( bit_pos + cnt >= 8 )
  {
    f->decode_ptr++;
    val |= *(f->decode_ptr) << (8-bit_pos);
    bit_pos -= 8;
  }
  val &= (1U<<cnt)-1;
  bit_pos += cnt;
  
  f->decode_bit_pos = bit_pos;
  return val;
}

/*
    2 bit --> cnt = 2
      -2,-1,0. 1

    3 bit --> cnt = 3
      -2,-1,0. 1
      -4,-3,-2,-1,0,1,2,3

      if ( x < 0 )
	r = bits(x-1)+1;
    else
	r = bits(x)+1;

*/
int fd_get_signed_bits(fd_t *t, int cnt)
{
  return (int)fd_get_unsigned_bits(t, cnt) - ((1<<cnt)>>1);
}


void fd_draw_pixel(fd_t *f)
{
  screen_set_pixel(f->x, f->y, '#');
}

void fd_decode(bg_t *bg, bbx_t *bbx, fd_t *f, unsigned rle_bits_per_0, unsigned rle_bits_per_1)
{
  unsigned a, b;
  unsigned i;
  
  screen_init();

  if ( bbx == NULL )
    bbx = &(bg->bbx);
  
  /* init decode algorithm */
  f->decode_ptr = bg->target_data;
  f->decode_bit_pos = 0;
  f->glyph_width = bbx->w;
  f->glyph_height = bbx->h;

  
  /* read glyph info */
  f->decode_ptr += 2;
  
  fd_get_unsigned_bits(f, f->bbx_w_max_bit_size);
  fd_get_unsigned_bits(f, f->bbx_h_max_bit_size);
  fd_get_signed_bits(f, f->bbx_x_max_bit_size);
  fd_get_signed_bits(f, f->bbx_y_max_bit_size);
  fd_get_signed_bits(f, f->dx_max_bit_size);
  
  /* reset local x/y position */
  f->x = 0;
  f->y = 0;
  
  //puts("");
  
  /* decode glyph */
  for(;;)
  {
    a = fd_get_unsigned_bits(f, rle_bits_per_0);
    b = fd_get_unsigned_bits(f, rle_bits_per_1);
    //printf("[%u %u]", a, b);
    do
    {
      for( i = 0; i < a; i++ )
      {
	fd_inc(f);
      }

      for( i = 0; i < b; i++ )
      {	
	fd_draw_pixel(f);
	fd_inc(f);
      }
      
    } while( fd_get_unsigned_bits(f, 1) != 0 );
    
    if ( f->y >= f->glyph_height )
      break;
  }
  
  screen_show();
}



/*===================================================*/


/*
  Desc:
    Output a and b to the stream.
    a and b must fit to the target size in bits.
    Additionally a repeat code r (one bit) is generated:
    It may look like this:
      r = 0: 0aaaabb
    or 
      r = 1: 1
    If r is 0, then the number of zeros (a) and ones (b) will follow and both
    values must be stored as in the decoder.
    If r os 1, then the number of zeros and ones is repeated once
  Args:
    a: number of 0 bits, log2(a) must be smaller or equal to the fieldsize
    b: number of 1 bits, log2(b) must be smaller or equal to the fieldsize
*/

static void bg_err(const char *s)
{
  puts(s);
}

static void bg_init_rle(bg_t *bg, unsigned rle_bits_per_0, unsigned rle_bits_per_1)
{
  bg->rle_bitcnt = 0;
  bg->rle_is_first = 1;
  bg->rle_bits_per_0 = rle_bits_per_0;
  bg->rle_bits_per_1 = rle_bits_per_1;
  bg->rle_last_0 = 0;
  bg->rle_last_1 = 1;
  bg_ClearTargetData(bg);
}
  
static int bg_01_rle(bg_t *bg, unsigned a, unsigned b)
{
  if ( bg->rle_is_first == 0 && bg->rle_last_0 == a && bg->rle_last_1 == b )
  {
    bg->rle_bitcnt++;
    if ( bg_AddTargetBits(bg, 1, 1) == 0 )
      return bg_err("error in bg_01_rle 1 0"), 0;
  }
  else
  {   
    if ( bg->rle_is_first == 0 )
    {
      if ( bg_AddTargetBits(bg, 1, 0) == 0 )
	return bg_err("error in bg_01_rle 1 0"), 0;
      bg->rle_bitcnt++;
    }
    if ( bg_AddTargetBits(bg, bg->rle_bits_per_0, a) == 0 )
      return bg_err("error in bg_01_rle 1 a"), 0;
    if ( bg_AddTargetBits(bg, bg->rle_bits_per_1, b) == 0 )
      return bg_err("error in bg_01_rle 1 b"), 0;
    
    bg->rle_is_first = 0;
    bg->rle_bitcnt +=bg->rle_bits_per_0;
    bg->rle_bitcnt +=bg->rle_bits_per_1;
    bg->rle_last_0 = a;
    bg->rle_last_1 = b;
  }
  return 1;
}

/*
  Desc:
    Write the number of zeros and ones to the bit stream.
    There is no restriction on the size of a and b.
  Args:
    a: number of 0 bits
    b: number of 1 bits
  
*/
static int bg_prepare_01_rle(bg_t *bg, unsigned a, unsigned b)
{
  //printf("[%u %u]", a, b);
  while( a >= (1<<bg->rle_bits_per_0) -1 )
  {
    if ( bg_01_rle(bg, (1<<bg->rle_bits_per_0) -1, 0) == 0 )
      return 0;
    a -= (1<<bg->rle_bits_per_0) -1;
  }
  while( b >= (1<<bg->rle_bits_per_1) -1 )
  {
    if ( bg_01_rle(bg, a, (1<<bg->rle_bits_per_1) -1) == 0 )
      return 0;
    a = 0;
    b -= (1<<bg->rle_bits_per_1) -1;
  }
  if ( a != 0 || b != 0 )
    if ( bg_01_rle(bg, a, b) == 0 )
      return 0;
  return 1;
}


int bg_rle_compress(bg_t *bg, bbx_t *bbx, unsigned rle_bits_per_0, unsigned rle_bits_per_1)
{
  int x;
  int y;
  int i;
  int bd_is_one;	/* bit delta */
  int bd_curr_len;
  int bd_max_len;
  int bd_chg_cnt;
  
  static int bd_list[1024*2];

  if ( bbx == NULL )
    bbx = &(bg->bbx);

  bg_init_rle(bg, rle_bits_per_0, rle_bits_per_1);
  

  /* step 0: output initial information */
  if ( bg_AddTargetData(bg, bg->encoding) < 0 )
    return bg_err("error in bg_rle_compress"), 0;
  /* size, will be added later */
  if ( bg_AddTargetData(bg, 0) < 0 )
    return bg_err("error in bg_rle_compress"), 0;
  if ( bg_AddTargetBits(bg, bg->bf->bbx_w_max_bit_size, bbx->w) == 0 )
    return bg_err("error in bg_rle_compress"), 0;
  if ( bg_AddTargetBits(bg, bg->bf->bbx_h_max_bit_size, bbx->h) == 0 )
    return bg_err("error in bg_rle_compress"), 0;
  if ( bg_AddTargetBits(bg, bg->bf->bbx_x_max_bit_size, bbx->x + (1<<(bg->bf->bbx_x_max_bit_size-1))) == 0 )
    return bg_err("error in bg_rle_compress"), 0;
  if ( bg_AddTargetBits(bg, bg->bf->bbx_y_max_bit_size, bbx->y + (1<<(bg->bf->bbx_y_max_bit_size-1))) == 0 )
    return bg_err("error in bg_rle_compress"), 0;
  if ( bg_AddTargetBits(bg, bg->bf->dx_max_bit_size, bg->dwidth_x + (1<<(bg->bf->dx_max_bit_size-1))) == 0 )
    return bg_err("error in bg_rle_compress"), 0;
  
  bd_is_one = 0;
  bd_curr_len = 0;
  bd_max_len = 0;
  bd_chg_cnt = 0;

  /* step 1: build array with pairs of a (number of zero bits) and b (number of one bits) */

  for( y = bbx->y+bbx->h-1; y >= bbx->y; y--)
  {
    for( x = bbx->x; x < bbx->x + bbx->w; x++)
    {
      if ( bg_GetBBXPixel(bg, x, y) == 0 )
      {
	if ( bd_is_one != 0 )
	{
	  bd_list[bd_chg_cnt] = bd_curr_len;
	  bd_is_one = 0;
	  bd_chg_cnt++;
	  bd_curr_len = 0;
	}
	bd_curr_len++;	
      }
      else
      {
	if ( bd_is_one == 0 )
	{
	  bd_list[bd_chg_cnt] = bd_curr_len;
	  bd_is_one = 1;
	  bd_chg_cnt++;
	  bd_curr_len = 0;
	}
	bd_curr_len++;	
      }
      
      if ( bd_max_len < bd_curr_len )
	bd_max_len = bd_curr_len;      
    }
  }
  
 
  bd_list[bd_chg_cnt] = bd_curr_len;
  bd_chg_cnt++;
  if ( (bd_chg_cnt & 1) == 1 )
  {
    bd_list[bd_chg_cnt] = 0;
    bd_chg_cnt++;
  }
  
  //printf("01 pairs = %d\n", bd_chg_cnt/2);
  
  /* step 2: convert the array into bit stream */
  
  for( i = 0; i < bd_chg_cnt; i+=2 )
  {
    if ( bg_prepare_01_rle(bg, bd_list[i], bd_list[i+1]) == 0 )
      return 0;
  }
  if ( bg_AddTargetBits(bg, 1, 0) == 0 )		// ensure that there is a 0 bit at the end.
    return 0;

  bg->target_data[1] = bg->target_cnt;
  
  /*
  {
    fd_t f;
    f.bbx_x_max_bit_size = bg->bf->bbx_x_max_bit_size;
    f.bbx_y_max_bit_size = bg->bf->bbx_y_max_bit_size;
    f.bbx_w_max_bit_size = bg->bf->bbx_w_max_bit_size;
    f.bbx_h_max_bit_size = bg->bf->bbx_h_max_bit_size;
    f.dx_max_bit_size = bg->bf->dx_max_bit_size;
  
    fd_decode(bg, bbx, &f, rle_bits_per_0, rle_bits_per_1);
  }
  */
  
  return 1;
}

unsigned long bf_RLECompressAllGlyphsWithFieldSize(bf_t *bf, bbx_t *bbx, int rle_0, int rle_1, int is_output)
{
  int i;
  bg_t *bg;
  unsigned long total_bits = 0;
  
  for( i = 0; i < bf->glyph_cnt; i++ )
  {
    bg = bf->glyph_list[i];
    if ( bg->map_to >= 0 )
    {
      bg_rle_compress(bg, bbx, rle_0, rle_1); 
      total_bits += bg->target_cnt*8+bg->target_bit_pos;
      if ( is_output != 0 )
      {
	bf_Log(bf, "RLE Compress: Encoding %ld bits %u/%u", bg->encoding, bg->rle_bitcnt, bg->target_cnt*8+bg->target_bit_pos);  
      }
    }
  }
  //bf_Log(bf, "RLE Compress: zero bits %d, one bits %d, total bit size %lu", rle_0, rle_1, total_bits);
  return total_bits;
}

void bf_RLECompressAllGlyphs(bf_t *bf, bbx_t *bbx)
{
  int i, j;
  bg_t *bg;
  
  int rle_0, rle_1;
  int best_rle_0=0, best_rle_1= 0;
  unsigned long total_bits = 0;
  unsigned long min_total_bits = 0xffffffff;
  
  for( rle_0 = 2; rle_0 < 7; rle_0++ )
  {
    for( rle_1 = 2; rle_1 < 7; rle_1++ )
    {
      total_bits = bf_RLECompressAllGlyphsWithFieldSize(bf, bbx, rle_0, rle_1, 0);
      if ( min_total_bits > total_bits )
      {
	min_total_bits = total_bits;
	best_rle_0 = rle_0;
	best_rle_1 = rle_1;
      }
      
    }
  }
  bf_Log(bf, "RLE Compress: best zero bits %d, one bits %d, total bit size %lu", best_rle_0, best_rle_1, min_total_bits);
  total_bits = bf_RLECompressAllGlyphsWithFieldSize(bf, bbx, best_rle_0, best_rle_1, 0);


  bf_ClearTargetData(bf);

  /*
    glyph_cnt = *font++;
    bits_per_0 = *font++;
    bits_per_1 = *font++;
    bits_per_char_width = *font++;
    bits_per_char_height = *font++;
    bits_per_char_x = *font++;
    bits_per_char_y = *font++;
    bits_per_delta_x = *font++;
  */
  
  bf_AddTargetData(bf, bf->selected_glyphs);
  bf_AddTargetData(bf, best_rle_0);
  bf_AddTargetData(bf, best_rle_1);

  bf_AddTargetData(bf, bf->bbx_w_max_bit_size);
  bf_AddTargetData(bf, bf->bbx_h_max_bit_size);
  bf_AddTargetData(bf, bf->bbx_x_max_bit_size);
  bf_AddTargetData(bf, bf->bbx_y_max_bit_size);
  bf_AddTargetData(bf, bf->dx_max_bit_size);

  for( i = 0; i < bf->glyph_cnt; i++ )
  {
    bg = bf->glyph_list[i];
    if ( bg->map_to >= 0 )
    {
      if ( bg->target_data != NULL )
      {
	for( j = 0; j < bg->target_cnt; j++ )
	{
	  bf_AddTargetData(bf, bf->target_data[j]);
	}
      }
    }
  }
  bf_Log(bf, "RLE Compress: Font size %d", bf->target_cnt);
  
}



