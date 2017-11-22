

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint16_t tga_width;
static uint16_t tga_height;
static uint8_t *tga_data = NULL;

static uint8_t *tga_font;
static int glyph_cnt;
static int bits_per_0;
static int bits_per_1;
static int bits_per_char_width;
static int bits_per_char_height;
static int bits_per_char_x;
static int bits_per_char_y;
static int bits_per_delta_x;




int tga_init(uint16_t w, uint16_t h)
{
  tga_width = 0;
  tga_height = 0;
  if ( tga_data != NULL )
    free(tga_data);
  tga_data = (uint8_t *)malloc((size_t)w*(size_t)h*3);
  if ( tga_data == NULL )
    return 0;
  tga_width = w;
  tga_height = h;
  memset(tga_data, 255, tga_width*tga_height*3);
  return 1;
}

void tga_set_pixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b)
{
  uint8_t *p;
  p = tga_data + (tga_height-y-1)*(size_t)tga_width*3 + (size_t)x*3;
  *p++ = b;
  *p++ = g;
  *p++ = r;
}

void tga_write_byte(FILE *fp, uint8_t byte)
{
  fputc(byte, fp);
}

void tga_write_word(FILE *fp, uint16_t word)
{
  tga_write_byte(fp, word&255);
  tga_write_byte(fp, word>>8);
}

void tga_save(const char *name)
{
  FILE *fp;
  fp = fopen(name, "wb");
  if ( fp != NULL )
  {
    tga_write_byte(fp, 0);		/* no ID */
    tga_write_byte(fp, 0);		/* no color map */
    tga_write_byte(fp, 2);		/* uncompressed true color */
    tga_write_word(fp, 0);		
    tga_write_word(fp, 0);		
    tga_write_byte(fp, 0);		
    tga_write_word(fp, 0);		/* x origin */
    tga_write_word(fp, 0);		/* y origin */
    tga_write_word(fp, tga_width);		/* width */
    tga_write_word(fp, tga_height);		/* height */
    tga_write_byte(fp, 24);		/* color depth */
    tga_write_byte(fp, 0);		
    fwrite(tga_data, tga_width*tga_height*3, 1, fp);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    tga_write_word(fp, 0);
    fwrite("TRUEVISION-XFILE.", 18, 1, fp);
    fclose(fp);
  }
}

void tga_set_font(uint8_t *font)
{
    glyph_cnt = *font++;
    bits_per_0 = *font++;
    bits_per_1 = *font++;
    bits_per_char_width = *font++;
    bits_per_char_height = *font++;
    bits_per_char_x = *font++;
    bits_per_char_y = *font++;
    bits_per_delta_x = *font++;
    tga_font = font;
}

uint8_t *tga_get_glyph_data(uint8_t encoding)
{
  int i;
  uint8_t *font = tga_font;
  for( i = 0; i < glyph_cnt; i++ )
  {
    if ( font[0] == encoding )
    {
      return font;
    }
    font += font[1];
  }
  return NULL;
}

/* font decode */
struct tga_fd_struct
{
  unsigned target_x;
  unsigned target_y;
  
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
typedef struct tga_fd_struct tga_fd_t;

/* increment x and consider line wrap (inc y)*/
void tga_fd_inc(tga_fd_t *f)
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


unsigned tga_fd_get_unsigned_bits(tga_fd_t *f, unsigned cnt)
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
int tga_fd_get_signed_bits(tga_fd_t *t, int cnt)
{
  return (int)tga_fd_get_unsigned_bits(t, cnt) - ((1<<cnt)>>1);
}


void tga_fd_draw_pixel(tga_fd_t *f)
{
  tga_set_pixel(f->target_x+f->x, f->target_y+f->y, 255,0,0);
}

void tga_fd_decode(tga_fd_t *f, uint8_t *glyph_data)
{
  unsigned a, b;
  unsigned i;
  
  
  /* init decode algorithm */
  f->decode_ptr = glyph_data;
  f->decode_bit_pos = 0;
  
  /* read glyph info */
  f->decode_ptr += 2;
  
  f->glyph_width = tga_fd_get_unsigned_bits(f, bits_per_char_width);
  f->glyph_height = tga_fd_get_unsigned_bits(f, bits_per_char_height);
  tga_fd_get_signed_bits(f, bits_per_char_x);
  tga_fd_get_signed_bits(f, bits_per_char_y);
  tga_fd_get_signed_bits(f, bits_per_delta_x);
  
  /* reset local x/y position */
  f->x = 0;
  f->y = 0;
  
  //puts("");
  
  /* decode glyph */
  for(;;)
  {
    a = tga_fd_get_unsigned_bits(f, bits_per_0);
    b = tga_fd_get_unsigned_bits(f, bits_per_1);
    //printf("[%u %u]", a, b);
    do
    {
      for( i = 0; i < a; i++ )
      {
	tga_fd_inc(f);
      }

      for( i = 0; i < b; i++ )
      {	
	tga_fd_draw_pixel(f);
	tga_fd_inc(f);
      }
      
    } while( tga_fd_get_unsigned_bits(f, 1) != 0 );
    
    if ( f->y >= f->glyph_height )
      break;
  }
  
}

void tga_draw_glyph(unsigned x, unsigned y, uint8_t encoding)
{
  tga_fd_t f;
  f.target_x = x;
  f.target_y = y;
  uint8_t *glyph_data = tga_get_glyph_data(encoding);
  tga_fd_decode(&f, glyph_data);
  
}

