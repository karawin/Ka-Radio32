
#include <SPI.h>
#include "ucg.h"

ucg_t ucg;


extern const ucg_fntpgm_uint8_t ucg_font_ncenB18[8114] UCG_FONT_SECTION("ucg_font_ncenB18");

uint8_t ucg_spi_cs_pin = 10;	/* more flexible: Ucglib uses independet chip select */
uint8_t ucg_spi_cd_pin = 9;	/* command / data line */
uint8_t ucg_spi_reset_pin = 8;


int16_t ucg_com_arduino_spi(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data)
{
  switch(msg)
  {
    case UCG_COM_MSG_POWER_UP:
      /* "data" is a pointer to ucg_com_info_t structure with the following information: */
      /*	((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
      /*	((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
      
      /* setup pins */
      pinMode(13, OUTPUT);
      pinMode(11, OUTPUT);
      pinMode(ucg_spi_reset_pin, OUTPUT);
      pinMode(ucg_spi_cd_pin, OUTPUT);
      pinMode(ucg_spi_cs_pin, OUTPUT);
      
      /* setup Arduino SPI */
      SPI.begin();
      //SPI.setClockDivider( SPI_CLOCK_DIV2 );
      SPI.setDataMode( SPI_MODE0 );
      SPI.setBitOrder(MSBFIRST);
      break;
    case UCG_COM_MSG_POWER_DOWN:
      SPI.end(); 
      break;
    case UCG_COM_MSG_DELAY:
      delayMicroseconds(arg);
      break;
    case UCG_COM_MSG_CHANGE_RESET_LINE:
      digitalWrite(ucg_spi_reset_pin, arg);
      break;
    case UCG_COM_MSG_CHANGE_CS_LINE:
      digitalWrite(ucg_spi_cs_pin, arg);
      break;
    case UCG_COM_MSG_CHANGE_CD_LINE:
      digitalWrite(ucg_spi_cd_pin, arg);
      break;
    case UCG_COM_MSG_SEND_BYTE:
      SPI.transfer(arg); 
      break;
    case UCG_COM_MSG_REPEAT_1_BYTE:
      while( arg > 0 ) {
	SPI.transfer(data[0]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_2_BYTES:
      while( arg > 0 ) {
	SPI.transfer(data[0]);
	SPI.transfer(data[1]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_3_BYTES:
      while( arg > 0 ) {
	SPI.transfer(data[0]);
	SPI.transfer(data[1]);
	SPI.transfer(data[2]);
	arg--;
      }
      break;
    case UCG_COM_MSG_SEND_STR:
      while( arg > 0 ) {
	SPI.transfer(*data++);
	arg--;
      }
      break;
  }
  return 1;
}

uint8_t ucg_port_d_cd_pin = 19;	/* command / data line */
uint8_t ucg_port_d_wr_pin = 18;	/* write enable */
uint8_t ucg_port_d_cs_pin = 17;	/* chip select */
uint8_t ucg_port_d_reset_pin = 16;

static void ucg_com_arduino_port_d_send(uint8_t data)
{
  PORTD = data;
  digitalWrite(ucg_port_d_wr_pin, 0);
  digitalWrite(ucg_port_d_wr_pin, 1);
}

int16_t ucg_com_arduino_port_d(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data)
{
  switch(msg)
  {
    case UCG_COM_MSG_POWER_UP:
      /* "data" is a pointer to ucg_com_info_t structure with the following information: */
      /*	((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
      /*	((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
      
      /* setup pins */
      pinMode(13, OUTPUT);
      pinMode(11, OUTPUT);
      pinMode(ucg_port_d_cd_pin, OUTPUT);
      pinMode(ucg_port_d_wr_pin, OUTPUT);
      pinMode(ucg_port_d_cs_pin, OUTPUT);
      pinMode(ucg_port_d_reset_pin, OUTPUT);

      pinMode(0, OUTPUT);
      pinMode(1, OUTPUT);
      pinMode(2, OUTPUT);
      pinMode(3, OUTPUT);
      pinMode(4, OUTPUT);
      pinMode(5, OUTPUT);
      pinMode(6, OUTPUT);
      pinMode(7, OUTPUT);

      digitalWrite(ucg_port_d_cd_pin, 1);
      digitalWrite(ucg_port_d_wr_pin, 1);
      digitalWrite(ucg_port_d_cs_pin, 1);
      digitalWrite(ucg_port_d_reset_pin, 1);

      break;
    case UCG_COM_MSG_POWER_DOWN:
      break;
    case UCG_COM_MSG_DELAY:
      delayMicroseconds(arg);
      break;
    case UCG_COM_MSG_CHANGE_RESET_LINE:
      digitalWrite(ucg_port_d_reset_pin, arg);
      break;
    case UCG_COM_MSG_CHANGE_CS_LINE:
      digitalWrite(ucg_port_d_cs_pin, arg);
      break;
    case UCG_COM_MSG_CHANGE_CD_LINE:
      digitalWrite(ucg_port_d_cd_pin, arg);
      break;
    case UCG_COM_MSG_SEND_BYTE:
      ucg_com_arduino_port_d_send(arg);
      break;
    case UCG_COM_MSG_REPEAT_1_BYTE:
      while( arg > 0 ) {
	ucg_com_arduino_port_d_send(data[0]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_2_BYTES:
      while( arg > 0 ) {
	ucg_com_arduino_port_d_send(data[0]);
	ucg_com_arduino_port_d_send(data[1]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_3_BYTES:
      while( arg > 0 ) {
	ucg_com_arduino_port_d_send(data[0]);
	ucg_com_arduino_port_d_send(data[1]);
	ucg_com_arduino_port_d_send(data[2]);
	arg--;
      }
      break;
    case UCG_COM_MSG_SEND_STR:
      while( arg > 0 ) {
	ucg_com_arduino_port_d_send(*data++);
	arg--;
      }
      break;
  }
  return 1;
}


void xsetup(void)
{
  ucg_Init(&ucg, ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, ucg_com_arduino_spi);
}

void setup(void)
{
  delay(1000);
  ucg_Init(&ucg, ucg_dev_ili9325_18x240x320_itdb02, ucg_ext_ili9325_18, ucg_com_arduino_port_d);
  delay(50);
}

uint8_t r,g,b;
void loop(void)
{
  ucg_SetColor(&ucg, 0, 255, 0, 0);
  ucg_DrawHLine(&ucg, 0, 0, 20);
  ucg_DrawHLine(&ucg, 0, 1, 20);
  ucg_DrawHLine(&ucg, 0, 2, 20);
  ucg_DrawHLine(&ucg, 0, 3, 20);
  ucg_SetColor(&ucg, 0, 0, 255, 0);
  ucg_DrawHLine(&ucg, 0, 4, 20);
  ucg_DrawHLine(&ucg, 0, 5, 20);
  ucg_DrawHLine(&ucg, 0, 6, 20);
  ucg_DrawHLine(&ucg, 0, 7, 20);


  ucg_SetColor(&ucg, 0, 255, g, 0);
  ucg_SetColor(&ucg, 1, r, 255, b);
  ucg_SetColor(&ucg, 2, 255, 0, 255);
  ucg_SetColor(&ucg, 3, 0, 255, 255);

  r +=3;
  g+=7;
  b += 11;

  ucg_DrawGradientBox(&ucg, 10, 43, 100, 20);
  
  if ( (r&1) == 0 )
    ucg_SetColor(&ucg, 0, 0, 0, 0);
  else
    ucg_SetColor(&ucg, 0, r,g,b);
  ucg.arg.pixel.rgb.color[0] = ucg.arg.rgb[0].color[0];
  ucg.arg.pixel.rgb.color[1] = ucg.arg.rgb[0].color[1];
  ucg.arg.pixel.rgb.color[2] = ucg.arg.rgb[0].color[2];
  ucg.arg.pixel.pos.x = 60;
  ucg.arg.pixel.pos.y = 90;
  ucg.arg.len = 30;
  ucg.arg.dir = 0;
  ucg_DrawL90FXWithArg(&ucg);
  ucg.arg.pixel.rgb.color[0] = ucg.arg.rgb[0].color[0];
  ucg.arg.pixel.rgb.color[1] = ucg.arg.rgb[0].color[1];
  ucg.arg.pixel.rgb.color[2] = ucg.arg.rgb[0].color[2];
  ucg.arg.pixel.pos.x = 60;
  ucg.arg.pixel.pos.y = 90;
  ucg.arg.len = 30;
  ucg.arg.dir = 1;
  ucg_DrawL90FXWithArg(&ucg);
  ucg.arg.pixel.rgb.color[0] = ucg.arg.rgb[0].color[0];
  ucg.arg.pixel.rgb.color[1] = ucg.arg.rgb[0].color[1];
  ucg.arg.pixel.rgb.color[2] = ucg.arg.rgb[0].color[2];
  ucg.arg.pixel.pos.x = 60;
  ucg.arg.pixel.pos.y = 90;
  ucg.arg.len = 30;
  ucg.arg.dir = 2;
  ucg_DrawL90FXWithArg(&ucg);
  ucg.arg.pixel.rgb.color[0] = ucg.arg.rgb[0].color[0];
  ucg.arg.pixel.rgb.color[1] = ucg.arg.rgb[0].color[1];
  ucg.arg.pixel.rgb.color[2] = ucg.arg.rgb[0].color[2];
  ucg.arg.pixel.pos.x = 60;
  ucg.arg.pixel.pos.y = 90;
  ucg.arg.len = 30;
  ucg.arg.dir = 3;
  ucg_DrawL90FXWithArg(&ucg);

  ucg_SetFont(&ucg, ucg_font_10x20r);
  ucg_SetColor(&ucg, 0, 255, 255, b);
  //ucg_SetFontPosBottom(&ucg);  
  ucg_DrawGlyph(&ucg, 70, 20, 0, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 1, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 2, 'A');
  ucg_DrawGlyph(&ucg, 70, 20, 3, 'A');


  delay(50);
  
}

