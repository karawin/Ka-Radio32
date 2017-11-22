

#include "ucg.h"
#include <stdlib.h>
#include <stdio.h>


int ucg_sdl_get_key(void);


ucg_t ucg;

uint8_t x_my_init_sequence[] = {
  UCG_CFG_CD(0,0),
  UCG_RST(0),
  UCG_DLY_MS(2),
  UCG_RST(1),
  UCG_DLY_MS(2),
  UCG_VARY(7,255,0),
  UCG_C11(0xaa, 0x055),
  UCG_END()
};

uint8_t my_init_sequence[] = {
	UCG_CS(0),					/* disable chip */
	UCG_CFG_CD(0,1),				/* DC=0 for command mode, DC=1 for data and args */
	UCG_DLY_MS(20),
  	UCG_RST(1),					
	UCG_DLY_MS(20),
  	UCG_RST(0),					
	UCG_DLY_MS(20),
  	UCG_RST(1),
	UCG_DLY_MS(20),
	UCG_CS(1),					/* enable chip */
	UCG_DLY_MS(50),
	UCG_C11(0x0fd, 0x012),			/* Unock normal commands */
	UCG_C11(0x0fd, 0x0b1),			/* Unock extra commands */
	UCG_C10(0xae),				/* Set Display Off */

  	UCG_C11(0x0b3, 0x0f1),			/* Front Clock Div */
  	UCG_C11(0x0ca, 0x07f),			/* Set Multiplex Ratio */
  	UCG_C11(0x0a0, 0x0b4),			/* Set Colour Depth */
  	UCG_C12(0x015, 0x000, 0x07f),	/* Set Column Address */
  	UCG_C12(0x075, 0x000, 0x07f),	/* Set Row Address */

  	UCG_C11(0x0a1, 0x000),			/* Set Display Start Line */
  	UCG_C11(0x0a2, 0x000),			/* Set Display Offset */
  	UCG_C11(0x0b5, 0x000),		/* Set GPIO */
  	UCG_C11(0x0ab, 0x001),			/* Set Function Selection */
  	UCG_C11(0x0b1, 0x032),		/* Set Phase Length */
  	UCG_C13(0x0b4, 0xa0,0xb5,0x55),		/* Set Segment Low Voltage */
  	UCG_C11(0x0bb, 0x017),		/* Set Precharge Voltage */
  	UCG_C11(0x0be, 0x005),			/* Set VComH Voltage */
  	UCG_C13(0x0c1, 0xc8, 0x80, 0xc8),	/* Set Contrast */
  	UCG_C11(0x0c7, 0x00f),			/* Set Master Contrast */
  	UCG_C11(0x0b6, 0x001),		/* Set Second Precharge Period */
	UCG_C10(0x0a6),				/* Set Display Mode Reset */
	
	UCG_C10(0x0b8),				/* Set CMD Grayscale Lookup, 63 Bytes follow */
	UCG_A8(0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c),
	UCG_A8(0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13,0x14),
	UCG_A8(0x15,0x16,0x18,0x1a,0x1b,0x1C,0x1D,0x1F),
	UCG_A8(0x21,0x23,0x25,0x27,0x2A,0x2D,0x30,0x33),
	UCG_A8(0x36,0x39,0x3C,0x3F,0x42,0x45,0x48,0x4C),
	UCG_A8(0x50,0x54,0x58,0x5C,0x60,0x64,0x68,0x6C),
	UCG_A8(0x70,0x74,0x78,0x7D,0x82,0x87,0x8C,0x91),
	UCG_A7(0x96,0x9B,0xA0,0xA5,0xAA,0xAF,0xB4),

	UCG_C10(0x0af),				/* Set Display On */
	UCG_C10(0x05c),				/* Write RAM */
	UCG_D3(255,255,255),
	UCG_D3(255,255,255),
	UCG_D3(255,255,255),
	UCG_D3(255,255,255),
	UCG_D3(255,255,255),
	UCG_D3(255,255,255),
	UCG_D3(255,255,255),
	UCG_DLY_MS(50),
	UCG_CS(0),					/* disable chip */
	
	UCG_END()					/* end of sequence */
};

ucg_int_t ucg_my_dev_cb(ucg_t *ucg, ucg_int_t msg, void *data)
{
  switch(msg)
  {
    case UCG_MSG_DEV_POWER_UP:
      ucg_com_PowerUp(ucg, 66, 300);
      ucg->arg.pixel.pos.y = 0x05555;
      ucg_com_SendCmdSeq(ucg, my_init_sequence);
      return 1;
    case UCG_MSG_DEV_POWER_DOWN:
      return 1;
    case UCG_MSG_GET_DIMENSION:
      ((ucg_wh_t *)data)->w = 40;
      ((ucg_wh_t *)data)->h = 15;
      return 1;
    case UCG_MSG_DRAW_PIXEL:
      return 1;
    case UCG_MSG_DRAW_L90FX:
      ucg_handle_l90fx(ucg, ucg_my_dev_cb);
      return 1;
    case UCG_MSG_DRAW_L90TC:
      ucg_handle_l90tc(ucg, ucg_my_dev_cb);
      return 1;
    case UCG_MSG_DRAW_L90SE:
      ucg_handle_l90se(ucg, ucg_my_dev_cb);
      return 1;
  }
  return ucg_dev_default_cb(ucg, msg, data);  
}

