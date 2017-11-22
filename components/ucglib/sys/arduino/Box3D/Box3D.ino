/*

  Box3D.ino
  
  Draw a rotating 3D box

  Universal uC Color Graphics Library
  
  Copyright (c) 2014, olikraus@gmail.com
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

#include <SPI.h>
#include "Ucglib.h"

/*
  Hardware SPI Pins:
    Arduino Uno		sclk=13, data=11
    Arduino Due		sclk=76, data=75
    Arduino Mega	sclk=52, data=51
    
  >>> Please uncomment (and update) one of the following constructors. <<<  
*/
//Ucglib8BitPortD ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, /* wr= */ 18 , /* cd= */ 19 , /* cs= */ 17, /* reset= */ 16 );
//Ucglib8Bit ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, 0, 1, 2, 3, 4, 5, 6, 7, /* wr= */ 18 , /* cd= */ 19 , /* cs= */ 17, /* reset= */ 16 );

//Ucglib4WireSWSPI ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, /*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	// not working
//Ucglib4WireSWSPI ucg(ucg_dev_ili9325_spi_18x240x320, ucg_ext_ili9325_spi_18, /*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	// not working
//Ucglib3WireILI9325SWSPI ucg(ucg_dev_ili9325_spi_18x240x320, ucg_ext_ili9325_spi_18, /*sclk=*/ 13, /*data=*/ 11, /*cs=*/ 10, /*reset=*/ 8);	// not working
//Ucglib3WireILI9325SWSPI ucg(ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, /*sclk=*/ 13, /*data=*/ 11, /*cs=*/ 10, /*reset=*/ 8);	// not working

//Ucglib_ST7735_18x128x160_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_ST7735_18x128x160_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);

//Ucglib_ILI9163_18x128x128_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5 , /*cs=*/ 3, /*reset=*/ 4);
//Ucglib_ILI9163_18x128x128_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);	/* HW SPI Adapter */

//Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5 , /*cs=*/ 3, /*reset=*/ 4);
//Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 4, /*data=*/ 3, /*cd=*/ 6 , /*cs=*/ 7, /*reset=*/ 5);	/* Elec Freaks Shield */

//Ucglib_SSD1351_18x128x128_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SSD1351_18x128x128_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SSD1351_18x128x128_FT_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SSD1351_18x128x128_FT_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);

//Ucglib_PCF8833_16x132x132_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cs=*/ 9, /*reset=*/ 8);	/* linksprite board */
//Ucglib_PCF8833_16x132x132_HWSPI ucg(/*cs=*/ 9, /*reset=*/ 8);	/* linksprite board */

//Ucglib_LD50T6160_18x160x128_6Bit ucg( /*d0 =*/ d0, /*d1 =*/ d1, /*d2 =*/ d2, /*d3 =*/ d3, /*d4 =*/ d4, /*d5 =*/ d5, /*wr=*/ wr, /*cd=*/ cd, /*cs=*/ cs, /*reset=*/ reset);
//Ucglib_LD50T6160_18x160x128_6Bit ucg( /*d0 =*/ 16, /*d1 =*/ 17, /*d2 =*/ 18, /*d3 =*/ 19, /*d4 =*/ 20, /*d5 =*/ 21, /*wr=*/ 14, /*cd=*/ 15); /* Samsung 160x128 OLED with 6Bit minimal interface with Due */ 
//Ucglib_LD50T6160_18x160x128_6Bit ucg( /*d0 =*/ 5, /*d1 =*/ 4, /*d2 =*/ 3, /*d3 =*/ 2, /*d4 =*/ 1, /*d5 =*/ 0, /*wr=*/ 7, /*cd=*/ 6); /* Samsung 160x128 OLED with 6Bit minimal interface with Uno */ 

//Ucglib_SSD1331_18x96x64_UNIVISION_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SSD1331_18x96x64_UNIVISION_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);

//Ucglib_SEPS225_16x128x128_UNIVISION_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
//Ucglib_SEPS225_16x128x128_UNIVISION_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);

// define a 3d point structure 
struct pt3d 
{
  ucg_int_t x, y, z;
};

struct surface
{
  uint8_t p[4];
  int16_t z;
};

struct pt2d 
{
  ucg_int_t x, y;
  unsigned is_visible;
};


