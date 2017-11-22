

#ifndef _BDF_FONT_H
#define BDF_FONT_H

#include <stdio.h>
#include "bdf_glyph.h"

#define BDF_LINE_LEN 1024

struct _bdf_font_struct
{
  int is_verbose;
  
  bg_t **glyph_list;
  int glyph_cnt;
  int glyph_max;

  /* variables for the parser */
  char line_buf[BDF_LINE_LEN];
  int line_pos;
  int is_bitmap_parsing;
  
  long encoding;
  
  long dwidth_x;
  long dwidth_y;
  
  long bbx_w;
  long bbx_h;
  long bbx_x;
  long bbx_y;
  
  int bitmap_x;			/* x position within bitmap parsing */
  int bitmap_y;			/* y position within bitmap parsing */
  int glyph_pos;		/* the position to which the glyph has been added in the list */
  FILE *fp;
  
  char *str_font;		/* argument for FONT in bdf file */
  char *str_copyright;	/* argument for COPYRIGHT in bdf file */
  
  long selected_glyphs;	/* number of mapped glyphs */
  
  /* bf_CalculateMaxBBX */
  bbx_t max;			/* max bbx, calculated from the mapped glyphs by bf_CalculateMaxBBX */

  /* bf_CalculateMinMaxDWidth */
  long dx_min;			/* calculated minimum and maximum dwidth value from the mapped glyphs by bf_CalculateMinMaxDWidth */
  long dx_max;		/* it is a monospaced font if max and min values are identical */

  /* bf_CalculateMinMaxDWidth */
  long x_min;			/* calculated minimum and maximum bbx.x value from the mapped glyphs by bf_CalculateMinMaxDWidth */
  long x_max;		/* it is a monospaced font if x_min >= 0 */

  /* bf_CalculateMaxBitFieldSize */
  int bbx_x_max_bit_size;
  int bbx_y_max_bit_size;
  int bbx_w_max_bit_size;
  int bbx_h_max_bit_size;
  int dx_max_bit_size;
  
  /* font target data */
  uint8_t *target_data;
  int target_max;
  int target_cnt;
  

};

/* bdf_font.c */


/* output error & log messages */
void bf_Error(bf_t *bf, char *fmt, ...);
void bf_Log(bf_t *bf, char *fmt, ...);

/* constructor/destructor */
bf_t *bf_Open(void);
void bf_Close(bf_t *bf);

/* returns glyph position or -1 */
int bf_AddGlyph(bf_t *bf);

/* add binary data */
void bf_ClearTargetData(bf_t *bf);
int bf_AddTargetData(bf_t *bf, uint8_t data);

void bf_CalculateSelectedNumberOfGlyphs(bf_t *bf);

void bf_ReduceAllGlyph(bf_t *bf);

/* only shows glyphs, which will be mapped (call bf_Map() first) */
void bf_ShowAllGlyphs(bf_t *bf, bbx_t *bbx);

/* calculate the max bbx for all mapped glyphs (call bf_Map() first) */
void bf_CalculateMaxBBX(bf_t *bf);

void bf_CalculateMinMaxDWidth(bf_t *bf);
void bf_CalculateMaxBitFieldSize(bf_t *bf, bbx_t *bbx);
void bf_RLECompressAllGlyphs(bf_t *bf, bbx_t *bbx);


/* bdf_parser.c */
int bf_ParseFile(bf_t *bf, const char *name);

/* bdf_map.c */
void bf_Map(bf_t *bf, char *map_cmd_list);

/* bdf_tga.c */
int tga_init(uint16_t w, uint16_t h);
void tga_set_pixel(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);
void tga_save(const char *name);
void tga_set_font(uint8_t *font);
void tga_draw_glyph(unsigned x, unsigned y, uint8_t encoding);


#endif