int16_t ucg_my_com_cb(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data)
{
  switch(msg)
  {
    case UCG_COM_MSG_POWER_UP:
      printf("%s com_status=0x%02x arg=%lu\n", "UCG_COM_MSG_POWER_UP", ucg->com_status, (long unsigned int)arg);
      break;
    case UCG_COM_MSG_POWER_DOWN:
      break;
    case UCG_COM_MSG_DELAY:
      //printf("%s com_status=0x%02x arg=%lu\n", "UCG_COM_MSG_DELAY", ucg->com_status, (long unsigned int)arg);
      break;
    case UCG_COM_MSG_CHANGE_RESET_LINE:
      printf("%s com_status=0x%02x arg=%lu\n", "UCG_COM_MSG_CHANGE_RESET_LINE", ucg->com_status, (long unsigned int)arg);
      break;
    case UCG_COM_MSG_CHANGE_CS_LINE:
      printf("%s com_status=0x%02x arg=%lu\n", "UCG_COM_MSG_CHANGE_CS_LINE", ucg->com_status, (long unsigned int)arg);
      break;
    case UCG_COM_MSG_CHANGE_CD_LINE:
      printf("%s com_status=0x%02x arg=%lu\n", "UCG_COM_MSG_CHANGE_CD_LINE", ucg->com_status, (long unsigned int)arg);
      break;
    case UCG_COM_MSG_SEND_BYTE:
      printf("%s com_status=0x%02x arg=%lu\n", "UCG_COM_MSG_SEND_BYTE", ucg->com_status, (long unsigned int)arg);
      break;
    case UCG_COM_MSG_REPEAT_1_BYTE:
      break;
    case UCG_COM_MSG_REPEAT_2_BYTES:
      break;
    case UCG_COM_MSG_REPEAT_3_BYTES:
      break;
    case UCG_COM_MSG_SEND_STR:
      printf("%s com_status=0x%02x arg=%lu\n", "UCG_COM_MSG_SEND_STR", ucg->com_status, (long unsigned int)arg);
      break;
  }
  return 1;
}


unsigned char bitmap[2] = { 0x0f0, 0x0f0 };

int main(void)
{
  ucg_int_t i;
  
  ucg_Init(&ucg, ucg_my_dev_cb, ucg_my_com_cb);
  
  ucg_SetColor(&ucg, 0, 255, 0, 0);
 
  
  ucg_DrawBitmapLine(&ucg, 9,0, 0,16, bitmap);
  ucg_DrawBitmapLine(&ucg, 10,1, 0,16, bitmap);
  
  ucg_DrawBitmapLine(&ucg, 0,9, 1,16, bitmap);
  ucg_DrawBitmapLine(&ucg, 1,10, 1,16, bitmap);
  
  for( i = 0; i < ucg_GetWidth(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, i, 30);
  for( i = 0; i < ucg_GetHeight(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, 30, i);
 
  ucg_SetClipRange(&ucg, 10, 10, 25, 25);

  ucg_SetColor(&ucg, 0, 0, 255, 0);
  for( i = 1; i < ucg_GetWidth(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, i, 30);
  for( i = 1; i < ucg_GetHeight(&ucg); i+= 2 )  
    ucg_DrawPixel(&ucg, 30, i);

  ucg_SetColor(&ucg, 0, 80, 80, 255);

  
  ucg_DrawHLine(&ucg, 8, 9, 5);
  ucg_DrawHLine(&ucg, 8, 10, 5);
  ucg_DrawHLine(&ucg, 8, 11, 5);
  ucg_DrawHLine(&ucg, 8, 12, 100);

  ucg_DrawHLine(&ucg, 12, 13, 5);
  ucg_DrawHLine(&ucg, 12, 14, 100);

  ucg_DrawHLine(&ucg, 2, 15, 5);
  ucg_DrawHLine(&ucg, 40, 16, 5);

  ucg_DrawHRLine(&ucg, 12, 17, 1);
  ucg_DrawHRLine(&ucg, 12, 18, 2);
  ucg_DrawHRLine(&ucg, 12, 19, 3);
  ucg_DrawHRLine(&ucg, 12, 20, 4);

  ucg_DrawHRLine(&ucg, 36, 17, 1);
  ucg_DrawHRLine(&ucg, 36, 18, 2);
  ucg_DrawHRLine(&ucg, 36, 19, 3);
  ucg_DrawHRLine(&ucg, 36, 20, 4);

  ucg_DrawBitmapLine(&ucg, 9,22, 0,16, bitmap);
  ucg_DrawBitmapLine(&ucg, 10,23, 0,16, bitmap);

  ucg_SetClipRange(&ucg, 70-9, 20-9, 20, 20);

  ucg_DrawGlyph(&ucg, 70, 20, 0, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 1, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 2, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 3, 'A');


  ucg_SetMaxClipRange(&ucg);
  ucg_SetColor(&ucg, 0, 255, 0, 0);
  ucg_SetColor(&ucg, 1, 0, 255, 0);
  
  ucg_SetColor(&ucg, 0, 255, 0, 0);
  ucg_SetColor(&ucg, 1, 0, 255, 0);
  ucg_SetColor(&ucg, 2, 255, 0, 255);
  ucg_SetColor(&ucg, 3, 0, 255, 255);

  ucg_DrawGradientLine(&ucg, 10, 40, 100, 0);

  ucg_DrawGradientBox(&ucg, 10, 43, 100, 20);


  
  return 0;
}