// define the point at which the observer looks, 3d box will be centered there
#define MX (ucg.getWidth()/2)
#define MY (ucg.getHeight()/2)

// define a value that corresponds to "1"
#define U 64

// eye to screen distance (fixed)
#define ZS U

// cube edge length is 2*U
struct pt3d cube[8] =
{
  { -U, -U, U}, 
  { U, -U, U}, 
  { U, -U, -U}, 
  { -U, -U, -U}, 
  { -U, U, U}, 
  { U, U, U}, 
  { U, U, -U}, 
  { -U, U, -U}, 
};

// define the surfaces
struct surface cube_surface[6] = 
{
  { {0, 1, 2, 3}, 0 },	// bottom
  { {4, 5, 6, 7}, 0 },	// top
  { {0, 1, 5, 4}, 0 },	// back
  
  { {3, 7, 6, 2}, 0 },	// front
  { {1, 2, 6, 5}, 0 },	// right
  { {0, 3, 7, 4}, 0 },	// left
};

// define some structures for the copy of the box, calculation will be done there
struct pt3d cube2[8];
struct pt2d cube_pt[8];

// will contain a rectangle border of the box projection into 2d plane
ucg_int_t x_min, x_max;
ucg_int_t y_min, y_max;

int16_t sin_tbl[65] = {
0,1606,3196,4756,6270,7723,9102,10394,11585,12665,13623,14449,15137,15679,16069,16305,16384,16305,16069,15679,
15137,14449,13623,12665,11585,10394,9102,7723,6270,4756,3196,1606,0,-1605,-3195,-4755,-6269,-7722,-9101,-10393,
-11584,-12664,-13622,-14448,-15136,-15678,-16068,-16304,-16383,-16304,-16068,-15678,-15136,-14448,-13622,-12664,-11584,-10393,-9101,-7722,
-6269,-4755,-3195,-1605,0};

int16_t cos_tbl[65] = {
16384,16305,16069,15679,15137,14449,13623,12665,11585,10394,9102,7723,6270,4756,3196,1606,0,-1605,-3195,-4755,
-6269,-7722,-9101,-10393,-11584,-12664,-13622,-14448,-15136,-15678,-16068,-16304,-16383,-16304,-16068,-15678,-15136,-14448,-13622,-12664,
-11584,-10393,-9101,-7722,-6269,-4755,-3195,-1605,0,1606,3196,4756,6270,7723,9102,10394,11585,12665,13623,14449,
15137,15679,16069,16305,16384};


void copy_cube(void)
{
  uint8_t i;
  for( i = 0; i < 8; i++ )
  {
    cube2[i] = cube[i];
  }
}

void rotate_cube_y(uint16_t w)
{
  uint8_t i;
  int16_t x, z;
  /*
    x' = x * cos(w) + z * sin(w)
    z' = - x * sin(w) + z * cos(w)  
  */
  for( i = 0; i < 8; i++ )
  {
    x = ((int32_t)cube2[i].x * (int32_t)cos_tbl[w] + (int32_t)cube2[i].z * (int32_t)sin_tbl[w])>>14;
    z = (- (int32_t)cube2[i].x * (int32_t)sin_tbl[w] + (int32_t)cube2[i].z * (int32_t)cos_tbl[w])>>14;
    //printf("%d: %d %d --> %d %d\n", i, cube2[i].x, cube2[i].z, x, z);
    cube2[i].x = x;
    cube2[i].z = z;
  }  
}

void rotate_cube_x(uint16_t w)
{
  uint8_t i;
  int16_t y, z;
  for( i = 0; i < 8; i++ )
  {
    y = ((int32_t)cube2[i].y * (int32_t)cos_tbl[w] + (int32_t)cube2[i].z * (int32_t)sin_tbl[w])>>14;
    z = (- (int32_t)cube2[i].y * (int32_t)sin_tbl[w] + (int32_t)cube2[i].z * (int32_t)cos_tbl[w])>>14;
    cube2[i].y = y;
    cube2[i].z = z;
  }  
}

void trans_cube(uint16_t z)
{
  uint8_t i;
  for( i = 0; i < 8; i++ )
  {
    cube2[i].z += z;
  }  
}

void reset_min_max(void)
{
  x_min = 0x07fff;
  y_min = 0x07fff;
  x_max = -0x07fff;
  y_max = -0x07fff;
}

// calculate xs and ys from a 3d value
void convert_3d_to_2d(struct pt3d *p3, struct pt2d *p2)
{
  int32_t t;
  p2->is_visible = 1;
  if ( p3->z >= ZS )
  {
    t = ZS;
    t *= p3->x;
    t <<=1;
    t /= p3->z;
    if ( t >= -MX && t <= MX-1 )
    {
      t += MX;
      p2->x = t;
      
      if ( x_min > t )
	x_min = t;
      if ( x_max < t )
	x_max = t;	
      
      t = ZS;
      t *= p3->y;
      t <<=1;
      t /= p3->z;
      if ( t >= -MY && t <= MY-1 )
      {
	t += MY;
	p2->y = t;
	
	if ( y_min > t )
	  y_min = t;
	if ( y_max < t )
	  y_max = t;	
      }
      else
      {
	p2->is_visible = 0;
      }
    }
    else
    {
      p2->is_visible = 0;
    }
  }
  else
  {
    p2->is_visible = 0;
  }
}

void convert_cube(void)
{
  uint8_t i;
  reset_min_max();
  for( i = 0; i < 8; i++ )
  {
    convert_3d_to_2d(cube2+i, cube_pt+i);
    //printf("%d: %d %d\n", i, cube_pt[i].x, cube_pt[i].y);
  }  
}

void calculate_z(void)
{
  uint8_t i, j;
  uint16_t z;
  for( i = 0; i < 6; i++ )
  {
    z = 0;
    for( j = 0; j < 4; j++ )
    {
      z+=cube2[cube_surface[i].p[j]].z;      
    }
    z/=4;
    cube_surface[i].z = z;
    //printf("%d: z=%d\n", i, z);
  }  
}

void draw_cube(void)
{
  uint8_t i, ii;
  uint8_t skip_cnt = 3;		/* it is known, that the first 3 surfaces are invisible */
  int16_t z, z_upper;
  
  
  z_upper = 32767;
  for(;;)
  {
    ii = 6;
    z = -32767;
    for( i = 0; i < 6; i++ )
    {
      if ( cube_surface[i].z <= z_upper )
      {
	if ( z < cube_surface[i].z )
	{
	  z = cube_surface[i].z;
	  ii = i;
	}
      }
    }
    
    if ( ii >= 6 )
      break;
    //printf("%d z=%d upper=%d\n", ii, z, z_upper);
    z_upper = cube_surface[ii].z;
    cube_surface[ii].z++;
    
    if ( skip_cnt > 0 )
    {
      skip_cnt--;
    }
    else
    {
      ucg.setColor(0, ((ii+1)&1)*255,(((ii+1)>>1)&1)*255,(((ii+1)>>2)&1)*255);
      ucg.drawTetragon( 
	cube_pt[cube_surface[ii].p[0]].x, cube_pt[cube_surface[ii].p[0]].y,
	cube_pt[cube_surface[ii].p[1]].x, cube_pt[cube_surface[ii].p[1]].y,
	cube_pt[cube_surface[ii].p[2]].x, cube_pt[cube_surface[ii].p[2]].y,
	cube_pt[cube_surface[ii].p[3]].x, cube_pt[cube_surface[ii].p[3]].y);
    }
  }
}



void calc_and_draw(uint16_t w, uint16_t v)
{
  copy_cube();
  rotate_cube_y(w);
  rotate_cube_x(v);
  trans_cube(U*8);
  convert_cube();
  calculate_z();
  draw_cube();
}


void setup(void)
{
  delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.setRotate90();
  ucg.clearScreen();
  ucg.setFont(ucg_font_ncenR10_tr);
  ucg.setPrintPos(0,25);
  ucg.setColor(255, 255, 255);
  ucg.print("Ucglib Box3D");
  
}

uint16_t w = 0;
uint16_t v = 0;

void loop(void)
{  
  calc_and_draw(w, v>>3);

  v+=3;
  v &= 511;

  w++;
  w &= 63;  
  delay(30);  
  
  ucg.setColor(0,0,0);
  ucg.drawBox(x_min, y_min, x_max-x_min+1, y_max-y_min+1);
}

